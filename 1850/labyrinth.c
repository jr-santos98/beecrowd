#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lista de adjacencia para o grafo
typedef struct lista_adjacencias {
    int vertice;
    char me;
    struct lista_adjacencias *prox;
} Lista;
typedef Lista *p_lista;

// Grafo para o problema
typedef struct {
    p_lista *vertices;
    int n;
    int m;
} Grafo;
typedef Grafo *p_grafo;

// No da Fila do bfs
typedef struct no_fila{
    int vertice;
    struct no_fila *prox;
} No_fila;
typedef No_fila *p_no_fila;

// Fila do bfs
typedef struct fila_bfs {
    p_no_fila ini;
    p_no_fila fim;
} Fila;
typedef Fila *p_fila;

// Dados do bfs para cada vertice
typedef struct {
    int *visitado;
    int *dist;
    int A, B, C, D, E, F, G;
} Data;
typedef Data *p_data;

void inicializa_data(p_data data, int tamanho) {
    data->A = 0; data->B = 0; data->C = 0;
    data->D = 0; data->E = 0; data->F = 0;
    data->G = 0;
    data->visitado = malloc(tamanho*sizeof(int));
    data->dist = malloc(tamanho*sizeof(int));
    for (int i=0; i<tamanho; i++) {
        data->visitado[i] = 0;
        data->dist[i] = -1;
    }
}

void marcar_visitado(p_data data, int vertice, int d_u) {
    data->visitado[vertice] = 1;
    data->dist[vertice] = d_u + 1;
}

int esta_visitado(p_data data, int vertice) {
    return data->visitado[vertice];
}

void adicionar_a_fila(p_fila fila, int vertice) {
    p_no_fila f;
    f = malloc(sizeof(No_fila));
    f->vertice = vertice;
    f->prox = NULL;
    if (fila->ini == NULL) {
        fila->ini = f;
        fila->fim = f;
    }
    else {
        fila->fim->prox = f;
        fila->fim = f;
    }
}

int remover_da_fila(p_fila fila) {
    int v;
    p_no_fila f;
    f = fila->ini;
    v = f->vertice;
    fila->ini = f->prox;
    free(f);
    return v;
}

int caminho_livre(p_data data, char adj) {
    int status = 1;

    // Coletar a chave
    if (adj == 'a') data->A = 1;
    else if (adj == 'b') data->B = 1;
    else if (adj == 'c') data->C = 1;
    else if (adj == 'd') data->D = 1;
    else if (adj == 'e') data->E = 1;
    else if (adj == 'f') data->F = 1;
    else if (adj == 'g') data->G = 1;

    // Verificar portas
    // if (adj == 'A' && !data->A) status = 0;
    // else if (adj == 'B' && !data->B) status = 0;
    // else if (adj == 'C' && !data->C) status = 0;
    // else if (adj == 'D' && !data->D) status = 0;
    // else if (adj == 'E' && !data->E) status = 0;
    // else if (adj == 'F' && !data->F) status = 0;
    // else if (adj == 'G' && !data->G) status = 0;
    
    return status;
}

void imprime_dados(p_data data, int n, int cols) {
    for (int i=0; i<n; i++) {
        if (i%cols == 0) printf("\n");
        printf("%2d ", data->dist[i]);
    }
    printf("\n");
}

void bfs(p_grafo grafo, int vertice_inicial) {
    // Inicializa a fila e os dados
    int tamanho = grafo->n*grafo->m;
    p_fila fila;
    fila = malloc(sizeof(Fila));
    fila->ini = NULL; fila->fim = NULL;
    p_data data;
    data = malloc(sizeof(Data));
    inicializa_data(data, tamanho);

    // Marca o vértice inicial como visitado
    marcar_visitado(data, vertice_inicial, data->dist[vertice_inicial]);
    adicionar_a_fila(fila, vertice_inicial);

    // Enquanto a fila não estiver vazia
    while (fila->ini != NULL) {
        // Remove o primeiro elemento da fila
        int vertice = remover_da_fila(fila);

        // Visita o vértice
        // printf("Visitando o vértice %d\n", grafo->vertices[vertice]->vertice);

        // Adiciona os vértices adjacentes não visitados à fila
        for (p_lista adjacente = grafo->vertices[vertice]; adjacente != NULL; adjacente = adjacente->prox) {
            char adj = grafo->vertices[adjacente->vertice]->me;
            // printf("%c ", adj);
            if (!esta_visitado(data, adjacente->vertice) && adj != '#' && caminho_livre(data, adj)) {
                marcar_visitado(data, adjacente->vertice, data->dist[vertice]);
                adicionar_a_fila(fila, adjacente->vertice);
            }
        }
    }

    imprime_dados(data, tamanho, grafo->m);
}

