#include <stdio.h>
#include <string.h>
#include <math.h>

struct resposta
{
	char doenca[25];
	float probabilidade;
};

// ----------- Percentual ----------------
float percentual(float acertos, float total)
{
	return (roundf((acertos / total) * 100));
}

//------------ Merge Sort -----------------
void mergeSort(struct resposta *vetorResposta, int posicaoInicial, int posicaoFinal)
{
	int i, j, k, metadeTamanho;
	struct resposta *vetorTemp;
	if (posicaoInicial == posicaoFinal)
		return;

	// ordenacao recursiva das duas metades
	metadeTamanho = (posicaoInicial + posicaoFinal) / 2;
	mergeSort(vetorResposta, posicaoInicial, metadeTamanho);
	mergeSort(vetorResposta, metadeTamanho + 1, posicaoFinal);

	// intercalacao no vetor temporario t
	i = posicaoInicial;
	j = metadeTamanho + 1;
	k = 0;
	vetorTemp = (struct resposta *)malloc(sizeof(struct resposta) * (posicaoFinal - posicaoInicial + 1));

	while (i < metadeTamanho + 1 || j < posicaoFinal + 1)
	{
		if (i == metadeTamanho + 1)
		{ // i passou do final da primeira metade, pegar v[j]
			vetorTemp[k] = vetorResposta[j];
			j++;
			k++;
		}
		else
		{
			if (j == posicaoFinal + 1)
			{
				// j passou do final da segunda metade, pegar v[i]
				vetorTemp[k] = vetorResposta[i];
				i++;
				k++;
			}
			else
			{
				if (vetorResposta[i].probabilidade >= vetorResposta[j].probabilidade)
				{
					vetorTemp[k] = vetorResposta[i];
					i++;
					k++;
				}
				else
				{
					vetorTemp[k] = vetorResposta[j];
					j++;
					k++;
				}
			}
		}
	}
	// copia vetor intercalado para o vetor original
	for (i = posicaoInicial; i <= posicaoFinal; i++)
	{
		vetorResposta[i] = vetorTemp[i - posicaoInicial];
	}
	free(vetorTemp);
}

// ----------- Inicializar ------------
void inicializar(int tab[], int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
	{
		tab[i] = -1;
	}
}

// Calcula tabela
void calcular_tabela(int tab[], char P[])
{
	unsigned int i, m = strlen(P);
	int j = -1;
	inicializar(tab, m);
	for (i = 1; i < m; i++)
	{
		while (j >= 0 && P[j + 1] != P[i])
			j = tab[j];
		if (P[j + 1] == P[i])
			j++;
		tab[i] = j;
	}
}

// KMP
//int kmp(int tab[], char T[], char P[], int subCad) {
//	unsigned int i, n = strlen(T);
//	unsigned int m = strlen(P);
//	int j = -1, seq=0, acertosValidos=0;
//	calcular_tabela(tab, P);
//	for(i = 0; i < n; i++) {
//
//		if (seq >= subCad){
//
//			acertosValidos += seq;
//			printf("          AV: %i\n",seq);
//			printf("          seq: %i\n",seq);
//
//			char strTemp[m - seq];
//
//			printf("          m-seq: %i\n",m-seq);
//
//
//			strncpy(strTemp, P+seq, m-seq);
//
//			printf("          strTemp: %s\n",strTemp);
//
//			if (seq == m) break;
//
//			strcpy(P,strTemp);
//			printf("          P: %s\n",strTemp);
//
//			calcular_tabela(tab, P);
//			m = m - seq;
//
//			seq = 0;
//			j=-1;
//
//
//
//		}
//
//		while(j >= 0 && P[j + 1] != T[i]) {
//			j = tab[j];
//			seq=0;
//		}
//
//		if(P[j + 1] == T[i]){
//			j++;
//			seq++;
//		}
//
//		if(j == m - 1) {
//			j = tab[j];
//			seq=0;
//		}
//	}
//	printf("     Acertos Validos: %i\n",acertosValidos);
//	return acertosValidos;
//}

