#include "ch0918pq.h"

bool        aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
    if (f == NULL)  return false; // fila vazia
    if (id < 0)     return false; // id negativo
    if (id > (f->maxElementos - 1)) return false; // id > maximo
    if ((f->arranjo[id] == NULL) ||
        (f->arranjo[id]->ant == NULL)
        )
        return false;

    // se nao tem esse na fila retorna false
    if (    (f->arranjo[id] == NULL) || 
            (f->arranjo[id]->ant == NULL) )
        return false;

    if (f->arranjo[id]->prioridade  >= novaPrioridade) return false;

    // o elemento existia com prioridade menor
    return trocaPrioridade(f, id, novaPrioridade);
};  // aumentarPrioridade()

bool        consultarPrioridade(PFILA f, int id, float* resposta)
{
    if (f == NULL)  return false; // fila vazia
    if (id < 0)     return false; // id negativo
    if (id > (f->maxElementos - 1)) return false; // id > maximo
    if (    (f->arranjo[id] == NULL) || 
            (f->arranjo[id]->ant == NULL)
        )
        return false;
    // o normal
    *resposta = f->arranjo[id]->prioridade;
    return true;
}

PFILA       criarFila(int max)
{
    PFILA res = (PFILA)malloc(sizeof(FILADEPRIORIDADE));
    res->maxElementos = max;
    res->arranjo = (PONT*)malloc(sizeof(PONT) * max);
    int i;
    for (i = 0; i < max; i++) res->arranjo[i] = NULL;
    PONT cabeca = (PONT)malloc(sizeof(ELEMENTO));
    res->fila = cabeca;
    cabeca->ant = cabeca;
    cabeca->prox = cabeca;
    cabeca->id = -1;
    cabeca->prioridade = 1000 * 1000;
    return res;
};  // criarFila()

bool        inserirElemento(PFILA f, int id, float prioridade)
{
    //
    // insere na fila f o elemento de id 'id'e 'prioridade'
    //
    printf("\
inserirElemento(%3d,P = %6.2f):\n",
id, prioridade);

    // retorna false se o identificador nao e valido
    if ((id < 0) || (id > (f->maxElementos - 1)))
    {
        printf("\
inserirElemento(): identificador invalido\n");
        return false;
    };

    // retorna false se ja tem alguem com esse id
    if ( (f->arranjo[id] != NULL) && (f->arranjo[id]->ant != NULL) )
    {
        printf("\
inserirElemento(): identificador %d ja ocupado\
prioridade: %6.2f\n",
id, f->arranjo[id]->prioridade);
        return false;
    };

    //
    // entao cria o novo ELEMENTO
    // mas antes verifica se ja nao atendeu alguem 
    // com esse id: como eh preciso preservar cada
    // ELEMENTO o id teria sido alterado para 
    // maxElementos e os ponteiros invalidados
    // na rotina removerElemento() que seria o 
    // atendimento
    //
    ELEMENTO* novo = NULL;
    if (f->arranjo[id] == NULL)
        novo = (ELEMENTO*)malloc(sizeof(ELEMENTO));
    else
        novo = f->arranjo[id];

    novo->id = id;
    novo->prioridade = prioridade;

    // e coloca no arranjo
    f->arranjo[id] = novo;

    // e coloca na lista
    ELEMENTO* p = f->fila->prox; // primeiro da fila
    // agora encontra a posicao certa na fila
    do
    {
        if (p->prioridade >= prioridade)
        {   // segue na fila: pr. na fila maior
            p = p->prox;
        }
        else
        {
            break;
        };  // if()
    } while (p->id >= 0);  // while()
    // vai inserir 'novo' antes de 'p'
    novo->ant = p->ant;
    novo->prox = p;
    p->ant->prox = novo;
    p->ant = novo;
    f->fila->id -= 1;
    return true;
};  // inserirElemento()

bool        reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
    if (f == NULL)  return false; // fila vazia
    if (id < 0)     return false; // id negativo
    if (id > (f->maxElementos - 1)) return false; // id > maximo
    if ((f->arranjo[id] == NULL) ||
        (f->arranjo[id]->ant == NULL)
        )
        return false;

    // se nao tem esse na fila retorna false
    if ((f->arranjo[id] == NULL) ||
        (f->arranjo[id]->ant == NULL))
        return false;

    if (f->arranjo[id]->prioridade <= novaPrioridade) return false;

    // o elemento existia com prioridade maior
    return trocaPrioridade(f, id, novaPrioridade);
}

