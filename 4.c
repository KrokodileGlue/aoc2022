#include <stdio.h>
#include <string.h>

int main(void)
{
        FILE *f = fopen("4.txt", "r");

        int a, b, c, d, sum = 0, sum2 = 0;

        while (fscanf(f, "%d-%d,%d-%d\n", &a, &b, &c, &d) == 4)
                if ((c >= a && c <= b && d >= a && d <= b)
                    || (a >= c && a <= d && b >= c && b <= d))
                        sum++, sum2++;
                else if ((c >= a && c <= b && b >= c && b <= d)
                         || (a >= c && a <= d && d >= a && d <= b))
                        sum2++;

        printf("%d\n", sum);
        printf("%d\n", sum2);
}
