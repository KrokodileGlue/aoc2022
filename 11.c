#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int prime = 0;

struct monkey {
        uint64_t items[100];
        int top;
        char op;
        int arg;
        int divisible;
        int monkey_a, monkey_b;
        uint64_t items_inspected;
} monkeys[] = {
#if 1
        {
                .items = { 54, 53 },
                .top = 2,
                .op = '*',
                .arg = 3,
                .divisible = 2,
                .monkey_a = 2,
                .monkey_b = 6,
        },
        {
                .items = { 95, 88, 75, 81, 91, 67, 65, 84 },
                .top = 8,
                .op = '*',
                .arg = 11,
                .divisible = 7,
                .monkey_a = 3,
                .monkey_b = 4,
        },
        {
                .items = { 76, 81, 50, 93, 96, 81, 83 },
                .top = 7,
                .op = '+',
                .arg = 6,
                .divisible = 3,
                .monkey_a = 5,
                .monkey_b = 1,
        },
        {
                .items = { 83, 85, 85, 63 },
                .top = 4,
                .op = '+',
                .arg = 4,
                .divisible = 11,
                .monkey_a = 7,
                .monkey_b = 4,
        },
        {
                .items = { 85, 52, 64 },
                .top = 3,
                .op = '+',
                .arg = 8,
                .divisible = 17,
                .monkey_a = 0,
                .monkey_b = 7,
        },
        {
                .items = { 57 },
                .top = 1,
                .op = '+',
                .arg = 2,
                .divisible = 5,
                .monkey_a = 1,
                .monkey_b = 3,
        },
        {
                .items = { 60, 95, 76, 66, 91 },
                .top = 5,
                .op = '*',
                .arg = -1,
                .divisible = 13,
                .monkey_a = 2,
                .monkey_b = 5,
        },
        {
                .items = { 65, 84, 76, 72, 79, 65 },
                .top = 6,
                .op = '+',
                .arg = 5,
                .divisible = 19,
                .monkey_a = 6,
                .monkey_b = 0,
        },
#else
        {
                .items = { 79, 98 },
                .top = 2,
                .op = '*',
                .arg = 19,
                .divisible = 23,
                .monkey_a = 2,
                .monkey_b = 3,
        },
        {
                .items = { 54, 65, 75, 74 },
                .top = 4,
                .op = '+',
                .arg = 6,
                .divisible = 19,
                .monkey_a = 2,
                .monkey_b = 0,
        },
        {
                .items = { 79, 60, 97 },
                .top = 3,
                .op = '*',
                .arg = -1,
                .divisible = 13,
                .monkey_a = 1,
                .monkey_b = 3,
        },
        {
                .items = { 74 },
                .top = 1,
                .op = '+',
                .arg = 3,
                .divisible = 17,
                .monkey_a = 0,
                .monkey_b = 1,
        },
#endif
};

void monkey_round(void)
{
        for (unsigned i = 0; i < sizeof monkeys / sizeof *monkeys; i++) {
                struct monkey m = monkeys[i];

                for (int j = 0; j < m.top; j++) {
                        uint64_t worry_level = m.items[j];
                        if (m.op == '*') worry_level *= m.arg == -1 ? worry_level : m.arg;
                        else worry_level += m.arg == -1 ? worry_level : m.arg;
                        /* worry_level /= 3; */
                        worry_level %= prime;

                        if (worry_level % m.divisible == 0) {
                                monkeys[m.monkey_a].items[monkeys[m.monkey_a].top++] = worry_level;
                        } else {
                                monkeys[m.monkey_b].items[monkeys[m.monkey_b].top++] = worry_level;
                        }

                        monkeys[i].items_inspected++;
                }

                monkeys[i].top = 0;
        }
}

int compare_monkeys(const void *a, const void *b)
{
        return ((struct monkey *)b)->items_inspected - ((struct monkey *)a)->items_inspected;
}

int main(void)
{
        for (unsigned i = 0; i < sizeof monkeys / sizeof *monkeys; i++) {
                struct monkey m = monkeys[i];
                if (!i) prime = m.divisible;
                else prime *= m.divisible;
        }

        printf("prime=%d\n", prime);

        for (int i = 0; i < 10000; i++)
                monkey_round();

        for (unsigned i = 0; i < sizeof monkeys / sizeof *monkeys; i++) {
                struct monkey m = monkeys[i];

                printf("Monkey %d: ", i);

                for (int j = 0; j < m.top; j++)
                        printf("%"PRIu64" ", m.items[j]);

                puts("");
        }

        qsort(monkeys, sizeof monkeys / sizeof *monkeys, sizeof *monkeys, compare_monkeys);

        printf("%"PRIu64"\n", monkeys[0].items_inspected * monkeys[1].items_inspected);
}
