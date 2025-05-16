//--------------------------------------------------------------
// INTEGRANTES: Fulano de Tal e Cicrano de Tal
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// INFORME O NRO DO GRUPO CONFORME PLANILHA DIVULGADA
int grupo() {
  return 36;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 14748678;  // substitua pelo seu n�mero USP
}

// E O SEGUNDO NROUSP AQUI, SE HOUVER
int nroUSP2() {
    return 0;  // se EP individual, mantenha zero
}

// elemento da lista de resposta - N�O ALTERE ESTA DEFINI��O
typedef struct estr {
      int adj; // um n�mero de v�rtice
      struct estr *prox;
} NO;

// Defini��o de n� para a lista de adjac�ncias do grafo
typedef struct adj_node {
    int vertex;
    struct adj_node* next;
} AdjNode;

// Fun��o para inserir uma aresta na lista de adjac�ncias
void addEdge(AdjNode **adjList, int src, int dest) {
    AdjNode *newNode = (AdjNode*) malloc(sizeof(AdjNode));
    if (newNode == NULL) exit(1);
    newNode->vertex = dest;
    newNode->next = adjList[src];
    adjList[src] = newNode;
}

// Fun��o de BFS para calcular as dist�ncias (n�mero de arestas) a partir do v�rtice start
void bfs(int start, int V, AdjNode **adjList, int *dist) {
    int *queue = (int*) malloc((V+1) * sizeof(int));
    if (queue == NULL) exit(1);
    int front = 0, rear = 0;

    // Inicializa as dist�ncias com -1 (n�o alcan�ado)
    for (int i = 1; i <= V; i++) {
        dist[i] = -1;
    }
    dist[start] = 0;
    queue[rear++] = start;

    while(front < rear) {
        int current = queue[front++];
        AdjNode *temp = adjList[current];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }
    free(queue);
}

//---------------------------------------------------------
// Implementa��o da fun��o solicitada
//---------------------------------------------------------
NO *equidistantes(int V, int A, int ij[], int v1, int v2)
{
    NO* resp = NULL;

    // Cria a lista de adjac�ncias
    AdjNode **adjList = (AdjNode**) malloc((V+1) * sizeof(AdjNode*));
    if (adjList == NULL) exit(1);
    for (int i = 1; i <= V; i++) {
        adjList[i] = NULL;
    }

    // Constroi o grafo a partir do vetor ij[]
    for (int i = 0; i < 2*A; i += 2) {
        int u = ij[i];
        int w = ij[i+1];
        addEdge(adjList, u, w);
        addEdge(adjList, w, u);
    }

    // Aloca vetores de dist�ncias
    int *dist1 = (int*) malloc((V+1) * sizeof(int));
    int *dist2 = (int*) malloc((V+1) * sizeof(int));
    if (dist1 == NULL || dist2 == NULL) exit(1);

    // Executa BFS a partir de v1 e v2
    bfs(v1, V, adjList, dist1);
    bfs(v2, V, adjList, dist2);

    // Monta a lista de resposta
    for (int i = 1; i <= V; i++) {
        if (i == v1 || i == v2) continue;
        if (dist1[i] != -1 && dist1[i] == dist2[i]) {
            NO *newNode = (NO*) malloc(sizeof(NO));
            if (newNode == NULL) exit(1);
            newNode->adj = i;
            newNode->prox = resp;
            resp = newNode;
        }
    }

    // Libera recursos
    free(dist1);
    free(dist2);
    for (int i = 1; i <= V; i++) {
        AdjNode *cur = adjList[i];
        while (cur) {
            AdjNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adjList);

    return resp;
}

//---------------------------------------------------------
// Fun��o main modificada para chamar conforme modelo.txt
//---------------------------------------------------------
int main() {

}
