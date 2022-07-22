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
    struct journal *next;
};

void EnterStr(char *str);

struct journal *addjournal(char *name, int num, int year, char *fnamea, char *lnamea, char *article);

void sortjournal(struct journal *logs);

int compariseinfo(struct journal log1, struct journal log2);

void infojournal(struct journal *logs);

struct journal *search(struct journal *logs, char *str);

struct journal *find_for_delete(struct journal *logs, char *str);

struct journal *delete_journal(struct journal *logs, struct journal *delete_log);

void freejournal(struct journal *logs);

struct journal *journal_out_file(char *file_name);

void journal_in_file(struct journal *logs, char *file_name);

#endif /* JOURNAL_H */


