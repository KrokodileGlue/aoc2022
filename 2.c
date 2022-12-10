#include <stdio.h>

int main(void)
{
        FILE *f = fopen("2.txt", "r");

        char a, b;

        enum {
                LOSE = 0,
                TIE = 3,
                WIN = 6,
        };

        enum {
                ROCK,
                PAPER,
                SCISSORS,
        };

        int rps[3][3] = {
                /* Rock Paper Scissors */
                { TIE,  LOSE, WIN },     /* Rock */
                { WIN,  TIE,  LOSE },    /* Paper */
                { LOSE, WIN,  TIE },     /* Scissors */
        };

        int sum = 0;

        while (fscanf(f, "%c %c\n", &a, &b) == 2) {
                a -= 'A';
                b -= 'X';
                b = (int [][3]){
                        /* Rock     Paper     Scissors */
                        { SCISSORS, ROCK,     PAPER },    /* Lose */
                        { ROCK,     PAPER,    SCISSORS }, /* Tie */
                        { PAPER,    SCISSORS, ROCK },     /* Win */
                }[(int)a][(int)b];
                int result = rps[(int)b][(int)a] + (int)b + 1;
                sum += result;
        }

        printf("%d\n", sum);
}
