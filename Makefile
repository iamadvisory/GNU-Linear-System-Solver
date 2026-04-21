CC = clang
CFLAGS = -O3 -Wall -Wextra
TARGET = glsq
SRC = src/main.c
PREFIX = /usr/local

WIN_CC = x86_64-w64-mingw32-gcc
WIN_TARGET = glsq.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm
	@echo "Build $(TARGET) complited."

windows:
	$(WIN_CC) $(CFLAGS) $(SRC) -o $(WIN_TARGET)
	@echo "Build $(WIN_TARGET) complited."

install: all
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin
	@echo "Program installed to the $(PREFIX)/bin"

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
	@echo "Program deleted."

clean:
	rm -f $(TARGET) $(WIN_TARGET)
	@echo "Cleaning complited."

.PHONY: all windows install uninstall clean
