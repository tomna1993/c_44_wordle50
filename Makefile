CC := gcc
#CFLAGS := 
DEST := ./build/

substitution: wordle50.c
	$(CC) wordle50.c -lcs50 -o $(DEST)/wordle50 