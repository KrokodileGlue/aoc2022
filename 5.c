#include <stdio.h>
#include <string.h>
#include <math.h>

#define HIGH 20

struct {
        char s[100];
        int top;
} stack[] = {
        { "FCJPHTW", 7, },
        { "GRVFZJBH", 8 },
        { "HPTR", 4 },
        { "ZSNPHT", 6 },
        { "NVFZHJCD", 8 },
        { "PMGFWDZ", 7 },
        { "MVZWSJDP", 8 },
        { "NDS", 3 },
        { "DZSFM", 5 },
};

void print(void)
{
        for (int j = 0; j < HIGH; j++) {
                for (unsigned i = 0; i < sizeof stack / sizeof *stack; i++)
                        printf("%c     ", HIGH - 1 - j < stack[i].top
                               && stack[i].s[HIGH - 1 - j]
                               ? stack[i].s[HIGH - 1 - j] : ' ');
                puts("");
        }

        puts("");
}

int main(void)
{
        FILE *f = fopen("5.txt", "r");

        int a, b, c;

        //print();

        while (fscanf(f, "move %d from %d to %d\n", &a, &b, &c) == 3) {
                b -= 1;
                c -= 1;

                memcpy(stack[c].s + stack[c].top,
                       stack[b].s + stack[b].top - a,
                       a);

                stack[c].top += a;
                stack[b].top -= a;

                stack[c].s[stack[c].top] = 0;
                stack[b].s[stack[b].top] = 0;

                //print();
        }

        for (unsigned i = 0; i < sizeof stack / sizeof *stack; i++)
                printf("%c", stack[i].s[stack[i].top - 1]);
        puts("");

        fclose(f);
}
