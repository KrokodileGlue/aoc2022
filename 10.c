#include <stdio.h>
#include <string.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

int cycle, sum, X = 1, x, arg;

void crt(void)
{
        putchar(abs(X - x) < 2 ? '#' : '.');

        cycle++, x++;

        if (x % 40 == 0) {
                x = 0;
                puts("");
        }

        if ((cycle - 20) % 40 == 0) sum += X * cycle;
}

int main(void)
{
        FILE *f = fopen("10.txt", "r");
        char line[100], cmd[5];

        while (fgets(line, 100, f)) {
                sscanf(line, "%s %d", cmd, &arg);

                if (!strcmp(cmd, "noop")) crt();
                else crt(), crt(), X += arg;
        }

        printf("%d\n", sum);
        fclose(f);
}
