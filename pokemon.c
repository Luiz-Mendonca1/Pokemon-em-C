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
    } ataques[4];
} Pokemon;

// Declarações das funções (protótipos)
void inicializarPokemon(Pokemon *p, char nome[], int hp, char ataques[][20], int danos[]);
void mostrarAtaques(Pokemon p);
void mostrarPokemon(Pokemon p);
void batalhar(Pokemon *jogador, Pokemon *inimigo);

int main() {
    srand(time(0));

    // Criação dos Pokémon
    Pokemon pikachu;
    char ataquesPikachu[4][20] = {"Choque do Trovão", "Investida", "Cauda de Ferro", "Ataque Rápido"};
    int danosPikachu[4] = {30, 15, 20, 10};
    inicializarPokemon(&pikachu, "Pikachu", 100, ataquesPikachu, danosPikachu);

    Pokemon charizard;
    char ataquesCharizard[4][20] = {"Lança-Chamas", "Garra de Dragão", "Rajada de Fogo", "Asas de Vento"};
    int danosCharizard[4] = {35, 25, 30, 10};
    inicializarPokemon(&charizard, "Charizard", 120, ataquesCharizard, danosCharizard);

    Pokemon bulbasaur;
    char ataquesBulbasaur[4][20] = {"Chicote de Vinha", "Folha Navalha", "Semente Sanguessuga", "Raio Solar"};
    int danosBulbasaur[4] = {25, 20, 15, 40};
    inicializarPokemon(&bulbasaur, "Bulbasaur", 110, ataquesBulbasaur, danosBulbasaur);

    Pokemon squirtle;
    char ataquesSquirtle[4][20] = {"Jato de Água", "Casco Estrela", "Redemoinho", "Quebra-Crânio"};
    int danosSquirtle[4] = {30, 20, 15, 25};
    inicializarPokemon(&squirtle, "Squirtle", 105, ataquesSquirtle, danosSquirtle);

    // Escolhe um inimigo aleatório
    Pokemon listaInimigos[] = {charizard, bulbasaur, squirtle};
    int numInimigos = 3;
    Pokemon inimigo = listaInimigos[rand() % numInimigos];

    printf("\n----- BATALHA POKÉMON -----\n");
    printf("Seu Pokémon: %s\n", pikachu.nome);
    printf("Inimigo: %s\n", inimigo.nome);

    batalhar(&pikachu, &inimigo);

    return 0;
}

// Implementação das funções
void inicializarPokemon(Pokemon *p, char nome[], int hp, char ataques[][20], int danos[]) {
    strcpy(p->nome, nome);
    p->hp = hp;
    p->hp_max = hp;
    for (int i = 0; i < 4; i++) {
        strcpy(p->ataques[i].nome, ataques[i]);
        p->ataques[i].dano = danos[i];
    }
}

void mostrarAtaques(Pokemon p) {
    printf("Ataques:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d - %s (Dano: %d)\n", i + 1, p.ataques[i].nome, p.ataques[i].dano);
    }
}

void mostrarPokemon(Pokemon p) {
    printf("\nPokémon: %s (HP: %d/%d)\n", p.nome, p.hp, p.hp_max);
    mostrarAtaques(p);
}

void batalhar(Pokemon *jogador, Pokemon *inimigo) {
    while (1) {
        // Turno do jogador
        printf("\n--- Seu Turno ---\n");
        printf("%s (HP: %d/%d) vs %s (HP: %d/%d)\n", 
               jogador->nome, jogador->hp, jogador->hp_max,
               inimigo->nome, inimigo->hp, inimigo->hp_max);
        
        mostrarAtaques(*jogador);
        printf("Escolha um ataque (1-4): ");
        int escolha;
        scanf("%d", &escolha);
        
        if (escolha < 1 || escolha > 4) {
            printf("Ataque inválido! Tente novamente.\n");
            continue;
        }
        
        int dano = jogador->ataques[escolha - 1].dano;
        inimigo->hp -= dano;
        
        printf("\n%s usou %s e causou %d de dano!\n", 
               jogador->nome, jogador->ataques[escolha - 1].nome, dano);
        
        if (inimigo->hp <= 0) {
            printf("\n%s derrotou %s! Vitória!\n", jogador->nome, inimigo->nome);
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