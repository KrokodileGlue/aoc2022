#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int compare(const void *a, const void *b) {
        return *(int *)b - *(int *)a;
}

int main(void)
{
        FILE *f = fopen("1.txt", "r");
        char buf[100];

        static int elves[2000];
        int elf = 0, m = 0, elf_index = 0;

        while (fgets(buf, sizeof buf, f)) {
                if (*buf == '\n') {
                        elf = 0;
                        elf_index++;
                        continue;
                }

                buf[strlen(buf) - 1] = 0;
                elf += strtol(buf, 0, 0);
                elves[elf_index] = elf;

                if (elf > m) m = elf;
        }

        qsort(elves, elf_index, sizeof *elves, compare);

        printf("%d\n", m);
        /* printf("top 3: %d %d %d\n", elves[0], elves[1], elves[2]); */
        printf("%d\n", elves[0] + elves[1] + elves[2]);
}
