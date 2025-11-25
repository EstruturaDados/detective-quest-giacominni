#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala* criarSala(char *nome) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

void explorarSalas(Sala *raiz) {
    Sala *atual = raiz;
    char opcao;

    printf("\n=== DETECTIVE QUEST: NIVEL NOVATO ===\n");

    while (atual != NULL) {
        printf("\n-----------------------------------\n");
        printf("VOCE ESTA EM: [ %s ]\n", atual->nome);
        printf("-----------------------------------\n");

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Beco sem saida. A exploracao terminou aqui.\n");
            break;
        }

        printf("Caminhos:\n");
        if (atual->esquerda != NULL) printf("[e] Ir para Esquerda (%s)\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf("[d] Ir para Direita (%s)\n", atual->direita->nome);
        printf("[s] Sair\n");
        
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e' || opcao == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao ha caminho para a esquerda.\n");
            }
        } 
        else if (opcao == 'd' || opcao == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao ha caminho para a direita.\n");
            }
        } 
        else if (opcao == 's' || opcao == 'S') {
            printf("Saindo da mansao...\n");
            break;
        } 
        else {
            printf("Opcao invalida.\n");
        }
    }
}

void liberarMapa(Sala *raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz);
    }
}

int main() {
    Sala *hall = criarSala("Hall de Entrada");
    
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");

    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Jardim de Inverno");

    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Porao Escuro");

    explorarSalas(hall);

    liberarMapa(hall);

    return 0;
}