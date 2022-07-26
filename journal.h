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
    struct tm date;
    int term;
    struct journal *next;
};

struct journal *add_journal(char *name, int num, int year_of_issue, char *fnamea, char *lnamea, char *article, int day, int mon, int year, int term);

struct journal cpy_journal(struct journal *log);

void sort_journal(struct journal *logs);

int comparise_info(struct journal log1, struct journal log2);

void info_journal(struct journal *logs, struct tm *today_date);

struct journal *search_author(struct journal *logs, char *str);

struct journal *search_debtors(struct journal *logs, struct tm *today_date);

struct journal *find_for_delete(struct journal *logs, char *str);

struct journal *delete_journal(struct journal *logs, struct journal *delete_log);

void free_journal(struct journal *logs);

struct journal *journal_out_file(char *file_name);

void journal_in_file(struct journal *logs, char *file_name);

#endif /* JOURNAL_H */


