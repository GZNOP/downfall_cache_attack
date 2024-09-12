CC=gcc
CFLAGS=-Wall -Wextra
LIB_PATH=./

.PHONY : all exportlpath clean

all: libbibfr.so spy.out victim.out exportlpath

libbibfr.so: bib.c
	$(CC) $(CFLAGS) --shared -fpic $^ -o $@

spy.out: fr.c bib.h
	$(CC) $(CFLAGS) -L$(LIB_PATH) $< -o $@ -lbibfr

victim.out: victim.c bib.h
	$(CC) $(CFLAGS) -L$(LIB_PATH) $< -o $@ -lbibfr

exportlpath:
	@echo 'execute the command: export LD_LIBRARY_PATH="./"'
clean:
	rm *.so *.out
