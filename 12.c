#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

struct node {
        int x, y, height, visited;
        struct node *prev;
} graph[10000];
int ngraph;

struct node *mark[10000];
int nmark;

int col = 0, row = 0;

struct node *get_node(int x, int y)
{
        for (int i = 0; i < ngraph; i++)
                if (graph[i].x == x && graph[i].y == y)
                        return graph + i;
        return NULL;
}

int visit(struct node *n)
{
        if (n->x < 0 || n->x >= col || n->y < 0 || n->y >= row || n->visited)
                return 0;

        if (n->height == 'z' - 'a') {
                int i = 0;
                for (struct node *m = n; m; m = m->prev, i++);
                printf("%d\n", i - 1);
                return 1;
        }

        for (int y = -1; y < 2; y++) {
                for (int x = -1; x < 2; x++) {
                        if (abs(x) == abs(y)) continue;
                        struct node *m = get_node(n->x + x, n->y + y);
                        if (!m || m == n || m->visited) continue;
                        if (m->height == n->height + 1 || m->height <= n->height) {
                                m->prev = n;
                                mark[nmark++] = m;
                        }
                }
        }

        n->visited = 1;

        return 0;
}

void bfs(struct node *root)
{
        mark[nmark++] = root;

        while (nmark) {
                struct node *n = mark[0];
                memmove(mark, mark + 1, (nmark - 1) * sizeof *mark);
                nmark--;
                if (visit(n)) break;
        }
}

int main(void)
{
        FILE *f = fopen("12.txt", "r");
        char line[200];
        struct node *root;

        while (fgets(line, sizeof line, f)) {
                if (!*line) break;
                col = strlen(line);
                line[col - 1] = 0;

                for (int i = 0; i < col; i++) {
                        graph[ngraph++] = (struct node){ i, row, 25 - (line[i] - 'a'), 0, 0 };
                        if (line[i] == 'E') {
                                root = &graph[ngraph - 1];
                                root->height = 0;
                        } else if (line[i] == 'S')
                                graph[ngraph - 1].height = 'z' - 'a';
                }

                row++;
        }

        fclose(f);
        bfs(root);
}
