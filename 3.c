#include <stdio.h>
#include <string.h>

int priority(char x)
{
        return x < 'a' ? x - 'A' + 27 : x - 'a' + 1;
}

int main(void)
{
        FILE *f = fopen("3.txt", "r");

        static char line[1000], left[500], right[500], common[1000];

        int sum = 0, i = 0, sum2 = 0;

        while (fgets(line, sizeof line, f)) {
                line[strlen(line) - 1] = 0;

                memset(left, 0, sizeof left);
                memset(right, 0, sizeof right);
                strncpy(left, line, strlen(line) / 2);
                strncpy(right, line + strlen(line) / 2, strlen(line) / 2);

                if (!i) {
                        strcpy(common, line);
                } else if (i % 3 == 0) {
                        sum2 += priority(*common);
                        strcpy(common, line);
                } else {
                        for (unsigned j = 0; j < strlen(common); j++) {
                                int found = 0;

                                for (unsigned k = 0; k < strlen(line); k++) {
                                        if (common[j] == line[k])
                                                found = 1;
                                }

                                if (!found) {
                                        memmove(common + j, common + j + 1, sizeof common - j - 1);
                                        j--;
                                }
                        }
                }

                int item_seen[53] = { 0 };

                for (unsigned j = 0; j < strlen(left); j++)
                        for (unsigned k = 0; k < strlen(right); k++) {
                                int index = priority(left[j]);

                                if (left[j] != right[k]
                                    || item_seen[index - 1]) continue;

                                sum += index;
                                item_seen[index - 1] = 1;
                        }

                i++;
        }

        sum2 += priority(*common);

        printf("%d\n", sum);
        printf("%d\n", sum2);
}
