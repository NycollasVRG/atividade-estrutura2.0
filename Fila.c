#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int num;
    struct Node* prox;
}Node;

typedef struct Fila
{
    Node* inicio;
}Fila;

Fila* CriarFila()
{
    Fila* novaFila = malloc(sizeof(Fila));
    novaFila->inicio = NULL;
    
    return novaFila;
}

void AdicionarNovoNodo(Fila* fila, int novoNum)
{
    if (fila->inicio == NULL)
    {
        Node* novoNodo = malloc(sizeof(Node));
        fila->inicio = novoNodo;
        novoNodo->num = novoNum;
        novoNodo->prox = NULL;
    }
    
    else
    {
        Node* aux = fila->inicio;
        Node* aux2;
        int check = 0;
        
        while (aux != NULL && check == 0)
        {
            if (aux->num == novoNum)
                check = 1;
            aux2 = aux;
            aux = aux->prox;
        }
        
        if (check == 0)
        {
            Node* novoNodo = malloc(sizeof(Node));
            novoNodo->num = novoNum;
            novoNodo->prox = NULL;
            aux2->prox = novoNodo;
        }
    }
}

void main(int argc, char *argv[])
{
    srand(time(NULL));
    
    Fila* fila = CriarFila();
    
    time_t inicio, agora;
    struct tm *tm;
    inicio = time(NULL);
    
    int cont = 0;
    
    while (cont < 1000000)
    {
        int num = rand();
        AdicionarNovoNodo(fila, num);
        cont += 1;
    }
    
    agora = time(NULL);
    agora = difftime(agora, inicio);

    
    printf("Tempo em segundos: %ld", agora);
}