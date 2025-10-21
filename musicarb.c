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


//Funções de Criação dos Elementos

Artista *criarartista(char *nome, char *estilo_musical, int numero_albuns){
  Artista *novo = (Artista*)malloc(sizeof(Artista));
    if(novo == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }   
    strcpy(novo->nome, nome);
    strcpy(novo->estilo_musical, estilo_musical);
    novo->numero_albuns = numero_albuns;
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

//-------

//funcoes de inserir 
Artista *inserirartista(Artista **raiz, char *nome, char *estilo_musical, int numero_albuns){
    Artista *novo = criarartista(nome, estilo_musical, numero_albuns);
    if(*raiz == NULL){
        *raiz = novo;
        (*raiz)->cor = BLACK; // raiz sempre preta
        return novo;
    }
    else{
        Artista *atual = *raiz;
        Artista *pai = NULL;
        while(atual != NULL){
            pai = atual;
            if(strcmp(novo->nome, atual->nome) < 0){
                atual = atual->esq;
            }
            else{
                atual = atual->dir;
            }
        }
        
        if(strcmp(novo->nome, pai->nome) < 0){
            pai->esq = novo;
        }
        else{
            pai->dir = novo;
        }
        // Aqui deveria vir a chamada para a funcao de balanceamento da arvore rubro-negra
        return novo;
        
    }
}

Album *inserirAlbum(Album **raiz, char *titulo, int ano_lancamento, int quant_musicas) {
    Album *novo = criaralbum(titulo, ano_lancamento, quant_musicas);

    if (*raiz == NULL) {
        // Primeiro nó da árvore (raiz)
        *raiz = novo;
        (*raiz)->cor = BLACK; // raiz sempre preta
        return *raiz;
    }

    Album *atual = *raiz;
    Album *pai = NULL;

    // Navega pela árvore comparando títulos
    while (atual != NULL) {
        pai = atual;
        if (strcmp(titulo, atual->titulo) < 0)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    // Insere o novo nó à esquerda ou à direita
    if (strcmp(titulo, pai->titulo) < 0)
        pai->esq = novo;
    else
        pai->dir = novo;

    // Aqui poderia vir a função de balanceamento rubro-negra (opcional)
    return novo;
}


//funcoes de buscar

Artista *buscarArtista(Artista *raiz, char *nome, Artista *auxiliar){
    if(raiz == NULL){
        return NULL;
    }
    
    if(strcmp(nome, raiz->nome) < 0){
        auxiliar = buscarArtista(raiz->esq, nome, auxiliar);
    }else if(strcmp(nome, raiz->nome) > 0){
        auxiliar = buscarArtista(raiz-> dir,  nome, auxiliar);
    }else{
        auxiliar = raiz;
    }
    
    return auxiliar;
}

Album *buscarAlbum(Album *raiz, char *titulo, Album *auxAlbum){
    if(raiz == NULL){
        return NULL;
    }

    if(strcmp(titulo, raiz->titulo) < 0){
        auxAlbum = buscarAlbum(raiz->esq, titulo, auxAlbum);
    }else if(strcmp(titulo, raiz->titulo) > 0){
        auxAlbum = buscarAlbum(raiz->dir, titulo, auxAlbum);
    }else{
        auxAlbum = raiz;
    }

    return auxAlbum;
}


//Funções de imprimir

void imprimirArtista(Artista *raiz, char *nome, Artista *auxiliar){

    Artista *achou = buscarArtista(raiz, nome, auxiliar);

    if(achou == NULL){
        printf("\nArtista não encontrado\n");
    }else{
        printf("\n----ENCONTRADO----\n");
        printf("Nome: %s\n", achou->nome);
        printf("Estilo Musical: %s\n", achou->estilo_musical);
        printf("Quantidade de albuns: %d\n", achou->numero_albuns);
    }
}

void imprimirAlbum(Album *raiz, char *titulo, Album *auxAlbum){
    Album *achou = buscarAlbum(raiz, titulo, auxAlbum);

    if(achou == NULL){
        printf("\nAlbum não encontrado\n");
    }else{
        printf("\n----ENCONTRADO----\n");
        printf("Titulo: %s\n", achou->titulo);
        printf("Ano de lancamento: %d\n", achou->ano_lancamento);
        printf("Quantidade de musicas: %d\n", achou->quant_musicas);
    }
}

//funcoes de remover


//Menu
void menu(){
    printf("\n---MENU---\n");
    printf("1. Inserir Artista\n");
    printf("2. Inserir Album\n");
    printf("3. Buscar Artista\n");
    printf("4. Buscar Album\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
    int opcao;
    scanf("%d", &opcao);
}