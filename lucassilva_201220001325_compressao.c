#include <stdio.h>

// Funcao de comparassao
int comp(float val1, float val2)
{

	if (val1 > val2)
	{
		return 1;
	}
	else
	{
		if (val1 < val2)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
}

// Funcao comparacao das traxas de compressao
float tcompressao(float toriginal, float tcomprimido)
{
	return roundf((tcomprimido / toriginal) * 100) / 100;
}

//  8bits Run-Length Encoding
void rle(char cadeia[])
{
}

// Huffman
void huf()
{
}

int main(int argc, char **argv)
{
	// Declaracao de constantes
	const int TMAX = 1000;

	// Declaracao de variaveis
	FILE *entrada, *saida;
	int qsequencia, nsequencia, cont1, cont2;

	// Argumentos
	printf("--------------------------------------------------------------------------------\n");
	printf("N DE ARGUMENTOS: %i\n", argc);
	printf("ENTRADA: %s\n", argv[1]);
	printf("SAIDA: %s\n", argv[2]);
	printf("--------------------------------------------------------------------------------\n\n");

	// Arquivo de entrada

	char fatia[TMAX];
	entrada = fopen(argv[1], "r");

	// Arquivo de saida
	saida = fopen(argv[2], "w");
	//fprintf(saida, "This is testing for fprintf...\n");

	// Le irformacao base
	printf("--------------------------------------------------------------------------------\n");
	fscanf(entrada, "%i", &qsequencia);
	printf("QUANTIDADE DE SEQUENCIAS: %i\n", qsequencia);
	printf("--------------------------------------------------------------------------------\n\n");

	for (cont1 = 0; cont1 < qsequencia; cont1++)
	{
		printf("--------------------------------------------------------------------------------\n");
		fscanf(entrada, "%i", &nsequencia);
		printf("SEQUENCIA: %i\n", cont1);
		printf("N DE ELEMENTOS: %i\n", nsequencia);
		for (cont2 = 0; cont2 < nsequencia; cont2++)
		{
			fscanf(entrada, "%s", fatia);
			printf("%s\n", fatia);
		}
		printf("--------------------------------------------------------------------------------\n\n");
	}

	printf("Taxa: %f", tcompressao(9, 5));

	// Fecha arquivos
	fclose(entrada);
	fclose(saida);
	return 0;
}
