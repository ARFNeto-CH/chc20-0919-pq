
#include "ch0918pq.h"

int		testaConsulta(FILADEPRIORIDADE*);
int		testaCriaUns(FILADEPRIORIDADE*);
int		testaMudaPrioridade(FILADEPRIORIDADE*);
int		testaRemoveTodos(FILADEPRIORIDADE*);

int main(void)
{
	srand(200920);
	int res = 0;
	FILADEPRIORIDADE* pq = NULL;
	exibirLog(pq);
	pq = criarFila(30);
	// cria
	testaCriaUns(pq);
	exibirLog(pq);

	// atende todos
	testaRemoveTodos(pq);

	// agora cria tudo de novo: deve reaproveitar os enderecos
	printf("\n\n\t==> Reocupando todos os lugares\n");
	testaCriaUns(pq);
	exibirLog(pq);

	testaConsulta(pq);
	testaMudaPrioridade(pq);
	return 0;
};	//	main()

int		testaConsulta(FILADEPRIORIDADE* F)
{
	int		res = 0;
	float	pri = 0;
	printf("\n\n\t==>Consulta todas as prioridades\n\n\n");
	for (int id = 0; id < 30; id += 1)
	{
		printf("consultarPrioridade(%d): ", id);
		res = consultarPrioridade(F, id, &pri);
		if (res)
			printf("P = %6.2f\n", pri);
		else
			printf("Erro\n");
	};	// if()
	exibirLog(F);
		return 0;
};

int		testaCriaUns(FILADEPRIORIDADE* pq)
{
	printf("\n\n\t==> Criando alguns registros\n\n\n");

	for (int id = 0; id < 30; id += 3)
	{
		int res = inserirElemento(pq, id, (float)(rand() % 2000) / 100.f);
		if (res < 0)
		{
			printf("Erro ao inserir %d\n", id);
			return 0;
		};
	};	// if()
	return 0;
};	// testaCriaUns()

int		testaMudaPrioridade(FILADEPRIORIDADE* f)
{
	printf("\n\n\t==> Teste:\n\
\t\tsoma 1 em todas as prioridades para ID pares\n\
\t\te diminui 1 em todas as impares\n\n\n");

	// mostra antes
	exibirLog(f);

	int ix = tamanho(f);
	ELEMENTO* p = f->fila->prox; // primeiro 
	while (ix > 0)
	{
		if (p->id % 2 == 0)
			aumentarPrioridade(f, p->id, (float)(p->prioridade + 1.0f));
		else
			reduzirPrioridade(f, p->id, (float)(p->prioridade - 1.0f));

		p = p->prox;
		ix -= 1;
	};	// while()

	// mostra depois
	exibirLog(f);

	return 0;
};	// testaMudaPrioridade()

int		testaRemoveTodos(FILADEPRIORIDADE* pq)
{
	// agora remove todos

	printf("\n\n\t==> Atendendo todo mundo: fila vai ficar vazia\n\n\n");
	
	// mostra antes
	exibirLog(pq);

	ELEMENTO* adeus = NULL;
	while (tamanho(pq) > 0)
	{
		adeus = removerElemento(pq);
		if (adeus != NULL)
		{
			printf("Removido elemento com endereco %p\n", adeus);
		}
		else
		{
			printf("Nao removeu elemento (%d,%6.2f)\n",
				pq->fila->prox->id, pq->fila->prox->prioridade);
		};	// if()
	};

	// mostra depois
	exibirLog(pq);

	return 0;
};	// testaRemoveTodos()
