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
void path_history(int **paths, int i, int j) {
    if (paths[i][j] == 0) {
        return;
    }

    else {
        path_history(paths, i, paths[i][j]);
        printf("%d ", paths[i][j]);
        path_history(paths, paths[i][j], j);
    }
}

// Floyd Warshall algorithm
int FloydWarshall(struct edge *edges, int n, int m) {
    // structure to keep current shortest path value and path
    int **distances = (int **) malloc(sizeof(int *) * (n+1));
    int **paths = (int **) malloc(sizeof(int *) * (n+1));

    for (int i=0; i<n+1; i++) {
        distances[i] = (int *) malloc(sizeof(int) * (n+1));
        paths[i] = (int *) malloc(sizeof(int) * (n+1));
    }

    // initialization
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (i == j) {
                distances[i][j] = 0;
            }

            else {
                distances[i][j] = INFINITE;
            }
        }
    }

    for (int i=0; i<m; i++) {
        distances[edges[i].vertex_id1][edges[i].vertex_id2] = edges[i].edge_weight;
    }

    // Floyd-Warshall algorithm
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            for (int k=1; k<n+1; k++) {
                if ((distances[j][i] != INFINITE) && (distances[i][k] != INFINITE) && (distances[j][i] + distances[i][k] < distances[j][k])) {
                    distances[j][k] = distances[j][i] + distances[i][k];
                    paths[j][k] = i;
                }
            }
        }
    }

    // check for negative-cost cycle
    for (int i=1; i<n+1; i++) {
        if (distances[i][i] < 0) {
            printf("Error: negative-cost cycle is found\n");
            return 0;
        }
    }

    // print APSP result
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (distances[i][j] == INFINITE) {
                printf("%d %d length: inf path: none\n", i, j);
            }

            else if (i != j) {
                printf("%d %d length: %d path: %d ", i, j, distances[i][j], i);
                path_history(paths, i, j);
                printf("%d\n", j);
            }
        }
    }

    // free memory
    for (int i=0; i<n+1; i++) {
        free(distances[i]);
        free(paths[i]);
    }

    free(distances);
    free(paths);

    return 1;
}

int main(){
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

    // Perform Floyd-Warshall
    FloydWarshall(edges, n, m);

    free(edges);
    return 0;

}
