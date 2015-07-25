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

void crypt(char* input, char* output);
void decrypt(char* input, char* output);
