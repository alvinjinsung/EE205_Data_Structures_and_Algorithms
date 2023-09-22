#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LINE 1024
#define INFINITE INT_MAX

// structure for each edge(source vertex, destination vertex, edge cost)
struct edge {
    int vertex_id1;
    int vertex_id2;
    int edge_weight;
};

// function to iteratively compute the shortest path we kept track of
void path_history(int *paths, int n, int s, int i) {
    if (paths[i] == s) {
        printf("%d ", paths[i]);
        return;
    }

    else {
        path_history(paths, n, s, paths[i]);
        printf("%d ", paths[i]);
        return;
    }
}

// Bellman-Ford algorithm
int BellmanFord(struct edge *edges, int n, int m, int s) {
    // structure to keep current shortest path value and path
    int *distances = (int *) malloc(sizeof(int) * (n+1));
    int *paths = (int *) malloc(sizeof(int) * (n+1));

    // initialization
    for (int i=1; i<n+1; i++) {
        if (i == s) {
            distances[i] = 0;
        }

        else {
            distances[i] = INFINITE;
        }
    }

    // Bellman-Ford algorithm
    for (int j=1; j<n; j++) {
        for (int k=0; k<m; k++) {
            if ((distances[edges[k].vertex_id1] != INFINITE) && (distances[edges[k].vertex_id1] + edges[k].edge_weight < distances[edges[k].vertex_id2])) {
                distances[edges[k].vertex_id2] = distances[edges[k].vertex_id1] + edges[k].edge_weight;
                paths[edges[k].vertex_id2] = edges[k].vertex_id1;
            }
        }
    }

    // check for negative-cost cycle
    for (int i=0; i<m; i++) {
        if ((distances[edges[i].vertex_id1] != INFINITE) && (distances[edges[i].vertex_id1] + edges[i].edge_weight < distances[edges[i].vertex_id2])) {
            printf("Error: negative-cost cycle is found\n");
            return 0;
        }
    }

    // print SSSP result
    for (int i=1; i<n+1; i++) {
        if (distances[i] == INFINITE) {
            printf("%d %d length: inf path: none\n", s, i);
        }

        else if (i != s) {
            printf("%d %d length: %d path: ", s, i, distances[i]);
            path_history(paths, n, s, i);
            printf("%d\n", i);
        }
    }

    // free memory
    free(distances);
    free(paths);

    return 1;
}

int main(int argc, char*argv[]){
    char input_value[MAX_LINE];
    char *input_temp;
    int n;
    int m;

    // read the first line into input_value
    fgets(input_value, sizeof(input_value), stdin);

    // assign n as number of vertices and m as number of edges
    input_temp = strtok(input_value, " ");
    n = atoi(input_temp);

    input_temp = strtok(NULL, " ");
    m = atoi(input_temp);

    // structure to store all the edges information given
    struct edge *edges = malloc(sizeof(struct edge) * m);

    int i = 0;

    // store edges information
    while(fgets(input_value, sizeof(input_value), stdin) != NULL) {
        input_temp = strtok(input_value, " ");
        edges[i].vertex_id1 = atoi(input_temp);

        input_temp = strtok(NULL, " ");
        edges[i].vertex_id2 = atoi(input_temp);

        input_temp = strtok(NULL, " ");
        edges[i].edge_weight = atoi(input_temp);

        i++;
    }

    // if source specified, perform Bellman-Ford once
    if (argc == 2) {
        int s;
        s = atoi(argv[1]);

        if ((s<1) || (s>n)) {
            printf("Error: source vertex does not exist\n");
            return -1;
        }

        BellmanFord(edges, n, m, s);
    }

    // if source not specified, perform Bellman-ford for all vertices
    else {
        for (int s=1; s<n+1; s++) {
            if (BellmanFord(edges, n, m, s) == 0) {
                break;
            }
        }
    }

    free(edges);
    return 0;

}