int kmp(int tab[], char T[], char P[], int tSubCad)
{
	unsigned int i, n = strlen(T);
	unsigned int m = strlen(P);
	int j = -1, totalAcertos = 0, seq = 0;
	calcular_tabela(tab, P);
	for (i = 0; i < n; i++)
	{

		if (seq >= tSubCad)
		{
			break;
		}

		while (j >= 0 && P[j + 1] != T[i])
		{
			totalAcertos += seq;
			seq++;
			j = tab[j];
			seq = 0;
		}

		if (P[j + 1] == T[i])
		{
			j++;
			seq++;
			printf("          seq parcial: %i\n", seq);
		}

		if (j == m - 1)
		{
			j = tab[j];
			totalAcertos += seq;
			break;
		}
	}
	printf("          totalAcertos: %i\n", totalAcertos);
	return totalAcertos;
}

// MAIN
int main(int argc, char **argv)
{
	// Declaracao de constantes
	const int TMAXCADEIA = 1000;

	// Declaracao de variaveis
	FILE *entrada, *saida;
	int tamanhoSubcadeia, numeroDoencas, numeroGenes, contGenes, contDoencas, posicaoDna, geneAcertos, genesEncontrados;
	char cdna[100000];

	// Argumentos
	printf("--------------------------------------------------------------------------------\n");
	printf("N DE ARGUMENTOS: %i\n", (argc - 1));
	printf("ENTRADA: %s\n", argv[1]);
	printf("SAIDA: %s\n", argv[2]);
	printf("--------------------------------------------------------------------------------\n\n");

	// Arquivo de entrada
	char fatia[TMAXCADEIA];
	entrada = fopen(argv[1], "r");

	// Arquivo de saida
	saida = fopen(argv[2], "w");

	// Le irformacao base
	printf("--------------------------------------------------------------------------------\n");
	fscanf(entrada, "%i", &tamanhoSubcadeia); // tamanho minimo da cadeia
	printf("TAMANHO DA CADEIA: %i\n", tamanhoSubcadeia);

	fscanf(entrada, "%s", &cdna); // cadeia de dna
	printf("CADEIA: %s\n", cdna);

	fscanf(entrada, "%i", &numeroDoencas); // numero de doencas
	printf("NUMERO DE DOENCAS: %i\n", numeroDoencas);
	printf("--------------------------------------------------------------------------------\n\n");

	// Estrutura de resposta
	struct resposta resp[numeroDoencas];

	// Le doencas e genes
	for (contDoencas = 0; contDoencas < numeroDoencas; contDoencas++)
	{
		printf("--------------------------------------------------------------------------------\n");

		fscanf(entrada, "%s", &resp[contDoencas].doenca);
		printf("DOENCA: %s\n", resp[contDoencas].doenca);

		fscanf(entrada, "%i", &numeroGenes);
		printf("NUMERO de GENES: %i\n", numeroGenes);

		genesEncontrados = 0;

		for (contGenes = 0; contGenes < numeroGenes; contGenes++)
		{
			fscanf(entrada, "%s", fatia);
			int tFatia = strlen(fatia);
			printf("GENE %i: %s %i simbolos \n", contGenes, fatia, tFatia);

			posicaoDna = 0;
			geneAcertos = 0;
			int tab[tFatia];

			// Roda KMP
			geneAcertos = kmp(tab, cdna, fatia, tamanhoSubcadeia);

			if ((geneAcertos / tFatia) >= 0.9)
				genesEncontrados++;
		}
		printf("Acertos: %i\n", genesEncontrados);

		float perc = 0;
		perc = percentual((float)genesEncontrados, (float)numeroGenes);
		printf("Probabilidade: %f\n", perc);
		resp[contDoencas].probabilidade = perc;

		printf("--------------------------------------------------------------------------------\n\n");
	}

	int contt;

	// Ordena doencas
	mergeSort(resp, 0, numeroDoencas - 1);

	// Imprime no arquivo de saida
	for (contt = 0; contt < numeroDoencas; contt++)
	{
		fprintf(saida, "%s: %.0f%% \n", resp[contt].doenca, roundf(resp[contt].probabilidade));
	}

	// Fecha Arquivos
	fclose(entrada);
	fclose(saida);

	return 0;
}