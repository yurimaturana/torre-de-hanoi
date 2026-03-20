#include <stdio.h>

int discos;
int pinos[3][100];
int topo[3];
int movimentos = 0;

void desenhar(int de, int para, int disco_movido, int fim)
{
	printf("\e[1;1H\e[2J");
	printf("Torre de Hanoi - %d discos - %d movimentos restantes\n\n", discos, (1 << discos) - 1 - movimentos);

	for (int i = discos - 1; i >= 0; i--)
	{
		for (int p = 0; p < 3; p++)
			if (i < topo[p])
				printf(" %d ", pinos[p][i]);
			else
				printf(" | ");

		printf("\n");
	}
	printf("-+--+--+-\n");
	printf(" A  B  C \n\n");

	if (fim)
		printf("SITUACAO FINAL: Resolvido!\n");
	else if (de != 0)
		printf("MOVIMENTO REALIZADO: Disco %d saiu de %c para %c\n", disco_movido, de + 64, para + 64);

	if (!fim)
	{
		printf("Pressione [Enter] para o proximo passo...");
		getchar();
	}
}

void moverDisco(int origem, int destino)
{
	int o = origem - 1;
	int d = destino - 1;

	int disco_movido = pinos[o][topo[o] - 1];

	topo[o]--;
	pinos[d][topo[d]] = disco_movido;
	topo[d]++;

	movimentos++;

	desenhar(origem, destino, disco_movido, 0);
}

void moverTorre(int n, int origem, int destino, int auxiliar)
{
	if (n == 1)
	{
		moverDisco(origem, destino);
		return;
	}

	moverTorre(n - 1, origem, auxiliar, destino);
	moverDisco(origem, destino);
	moverTorre(n - 1, auxiliar, destino, origem);
}

int main()
{
	do
	{
		printf("\e[1;1H\e[2J");
		printf("Digite a quantidade de discos (1-10): ");
		scanf("%d", &discos);
	} while (discos <= 0 || discos > 10);

	getchar();

	topo[0] = discos;
	topo[1] = 0;
	topo[2] = 0;

	for (int i = 0; i < discos; i++)
		pinos[0][i] = discos - i;

	desenhar(0, 0, 0, 0);

	moverTorre(discos, 1, 3, 2);

	desenhar(0, 0, 0, 1);

	return 0;
}
