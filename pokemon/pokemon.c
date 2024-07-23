#include <stdio.h>
#include <string.h>

#define MAX_POKEMON 100
#define MAX_NAME_LENGTH 50
#define SUPEREFFECTIVE 1.2f
#define WEAK 0.8f
#define EFFECTIVE 1.0f
// atributos dos pokemons
typedef struct
{
    char nome[MAX_NAME_LENGTH];
    float atk;
    float defesa;
    float vida;
    char tipo[MAX_NAME_LENGTH];
} Pokemon;
// funcao pra mostrar os pokemons
void imprimirPokemon(Pokemon pokemon)
{
    printf("%s ", pokemon.nome);
    printf("%.1f ", pokemon.atk);
    printf("%.1f ", pokemon.defesa);
    printf("%.1f ", pokemon.vida);
    printf("%s \n", pokemon.tipo);
}
// regular os ataques
float Balanceamento(Pokemon pok1, Pokemon pok2)
{
    if (strcmp(pok1.tipo, "eletrico") == 0 && (strcmp(pok2.tipo, "agua") == 0))
    {
        return pok1.atk * SUPEREFFECTIVE;
    }
    if (strcmp(pok1.tipo, "eletrico") == 0 && (strcmp(pok2.tipo, "pedra") == 0))
    {
        return pok1.atk * WEAK;
    }
    if (strcmp(pok1.tipo, "fogo") == 0 && (strcmp(pok2.tipo, "gelo") == 0))
    {
        return pok1.atk * SUPEREFFECTIVE;
    }
    if (strcmp(pok1.tipo, "fogo") == 0 && (strcmp(pok2.tipo, "agua") == 0))
    {
        return pok1.atk * WEAK;
    }
    if (strcmp(pok1.tipo, "agua") == 0 && (strcmp(pok2.tipo, "fogo") == 0))
    {
        return pok1.atk * SUPEREFFECTIVE;
    }
    if (strcmp(pok1.tipo, "agua") == 0 && (strcmp(pok2.tipo, "eletrico") == 0))
    {
        return pok1.atk * WEAK;
    }
    if (strcmp(pok1.tipo, "gelo") == 0 && (strcmp(pok2.tipo, "pedra") == 0))
    {
        return pok1.atk * SUPEREFFECTIVE;
    }
    if (strcmp(pok1.tipo, "gelo") == 0 && (strcmp(pok2.tipo, "fogo") == 0))
    {
        return pok1.atk * WEAK;
    }
    if (strcmp(pok1.tipo, "pedra") == 0 && (strcmp(pok2.tipo, "eletrico") == 0))
    {
        return pok1.atk * SUPEREFFECTIVE;
    }
    if (strcmp(pok1.tipo, "pedra") == 0 && (strcmp(pok2.tipo, "gelo") == 0))
    {
        return pok1.atk * WEAK;
    }
    return pok1.atk;
}

int main()
{
    int N, M;
    Pokemon player1[MAX_POKEMON], player2[MAX_POKEMON];
    // abrindo o arquivo
    FILE *file = fopen("input.txt", "r");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Lendo o numero de pokemons
    fscanf(file, "%d %d", &N, &M);

    // pokemons do player1
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%s %f %f %f %s", player1[i].nome, &player1[i].atk, &player1[i].defesa, &player1[i].vida, player1[i].tipo);
    }

    // pokemons do player2
    for (int i = 0; i < M; i++)
    {
        fscanf(file, "%s %f %f %f %s", player2[i].nome, &player2[i].atk, &player2[i].defesa, &player2[i].vida, player2[i].tipo);
    }

    // imprindo os pokemons dos players
    printf("%d %d \n", N, M);
    for (int i = 0; i < N; i++)
    {
        imprimirPokemon(player1[i]);
    }
    for (int i = 0; i < M; i++)
    {
        imprimirPokemon(player2[i]);
    }

    fclose(file);

    int i = 0, j = 0, turno = 1;
    // batalha entre os players
    float ataque_atacante;
    while (i < N && j < M)
    {
        if (turno == 1)
        {
            ataque_atacante = Balanceamento(player1[i], player2[j]);
            // printf("dano balanceado: %f ", ataque_atacante); // verificaçao do balanceamento
            if (ataque_atacante > player2[j].defesa)
            {
                player2[j].vida -= (ataque_atacante - player2[j].defesa);
            }
            else
            {
                player2[j].vida -= 1;
            }
            // printf("%s atacou %s, vida restante de %s: %f\n", player1[i].nome, player2[j].nome, player2[j].nome, player2[j].vida);

            if (player2[j].vida <= 0)
            {
                printf("%s ", player1[i].nome);
                printf("venceu %s\n", player2[j].nome);
                j++;
            }
            turno = 2;
        }
        else
        {
            ataque_atacante = Balanceamento(player2[j], player1[i]);
            // printf("dano balanceado: %f ", ataque_atacante); // verificaçao do balanceamento
            if (ataque_atacante > player1[i].defesa)
            {
                player1[i].vida -= (ataque_atacante - player1[i].defesa);
            }
            else
            {
                player1[i].vida -= 1;
            }
            // printf("%s atacou %s, vida restande de %s: %f\n", player2[j].nome, player1[i].nome, player1[i].nome, player1[i].vida);
            if (player1[i].vida <= 0)
            {
                printf("%s ", player2[j].nome);
                printf("venceu %s\n", player1[i].nome);
                i++;
            }
            turno = 1;
        }
    }

    if (i < N)
    {
        printf("Jogador 1 venceu\npokemons sobreviventes:\n");
        for (int k = i; k < N; k++)
        {
            printf("%s\n", player1[k].nome);
        }
    }
    else
    {
        printf("Jogador 2 venceu\npokemons sobreviventes:\n");
        for (int k = j; k < M; k++)
        {
            printf("%s\n", player2[k].nome);
        }
    }

    printf("pokemons derrotados:\n");
    for (int k = 0; k < i; k++)
    {
        printf("%s\n", player1[k].nome);
    }
    for (int k = 0; k < j; k++)
    {
        printf("%s\n", player2[k].nome);
    }

    return 0;
}
