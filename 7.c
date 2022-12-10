#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct dir {
        struct dir *child, *next, *parent;
        char *name;
        int size;
        struct file {
                char *name;
                int size;
                struct file *next;
        } *file;
};

void add_file(struct dir *d, char *name, int size)
{
        char *name_buf = malloc(100);
        strcpy(name_buf, name);

        struct file **head = &d->file;
        while (*head) head = &(*head)->next;
        *head = calloc(1, sizeof **head);
        **head = (struct file){
                .size = size,
                .name = name_buf,
        };

        for (struct dir *c = d; c; c = c->parent)
                c->size += size;
}

void add_child(struct dir *d, char *name)
{
        char *name_buf = malloc(100);
        strcpy(name_buf, name);

        struct dir **head = &d->child;
        while (*head) head = &(*head)->next;
        *head = calloc(1, sizeof **head);
        **head = (struct dir){
                .name = name_buf,
                .parent = d,
        };
}

struct dir *cd(struct dir *d, char *name)
{
        if (!strcmp(name, "..")) return d->parent;

        for (struct dir *c = d->child; c; c = c->next)
                if (!strcmp(c->name, name))
                        return c;

        return NULL;
}

int magic(struct dir *d)
{
        int sum = 0;

        if (d->size <= 100000) sum += d->size;

        for (struct dir *c = d->child; c; c = c->next)
                sum += magic(c);

        return sum;
}

int minimum = 1000000000;

void dir_floor(struct dir *d, int size_floor)
{
        if (!d || d->size < size_floor) return;

        if (d->size - size_floor < minimum)
                minimum = d->size - size_floor;

        for (struct dir *c = d->child; c; c = c->next)
                dir_floor(c, size_floor);
}

void ls(struct dir *d)
{
        static int depth = 0;

        for (int i = 0; i < depth; i++) printf("   ");

        printf("- %s (dir, size=%d)\n", d->name ? d->name : "/", d->size);

        for (struct dir *c = d->child; c; c = c->next)
                depth++, ls(c), depth--;

        for (struct file *c = d->file; c; c = c->next) {
                for (int i = 0; i < depth; i++) printf("   ");
                printf("   - %s (file, size=%d)\n", c->name, c->size);
        }
}

int main(void)
{
        FILE *f = fopen("7.txt", "r");

        char a[100], b[100], c[100], buf[100];

        struct dir *root = calloc(1, sizeof *root), *cwd = root;

        while (fgets(buf, sizeof buf, f)) {
                *c = 0;
                sscanf(buf, "%s %s %s\n", a, b, c);

                if (!strcmp(a, "$")) {
                        if (!strcmp(b, "cd")) {
                                if (*c == '/') {
                                        cwd = root;
                                        continue;
                                }

                                cwd = cd(cwd, c);
                        }
                } else {
                        if (!strcmp(a, "dir")) add_child(cwd, b);
                        else add_file(cwd, b, strtol(a, 0, 0));
                }
        }

        int size_floor = 30000000 - (70000000 - root->size);
        dir_floor(root, size_floor);

        /* ls(root); */

        printf("%d\n", magic(root));
        printf("%d\n", minimum + size_floor);
}
