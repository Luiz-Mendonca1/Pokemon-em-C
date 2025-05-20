#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum {
    AGUA,
    FOGO,
    PLANTA,
    ELETRICO,
    NORMAL
} TipoPokemon;

typedef struct {
    char nome[20];
    int hp;
    int hp_max;
    TipoPokemon tipo;
    struct {
        char nome[20];
        int dano;
        TipoPokemon tipo;
    } ataques[4];
} Pokemon;

void inicializarPokemon(Pokemon *p, const char *nome, int hp, TipoPokemon tipo, 
                       const char ataques[][20], const int danos[], const TipoPokemon tiposAtaques[]);
void mostrarAtaques(Pokemon p);
void mostrarPokemon(Pokemon p);
float calcularVantagem(TipoPokemon ataque, TipoPokemon defesa);
void batalhar(Pokemon *jogador, Pokemon *inimigo);

int main() {
    srand(time(0));

    Pokemon pikachu;
    const char ataquesPikachu[4][20] = {"Choque do Trovao", "Investida", "Cauda de Ferro", "Ataque Rapido"};
    const int danosPikachu[4] = {30, 15, 20, 10};
    const TipoPokemon tiposAtaquesPikachu[4] = {ELETRICO, NORMAL, NORMAL, NORMAL};
    inicializarPokemon(&pikachu, "Pikachu", 100, ELETRICO, ataquesPikachu, danosPikachu, tiposAtaquesPikachu);

    Pokemon charizard;
    const char ataquesCharizard[4][20] = {"Lanca-Chamas", "Garra de Dragao", "Rajada de Fogo", "Asas de Vento"};
    const int danosCharizard[4] = {35, 25, 30, 10};
    const TipoPokemon tiposAtaquesCharizard[4] = {FOGO, NORMAL, FOGO, NORMAL};
    inicializarPokemon(&charizard, "Charizard", 120, FOGO, ataquesCharizard, danosCharizard, tiposAtaquesCharizard);

    Pokemon venusaur;
    const char ataquesVenusaur[4][20] = {"Chicote de Vinha", "Folha Navalha", "Raio Solar", "Terremoto"};
    const int danosVenusaur[4] = {30, 25, 45, 20};
    const TipoPokemon tiposAtaquesVenusaur[4] = {PLANTA, PLANTA, PLANTA, NORMAL};
    inicializarPokemon(&venusaur, "Venusaur", 140, PLANTA, ataquesVenusaur, danosVenusaur, tiposAtaquesVenusaur);

    Pokemon blastoise;
    const char ataquesBlastoise[4][20] = {"Jato de Agua", "Hidro Bomba", "Casco Canhao", "Quebra-Cranio"};
    const int danosBlastoise[4] = {35, 40, 30, 25};
    const TipoPokemon tiposAtaquesBlastoise[4] = {AGUA, AGUA, NORMAL, NORMAL};
    inicializarPokemon(&blastoise, "Blastoise", 130, AGUA, ataquesBlastoise, danosBlastoise, tiposAtaquesBlastoise);

    Pokemon listaInimigos[] = {charizard, venusaur, blastoise};
    Pokemon inimigo = listaInimigos[rand() % 3];

    printf("\n----- BATALHA POKEMON -----\n");
    printf("Seu Pokemon: %s (Tipo: ", pikachu.nome);
    switch(pikachu.tipo) {
        case ELETRICO: printf("Eletrico)\n"); break;
        case FOGO: printf("Fogo)\n"); break;
        case AGUA: printf("Agua)\n"); break;
        case PLANTA: printf("Planta)\n"); break;
        default: printf("Normal)\n");
    }
    
    printf("Inimigo: %s (Tipo: ", inimigo.nome);
    switch(inimigo.tipo) {
        case ELETRICO: printf("Eletrico)\n"); break;
        case FOGO: printf("Fogo)\n"); break;
        case AGUA: printf("Agua)\n"); break;
        case PLANTA: printf("Planta)\n"); break;
        default: printf("Normal)\n");
    }

    batalhar(&pikachu, &inimigo);

    return 0;
}