int main() {
    char maze[100][101]; // Assumindo que o tamanho máximo é 100x100 com um caractere de nova linha no final de cada linha
    int rows = 0;
    int cols = 0;
    int tamanho, vizinhos[4], vertice_inicial, vertice_final;
    p_grafo grafo;
    grafo = malloc(sizeof(Grafo));

    // Ler a entrada até o final do arquivo ou o número máximo de linhas
    while (rows < 100 && fgets(maze[rows], 101, stdin) != NULL) {
        rows++;
    }

    for (int i=0; maze[0][i] != '\0'; i++) cols++;

    // Print the maze
    for (int i = 0; i < rows; i++) {
        printf("%s", maze[i]);
    }

    // Normalizando valor
    if (strcmp(maze[rows-1], "end-of-file") == 0) cols--;
    rows--;

    printf("\nLabirinto tem %d por %d\n", rows, cols);

    // Definindo valores do grafo
    grafo->n = rows; 
    grafo->m = cols;
    tamanho = rows*cols;
    vertice_inicial = -1;
    vertice_final = -1;
    grafo->vertices = malloc(tamanho*sizeof(p_lista));
    for (int i=0; i<tamanho; i++) grafo->vertices[i] = NULL;

    // Adiona os adjacentes
    for (int i=0; i<tamanho; i++) {
        vizinhos[0] = i+1;
        vizinhos[1] = i+cols;
        vizinhos[2] = i-1;
        vizinhos[3] = i-cols;
        // printf("O vertice %d é vizinho de: ", i);
        for (int r=0; r<4; r++) {
            // printf("i=%d, cold=%d, %d / %d\n",i, cols, i/cols, (i+1)/cols);
            if ( (r==0 && i/cols == (i+1)/cols) || (r==1 && (i+cols)/cols < rows) || 
                    (r==2 && i-1 >= 0 && i/cols == (i-1)/cols) || (r==3 && i-cols >= 0) ) {
                // printf("%d ", vizinhos[r]);
                p_lista vertice;
                p_lista vertice_aux;
                vertice = malloc(sizeof(Lista));
                vertice->me = maze[i/cols][i%cols];
                vertice->vertice = vizinhos[r];
                vertice->prox = NULL;
                if (grafo->vertices[i] == NULL)
                    grafo->vertices[i] = vertice;
                else {
                    vertice_aux = grafo->vertices[i];
                    while (vertice_aux->prox != NULL) vertice_aux = vertice_aux->prox;
                    vertice_aux->prox = vertice;
                }
                if (vertice->me == '@') vertice_inicial = i;
                else if (vertice->me == '*') vertice_final = i;
            }
        }
        // printf("\n");
    }

    printf("Vertice inicial é %d, e o final é %d\n", vertice_inicial, vertice_final);
    // Imprime valor, pode apagar
    // int aux = 2;
    // p_lista vertice_aux;
    // for (int i=0; i<cols; i++) {
    //     printf("%c", grafo->vertices[aux*cols+i]->me);
    //     vertice_aux = grafo->vertices[aux*cols+i];
    //     for (int r=0; r<20;r++) {
    //         printf("%d é vizinho de %d, ",aux*cols+i, vertice_aux->vertice);
    //         if (vertice_aux->prox == NULL) break;
    //         else vertice_aux = vertice_aux->prox;
    //     }
    // }
    // printf("\n");

    // Realiza a busca em largura
    bfs(grafo, vertice_inicial);

    return 0;
}
