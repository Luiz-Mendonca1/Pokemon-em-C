# PokemonEmC
Jogo criado em C para estudo de linguagem

Informações introdutorias:

#include <stdlib.h>: para alocação de memória, números aleatórios e conversões.
#include <time.h>: gerar números verdadeiramente aleatórios.
#include <string.h>: para copiar, comparar e manipular cadeias de caracteres.

struct = Molde pra criar um novo tipo de variável (que guarda vários dados juntos).
typedef = Apelido pra não precisar digitar struct toda hora.
char nome[20];          // Armazena até 20 letras (ex.: "Pikachu")
char ataques[4][20];    // 4 ataques, cada um com até 20 letras
(O \0 marca o fim da palavra, e o resto fica vazio)

Recebe as informações para criar um Pokémon:
Pokemon *p para criar um dicionario para cada pokemon futuramente
char ataques[][20] - [] para definir numero de palavras, [20] numero de letras dentro, no caso 20
strcpy(p->nome, nome); - strcpy significa string copy, o 'p' é aquele item variavel de antes, que ira copiar a string nome para ele
i é o valor do ataque, ataques[0] = "Choque do Trovão", ataques[1] = "Investida"

tem um 'for' pra repetir o i que vai aumentando e mostrando suas informações de acordo com sua posição na lista

usa jogador e inimigo como itens para atribuir variaveis com valores definidos para cada um 
repete a logica para o inimigo que escolhe seus ataques aleatoriamente de acordo com o comando 
