#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

// Função para imprimir texto letra por letra (apenas para narrações)
void imprimirNarracao(const char *texto, int delay) {
    for (int i = 0; texto[i] != '\0'; i++) {
        putchar(texto[i]);
        fflush(stdout);
        Sleep(delay);
    }
}

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
    int pocoes;
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

void esperar(float segundos) {
    #ifdef _WIN32
        Sleep((int)(segundos * 1000));
    #else
        usleep((int)(segundos * 1000000));
    #endif
}

int main() {
    srand(time(0));

    // Introdução com efeito de digitação
    imprimirNarracao("\n----- BATALHA POKEMON -----\n", 10);
    imprimirNarracao("Voce esta prestes a comecar uma emocionante batalha Pokemon!\n", 10);
    imprimirNarracao("Seu Pikachu enfrentara um oponente aleatorio. Prepare-se!\n\n", 10);

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
    const char ataquesVenusaur[4][20] = {"Chicote de Vinha", "Folha Navalha", "Raio Solar", "Investida"};
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

    // Mostrar informações dos Pokémon com efeito de digitação
    char info[200];
    sprintf(info, "\nSeu Pokemon: %s (Tipo: ", pikachu.nome);
    imprimirNarracao(info, 10);
    
    switch(pikachu.tipo) {
        case ELETRICO: imprimirNarracao("Eletrico)\n", 10); break;
        case FOGO: imprimirNarracao("Fogo)\n", 10); break;
        case AGUA: imprimirNarracao("Agua)\n", 10); break;
        case PLANTA: imprimirNarracao("Planta)\n", 10); break;
        default: imprimirNarracao("Normal)\n", 10);
    }
    
    sprintf(info, "Inimigo: %s (Tipo: ", inimigo.nome);
    imprimirNarracao(info, 10);
    
    switch(inimigo.tipo) {
        case ELETRICO: imprimirNarracao("Eletrico)\n", 10); break;
        case FOGO: imprimirNarracao("Fogo)\n", 10); break;
        case AGUA: imprimirNarracao("Agua)\n", 10); break;
        case PLANTA: imprimirNarracao("Planta)\n", 10); break;
        default: imprimirNarracao("Normal)\n", 10);
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
    p->pocoes = 5;
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
        imprimirNarracao("\n--- Seu Turno ---\n", 10);
        esperar(1.5);
        
        char status[150];
        sprintf(status, "%s (HP: %d/%d) vs %s (HP: %d/%d)\n", 
               jogador->nome, jogador->hp, jogador->hp_max,
               inimigo->nome, inimigo->hp, inimigo->hp_max);
        imprimirNarracao(status, 10);
        esperar(1.5);
               
        int respbag;
        int escolhaPrincipal;
        printf("\nO que deseja fazer?\n");
        printf("1 - Atacar\n");
        printf("2 - Mochila\n");
        printf("3 - Trocar de Pokemon\n");
        printf("4 - Fugir\n");
        printf("---------\n");
        printf("Escolha: ");
        scanf("%d", &escolhaPrincipal);
        printf("---------\n");
        esperar(1.5);

        switch (escolhaPrincipal) {
            case 1:
                mostrarAtaques(*jogador);
                printf("Escolha um ataque (1-4): ");
                int escolhaAtaque;
                scanf("%d", &escolhaAtaque);

                if (escolhaAtaque < 1 || escolhaAtaque > 4) {
                    printf("Ataque invalido! Tente novamente.\n");
                    continue;
                }

                float multiplicador = calcularVantagem(jogador->ataques[escolhaAtaque-1].tipo, inimigo->tipo);
                int dano = jogador->ataques[escolhaAtaque-1].dano * multiplicador;
                inimigo->hp -= dano;
                if (inimigo->hp < 0) inimigo->hp = 0;
                
                esperar(1.5);
                char ataqueMsg[100];
                sprintf(ataqueMsg, "\n%s usou %s!", jogador->nome, jogador->ataques[escolhaAtaque-1].nome);
                imprimirNarracao(ataqueMsg, 10);
                if (multiplicador > 1) imprimirNarracao(" E supereficaz!", 10);
                if (multiplicador < 1) imprimirNarracao(" Nao foi muito eficaz...", 10);
                esperar(1.5);
                sprintf(ataqueMsg, " Causou %d de dano!\n", dano);
                imprimirNarracao(ataqueMsg, 10);
                esperar(1.5);
                sprintf(ataqueMsg, "%s agora tem %d/%d de HP.\n", inimigo->nome, inimigo->hp, inimigo->hp_max);
                imprimirNarracao(ataqueMsg, 10);

                if (inimigo->hp <= 0) {
                    sprintf(ataqueMsg, "\n%s derrotou %s! Vitoria!\n", jogador->nome, inimigo->nome);
                    imprimirNarracao(ataqueMsg, 10);
                    return;
                }
                break;

            case 2:
                printf("Voce abriu a mochila...\nItens:\n");
                printf("1 - Pocao (%d disponiveis)\n", jogador->pocoes);
                printf("2 - Voltar\n");
                printf("Escolha o item: ");
                scanf("%d", &respbag);

                switch (respbag) {
                    case 1:
                    if (jogador->pocoes > 0) {
                        int cura = 30;
                        jogador->hp += cura;
                        if (jogador->hp > jogador->hp_max) jogador->hp = jogador->hp_max;
                        jogador->pocoes--;
                        printf("%s usou uma pocao e recuperou %d de HP! (HP atual: %d)\n", jogador->nome, cura, jogador->hp);
                        imprimirNarracao(ataqueMsg, 10);
                    } else {
                        printf("Voce nao tem mais pocoes!\n");
                        imprimirNarracao(ataqueMsg, 10);
                    }
                    break;

                    case 2:
                        printf("---------\n");
                        printf("Voltando ao menu principal...\n");
                        imprimirNarracao(ataqueMsg, 10);
                        printf("---------\n");
                        continue;  // Volta para o início do loop do jogador

                    default:
                        printf("Item invalido! Voltando ao menu principal...\n");
                        imprimirNarracao(ataqueMsg, 10);
                        continue;
                }
                break;

            case 3:
                printf("\nVoce so tem esse Pokemon! Nao ha como trocar.\n");
                imprimirNarracao(ataqueMsg, 10);
                break;

            case 4:
                printf("\nVoce nao pode fugir de batalhar Pokemon!\n");
                imprimirNarracao(ataqueMsg, 10);
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
        
        esperar(1.5);
        imprimirNarracao("\n--- Turno do Inimigo ---\n", 10);
        int ataqueInimigo = rand() % 4;
        float multiplicador = calcularVantagem(inimigo->ataques[ataqueInimigo].tipo, jogador->tipo);
        int dano = inimigo->ataques[ataqueInimigo].dano * multiplicador;
        jogador->hp -= dano;
        if (jogador->hp < 0) {
            jogador->hp = 0;
        }
        
        esperar(1.5);
        char ataqueInimigoMsg[100];
        sprintf(ataqueInimigoMsg, "%s usou %s!", inimigo->nome, inimigo->ataques[ataqueInimigo].nome);
        imprimirNarracao(ataqueInimigoMsg, 10);
        if (multiplicador > 1) imprimirNarracao(" E supereficaz!", 10);
        if (multiplicador < 1) imprimirNarracao(" Nao foi muito eficaz...", 10);
        esperar(1.5);
        sprintf(ataqueInimigoMsg, " Causou %d de dano!\n", dano);
        imprimirNarracao(ataqueInimigoMsg, 10);
        esperar(1.5);
        sprintf(ataqueInimigoMsg, "%s agora tem %d/%d de HP.\n", jogador->nome, jogador->hp, jogador->hp_max);
        imprimirNarracao(ataqueInimigoMsg, 10);
        esperar(1.5);

        if (jogador->hp <= 0) {
            esperar(1.5);
            char derrotaMsg[100];
            sprintf(derrotaMsg, "\n%s foi derrotado... Game Over!\n", jogador->nome);
            imprimirNarracao(derrotaMsg, 10);
            break;
        }
    }
}