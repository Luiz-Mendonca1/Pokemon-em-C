#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Estrutura do Pokémon
typedef struct {
    char nome[20];
    int hp;
    int hp_max;
    struct {
        char nome[20];
        int dano;
    } ataques[4]; // Máximo de 4 ataques
} Pokemon;

// Inicializa um Pokémon
void inicializarPokemon(Pokemon *p, char nome[], int hp, char ataques[][20], int danos[]) {
    strcpy(p->nome, nome);
    p->hp = hp;
    p->hp_max = hp;
    for (int i = 0; i < 4; i++) {
        strcpy(p->ataques[i].nome, ataques[i]);
        p->ataques[i].dano = danos[i];
    }
} 

// Exibe os ataques do Pokémon
void mostrarAtaques(Pokemon p) {
    printf("\nAtaques de %s:\n", p.nome);
    for (int i = 0; i < 4; i++) {
        printf("%d - %s (Dano: %d)\n", i + 1, p.ataques[i].nome, p.ataques[i].dano);
    }
}

// Batalha entre dois Pokémon
void batalhar(Pokemon *jogador, Pokemon *inimigo) {
    int escolha;
    while (1) {
        // Turno do jogador
        printf("\n--- Seu Turno ---\n");
        printf("%s (HP: %d/%d) vs %s (HP: %d/%d)\n", 
               jogador->nome, jogador->hp, jogador->hp_max,
               inimigo->nome, inimigo->hp, inimigo->hp_max);
        
        mostrarAtaques(*jogador);
        printf("Escolha um ataque (1-4): ");
        scanf("%d", &escolha);
        
        if (escolha < 1 || escolha > 4) {
            printf("Ataque inválido!\n");
            continue;
        }
        
        int dano = jogador->ataques[escolha - 1].dano;
        inimigo->hp -= dano;
        
        printf("\n%s usou %s e causou %d de dano!\n", 
               jogador->nome, jogador->ataques[escolha - 1].nome, dano);
        
        if (inimigo->hp <= 0) {
            printf("\n%s derrotou %s! Vitoria!\n", jogador->nome, inimigo->nome);
            break;
        }
        
        // Turno do inimigo (ataque aleatório)
        printf("\n--- Turno do Inimigo ---\n");
        int ataqueInimigo = rand() % 4;
        dano = inimigo->ataques[ataqueInimigo].dano;
        jogador->hp -= dano;
        
        printf("%s usou %s e causou %d de dano!\n", 
               inimigo->nome, inimigo->ataques[ataqueInimigo].nome, dano);
        
        if (jogador->hp <= 0) {
            printf("\n%s foi derrotado... Game Over!\n", jogador->nome);
            break;
        }
    }
}

int main() {
    srand(time(0)); // Inicializa o gerador de números aleatórios
    
    // Cria os Pokémon
    Pokemon pikachu;
    char ataquesPikachu[4][20] = {"Choque do Trovão", "Investida", "Cauda de Ferro", "Ataque Rápido"};
    int danosPikachu[4] = {30, 15, 20, 10};
    inicializarPokemon(&pikachu, "Pikachu", 100, ataquesPikachu, danosPikachu);
    
    Pokemon charizard;
    char ataquesCharizard[4][20] = {"Lança-Chamas", "Garra de Dragão", "Rajada de Fogo", "Asas de Vento"};
    int danosCharizard[4] = {35, 25, 30, 10};
    inicializarPokemon(&charizard, "Charizard", 120, ataquesCharizard, danosCharizard);
    
    // Inicia a batalha
    printf("----- BATALHA POKEMON -----\n");
    batalhar(&pikachu, &charizard);
    
    return 0;
}