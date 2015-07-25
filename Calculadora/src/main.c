#include <stdio.h>
#include "calc.h"

int main()
{
	int operacao_invalida = 0;
	int numero1, numero2, operacao;

	printf("Digite o primeiro numero: ");
	scanf("%d", &numero1);
	printf("Digite o segundo numero: ");
	scanf("%d", &numero2);
	do
	{
		printf("\nDigite a operacao desejada:\n1. Soma\n2. Subtracao\n3. Multiplicacao\n4. Divisao\n");
		scanf("%d", &operacao);
		switch(operacao)
		{
			case 1: printf("Soma: %d\n", soma(numero1, numero2));
					operacao_invalida = 0;
					break;
			case 2: printf("Subtracao: %d\n", subtracao(numero1, numero2));
					operacao_invalida = 0;
					break;
			case 3: printf("Multiplicacao: %d\n", multiplicacao(numero1, numero2));
					operacao_invalida = 0;
					break;
			case 4: printf("Divisao: %d\n", divisao(numero1, numero2));
					operacao_invalida = 0;
					break;
			default: operacao_invalida = 1;
					 printf("Erro: Operacao nao disponivel. Tente novamente!\n");
		}
	} while(operacao_invalida);
}
