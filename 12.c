#include <string.h>
#include <stdio.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

struct node {
        int x, y, height, visited;
        struct node *prev;
} graph[10000], *mark[1000];

int col, row, ngraph, nmark;

struct node *get_node(int x, int y)
{
        for (int i = 0; i < ngraph; i++)
                if (graph[i].x == x && graph[i].y == y && !graph[i].visited)
                        return graph + i;
        return NULL;
}

void visit(struct node *n)
{
        if (n->x < 0 || n->x >= col || n->y < 0 || n->y >= row || n->visited)
                return;

        for (int y = -1; y < 2; y++)
                for (int x = -1; x < 2; x++) {
                        struct node *m = get_node(n->x + x, n->y + y);
                        if (!m || m == n || abs(x) == abs(y))
                                continue;
                        if (m->height <= n->height + 1)
                                m->prev = n, mark[nmark++] = m;
                }

        n->visited = 1;
}

int bfs(struct node *root)
{
        int ret = 0;

        mark[0] = root;
        nmark = 1;

        while (nmark) {
                struct node *n = mark[0];

                if (n->height == 25) {
                        for (struct node *m = n; m; m = m->prev, ret++);
                        break;
                }

                memmove(mark, mark + 1, (nmark-- - 1) * sizeof *mark);
                visit(n);
        }

        return ret;
}

int main(void)
{
        FILE *f = fopen("12.txt", "r");
        char line[200];
        struct node *S, *E;

        while (fgets(line, sizeof line, f)) {
                line[strlen(line) - 1] = 0;
                if (!*line) break;
                col = strlen(line);

                for (int i = 0; i < col; i++) {
                        graph[ngraph++] = (struct node){ i, row, line[i] - 'a', 0, 0 };
                        if (line[i] == 'S') {
                                S = &graph[ngraph - 1];
                                S->height = 0;
                        } else if (line[i] == 'E') {
                                E = &graph[ngraph - 1];
                                E->height = 25;
                        }
                }

                row++;
        }

        fclose(f);

        printf("%d\n", bfs(S));

        for (int i = 0; i < ngraph; i++) {
                graph[i].prev = NULL;
                graph[i].visited = 0;
                graph[i].height = 25 - graph[i].height;
        }

        printf("%d\n", bfs(E) - 1);
}
