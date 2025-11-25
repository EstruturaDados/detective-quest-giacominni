#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pista {
    char texto[50];
    struct Pista *esquerda;
    struct Pista *direita;
} Pista;

typedef struct Sala {
    char nome[50];
    char pista[50];
    int pistaColetada;
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Pista* criarPista(char *texto) {
    Pista *nova = (Pista*) malloc(sizeof(Pista));
    strcpy(nova->texto, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

Pista* inserirPista(Pista *raiz, char *texto) {
    if (raiz == NULL) {
        return criarPista(texto);
    }
    if (strcmp(texto, raiz->texto) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    } else if (strcmp(texto, raiz->texto) > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    return raiz;
}

void exibirPistasEmOrdem(Pista *raiz) {
    if (raiz != NULL) {
        exibirPistasEmOrdem(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        exibirPistasEmOrdem(raiz->direita);
    }
}

Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    
    if (pista != NULL) {
        strcpy(nova->pista, pista);
        nova->pistaColetada = 0;
    } else {
        strcpy(nova->pista, "");
        nova->pistaColetada = 1;
    }
    
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void explorarSalas(Sala *mapa) {
    Sala *atual = mapa;
    Pista *inventarioPistas = NULL;
    char opcao;
    int pistasEncontradas = 0;

    printf("\n=== DETECTIVE QUEST: NIVEL AVENTUREIRO ===\n");

    while (atual != NULL) {
        printf("\n-----------------------------------\n");
        printf("VOCE ESTA EM: [ %s ]\n", atual->nome);
        
        if (atual->pistaColetada == 0) {
            printf(">> VOCE ENCONTROU UMA PISTA: '%s'!\n", atual->pista);
            inventarioPistas = inserirPista(inventarioPistas, atual->pista);
            atual->pistaColetada = 1;
            pistasEncontradas++;
        }
        printf("-----------------------------------\n");

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho (Sem saidas).\n");
        } else {
            printf("Caminhos:\n");
            if (atual->esquerda != NULL) printf("[e] Esquerda (%s)\n", atual->esquerda->nome);
            if (atual->direita != NULL) printf("[d] Direita (%s)\n", atual->direita->nome);
        }
        
        printf("[i] Ver Pistas (%d coletadas)\n", pistasEncontradas);
        printf("[s] Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e' || opcao == 'E') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
            else printf("Caminho bloqueado.\n");
        } 
        else if (opcao == 'd' || opcao == 'D') {
            if (atual->direita != NULL) atual = atual->direita;
            else printf("Caminho bloqueado.\n");
        }
        else if (opcao == 'i' || opcao == 'I') {
            printf("\n--- PISTAS COLETADAS (Ordem Alfabetica) ---\n");
            if (inventarioPistas == NULL) printf("(Nenhuma pista encontrada ainda)\n");
            else exibirPistasEmOrdem(inventarioPistas);
        }
        else if (opcao == 's' || opcao == 'S') {
            printf("Encerrando investigacao...\n");
            break;
        }
        else {
            printf("Opcao invalida.\n");
        }
    }
}

int main() {
    Sala *hall = criarSala("Hall de Entrada", NULL);
    
    hall->esquerda = criarSala("Sala de Estar", "Relogio Parado");
    hall->direita = criarSala("Cozinha", "Faca Enferrujada");

    hall->esquerda->esquerda = criarSala("Biblioteca", "Diario Antigo");
    hall->esquerda->direita = criarSala("Jardim de Inverno", NULL);

    hall->direita->esquerda = criarSala("Despensa", NULL);
    hall->direita->direita = criarSala("Porao Escuro", "Pegadas de Barro");

    explorarSalas(hall);

    return 0;
}