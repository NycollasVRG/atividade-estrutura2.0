#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int num;
    struct Node* prox;
}Node;

typedef struct Pilha
{
    Node* topo;
}Pilha;

Pilha* CriarPilha()
{
    Pilha* novaPilha = malloc(sizeof(Pilha));
    novaPilha->topo = NULL;
    
    return novaPilha;
}

void AdicionarNovoNodo(Pilha* pilha, int novoNum)
{
    if (pilha->topo == NULL)
    {
        Node* novoNodo = malloc(sizeof(Node));
        pilha->topo = novoNodo;
        novoNodo->num = novoNum;
        novoNodo->prox = NULL;
    }
    
    else
    {
        Node* aux = pilha->topo;
        int check = 0;
        
        while (aux != NULL && check == 0)
        {
            if (aux->num == novoNum)
                check = 1;

            aux = aux->prox;
        }
        
        if (check == 0)
        {
            Node* novoNodo = malloc(sizeof(Node));

            novoNodo->prox = pilha->topo;
            novoNodo->num = novoNum;
            pilha->topo = novoNodo;
        }
    }
}

void main(int argc, char *argv[])
{
    srand(time(NULL));
    
    Pilha* pilha = CriarPilha();
    
    time_t inicio, agora;
    struct tm *tm;
    inicio = time(NULL);
    
    int cont = 0;
    
    while (cont < 1000000)
    {
        int num = rand();
        AdicionarNovoNodo(pilha, num);
        cont += 1;
    }
    
    agora = time(NULL);
    agora = difftime(agora, inicio);

    
    printf("Tempo em segundos: %ld", agora);
}