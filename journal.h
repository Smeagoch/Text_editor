#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef JOURNAL_H
#define JOURNAL_H
#define NBUF 128

struct journal
{
    char *name;
    int *number;
    int *year;
    char *fNameAutor;
    char *lNameAutor;
    char *article;
};

char *EnterStr()
{
    char buffer[NBUF];
    fgets (buffer, NBUF, stdin);
    buffer[strlen(buffer) - 1] = 0;
    char *str = (char *)malloc (strlen(buffer) * sizeof (char));
    strcpy(str, buffer);
    strcat(str, "\0");
    return str;
}

void addjournal(struct journal log)
{
    char buffer[NBUF];

    printf ("Enter name of the journal: ");
    fgets (buffer, NBUF, stdin);
    buffer[strlen(buffer) - 1] = 0;
    log.name = (char *)realloc(log.name, strlen(buffer) * sizeof(char));
    strcpy(log.name, buffer);
    strcat(log.name, "\0");

    printf ("Enter number of the journal: ");
    scanf ("%d", log.number);
    printf ("%d", *log.number);

    printf ("Enter year of issue of the journal: ");
    scanf ("%d", log.year);
    char n[2];
    fgets(n, 2, stdin);

    printf ("Enter the autor's first name: ");
    fgets (buffer, NBUF, stdin);
    buffer[strlen(buffer) - 1] = 0;
    log.fNameAutor = (char *)realloc(log.fNameAutor, strlen(buffer) * sizeof(char));
    strcpy(log.fNameAutor, buffer);
    strcat(log.fNameAutor, "\0");

    printf ("Enter the autor's last name: ");
    fgets (buffer, NBUF, stdin);
    buffer[strlen(buffer) - 1] = 0;
    log.lNameAutor = (char *)realloc(log.lNameAutor, strlen(buffer) * sizeof(char));
    strcpy(log.lNameAutor, buffer);
    strcat(log.lNameAutor, "\0");

    printf ("Enter the title of the article: ");
    fgets (buffer, NBUF, stdin);
    buffer[strlen(buffer) - 1] = 0;
    log.article = (char *)realloc(log.article, strlen(buffer) * sizeof(char));
    strcpy(log.article, buffer);
    strcat(log.article, "\0");
}

int nJournal(struct journal *logs)
{
    int count = 0;
    while(1)
    {
	if (logs[count].name != NULL)
	{
	    count++;
	}
	else
	{
	    break;
	}
    }
    return count;
}

int sort_comparise(const void *log1, const void *log2)
{
    const char *name1 = ((const struct journal *) log1)->name;
    const char *name2 = ((const struct journal *) log2)->name;
    const int *num1 = ((const struct journal *) log1)->number;
    const int *num2 = ((const struct journal *) log2)->number;
    const int *year1 = ((const struct journal *) log1)->year;
    const int *year2 = ((const struct journal *) log2)->year;
    if ((strcmp(name1, name2) == 0) && (*num1 != *num2))
    {
        if (*num1 > *num2)
            return 1;
        if (*num1 == *num2)
            return 0;
        if (*num1 < *num2)
            return -1;
    }
    else
    {
	if ((strcmp(name1, name2) == 0) && (*num1 == *num2))
	{
            if (*year1 > *year2)
                return -1;
            if (*year1 == *year2)
                return 0;
            if (*year1 < *year2)
                return 1;
	}
	else
            return strcmp(name1, name2);
    }
}

void sortjournal(struct journal *logs)
{
    qsort(logs, nJournal(logs), sizeof(struct journal), &sort_comparise);
}

int compariseinfo(struct journal log1, struct journal log2)
{
    int var = 1;
    if (strcmp(log1.name, log2.name) != 0)
	var = 0;
    if (*log1.number != *log2.number)
	var = 0;
    if (*log1.year != *log2.year)
	var = 0;
    return var;
}

void infojournal(struct journal *logs)
{
    system("clear");
    for (int count = 0; count < nJournal(logs);)
    {
        printf("%s\n", logs[count].name);
        printf("Issue number: %d\n", *logs[count].number);
        printf("Year of release: %d\n", *logs[count].year);
	printf("Articles:\n");
	int oldcount = count;
	printf("____________________");
        for (int i = oldcount; i < nJournal(logs); i++)
        {
	    printf("____________________");
	    count++;
	    if (count != nJournal(logs))
	    {
		if (compariseinfo(logs[i], logs[i + 1]) == 0)
		{
                    break;
		}
	    }
	}
	printf("\n");
	printf("|Autor's name      |");
	for (int i = oldcount; i < count; i++)
	    printf("|%-9s %-8s|", logs[i].fNameAutor, logs[i].lNameAutor);
	printf("\n");
	for (int i = oldcount; i < count + 1; i++)
	    printf("|__________________|");
	printf("\n");
	printf("|Title of article  |");
	for (int i = oldcount; i < count; i++)
	    printf("|%-18s|", logs[i].article);
	printf("\n");
	for (int i = oldcount; i < count + 1; i++)
	    printf("|__________________|");
	printf("\n\n");
    }
}

void freejournal(struct journal *logs)
{
    for (int i = 0; i < nJournal(logs); i++)
    {
	free(logs[i].name);
	free(logs[i].number);
	free(logs[i].year);
	free(logs[i].fNameAutor);
	free(logs[i].lNameAutor);
	free(logs[i].article);
    }
    free(logs);
}

#endif /* JOURNAL_H */

