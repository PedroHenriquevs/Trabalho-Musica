#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Color
{
    RED,
    BLACK
};

typedef struct musica
{
    char titulo[100];
    char duracao[10];
    struct musica *prox;
} Musica;

typedef struct album
{
    char titulo[100];
    int ano_lancamento;
    int quant_musicas;
    Musica *limusicas;
    struct album *esq;
    struct album *dir;
    enum Color cor;
} Album;

typedef struct artista
{
    char nome[100];
    char estilo_musical[100];
    int numero_albuns;
    Album *raizalbum;
    struct artista *pai;
    struct artista *esq;
    struct artista *dir;
    enum Color cor;

} Artista;

Artista *raizArtista = NULL;
Album *raizAlbum = NULL;

// funções de rotação de Artista
Artista *rotacaoEsquerda(Artista *raiz, Artista *x)
{
    Artista *y = x->dir;
    x->dir = y->esq;
    if (y->esq)
        y->esq->pai = x;

    y->pai = x->pai;
    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;

    return raiz;
}

Artista *rotacaoDireita(Artista *raiz, Artista *x)
{
    Artista *y = x->esq;
    x->esq = y->dir;
    if (y->dir)
        y->dir->pai = x;

    y->pai = x->pai;
    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->dir)
        x->pai->dir = y;
    else
        x->pai->esq = y;

    y->dir = x;
    x->pai = y;

    return raiz;
}

// funções de rotação de Album

Album *rotacaoEsquerdaAlbum(Album *raiz, Album *x)
{
    Album *y = x->dir;
    x->dir = y->esq;
    y->esq = x;

    // Ajusta a raiz se necessário
    if (raiz == x)
        raiz = y;

    return raiz;
}

Album *rotacaoDireitaAlbum(Album *raiz, Album *x)
{
    Album *y = x->esq;
    x->esq = y->dir;
    y->dir = x;

    // Ajusta a raiz se necessário
    if (raiz == x)
        raiz = y;

    return raiz;
}

// Funções de Criação dos Elementos

