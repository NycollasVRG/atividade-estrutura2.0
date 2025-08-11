#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int num;
    struct Node* prox;
} Node;

typedef struct Lista {
    Node* inicio;
    Node* fim;  // Para otimizar inserção no fim
    int tamanho;
} Lista;

// Cria uma nova lista vazia
Lista* CriarLista() {
    Lista* novaLista = (Lista*)malloc(sizeof(Lista));
    if (!novaLista) {
        perror("Erro ao alocar memória para a lista");
        exit(EXIT_FAILURE);
    }
    novaLista->inicio = NULL;
    novaLista->fim = NULL;
    novaLista->tamanho = 0;
    return novaLista;
}

// Verifica se o número existe na lista (pra não repetir)
int ExisteNumero(Lista* lista, int num) {
    Node* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->num == num) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

// Adiciona um novo número à lista (sem repetições)
void AdicionarNumero(Lista* lista, int novoNum) {
    // Cria novo nó
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (!novoNode) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    novoNode->num = novoNum;
    novoNode->prox = NULL;

    if (lista->fim == NULL) {
        // Lista vazia
        lista->inicio = lista->fim = novoNode;
    } else {
        lista->fim->prox = novoNode;
        lista->fim = novoNode;
    }
    lista->tamanho++;
}

// Libera a memória da lista
void LiberarLista(Lista* lista) {
    Node* atual = lista->inicio;
    while (atual != NULL) {
        Node* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    Lista* lista = CriarLista();
    
    time_t inicio = time(NULL);
    
    int total_desejado = 100000;
    int total_adicionados = 0;
    int tentativas = 0;
    
  while (tentativas < total_desejado) {
        int num = rand();
        tentativas++;

        if (!ExisteNumero(lista, num)) {
            AdicionarNumero(lista, num);
            total_adicionados++;
        }

        // Para evitar loop infinito caso não consiga números únicos
        if (tentativas > total_desejado * 10) {
            printf("Muitos números repetidos, saindo...\n");
            break;
        }
    }
    
    time_t fim = time(NULL);
    double tempo = difftime(fim, inicio);
    if (tempo == 0) tempo = 1;  // evita divisão por zero
    
    printf("\nResultado Final:\n");
    printf("Numeros unicos adicionados: %d\n", lista->tamanho);
    printf("Tempo total: %.2f segundos\n", tempo);
    printf("Numeros por segundo: %.2f\n", lista->tamanho / tempo);
    
    LiberarLista(lista);
    return 0;
}
