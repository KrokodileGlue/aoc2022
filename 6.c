#include <stdio.h>
#include <string.h>

#define N 14

int main(void)
{
        static char buf[10000];

        FILE *f = fopen("6.txt", "r");
        fgets(buf, sizeof buf, f);
        fclose(f);

        char last[N] = { 0 };

        for (unsigned i = 0; i < strlen(buf); i++) {
                memmove(last, last + 1, N - 1);
                last[N - 1] = buf[i];

                if (i < N - 1) continue;

                int dupe = 0;

                for (int j = 0; j < N; j++)
                        for (int k = 0; k < N; k++)
                                if (j != k && last[j] == last[k])
                                        dupe = 1;

                if (dupe) continue;

                printf("%d\n", i + 1);
                break;
        }
}
