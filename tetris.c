#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// 🧩 Nível Novato: Fila de Peças Futuras
// Struct para representar uma peça
typedef struct {
    char tipo;  // Tipo da peça (I, O, T, S, Z, J, L)
    int id;     // ID sequencial da peça
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[5];
    int frente;
    int tras;
    int tamanho;
} FilaCircular;

// Estrutura da pilha linear
typedef struct {
    Peca pecas[3];
    int topo;
} PilhaLinear;

// Variáveis globais
FilaCircular fila;
PilhaLinear pilha;
int proximoId = 1;

// 🧩 Nível Novato: Funções da Fila Circular
void inicializarFila() {
    fila.frente = 0;
    fila.tras = 0;
    fila.tamanho = 0;
}

int filaVazia() {
    return fila.tamanho == 0;
}

int filaCheia() {
    return fila.tamanho == 5;
}

void enqueue(Peca peca) {
    if (!filaCheia()) {
        fila.pecas[fila.tras] = peca;
        fila.tras = (fila.tras + 1) % 5;
        fila.tamanho++;
    }
}

Peca dequeue() {
    Peca pecaVazia = {' ', -1};
    if (!filaVazia()) {
        Peca peca = fila.pecas[fila.frente];
        fila.frente = (fila.frente + 1) % 5;
        fila.tamanho--;
        return peca;
    }
    return pecaVazia;
}

// 🧠 Nível Aventureiro: Funções da Pilha Linear
void inicializarPilha() {
    pilha.topo = -1;
}

int pilhaVazia() {
    return pilha.topo == -1;
}

int pilhaCheia() {
    return pilha.topo == 2;
}

void push(Peca peca) {
    if (!pilhaCheia()) {
        pilha.topo++;
        pilha.pecas[pilha.topo] = peca;
    }
}

Peca pop() {
    Peca pecaVazia = {' ', -1};
    if (!pilhaVazia()) {
        Peca peca = pilha.pecas[pilha.topo];
        pilha.topo--;
        return peca;
    }
    return pecaVazia;
}

// Função para gerar peça aleatória
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
    novaPeca.tipo = tipos[rand() % 7];
    novaPeca.id = proximoId++;
    return novaPeca;
}

// Função para mostrar a fila
void mostrarFila() {
    printf("\n=== FILA DE PEÇAS FUTURAS ===\n");
    if (filaVazia()) {
        printf("Fila vazia!\n");
        return;
    }
    
    int i = fila.frente;
    int count = 0;
    printf("Frente -> ");
    while (count < fila.tamanho) {
        printf("[%c-%d] ", fila.pecas[i].tipo, fila.pecas[i].id);
        i = (i + 1) % 5;
        count++;
    }
    printf("<- Trás\n");
    printf("Tamanho: %d/5\n", fila.tamanho);
}

// Função para mostrar a pilha
void mostrarPilha() {
    printf("\n=== PILHA DE RESERVA ===\n");
    if (pilhaVazia()) {
        printf("Pilha vazia!\n");
        return;
    }
    
    printf("Topo -> ");
    for (int i = pilha.topo; i >= 0; i--) {
        printf("[%c-%d] ", pilha.pecas[i].tipo, pilha.pecas[i].id);
    }
    printf("<- Base\n");
    printf("Tamanho: %d/3\n", pilha.topo + 1);
}

// 🔄 Nível Mestre: Funções de Troca
void trocarPecaFrenteComTopo() {
    if (filaVazia()) {
        printf("Erro: Fila vazia! Não é possível trocar.\n");
        return;
    }
    if (pilhaVazia()) {
        printf("Erro: Pilha vazia! Não é possível trocar.\n");
        return;
    }
    
    // Troca direta entre a frente da fila e o topo da pilha
    Peca temp = fila.pecas[fila.frente];
    fila.pecas[fila.frente] = pilha.pecas[pilha.topo];
    pilha.pecas[pilha.topo] = temp;
    
    printf("Troca realizada: Peça da frente da fila trocada com o topo da pilha!\n");
}

