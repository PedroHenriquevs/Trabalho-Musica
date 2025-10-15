#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum Color {RED, BLACK};
typedef struct artista{
    char nome[100];
    char estilo_musical[100];
    int numero_albuns;
    Album *raizalbum;
    struct artista *esq;
    struct artista *dir;
    enum Color cor;

}Artista;

typedef struct album{
    char titulo[100];
    int ano_lancamento;
    int quant_musicas;
    Musica *limusicas;
    struct album *esq;
    struct album *dir;
    enum Color cor;
}Album;

typedef struct musica{
    char titulo[100];
    char duracao[10];
    struct musica *prox;
}Musica;

typedef struct no{
    Artista *artista;
    enum Color cor;
    struct no *esq, *dir, *pai;
} No;


//funcoes criar

Artista *criarartista(char *nome, char *estilo_musical, int numero_albuns){
  Artista *novo = (Artista*)malloc(sizeof(Artista));
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }   
    strcpy(novo->nome, nome);
    strcpy(novo->estilo_musical, estilo_musical);
    novo->numero_albuns = 0;
    novo->raizalbum = NULL;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->cor = RED; // novo no sempre vermelho
    return novo;
}

Album *criaralbum(char *titulo, int ano_lancamento, int quant_musicas){
    Album *novo = (Album*)malloc(sizeof(Album));
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    strcpy(novo->titulo, titulo);
    novo->ano_lancamento = ano_lancamento;
    novo->quant_musicas = quant_musicas;
    novo->limusicas = NULL;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->cor = RED; // novo no sempre vermelho
    return novo;
}

Musica *criarmusica(char *titulo, char *duracao){
    Musica *novo = (Musica*)malloc(sizeof(Musica));
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    strcpy(novo->titulo, titulo);
    strcpy(novo->duracao, duracao);
    return novo;
}

No *criarno(Artista* artista){
    No *novo = (No*)malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    novo->artista = artista;
    novo->cor = RED; // novo no sempre vermelho
    novo->esq = NULL;
    novo->dir = NULL; 
    novo->pai = NULL;
    return novo;

}

//funcoes de inserir 

