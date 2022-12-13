#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/param.h>

struct packet {
        enum { INT, LIST } type;
        int num, nlist;
        struct packet **list;
};

struct packet *packet_parse(char **x)
{
        struct packet *p = calloc(1, sizeof *p);
        if (isdigit(**x))
                return *p = (struct packet){ INT, strtol(*x, x, 0), 0, 0 }, p;
        (*x)++, p->type = LIST;
        while (**x && **x != ']')
                if (**x == ',') (*x)++;
                else {
                        p->list = realloc(p->list, ++p->nlist * sizeof *p->list);
                        p->list[p->nlist - 1] = packet_parse(x);
                }
        return (*x)++, p;
}

struct packet *packet_int_to_list(struct packet *p)
{
        if (p->type != INT) return p;
        struct packet *ret = calloc(1, sizeof *ret);
        return *ret = (struct packet){
                .type = LIST,
                .nlist = 1,
                .list = calloc(1, sizeof **ret->list),
        }, *ret->list = p, ret;
}

int packet_cmp(struct packet *a, struct packet *b)
{
        if (a->type == INT && b->type == INT) return b->num - a->num;
        if (a->type == LIST && b->type == LIST) {
                for (int i = 0; i < MIN(a->nlist, b->nlist); i++) {
                        int j = packet_cmp(a->list[i], b->list[i]);
                        if (j) return j;
                }
                return b->nlist - a->nlist;
        }
         return packet_cmp(packet_int_to_list(a), packet_int_to_list(b));
}

int main(void)
{
        struct packet *p2 = packet_parse(&(char *){ "[[2]]" }),
                *p6 = packet_parse(&(char *){ "[[6]]" }),
                *prev = NULL, *p = NULL;
        static char buf[1000];
        int i = 1, sum = 0, key1 = 1, key2 = 1;
        for (FILE *f = fopen("13.txt", "r");
             fgets(buf, sizeof buf, f);
             prev = p, i++) {
                if (*buf == '\n' && i--) continue;
                p = packet_parse(&(char *){ buf });
                if (packet_cmp(p, p2) > 0) key1++;
                if (packet_cmp(p, p6) > 0) key2++;
                if (!(i % 2) && packet_cmp(prev, p) >= 0) sum += i / 2;
        }
        printf("%d\n%d\n", sum, key1 > key2 ?
               (key1 + 1) * key2 : key1 * (key2 + 1));
}
