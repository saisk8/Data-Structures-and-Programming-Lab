#include <stdio.h>
#include <stdlib.h>

struct Node {
  unsigned int vertex;
  struct Node *next;
};

struct Node *addEdge(struct Node *head, unsigned int vertex) {
  struct Node *newNode = (struct Node *)calloc(1, sizeof(struct Node));
  newNode->vertex = vertex;
  newNode->next = head;
  return newNode;
}

void countPaths(int source, int destination, int *visited, int *count,
                struct Node *adjacencyList[]) {
  visited[source] = 1;
  if (source == destination)
    (*count)++;
  else {
    struct Node *adjacent = adjacencyList[source];
    while (adjacent != NULL) {
      // printf("%d\n", adjacent->vertex);
      if (!visited[adjacent->vertex]) {
        countPaths(adjacent->vertex, destination, visited, count,
                   adjacencyList);
      }
      adjacent = adjacent->next;
    }
  }
  visited[source] = 0;
}

int getNumberOfPaths(int vertices, struct Node *adjacencyList[], int source,
                     int destination) {
  int *visited = (int *)malloc(sizeof(int) * vertices);
  int pathCount = 0;
  for (int i = 0; i < vertices; ++i) visited[i] = 0;
  visited[source] = 1;
  countPaths(source, destination, visited, &pathCount, adjacencyList);
  return pathCount;
}

int main() {
  int vertices, edges, v1, v2, source, destination;
  FILE *p, *q;
  p = fopen("input.txt", "r");
  q = fopen("output.txt", "w");
  int testCases, count = 0;
  fscanf(p, "%d", &testCases);
  while (testCases--) {
    fprintf(q, "\nTest Case: %d\n", ++count);
    fscanf(p, "%d", &vertices);
    fscanf(p, "%d", &edges);
    struct Node *adjacencyList[vertices];
    for (int i = 0; i < vertices; ++i) {
      adjacencyList[i] = NULL;
    }
    for (int i = 0; i < edges; ++i) {
      fscanf(p, "%d%d", &v1, &v2);
      adjacencyList[v1] = addEdge(adjacencyList[v1], v2);
    }
    fscanf(p, "%d", &source);
    printf("Source %d\n", source);
    fscanf(p, "%d", &destination);
    fprintf(q, "The number of paths is/are: %d",
            getNumberOfPaths(vertices, adjacencyList, source, destination));
  }
  return 0;
}