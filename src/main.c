#include <stdio.h>
#include <math.h>
#include <string.h>

#define EPS 1e-9

typedef struct {
    const char *title;
    const char *input_eq1;
    const char *input_eq2;
    const char *res_label;
    const char *sol_label;
    const char *no_sol;
    const char *inf_sol;
    const char *err_gnuplot;
} Lang;

Lang en = {
    "SLAU Solution", "Enter coeffs (a b c) for Eq 1: ", "Enter coeffs (a b c) for Eq 2: ",
    "Result", "Solution", "The system has no solutions.", "Infinite solutions.", "Error: gnuplot not found!"
};

Lang ru = {
    "Решение СЛАУ", "Введите коэф. (a b c) для уравнения 1: ", "Введите коэф. (a b c) для уравнения 2: ",
    "Результат", "Решение", "Система не имеет решений.", "Бесконечно много решений.", "Ошибка: gnuplot не найден!"
};

void draw_graph(Lang *L, double a1, double b1, double c, double a2, double b2, double d, double x_sol, double y_sol) {
    #ifdef _WIN32
        FILE *pipe = _popen("gnuplot -persistent", "w");
    #else
        FILE *pipe = popen("gnuplot -persistent", "w");
    #endif

    if (pipe == NULL) {
        fprintf(stderr, "%s\n", L->err_gnuplot);
        return;
    }

    fprintf(pipe, "set title '%s: x = %.2f, y = %.2f'\n", L->title, x_sol, y_sol);
    fprintf(pipe, "set grid\n");
    fprintf(pipe, "set xzeroaxis lt -1\n");
    fprintf(pipe, "set yzeroaxis lt -1\n");

    fprintf(pipe, "set xr [%.2f - 5 : %.2f + 5]\n", x_sol, x_sol);
    fprintf(pipe, "set yr [%.2f - 5 : %.2f + 5]\n", y_sol, y_sol);
    fprintf(pipe, "set clip two\n");
    fprintf(pipe, "set samples 1000\n");

    if (fabs(b1) < EPS)
        fprintf(pipe, "set arrow from %.2f, graph 0 to %.2f, graph 1 nohead lc rgb 'blue' lw 2\n", c/a1, c/a1);
    if (fabs(b2) < EPS)
        fprintf(pipe, "set arrow from %.2f, graph 0 to %.2f, graph 1 nohead lc rgb 'green' lw 2\n", d/a2, d/a2);

    fprintf(pipe, "plot [x=%.2f:%.2f] ", x_sol-20, x_sol+20);

    if (fabs(b1) >= EPS)
        fprintf(pipe, "(%.15g - %.15g*x) / %.15g title 'L1' lw 2 lc rgb 'blue', ", c, a1, b1);
    else
        fprintf(pipe, "keyentry with lines lc rgb 'blue' lw 2 title 'L1 (x=%.2f)', ", c/a1);

    if (fabs(b2) >= EPS)
        fprintf(pipe, "(%.15g - %.15g*x) / %.15g title 'L2' lw 2 lc rgb 'green', ", d, a2, b2);
    else
        fprintf(pipe, "keyentry with lines lc rgb 'green' lw 2 title 'L2 (x=%.2f)', ", d/a2);

    fprintf(pipe, "'-' with points pt 7 ps 2 lc rgb 'red' title '%s'\n", L->sol_label);
    fprintf(pipe, "%.15g %.15g\ne\n", x_sol, y_sol);

    fflush(pipe);
    #ifdef _WIN32
        _pclose(pipe);
    #else
        pclose(pipe);
    #endif
}

int main(int argc, char *argv[]) {
    Lang *L = &en;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ru") == 0 || strcmp(argv[i], "-r") == 0) {
            L = &ru;
        }
    }

    printf("╭─────────────────────────────────╮\n");
    printf("│   glsq v0.4 | by iam-advisory   │\n");
    printf("│   GNU Linear System Solver      │\n");
    printf("╰─────────────────────────────────╯\n\n");

    double a1, b1, c, a2, b2, d;

    printf("%s", L->input_eq1);
    if (scanf("%lf %lf %lf", &a1, &b1, &c) != 3) return 1;

    printf("%s", L->input_eq2);
    if (scanf("%lf %lf %lf", &a2, &b2, &d) != 3) return 1;

    double det = a1 * b2 - a2 * b1;

    if (fabs(det) > EPS) {
        double x = (c * b2 - d * b1) / det;
        double y = (a1 * d - a2 * c) / det;

        printf("\n%s: x = %.4f, y = %.4f\n", L->res_label, x, y);
        draw_graph(L, a1, b1, c, a2, b2, d, x, y);
    } else {
        double detX = c * b2 - d * b1;
        if (fabs(detX) < EPS)
            printf("\n%s\n", L->inf_sol);
        else
            printf("\n%s\n", L->no_sol);
    }

    return 0;
}
