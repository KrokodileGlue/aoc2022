#include <stdio.h>
#include <unistd.h>

#define N 10
#define abs(x) ((x) < 0 ? -(x) : (x))

struct point { int x, y; } rope[N], visit[10000];
int nvisit;

struct point drag(struct point a, struct point b)
{
        if (b.y < a.y - 1) {
                b.y++;
                if (b.x < a.x) b.x++;
                if (b.x > a.x) b.x--;
        }

        if (b.y > a.y + 1) {
                b.y--;
                if (b.x < a.x) b.x++;
                if (b.x > a.x) b.x--;
        }

        if (b.x < a.x - 1) {
                b.x++;
                if (b.y < a.y) b.y++;
                if (b.y > a.y) b.y--;
        }

        if (b.x > a.x + 1) {
                b.x--;
                if (b.y < a.y) b.y++;
                if (b.y > a.y) b.y--;
        }

        return b;
}

void move(int i)
{
        if (i == N - 1) {
                for (int j = 0; j < nvisit; j++)
                        if (visit[j].x == rope[N - 1].x
                            && visit[j].y == rope[N - 1].y)
                                return;
                visit[nvisit++] = rope[N - 1];
                return;
        }

        rope[i + 1] = drag(rope[i], rope[i + 1]);
        move(i + 1);
}

int main(void)
{
        FILE *f = fopen("9.txt", "r");

        char direction;
        int distance;

        while (fscanf(f, "%c %d\n", &direction, &distance) == 2)
                for (int i = 0; i < distance; i++) {
                        switch (direction) {
                        case 'U': rope[0].y++; break;
                        case 'D': rope[0].y--; break;
                        case 'R': rope[0].x++; break;
                        case 'L': rope[0].x--; break;
                        }

                        move(0);
                }

        printf("%d\n", nvisit);
}
