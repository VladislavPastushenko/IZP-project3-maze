all:
	gcc -std=c99 -Wall -Wextra -Werror proj3.c -o proj3
clean:
	rm proj3
test:
	./proj3 --lpath 6 1 bludiste.txt