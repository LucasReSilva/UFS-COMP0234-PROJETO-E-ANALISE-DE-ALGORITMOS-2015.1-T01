#include <stdio.h>
#include <math.h>
#include <string.h>

// Declaração de constantes
const long M = 1103515245;
const long D = 12345;
unsigned long key;

unsigned long G(unsigned long k)
{
	static unsigned long int j = 0;
	if (j == 0)
	{
		key = M * key + D;
	}
	unsigned long z = (key >> j) & 0xFF;
	j = (j + 8) % 32;
	return z;
}

unsigned long meuMod(unsigned long b, unsigned long ex, unsigned long mod)
{
	if (mod == 1)
	{
		return 0;
	}
	//printf("meuMODULO %lu %lu %lu\n", b,ex, mod);
	unsigned long resto = 1;
	unsigned long exCount;
	for (exCount = 0; exCount < ex; exCount++)
	{
		resto = (resto * b) % mod;
	}
	return resto;
}

int main(int argc, char **argv)
{

	// Declaracao de variaveis
	FILE *entrada, *saida;
	unsigned long a, b, p, g, A, B, S, numeroMensagens, mCount;
	char La, Lb, letra, DH[2];

	// Argumentos
	//printf("------------------------ Criptografia ------------------------------------------\n");
	//printf("N DE ARGUMENTOS: %i\n",(argc-1));
	//printf("ENTRADA: %s\n",argv[1]);
	//printf("SAIDA: %s\n",argv[2]);
	//printf("M: %i D: %i\n",M,D);
	//printf("--------------------------------------------------------------------------------\n\n");

	// Arquivo de entrada
	entrada = fopen(argv[1], "r");

	// Arquivo de saida
	saida = fopen(argv[2], "w");

	// Le irformacao base
	//printf("--------------------------------------------------------------------------------\n");
	fscanf(entrada, "%c", &La);
	fscanf(entrada, "%lu", &a);
	fscanf(entrada, " %c", &Lb);
	fscanf(entrada, "%lu", &b);
	fscanf(entrada, "%s", &DH);
	fscanf(entrada, "%lu", &p);
	fscanf(entrada, "%lu", &g);
	fscanf(entrada, "%lu", &numeroMensagens);
	//printf("%c %lu\n", La,a);
	//printf("%c %lu\n", Lb,b);
	//printf("%s %lu %lu\n", DH,p,g);
	//printf("NUMERO DE MENSAGENS: %i\n", numeroMensagens);

	// DAQUI PRA CIMA OK

	//A = 332073;
	//B = 516492;
	//A = 25;
	//B = 84;

	A = meuMod(g, a, p);
	B = meuMod(g, b, p);

	fprintf(saida, "A->B: %lu\n", A);
	fprintf(saida, "B->A: %lu\n", B);
	//printf("%c->%c\: %lu\n", La,Lb,A);
	//printf("%c->%c\: %lu\n", La,Lb,B);

	//S = 482324;
	//S = 87;

	S = meuMod(A, b, p);

	//printf("S: %lu\n", S);
	//printf("--------------------------------------------------------------------------------\n\n");

	// DAQUI PRA BAIXO OK

	key = S;
	// le  as msg
	mCount = 0;
	for (mCount = 0; mCount < numeroMensagens; mCount++)
	{

		char mensagem[1000];

		fscanf(entrada, "%s", &mensagem);
		("MENSAGEM 1: %i\n", mensagem[0]);

		if ((int)fmod((double)mCount, (double)2) == 0)
		{
			////printf("A->B: %s\n", mensagem);
			fprintf(saida, "A->B:");
		}
		else
		{
			////printf("B->A: %s\n", mensagem);
			fprintf(saida, "B->A:");
		}

		int tamanhoMensagem = strlen(mensagem);
		////printf("TAMANHO DA MENSAGEN: %i\n",tamanhoMensagem);
		int lCont = 0;
		for (lCont = 0; lCont < tamanhoMensagem; lCont++)
		{
			//printf(" %i", mensagem[lCont]);
			fprintf(saida, " %lu", mensagem[lCont] ^ G(S));
		}

		// quebra de linha
		//printf("\n");
		fprintf(saida, "\n");
	}

	// Fecha Arquivos
	fclose(entrada);
	fclose(saida);

	//printf("%c %i\n", La,a);
	//printf("%c %i\n", Lb,b);
	//printf("%s %i %i\n", DH,p,g);
	//printf("NUMERO DE MENSAGENS: %i\n", numeroMensagens);
	//printf("S: %lu\n", S);

	return 0;
}