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

//funcoes de rotacao
void *rotacaoesquerda(No *raiz, No *J){
    No *filhodir = J->dir;
    J->dir = filhodir->esq;
    if(filhodir->esq != NULL){
        filhodir->esq->pai = J;
    }
    filhodir->pai = J->pai;
    if(J->pai == NULL){
        raiz = filhodir;
    } else if(J == J->pai->esq){
        J->pai->esq = filhodir;
    } else {
        J->pai->dir = filhodir;
    }
    filhodir->esq = J;
    J->pai = filhodir;

}

void rotacaodireita(No *raiz, No *J){
    No *filhoesq = J->esq;
    J->esq = filhoesq->dir;
    if(filhoesq->dir != NULL){
        filhoesq->dir->pai = J;
    }
    filhoesq->pai = J->pai;
    if(J->pai == NULL){
        raiz = filhoesq;
    } else if(J == J->pai->dir){
        J->pai->dir = filhoesq;
    } else {
        J->pai->esq = filhoesq;
    }
    filhoesq->dir = J;
    J->pai = filhoesq;

}
No *Arvartista(Artista* artista){
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

No *Arvalbum(Album* album){
    No *novo = (No*)malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    novo->artista = album;
    novo->cor = RED; // novo no sempre vermelho
    novo->esq = NULL;
    novo->dir = NULL; 
    novo->pai = NULL;
    return novo;

}

//-------

//funcoes de inserir 
No *inserirartista(No **raiz, char *nome, char *estilo_musical, int numero_albuns){
    Artista *novo = criarartista(nome, estilo_musical, numero_albuns);
    if(*raiz == NULL){
        *raiz = Arvartista(novo);
        (*raiz)->cor = BLACK; // raiz sempre preta
        return novo;
    }
    else{
        No *atual = *raiz;
        No *pai = NULL;
        while(atual != NULL){
            pai = atual;
            if(strcmp(novo->nome, atual->artista->nome) < 0){
                atual = atual->esq;
            }
            else{
                atual = atual->dir;
            }
        }
        No *novo_no = Arvartista(novo);
        novo_no->pai = pai;
        if(strcmp(novo->nome, pai->artista->nome) < 0){
            pai->esq = novo_no;
        }
        else{
            pai->dir = novo_no;
        }
        // Aqui deveria vir a chamada para a funcao de balanceamento da arvore rubro-negra
        return novo;
        
    }
}

No *inserirAlbum(No **raiz, char *titulo, int ano_lancamento, int quant_musicas) {
    Album *novo = criaralbum(titulo, ano_lancamento, quant_musicas);

    if (*raiz == NULL) {
        *raiz = Arvalbum(novo);
        (*raiz)->cor = BLACK; // raiz sempre preta
        return *raiz;
    } else {
        No *atual = *raiz;
        No *pai = NULL;

        //compara os titulos
        while (atual != NULL) {
            pai = atual;
            Album *atualAlbum = (Album*) atual->artista; //acessar artista
            if (strcmp(titulo, atualAlbum->titulo) < 0)
                atual = atual->esq;
            else
                atual = atual->dir;
        }

        No *novo_no = Arvalbum(novo);
        novo_no->pai = pai;

        Album *paiAlbum = (Album*) pai->artista;
        if (strcmp(titulo, paiAlbum->titulo) < 0)
            pai->esq = novo_no;
        else
            pai->dir = novo_no;

       //colocar baleanceamento aqui
        return novo_no;
    }
}


void inserirmusica(Album *album, char *titulo, char *duracao){
    if(album == NULL){
        printf("album nao existe\n");
        return;
    }

    Musica *novo = criarmusica(titulo, duracao);
    //se nao tiver musicas ainda
    if(album->limusicas == NULL){
        album->limusicas = novo;
    } else {
        //percorrer ate o final da lista
        Musica *atual = album->limusicas;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    album->quant_musicas++;
}