Artista *criarartista(char *nome, char *estilo_musical, int numero_albuns)
{
    Artista *novo = (Artista *)malloc(sizeof(Artista));
    if (novo == NULL)
    {
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

Album *criaralbum(char *titulo, int ano_lancamento, int quant_musicas)
{
    Album *novo = (Album *)malloc(sizeof(Album));
    if (novo == NULL)
    {
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
    novo->limusicas = NULL;
    return novo;
}

Musica *criarmusica(char *titulo, char *duracao)
{
    Musica *novo = (Musica *)malloc(sizeof(Musica));
    if (novo == NULL)
    {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    strcpy(novo->titulo, titulo);
    strcpy(novo->duracao, duracao);
    return novo;
}

//-------

// funcoes de inserir

Artista *inserirartista(Artista **raiz, char *nome, char *estilo_musical, int numero_albuns)
{
    Artista *novo = criarartista(nome, estilo_musical, numero_albuns);
    if (*raiz == NULL)
    {
        *raiz = novo;
        (*raiz)->cor = BLACK; // raiz sempre preta
        return novo;
    }
    else
    {
        Artista *atual = *raiz;
        Artista *pai = NULL;
        while (atual != NULL)
        {
            pai = atual;
            if (strcmp(novo->nome, atual->nome) < 0)
            {
                atual = atual->esq;
            }
            else
            {
                atual = atual->dir;
            }
        }

        if (strcmp(novo->nome, pai->nome) < 0)
        {
            pai->esq = novo;
        }
        else
        {
            pai->dir = novo;
        }
        // Aqui deveria vir a chamada para a funcao de balanceamento da arvore rubro-negra
        return novo;
    }
}

Album *inserirAlbumParaArtista(Artista *artista, char *titulo, int ano_lancamento, int quant_musicas)
{
    if (!artista)
        return NULL;

    Album *novo = criaralbum(titulo, ano_lancamento, quant_musicas);

    if (!artista->raizalbum)
    {
        artista->raizalbum = novo;
        artista->raizalbum->cor = BLACK; // raiz sempre preta
        return novo;
    }

    Album *atual = artista->raizalbum;
    Album *pai = NULL;

    while (atual)
    {
        pai = atual;
        if (strcmp(titulo, atual->titulo) < 0)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    if (strcmp(titulo, pai->titulo) < 0)
        pai->esq = novo;
    else
        pai->dir = novo;

    return novo;
}

// funcoes de buscar

Artista *buscarArtista(Artista *raiz, char *nome, Artista *auxiliar)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (strcmp(nome, raiz->nome) < 0)
    {
        auxiliar = buscarArtista(raiz->esq, nome, auxiliar);
    }
    else if (strcmp(nome, raiz->nome) > 0)
    {
        auxiliar = buscarArtista(raiz->dir, nome, auxiliar);
    }
    else
    {
        auxiliar = raiz;
    }

    return auxiliar;
}

Album *buscarAlbum(Album *raiz, char *titulo, Album *auxAlbum)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (strcmp(titulo, raiz->titulo) < 0)
    {
        auxAlbum = buscarAlbum(raiz->esq, titulo, auxAlbum);
    }
    else if (strcmp(titulo, raiz->titulo) > 0)
    {
        auxAlbum = buscarAlbum(raiz->dir, titulo, auxAlbum);
    }
    else
    {
        auxAlbum = raiz;
    }

    return auxAlbum;
}

Musica *buscarMusica(Album *album, char *titulo) {
    if (!album || !album->limusicas)
        return NULL;

    Musica *atual = album->limusicas;
    while (atual) {
        if (strcmp(atual->titulo, titulo) == 0)
            return atual;
        atual = atual->prox;
    }

    return NULL; // não encontrada
}

void inserirMusica()
{
    char nomeArtista[100];
    char tituloAlbum[100];
    char tituloMusica[100];
    char duracao[10];

    // Verificar artista
    printf("Digite o nome do artista: ");
    fgets(nomeArtista, sizeof(nomeArtista), stdin);
    nomeArtista[strcspn(nomeArtista, "\n")] = 0;

    Artista *auxArtista = buscarArtista(raizArtista, nomeArtista, NULL);
    if (!auxArtista)
    {
        printf("Artista nao encontrado!\n");
        return;
    }

    // Verificar se o artista tem albuns
    if (!auxArtista->raizalbum)
    {
        printf("O artista nao possui nenhum album cadastrado!\n");
        return;
    }

    // Perguntar qual album
    printf("Digite o titulo do album para adicionar a musica: ");
    fgets(tituloAlbum, sizeof(tituloAlbum), stdin);
    tituloAlbum[strcspn(tituloAlbum, "\n")] = 0;

    Album *auxAlbum = buscarAlbum(auxArtista->raizalbum, tituloAlbum, NULL);
    if (!auxAlbum)
    {
        printf("Album nao encontrado!\n");
        return;
    }

    // Contar quantas músicas já existem
    int contMusicas = 0;
    Musica *p = auxAlbum->limusicas;
    while (p)
    {
        contMusicas++;
        p = p->prox;
    }

    if (contMusicas >= auxAlbum->quant_musicas)
    {
        printf("Album ja atingiu o numero maximo de musicas (%d)!\n", auxAlbum->quant_musicas);
        return;
    }

    // Solicitar dados da música
    printf("Digite o titulo da musica: ");
    fgets(tituloMusica, sizeof(tituloMusica), stdin);
    tituloMusica[strcspn(tituloMusica, "\n")] = 0;

    printf("Digite a duracao da musica (ex: 03:45): ");
    fgets(duracao, sizeof(duracao), stdin);
    duracao[strcspn(duracao, "\n")] = 0;

    // Criar a música
    Musica *nova = criarmusica(tituloMusica, duracao);

    // Inserir no final da lista encadeada
    if (!auxAlbum->limusicas)
    {
        auxAlbum->limusicas = nova;
    }
    else
    {
        p = auxAlbum->limusicas;
        while (p->prox)
            p = p->prox;
        p->prox = nova;
    }

    printf("Musica adicionada com sucesso ao album '%s'!\n", auxAlbum->titulo);
}

// Funções de imprimir

void imprimirArtista(Artista *raiz, char *nome, Artista *auxiliar)
{

    Artista *achou = buscarArtista(raiz, nome, auxiliar);

    if (achou == NULL)
    {
        printf("\nArtista não encontrado\n");
    }
    else
    {
        printf("\n----ENCONTRADO----\n");
        printf("Nome: %s\n", achou->nome);
        printf("Estilo Musical: %s\n", achou->estilo_musical);
        printf("Quantidade de albuns: %d\n", achou->numero_albuns);
    }
}

void imprimirAlbum(Album *raiz, char *titulo, Album *auxAlbum)
{
    Album *achou = buscarAlbum(raiz, titulo, auxAlbum);

    if (achou == NULL)
    {
        printf("\nAlbum não encontrado\n");
    }
    else
    {
        printf("\n----ENCONTRADO----\n");
        printf("Titulo: %s\n", achou->titulo);
        printf("Ano de lancamento: %d\n", achou->ano_lancamento);
        printf("Quantidade de musicas: %d\n", achou->quant_musicas);
    }
}

void imprimirMusica(Album *album, char *titulo) {
    Musica *musica = buscarMusica(album, titulo);
    if (!musica) {
        printf("Musica '%s' nao encontrada no album '%s'.\n", titulo, album->titulo);
        return;
    }

    printf("\n----MUSICA ENCONTRADA----\n");
    printf("Titulo: %s\n", musica->titulo);
    printf("Duracao: %s\n", musica->duracao);
}

// funcoes de remover
// Remover Artista
Artista *pai(Artista *n) { return n ? n->pai : NULL; }
Artista *avo(Artista *n) { return pai(n) ? pai(n)->pai : NULL; }
Artista *irmao(Artista *n)
{
    Artista *p = pai(n);
    if (!p)
        return NULL;
    return n == p->esq ? p->dir : p->esq;
}

Artista *minimo(Artista *n)
{
    while (n->esq)
        n = n->esq;
    return n;
}

Artista *corrigirRemocao(Artista *raiz, Artista *filhoQueSobe)
{
    while (filhoQueSobe != raiz && (filhoQueSobe == NULL || filhoQueSobe->cor == BLACK))
    {
        Artista *p = pai(filhoQueSobe);
        if (filhoQueSobe == p->esq)
        {
            Artista *irmao = p->dir;
            if (irmao->cor == RED)
            {
                irmao->cor = BLACK;
                p->cor = RED;
                raiz = rotacaoEsquerda(raiz, p);
                irmao = p->dir;
            }
            if ((!irmao->esq || irmao->esq->cor == BLACK) &&
                (!irmao->dir || irmao->dir->cor == BLACK))
            {
                irmao->cor = RED;
                filhoQueSobe = p;
            }
            else
            {
                if (!irmao->dir || irmao->dir->cor == BLACK)
                {
                    if (irmao->esq)
                        irmao->esq->cor = BLACK;
                    irmao->cor = RED;
                    raiz = rotacaoDireita(raiz, irmao);
                    irmao = p->dir;
                }
                irmao->cor = p->cor;
                p->cor = BLACK;
                if (irmao->dir)
                    irmao->dir->cor = BLACK;
                raiz = rotacaoEsquerda(raiz, p);
                filhoQueSobe = raiz;
            }
        }
        else
        {
            Artista *irmao = p->esq;
            if (irmao->cor == RED)
            {
                irmao->cor = BLACK;
                p->cor = RED;
                raiz = rotacaoDireita(raiz, p);
                irmao = p->esq;
            }
            if ((!irmao->esq || irmao->esq->cor == BLACK) &&
                (!irmao->dir || irmao->dir->cor == BLACK))
            {
                irmao->cor = RED;
                filhoQueSobe = p;
            }
            else
            {
                if (!irmao->esq || irmao->esq->cor == BLACK)
                {
                    if (irmao->dir)
                        irmao->dir->cor = BLACK;
                    irmao->cor = RED;
                    raiz = rotacaoEsquerda(raiz, irmao);
                    irmao = p->esq;
                }
                irmao->cor = p->cor;
                p->cor = BLACK;
                if (irmao->esq)
                    irmao->esq->cor = BLACK;
                raiz = rotacaoDireita(raiz, p);
                filhoQueSobe = raiz;
            }
        }
    }
    if (filhoQueSobe)
        filhoQueSobe->cor = BLACK;
    return raiz;
}

Artista *removerArtista(Artista *raiz, char *nome)
{
    Artista *removido = raiz;

    // Buscar nó pelo nome
    while (removido && strcmp(removido->nome, nome) != 0)
    {
        if (strcmp(nome, removido->nome) < 0)
            removido = removido->esq;
        else
            removido = removido->dir;
    }

    if (!removido)
        return raiz; // não encontrado

    Artista *sucessor, *filhoQueSobe;
    enum Color corOriginal = removido->cor;

    // Caso com zero ou um filho
    if (!removido->esq)
    {
        filhoQueSobe = removido->dir;
        if (filhoQueSobe)
            filhoQueSobe->pai = removido->pai;

        if (!removido->pai)
            raiz = filhoQueSobe;
        else if (removido == removido->pai->esq)
            removido->pai->esq = filhoQueSobe;
        else
            removido->pai->dir = filhoQueSobe;
    }
    else if (!removido->dir)
    {
        filhoQueSobe = removido->esq;
        if (filhoQueSobe)
            filhoQueSobe->pai = removido->pai;

        if (!removido->pai)
            raiz = filhoQueSobe;
        else if (removido == removido->pai->esq)
            removido->pai->esq = filhoQueSobe;
        else
            removido->pai->dir = filhoQueSobe;
    }
    else
    {
        // Dois filhos → encontrar sucessor
        sucessor = minimo(removido->dir);
        corOriginal = sucessor->cor;
        filhoQueSobe = sucessor->dir;

        if (sucessor->pai == removido)
        {
            if (filhoQueSobe)
                filhoQueSobe->pai = sucessor;
        }
        else
        {
            if (filhoQueSobe)
                filhoQueSobe->pai = sucessor->pai;
            sucessor->pai->esq = filhoQueSobe;
            sucessor->dir = removido->dir;
            if (sucessor->dir)
                sucessor->dir->pai = sucessor;
        }

        if (!removido->pai)
            raiz = sucessor;
        else if (removido == removido->pai->esq)
            removido->pai->esq = sucessor;
        else
            removido->pai->dir = sucessor;

        sucessor->pai = removido->pai;
        sucessor->esq = removido->esq;
        if (sucessor->esq)
            sucessor->esq->pai = sucessor;
        sucessor->cor = removido->cor;
    }

    free(removido);

    if (corOriginal == BLACK)
        raiz = corrigirRemocao(raiz, filhoQueSobe);

    return raiz;
}

// Menu
void menu()
{
    printf("\n---MENU---\n");
    printf("1. Inserir Artista\n");
    printf("2. Inserir Album\n");
    printf("3. Buscar Artista\n");
    printf("4. Buscar Album\n");
    printf("5. Remover Artista\n");
    printf("6. Remover Album\n");
    printf("7. Adicionar Musica\n");
    printf("8. Buscar Musica\n");
    printf("9. Sair\n");
    printf("Escolha uma opcao: ");

    int opcao;
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &opcao);

    switch (opcao)
    {
    case 1:
    {
        char nome[100];
        char estilo_musical[100];
        int numero_albuns;

        printf("Digite o nome do artista: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0;

        printf("Digite o estilo musical: ");
        fgets(estilo_musical, sizeof(estilo_musical), stdin);
        estilo_musical[strcspn(estilo_musical, "\n")] = 0;

        printf("Digite o numero de albuns: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &numero_albuns);

        inserirartista(&raizArtista, nome, estilo_musical, numero_albuns);
        printf("Artista inserido com sucesso!\n");
        break;
    }
    case 2:
    {
        char nomeArtista[100];
        char titulo[100];
        int ano_lancamento;
        int quant_musicas;

        printf("Digite o nome do artista: ");
        fgets(nomeArtista, sizeof(nomeArtista), stdin);
        nomeArtista[strcspn(nomeArtista, "\n")] = 0;

        Artista *auxArtista = buscarArtista(raizArtista, nomeArtista, NULL);
        if (!auxArtista)
        {
            printf("Artista nao encontrado!\n");
            break;
        }

        printf("Digite o titulo do album: ");
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = 0;

        printf("Digite o ano de lancamento: ");
        scanf("%d", &ano_lancamento);
        getchar();  // Limpar o buffer

        printf("Digite a quantidade de musicas: ");
        scanf("%d", &quant_musicas);
        getchar();  // Limpar o buffer

        inserirAlbumParaArtista(auxArtista, titulo, ano_lancamento, quant_musicas);
        printf("Album inserido com sucesso!\n");
        break;
    }
    case 3:
    {
        char nomeBusca[100];
        printf("Digite o nome do artista para buscar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = 0;

        Artista *auxiliar = NULL;
        imprimirArtista(raizArtista, nomeBusca, auxiliar);
        break;
    }
    case 4:
    {
        char titulo[100];
        printf("Digite o titulo do album para buscar: ");
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = 0;

        Album *auxAlbum = NULL;
        imprimirAlbum(raizAlbum, titulo, auxAlbum);
        break;
    }
    case 5:
    {
        char nome[100];
        printf("Digite o nome do artista para remover: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0;

        raizArtista = removerArtista(raizArtista, nome);
        printf("Remocao realizada!\n");
        break;
    }
    case 6:
        // Implementar remocao de album (similar ao artista)
        break;
    case 7:
        inserirMusica();
        break;
    case 8:{
        char titulo[100];
        Album *retorno = NULL;
        printf("Digite o titulo da musica para buscar: ");
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = 0;

        buscarAlbum(raizAlbum, titulo, retorno);
        if (!retorno) {
            printf("Album nao encontrado!\n");
            break;
        }

        imprimirMusica(retorno, titulo);
        break;
    }
        
    case 9:{
        printf("Saindo...\n");
        exit(0);
        break;
    }
    default:
        printf("Opcao invalida!\n");
        break;
    }
}

int main()
{
    while (1)
    {
        menu();
    }
    return 0;
}