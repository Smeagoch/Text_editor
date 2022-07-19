#ifndef JOURNAL_H
#define JOURNAL_H
#define NBUF 128

struct journal
{
    char *name;
    int number;
    int year;
    char *fNameAutor;
    char *lNameAutor;
    char *article;
};

void EnterStr(char *str);

struct journal *addjournal(char *name, int num, int year, char *fnamea, char *lnamea, char *article);

void sortjournal(struct journal **logs, int n);

int compariseinfo(struct journal log1, struct journal log2);

void infojournal(struct journal **logs, int n);

int search(struct journal **logs, int n, char *str, struct journal **slogs);

void freejournal(struct journal **logs, int n);

#endif /* JOURNAL_H */