PONT        removerElemento(PFILA f)
{
    // o simples: a funcao de atendimento()

    // retorna NULL se nao tem ninguem na fila

    if (f->fila->prox == f->fila)
        return NULL;

    //
    // no arranjo, exclui o primeiro da fila,
    // mas preserva o ELEMENTO alocado
    // so que NULL eh zero e zero eh um 
    // indentificador valido entao vou
    // zerar os ponteiros, que jamais seriam 
    // zero ja que a lista eh circular com
    // sentinela
    //
    ELEMENTO* a_excluir = f->fila->prox;
    printf("removerElemento(%3d,P = %6.2f)\n",
        a_excluir->id, a_excluir->prioridade
    );

    if (f->fila->prox == f->fila->ant)
    {
        // so tem um
        // arruma o vetor
        a_excluir->id = f->maxElementos;
        a_excluir->ant = NULL;
        a_excluir->prox = NULL;
        // arruma a lista ligada
        f->fila->prox = f->fila;
        f->fila->ant = f->fila;
        f->fila->id += 1;
        return a_excluir;
    };  // if()

    // tem mais de um:
    // na lista ligada, exclui o cara
    // mas nao apaga o ELEMENTO
    int     id_a_excluir = a_excluir->id;
    // novo primeiro da fila vem depois da sentinela
    a_excluir->prox->ant = f->fila;
    f->fila->prox = a_excluir->prox;

    f->arranjo[id_a_excluir]->id = f->maxElementos;
    f->arranjo[id_a_excluir]->ant = NULL;
    f->arranjo[id_a_excluir]->prox = NULL;
    f->fila->id += 1;

    return a_excluir;
};  // removerElemento()

int         tamanho(PFILA f)
{
    //
    // convencao: os id vao de 0 a maxElementos, e o 
    // id do sentilena = '-1'. Entao usamos esse campo
    // para contar o tamanho. Muito mais simples e rápido
    // usando -1 para 0, -2 para 1, -3 para 2, e
    // -(N + 1) para N
    //
    return -(f->fila->id + 1);
};  // tamanho()

// helpers

void        exibirLog(PFILA f)
{
    //
    // exibirLog() simples listagem dos elementos da fila a
    // partir do inicio
    //
    // PFILA e um ponteiro para a fila
    // so que em f->arranjo tem uma lista circular a partir
    // da sentinela, unico registro com Id negativa
    if (f == NULL)
    {
        printf("\n\nexibirLog(): Fila nao foi criada\n\n");
        return;
    };

    printf("\n\nexibirLog(): Fila tem %3d lugares. %3d ocupados\n",
        f->maxElementos, tamanho(f) );

    if (tamanho(f) < 1) return;

    // lista por ID

    printf("\n\tListagem por identificador:\n\n");
    int ix = 1;
    int id = 0;
    while (ix <= tamanho(f))
    {
        if (
            (f->arranjo[id] != NULL) &&
            ( f->arranjo[id]->id < f->maxElementos )
            )
        {
            printf("%4d/%4d: [ id: %4d P: %6.2f ]\n",
                ix, f->maxElementos, id, f->arranjo[id]->prioridade);
            ix += 1;
        };  // if()  
        id += 1;
    };  // while()

    // lista por prioridade

    printf("\n\tListagem por prioridade: [ inicio: 0x%p ]\n\n", f->fila);
    ELEMENTO*   p = f->fila->prox; // sentinela
    ix = 1; // conta os caras
    while ( ix <= tamanho(f)  )
    {
        printf("\
%4d/%4d: [ id: %4d p: %6.2f ] [ 0x%p, ant:0x%p, prox: 0x%p] \n",
            ix, tamanho(f), p->id, p->prioridade, p, p->ant, p->prox
        );
        p = p->prox;
        ix += 1;
    };
    printf("\nFim da listagem\n\n");
    return;
};  // exibirLog()

bool        trocaPrioridade(PFILA f, int id, float pri)
{
    // troca a posicao do elemento na fila para a
    // que corresponde a nova prioridade. 
    //

    // desconecta da fila
    (f->arranjo[id]->ant)->prox = f->arranjo[id]->prox;
    (f->arranjo[id]->prox)->ant = f->arranjo[id]->ant;

    // o elementoja esta na fila ou nao estariamos aqui
    // agora acha a nova posicao consirando a nova 
    // prioridade

    ELEMENTO* p = f->fila->prox; // sentinela
    while (p != f->fila)
    {
        if ( pri > p->prioridade ) break;
        p = p->prox;
    };  // while()
    // o lugar novo eh antes de p
    p->ant->prox = f->arranjo[id];
    f->arranjo[id]->ant = p->ant;
    p->ant = f->arranjo[id];
    f->arranjo[id]->prox = p;
    f->arranjo[id]->prioridade = pri;
    return true;
};  // trocaPrioridade()

// fim