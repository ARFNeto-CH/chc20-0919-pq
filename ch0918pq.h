#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define		_MAX_ELEMENTOS_ 1000

typedef int bool;

typedef struct aux
{
	int			id;
	float		prioridade;
	struct aux* ant;
	struct aux* prox;

} ELEMENTO, * PONT;


typedef struct
{
	int			maxElementos;
	PONT    	fila;
	PONT*		arranjo;

} FILADEPRIORIDADE, * PFILA;

// as funcoes

bool		aumentarPrioridade(PFILA,int,float);
bool		consultarPrioridade(PFILA,int,float*);
PFILA		criarFila(int);
bool		inserirElemento(PFILA,int,float);
bool		reduzirPrioridade(PFILA,int,float);
PONT		removerElemento(PFILA);
int			tamanho(PFILA);

// outras funcoes

void		exibirLog(PFILA);
bool        trocaPrioridade(PFILA, int, float);
