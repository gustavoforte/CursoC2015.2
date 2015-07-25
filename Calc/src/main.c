#include <stdio.h>
#include "calc.h"

int main()
{
	printf("Hello World! %d\n", soma(21, 21));
	printf("Soma: %d\n", soma(3, 7));
	printf("Subtracao: %d\n", subtracao(3, 7));
	printf("Multiplicacao: %d\n", multiplicacao(3, 7));
	printf("Divisao: %d\n", divisao(10, 10));
}

int soma(int a, int b)
{
	return(a+b);
}

int subtracao(int a, int b)
{
	return(a-b);
}

int multiplicacao(int a, int b)
{
	return(a*b);
}

int divisao(int a, int b)
{
	return(b == 0 ? 0 : a/b);
}
