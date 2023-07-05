#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *var = getenv("$?");
	printf("la valeur de SHELL est %s\n", var );
}
