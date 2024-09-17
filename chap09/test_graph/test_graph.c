#include <stdio.h>
#include <stdlib.h>

#include <container/graph.h>

struct Graph_Entry {
    struct Vertex v;
    char data;
};

static struct Edge *Graph_CreateEdge(
    struct Graph_Entry *from, struct Graph_Entry *to, int weight)
{
    struct Edge *e;

    e = malloc(sizeof(*e));
    Edge_Init(e);

    e->from = &from->v;
    e->to = &to->v;
    e->weight = weight;

    return e;
}

static struct Graph_Entry *Graph_CreateVertex(char data)
{
    struct Graph_Entry *entry;

    entry = malloc(sizeof(*entry));

    Vertex_Init(&entry->v);
    entry->data = data;

    return entry;
}

static void Graph_DestroyVertex(struct Graph_Entry *entry)
{
    struct DLL_Node *node = entry->v.adjacency.next;

    while (node != &entry->v.adjacency) {
        struct DLL_Node *next = node->next;
        struct Edge *e = CONTAINER_OF(node, struct Edge, node);

        free(e);
        node = next;
    }

    free(entry);
}

static void Graph_PrintVertex(struct Graph_Entry *entry)
{
    struct DLL_Node *node = entry->v.adjacency.next;

    while (node != &entry->v.adjacency) {
        struct Edge *e = CONTAINER_OF(node, struct Edge, node);
        struct Graph_Entry *to = CONTAINER_OF(e->to, struct Graph_Entry, v);

        printf("%c[%d] ", to->data, e->weight);

        node = node->next;
    }

    printf("\n");
}

static struct Graph *Graph_CreateGraph(void)
{
    struct Graph *g;

    g = malloc(sizeof(*g));
    Graph_Init(g);

    return g;
}

static void Graph_DestroyGraph(struct Graph *g)
{
    struct DLL_Node *node = g->head.next;

    while (node != &g->head) {
        struct DLL_Node *next = node->next;
        struct Graph_Entry *entry
            = CONTAINER_OF(node, struct Graph_Entry, v.node);

        Graph_DestroyVertex(entry);
        node = next;
    }

    free(g);
}

static void Grpah_PrintGraph(struct Graph *g)
{
    struct DLL_Node *node = g->head.next;

    while (node != &g->head) {
        struct Graph_Entry *entry
            = CONTAINER_OF(node, struct Graph_Entry, v.node);

        printf("%c : ", entry->data);

        Graph_PrintVertex(entry);
        node = node->next;
    }
}

int main(int argc, char *argv[])
{
    /* 그래프 생성 */
    struct Graph *g = Graph_CreateGraph();

    /* 정점 생성 */
    struct Graph_Entry *v1 = Graph_CreateVertex('1');
    struct Graph_Entry *v2 = Graph_CreateVertex('2');
    struct Graph_Entry *v3 = Graph_CreateVertex('3');
    struct Graph_Entry *v4 = Graph_CreateVertex('4');
    struct Graph_Entry *v5 = Graph_CreateVertex('5');

    /* 그래프 정점을 추가 */
    Graph_AddVertex(g, &v1->v);
    Graph_AddVertex(g, &v2->v);
    Graph_AddVertex(g, &v3->v);
    Graph_AddVertex(g, &v4->v);
    Graph_AddVertex(g, &v5->v);

    /* 정점과 정점을 간선으로 잇기 */
    Vertex_AddEdge(&v1->v, Graph_CreateEdge(v1, v2, 0));
    Vertex_AddEdge(&v1->v, Graph_CreateEdge(v1, v3, 0));
    Vertex_AddEdge(&v1->v, Graph_CreateEdge(v1, v4, 0));
    Vertex_AddEdge(&v1->v, Graph_CreateEdge(v1, v5, 0));

    Vertex_AddEdge(&v2->v, Graph_CreateEdge(v2, v1, 0));
    Vertex_AddEdge(&v2->v, Graph_CreateEdge(v2, v3, 0));
    Vertex_AddEdge(&v2->v, Graph_CreateEdge(v2, v5, 0));

    Vertex_AddEdge(&v3->v, Graph_CreateEdge(v3, v1, 0));
    Vertex_AddEdge(&v3->v, Graph_CreateEdge(v3, v2, 0));

    Vertex_AddEdge(&v4->v, Graph_CreateEdge(v4, v1, 0));
    Vertex_AddEdge(&v4->v, Graph_CreateEdge(v4, v5, 0));

    Vertex_AddEdge(&v5->v, Graph_CreateEdge(v5, v1, 0));
    Vertex_AddEdge(&v5->v, Graph_CreateEdge(v5, v2, 0));
    Vertex_AddEdge(&v5->v, Graph_CreateEdge(v5, v4, 0));

    Grpah_PrintGraph(g);

    /* 그래프 소멸 */
    Graph_DestroyGraph(g);

    return 0;
}
