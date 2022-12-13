#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define min(x,y) ((x) < (y) ? (x) : (y))

struct packet {
        enum {
                INT,
                LIST,
        } type;

        int integer;

        int nlist;
        struct packet **list;
};

void packet_add_to_list(struct packet *a, struct packet *b)
{
        a->list = realloc(a->list, ++a->nlist * sizeof *a->list);
        a->list[a->nlist - 1] = b;
}

struct packet *packet_parse(char **x)
{
        struct packet *p = calloc(1, sizeof *p);

        if (isdigit(**x)) {
                p->type = INT;
                p->integer = strtol(*x, x, 0);
                return p;
        }

        p->type = LIST;

        (*x)++;

        while (**x && **x != ']') {
                if (**x == ',') {
                        (*x)++;
                        continue;
                }

                packet_add_to_list(p, packet_parse(x));
        }

        (*x)++;

        return p;
}

void packet_show(struct packet *p)
{
        if (p->type == INT) printf("%d", p->integer);
        else {
                putchar('[');
                for (int i = 0; i < p->nlist; i++) {
                        packet_show(p->list[i]);
                        if (i != p->nlist - 1) putchar(',');
                }
                putchar(']');
        }
}

struct packet *packet_int_to_list(struct packet *p)
{
        struct packet *tmp = calloc(1, sizeof *tmp);

        *tmp = (struct packet){
                .type = INT,
                .integer = p->integer,
        };

        struct packet *ret = calloc(1, sizeof *ret);

        *ret = (struct packet){
                .type = LIST,
                .nlist = 1,
                .list = calloc(1, sizeof **ret->list),
        };

        ret->list[0] = tmp;

        return ret;
}

int packet_cmp(struct packet *a, struct packet *b)
{
        if (a->type == INT && b->type == INT) {
                return b->integer - a->integer;
        } else if (a->type == LIST && b->type == LIST) {
                for (int i = 0; i < min(a->nlist, b->nlist); i++) {
                        int tmp = packet_cmp(a->list[i], b->list[i]);
                        if (tmp) return tmp;
                }

                return b->nlist - a->nlist;
        }

         if (a->type == INT) a = packet_int_to_list(a);
         if (b->type == INT) b = packet_int_to_list(b);

         return packet_cmp(a, b);
}

int packet_qsort(const void *a, const void *b)
{
        return -packet_cmp(*(struct packet **)a, *(struct packet **)b);
}

int main(void)
{
        FILE *f = fopen("13.txt", "r");
        static char buf[1000];
        int index = 1, sum = 0;

        static struct packet *packets[1000];
        static int npacket;

        while (fgets(buf, sizeof buf, f)) {
                if (*buf == '\n') continue;
                char *ptr = buf;
                struct packet *a = packet_parse(&ptr);
                fgets(buf, sizeof buf, f);
                ptr = buf;
                struct packet *b = packet_parse(&ptr);
                packets[npacket++] = a;
                packets[npacket++] = b;
                if (packet_cmp(a, b) >= 0) sum += index;
                index++;
        }

        printf("%d\n", sum);

        struct packet *p2 = packets[npacket++] = packet_parse(&(char *){ "[[2]]" });
        struct packet *p6 = packets[npacket++] = packet_parse(&(char *){ "[[6]]" });

        qsort(packets, npacket, sizeof *packets, packet_qsort);

        int key1, key2;

        for (int i = 0; i < npacket; i++) {
                /* packet_show(packets[i]), puts(""); */
                if (packets[i] == p2) key1 = i + 1;
                if (packets[i] == p6) key2 = i + 1;
        }

        printf("%d\n", key1 * key2);
}