void inicializarPokemon(Pokemon *p, const char *nome, int hp, TipoPokemon tipo, 
                       const char ataques[][20], const int danos[], const TipoPokemon tiposAtaques[]) {
    strcpy(p->nome, nome);
    p->hp = hp;
    p->hp_max = hp;
    p->tipo = tipo;
    for (int i = 0; i < 4; i++) {
        strcpy(p->ataques[i].nome, ataques[i]);
        p->ataques[i].dano = danos[i];
        p->ataques[i].tipo = tiposAtaques[i];
    }
}

void mostrarAtaques(Pokemon p) {
    printf("Ataques:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d - %s (Dano: %d, Tipo: ", i+1, p.ataques[i].nome, p.ataques[i].dano);
        switch(p.ataques[i].tipo) {
            case ELETRICO: printf("Eletrico)\n"); break;
            case FOGO: printf("Fogo)\n"); break;
            case AGUA: printf("Agua)\n"); break;
            case PLANTA: printf("Planta)\n"); break;
            default: printf("Normal)\n");
        }
    }
}

void mostrarPokemon(Pokemon p) {
    printf("\nPokemon: %s (HP: %d/%d)\n", p.nome, p.hp, p.hp_max);
    mostrarAtaques(p);
}

float calcularVantagem(TipoPokemon ataque, TipoPokemon defesa) {
    if (ataque == FOGO && defesa == PLANTA) return 1.5f;
    if (ataque == AGUA && defesa == FOGO) return 1.5f;
    if (ataque == PLANTA && defesa == AGUA) return 1.5f;
    if (ataque == ELETRICO && defesa == AGUA) return 1.5f;
    if (ataque == FOGO && defesa == AGUA) return 0.5f;
    if (ataque == AGUA && defesa == PLANTA) return 0.5f;
    if (ataque == PLANTA && defesa == FOGO) return 0.5f;
    return 1.0f;
}

void batalhar(Pokemon *jogador, Pokemon *inimigo) {
    while (1) {
        printf("\n--- Seu Turno ---\n");
        printf("%s (HP: %d/%d) vs %s (HP: %d/%d)\n", 
               jogador->nome, jogador->hp, jogador->hp_max,
               inimigo->nome, inimigo->hp, inimigo->hp_max);
        
        mostrarAtaques(*jogador);
        printf("Escolha um ataque (1-4): ");
        int escolha;
        scanf("%d", &escolha);
        
        if (escolha < 1 || escolha > 4) {
            printf("Ataque invalido! Tente novamente.\n");
            continue;
        }
        
        float multiplicador = calcularVantagem(jogador->ataques[escolha-1].tipo, inimigo->tipo);
        int dano = jogador->ataques[escolha-1].dano * multiplicador;
        inimigo->hp -= dano;
        
        printf("\n%s usou %s!", jogador->nome, jogador->ataques[escolha-1].nome);
        if (multiplicador > 1) printf(" E supereficaz!");
        if (multiplicador < 1) printf(" Nao foi muito eficaz...");
        printf(" Causou %d de dano!\n", dano);
        
        if (inimigo->hp <= 0) {
            printf("\n%s derrotou %s! Vitoria!\n", jogador->nome, inimigo->nome);
            break;
        }
        
        printf("\n--- Turno do Inimigo ---\n");
        int ataqueInimigo = rand() % 4;
        multiplicador = calcularVantagem(inimigo->ataques[ataqueInimigo].tipo, jogador->tipo);
        dano = inimigo->ataques[ataqueInimigo].dano * multiplicador;
        jogador->hp -= dano;
        
        printf("%s usou %s!", inimigo->nome, inimigo->ataques[ataqueInimigo].nome);
        if (multiplicador > 1) printf(" E supereficaz!");
        if (multiplicador < 1) printf(" Nao foi muito eficaz...");
        printf(" Causou %d de dano!\n", dano);
        
        if (jogador->hp <= 0) {
            printf("\n%s foi derrotado... Game Over!\n", jogador->nome);
            break;
        }
    }
}