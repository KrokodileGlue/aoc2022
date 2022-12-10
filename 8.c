#include <stdio.h>
#include <string.h>

int main(void)
{
        FILE *f = fopen("8.txt", "r");

        static char height[1000][1000];

        int col, row = 0;

        while (fgets(height[row], sizeof height[row], f)) {
                if (*height[row] == '\n') break;
                height[row][strlen(height[row]) - 1] = 0;
                col = strlen(height[row]);
                memcpy(height[row], height[row], col);
                row++;
        }

        char visible[row][col];
        memset(visible, 0, sizeof visible);

        int max = 0;

        for (int x = 0; x < col; x++) {
                for (int y = 0; y < row; y++)
                        if (height[y][x] > max) {
                                max = height[y][x];
                                visible[y][x] = 1;
                        }
                max = 0;
                for (int y = row - 1; y >= 0; y--)
                        if (height[y][x] > max) {
                                max = height[y][x];
                                visible[y][x] = 1;
                        }
                max = 0;
        }

        for (int y = 0; y < row; y++) {
                for (int x = 0; x < col; x++)
                        if (height[y][x] > max) {
                                max = height[y][x];
                                visible[y][x] = 1;
                        }
                max = 0;
                for (int x = col - 1; x >= 0; x--)
                        if (height[y][x] > max) {
                                max = height[y][x];
                                visible[y][x] = 1;
                        }
                max = 0;
        }

        int sum = 0;

        for (int y = 0; y < row; y++)
                for (int x = 0; x < col; x++)
                        sum += visible[y][x];

        printf("%d\n", sum);

        int scenic[row][col][4];
        memset(scenic, 0, sizeof scenic);

        for (int y = 0; y < row; y++)
                for (int x = 0; x < col; x++) {
                        for (int Y = y + 1; Y < row; Y++) {
                                scenic[y][x][0]++;
                                if (height[Y][x] >= height[y][x]) break;
                        }
                        for (int Y = y - 1; Y >= 0; Y--) {
                                scenic[y][x][1]++;
                                if (height[Y][x] >= height[y][x]) break;
                        }
                        for (int X = x + 1; X < col; X++) {
                                scenic[y][x][2]++;
                                if (height[y][X] >= height[y][x]) break;
                        }
                        for (int X = x - 1; X >= 0; X--) {
                                scenic[y][x][3]++;
                                if (height[y][X] >= height[y][x]) break;
                        }
                }

        max = 0;

        for (int y = 0; y < row; y++)
                for (int x = 0; x < col; x++) {
                        int prod = scenic[y][x][0];
                        for (int i = 1; i < 4; i++) prod *= scenic[y][x][i];
                        if (prod > max) max = prod;
                }

        printf("%d\n", max);
}
