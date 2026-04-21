# glsq (GNU Linear System Quick) v0.4

A lightweight C utility to solve 2x2 systems of linear equations with high-precision visualization using gnuplot.

## Features
- **Accurate:** Uses Cramer's rule with `double` precision and `EPS` thresholding.
- **Visual:** High-quality plots with infinite lines and intersection markers.
- **Robust:** Handles vertical lines, parallel lines, and overlapping equations.
- **Multilingual:** Supports English (default) and Russian.

## Requirements
- **Compiler:** `clang` or `gcc`
- **Gnuplot:** Must be installed and added to your system PATH.

## Installation (Linux/macOS)
```bash
make
sudo make install
```
## Usage
Run with default English locale:
```bash
glsq
```
Run with Russian locale:
```bash
glsq --ru
```
## Windows Build
To compile for Windows using MinGW:
```bash
x86_64-w64-mingw32-gcc -O3 src/main.c -o glsq.exe
```
