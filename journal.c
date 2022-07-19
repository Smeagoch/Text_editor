#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include "journal.h"

void EnterStr(char *str)
{
    char buffer[NBUF];
    fgets (buffer, NBUF, stdin);
    buffer[strlen(buffer) - 1] = 0;
    str = (char *)malloc (strlen(buffer) * sizeof (char));
    strcpy(str, buffer);
    strcat(str, "\0");
}

struct journal *addjournal(char *name, int num, int year, char *fnamea, char *lnamea, char *article)
{
    struct journal *log = (struct journal *)malloc(sizeof(struct journal));

    log->name = (char *)malloc(strlen(name) * sizeof(char));
    strcpy(log->name, name);

    log->number = num;

    log->year = year;

    log->fNameAutor = (char *)malloc(strlen(fnamea) * sizeof(char));
    strcpy(log->fNameAutor, fnamea);

    log->lNameAutor = (char *)malloc(strlen(lnamea) * sizeof(char));
    strcpy(log->lNameAutor, lnamea);

    log->article = (char *)malloc(strlen(article) * sizeof(char));
    strcpy(log->article, article);

    return log;
}

void sortjournal(struct journal **logs, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
	for (int j = i + 1; j < n; j++)
	{
	    if (strcmp((*logs[i]).name, (*logs[j]).name) > 0)
	    {
		struct journal *p = logs[i];
		logs[i] = logs[j];
		logs[j] = p;
	    }
	}
    }

    for (int i = 0; i < n - 1; i++)
    {
	for (int j = i + 1; j < n; j++)
	{
            if (strcmp((*logs[i]).name, (*logs[j]).name) == 0)
	    {
		if ((*logs[i]).number > (*logs[j]).number)
                {
        	    struct journal *p = logs[i];
                    logs[i] = logs[j];
                    logs[j] = p;
		}
            }
	}
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((strcmp((*logs[i]).name, (*logs[j]).name) == 0) && ((*logs[i]).number == (*logs[j]).number))
            {
	        if ((*logs[i]).year < (*logs[j]).year)
	        {
                    struct journal *p = logs[i];
                    logs[i] = logs[j];
                    logs[j] = p;
	        }
            }
        }
    }

}

int compariseinfo(struct journal log1, struct journal log2)
{
    int var = 1;
    if (strcmp(log1.name, log2.name) != 0)
        var = 0;
    if (log1.number != log2.number)
        var = 0;
    if (log1.year != log2.year)
        var = 0;
    return var;
}

void infojournal(struct journal **logs, int n)
{
    system("clear");
    for (int count = 0; count < n;)
    {
        printf("%s\n", (*logs[count]).name);
        printf("Issue number: %d\n", (*logs[count]).number);
        printf("Year of release: %d\n", (*logs[count]).year);
        printf("Articles:\n");
        int oldcount = count;
        printf("____________________");
        for (int i = oldcount; i < n; i++)
        {
            printf("____________________");
            count++;
            if (count != n)
            {
                if (compariseinfo(*logs[i], *logs[i + 1]) == 0)
                {
                    break;
                }
            }
        }
        printf("\n");
        printf("|Author's name     |");
        for (int i = oldcount; i < count; i++)
            printf("|%-8s %-9s|", (*logs[i]).fNameAutor, (*logs[i]).lNameAutor);
        printf("\n");
        for (int i = oldcount; i < count + 1; i++)
            printf("|__________________|");
        printf("\n");
        printf("|Title of article  |");
        for (int i = oldcount; i < count; i++)
            printf("|%-18s|", (*logs[i]).article);
        printf("\n");
        for (int i = oldcount; i < count + 1; i++)
            printf("|__________________|");
        printf("\n\n");
    }
}

int search_comparise(struct journal log, char *str)
{
    int var = 0;
    char buffer[NBUF];
    strcpy(buffer, log.fNameAutor);
    if (strcmp(str, strcat(strcat(buffer, " "), log.lNameAutor)) == 0)
	return 1;
    else
    {
	strcpy(buffer, log.lNameAutor);
	if (strcmp(str, strcat(strcat(buffer, " "), log.fNameAutor)) == 0)
	    return 1;
        else
	{
	    if (strcmp(str, log.fNameAutor) == 0)
	        return 1;
            else
	    {
		if (strcmp(str, log.lNameAutor) == 0)
	            return 1;
		else
		    return 0;
	    }
	}
    }
}

int search(struct journal **logs, int n, char *str, struct journal **slogs)
{
    struct journal **p = slogs;
    for (int i = 0; i < n; i++)
    {
	if (search_comparise(*logs[i], str))
	{
	    p++;
	    if (p - slogs != 1)
	    {
	        slogs = (struct journal **)realloc(slogs, (p - slogs) * sizeof(struct journal *));
	    }
	    *(p - 1) = logs[i];
	}
    }
    return p - slogs;
}

void freejournal(struct journal **logs, int n)
{
    for (int i = 0; i < n; i++)
    {
        free((*logs[i]).name);
        free((*logs[i]).fNameAutor);
        free((*logs[i]).lNameAutor);
        free((*logs[i]).article);
	free(logs[i]);
    }
    free(logs);
}