void trocarTresPrimeiros() {
    if (fila.tamanho < 3) {
        printf("Erro: Fila deve ter pelo menos 3 peças! Atual: %d\n", fila.tamanho);
        return;
    }
    if (pilha.topo != 2) {
        printf("Erro: Pilha deve ter exatamente 3 peças! Atual: %d\n", pilha.topo + 1);
        return;
    }
    
    // Troca os 3 primeiros da fila com as 3 da pilha
    for (int i = 0; i < 3; i++) {
        int indiceFila = (fila.frente + i) % 5;
        Peca temp = fila.pecas[indiceFila];
        fila.pecas[indiceFila] = pilha.pecas[i];
        pilha.pecas[i] = temp;
    }
    
    printf("Troca realizada: 3 primeiros da fila trocados com as 3 peças da pilha!\n");
}

// Função para preencher a fila inicial
void preencherFilaInicial() {
    for (int i = 0; i < 5; i++) {
        enqueue(gerarPeca());
    }
}

// Função para mostrar o menu
void mostrarMenu() {
    printf("\n=== MENU TETRIS STACK ===\n");
    printf("1 - Jogar peça (remover da frente da fila)\n");
    printf("2 - Enviar peça da fila para a reserva (pilha)\n");
    printf("3 - Usar peça da reserva (remover do topo da pilha)\n");
    printf("4 - Trocar peça da frente com topo da pilha\n");
    printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializar estruturas
    inicializarFila();
    inicializarPilha();
    
    // Preencher fila inicial
    preencherFilaInicial();
    
    printf("=== SISTEMA TETRIS STACK ===\n");
    printf("Bem-vindo ao sistema de controle de peças do Tetris!\n");
    
    int opcao;
    do {
        mostrarFila();
        mostrarPilha();
        mostrarMenu();
        
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                // Jogar peça (remover da frente da fila)
                if (filaVazia()) {
                    printf("Erro: Fila vazia! Não é possível jogar peça.\n");
                } else {
                    Peca pecaJogada = dequeue();
                    printf("Peça jogada: [%c-%d]\n", pecaJogada.tipo, pecaJogada.id);
                    
                    // Repor a fila com uma nova peça
                    if (!filaCheia()) {
                        enqueue(gerarPeca());
                    }
                }
                break;
            }
            
            case 2: {
                // Enviar peça da fila para a reserva (pilha)
                if (filaVazia()) {
                    printf("Erro: Fila vazia! Não é possível enviar peça.\n");
                } else if (pilhaCheia()) {
                    printf("Erro: Pilha cheia! Não é possível enviar peça.\n");
                } else {
                    Peca peca = dequeue();
                    push(peca);
                    printf("Peça [%c-%d] enviada da fila para a reserva!\n", peca.tipo, peca.id);
                    
                    // Repor a fila com uma nova peça
                    if (!filaCheia()) {
                        enqueue(gerarPeca());
                    }
                }
                break;
            }
            
            case 3: {
                // Usar peça da reserva (remover do topo da pilha)
                if (pilhaVazia()) {
                    printf("Erro: Pilha vazia! Não é possível usar peça da reserva.\n");
                } else {
                    Peca pecaUsada = pop();
                    printf("Peça da reserva usada: [%c-%d]\n", pecaUsada.tipo, pecaUsada.id);
                }
                break;
            }
            
            case 4: {
                // Trocar peça da frente com topo da pilha
                trocarPecaFrenteComTopo();
                break;
            }
            
            case 5: {
                // Trocar 3 primeiros da fila com os 3 da pilha
                trocarTresPrimeiros();
                break;
            }
            
            case 0: {
                printf("Obrigado por usar o Sistema Tetris Stack! Até logo!\n");
                break;
            }
            
            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while (opcao != 0);

    return 0;
}

