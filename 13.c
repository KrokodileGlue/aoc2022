#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/param.h>

static int cmp(char *const s1, char *const s2)
{
        char *a = s1, *b = s2;

        while (*a && *b) {
                if (*a == ',') { a++; continue; }
                if (*b == ',') { b++; continue; }
                if (*a == ']' && *b != ']') return 1;
                if (*a != ']' && *b == ']') return -1;
                if (*a == '[' && *b == '[') { a++, b++; continue; }
                if (*a == ']' && *b == ']') { a++, b++; continue; }

                if (isdigit(*a) && isdigit(*b)) {
                        int A = strtol(a, &a, 0), B = strtol(b, &b, 0);
                        if (A != B) return B - A;
                        continue;
                }

                if (isdigit(*a) && *b == '[') {
                        int x = strtol(a, &a, 0);
                        int depth = 0;
                        while (*b == '[') depth++, b++;
                        int y = strtol(b, &b, 0);
                        if (x != y) return y - x;
                        while (depth) {
                                if (*b != ']') return 1;
                                depth--, b++;
                        }
                        continue;
                }

                if (isdigit(*b) && *a == '[') {
                        int y = strtol(b, &b, 0);
                        int depth = 0;
                        while (*a == '[') depth++, a++;
                        int x = strtol(a, &a, 0);
                        if (x != y) return y - x;
                        while (depth) {
                                if (*a != ']') return -1;
                                depth--, a++;
                        }
                        continue;
                }
        }
}

int main(void)
{
        static char b1[1000], b2[1000], *prev, *buf = b2;
        int i = 1, sum = 0, key1 = 1, key2 = 2;
        for (FILE *f = fopen("13.txt", "r");
             fgets(buf, 1000, f);
             i++) {
                if (*buf == '\n') {
                        i--;
                        continue;
                }
                buf[strlen(buf) - 1] = 0;
                if (cmp(buf, "[[2]]") > 0) key1++;
                if (cmp(buf, "[[6]]") > 0) key2++;
                if (!(i % 2) && cmp(prev, buf) > 0) sum += i / 2;
                prev = buf, buf = i % 2 ? b1 : b2;
        }
        printf("%d\n%d\n", sum, key1 * key2);
}
