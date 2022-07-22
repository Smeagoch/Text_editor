#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include <math.h>
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

    log->next = NULL;
    return log;
}

/*void sortjournal(struct journal *logs)
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
*/
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

void infojournal(struct journal *logs)
{
    system("clear");
    struct journal *p = logs;
    while (p != NULL)
    {
        printf("%s\n", (*p).name);
        printf("Issue number: %d\n", (*p).number);
        printf("Year of release: %d\n", (*p).year);
        printf("Articles:\n");
        struct journal *oldp = p;
        printf("____________________");
        while (p != NULL)
        {
            printf("____________________");
            p = (*p).next;
            if (p != NULL)
		if ((*p).next != NULL)
                    if (compariseinfo(*p, (*(*p).next)) == 0)
                    {
                        break;
                    }
        }
        printf("\n");
        printf("|Author's name     |");
	struct journal *pd = oldp;
        while (pd != p)
	{
            printf("|%-8s %-9s|", (*pd).fNameAutor, (*pd).lNameAutor);
            pd = (*pd).next;
	}
	printf("\n");
	pd = oldp;
        while (pd != p)
	{
            printf("|__________________|");
            pd = (*pd).next;
	}
	printf("|__________________|");
	printf("\n");
        printf("|Title of article  |");
	pd = oldp;
	while (pd != p)
	{
            printf("|%-18s|", (*pd).article);
            pd = (*pd).next;
	}
	printf("\n");
	pd = oldp;
	while (pd != p)
	{
            printf("|__________________|");
            pd = (*pd).next;
	}
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

struct journal *search(struct journal *logs, char *str)
{
    struct journal *slogs = NULL;
    struct journal *lslogs = NULL;
    struct journal *plogs = logs;
    while (plogs != NULL)
    {
	if (search_comparise(*plogs, str))
	{
	    struct journal *pslogs = (struct journal *)malloc(sizeof(struct journal));
	    *pslogs = *plogs;
	    pslogs->next = NULL;
	    if (lslogs != NULL)
	    {
		lslogs->next = pslogs;
	    }
	    else
	    {
		slogs = pslogs;
		lslogs = slogs;
	    }
	}
	plogs = plogs->next;
    }
    return slogs;
}

struct journal *find_for_delete(struct journal *logs, char *str)
{
    struct journal *p = logs;
    char buffer[NBUF];
    while (p != NULL)
    {
        strcpy(buffer, p->fNameAutor);
	strcat(buffer, " "); strcat(buffer, p->lNameAutor);
	strcat(buffer, " "); strcat(buffer, p->article);
	if (strcmp(buffer, str) == 0)
	{
	    return p;
	    break;
	}
	p = p->next;
    }
    if (p == NULL)
	return NULL;
}

struct journal *delete_journal(struct journal *logs, struct journal *delete_log)
{
    struct journal *p = logs;
    free(delete_log->name); free(delete_log->fNameAutor); free(delete_log->lNameAutor); free(delete_log->article);
    if (logs == delete_log)
    {
	p = p->next;
	free(delete_log);
	return p;
    }
    else
    {
        while (p != NULL)
        {
	    if (p->next == delete_log)
	    {
	        p->next = delete_log->next;
	        free(delete_log);
	        break;
	    }
	    p = p->next;
        }
    return logs;
    }
}

void freejournal(struct journal *logs)
{
    struct journal *next;
    for (struct journal *i = logs; (*i).next != NULL; i = next)
    {
        free((*i).name);
        free((*i).fNameAutor);
        free((*i).lNameAutor);
        free((*i).article);
	next = (*i).next;
	free(i);
    }
}

struct journal *journal_out_file(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
	return NULL;
    char buffer[NBUF];
    char *estr = fgets(buffer, NBUF, file);
    struct journal *log = NULL;
    struct journal *plog = NULL;;
    char str[NBUF];

    while (estr != NULL)
    {
        int i = 0;

	struct journal *p = (struct journal *)malloc(sizeof(struct journal));

        for (i; i < NBUF; i++)
        {
            if (buffer[i] == 59)
            {
		str[i] = 0;
                i = i + 2;
                break;
            }
            str[i] = buffer[i];
        }
        p->name = (char *)malloc(strlen(str) * sizeof(char));
        strcpy(p->name, str);

	int j = 0;
        for (i, j; i < NBUF; i++, j++)
        {
            if (buffer[i] == 59)
            {
		str[j] = 0;
                i = i + 2;
                break;
            }
            str[j] = buffer[i];
        }
	int num = 0;
	for (j = 0; j < strlen(str); j++)
	    num = num + (str[j] - '0') * pow(10, strlen(str) - (j + 1));
	p->number = num;

        for (i, j = 0; i < NBUF; i++, j++)
        {
            if (buffer[i] == 59)
            {
		str[j] = 0;
                i = i + 2;
                break;
            }
            str[j] = buffer[i];
        }
	num = 0;
	for (j = 0; j < strlen(str); j++)
	    num = num + (str[j] - '0') * pow(10, strlen(str) - (j + 1));
        p->year = num;

	for (i, j = 0; i < NBUF; i++, j++)
        {
            if (buffer[i] == 59)
            {
		str[j] = 0;
                i = i + 2;
                break;
            }
            str[j] = buffer[i];
        }
        p->fNameAutor = (char *)malloc(strlen(str) * sizeof(char));
        strcpy(p->fNameAutor, str);

        for (i, j = 0; i < NBUF; i++, j++)
        {
            if (buffer[i] == 59)
            {
		str[j] = 0;
                i = i + 2;
                break;
            }
            str[j] = buffer[i];
        }
        p->lNameAutor = (char *)malloc(strlen(str) * sizeof(char));
        strcpy(p->lNameAutor, str);

        for (i, j = 0; i < NBUF; i++, j++)
        {
            if (buffer[i] == 59)
            {
		str[j] = 0;
                i = i + 2;
                break;
            }
            str[j] = buffer[i];
        }
        p->article = (char *)malloc(strlen(str) * sizeof(char));
        strcpy(p->article, str);

	p->next = NULL;

	if (log == NULL)
	{
	    log = p;
	    plog = log;
	}
	else
	{
	    plog->next = p;
	    plog = p;
	}
	estr = fgets(buffer, NBUF, file);
    }
    fclose(file);
    return log;
}

void journal_in_file(struct journal *logs, char *file_name)
{
    FILE *file = fopen(file_name, "w");

    struct journal *plogs = logs;
    while (plogs != NULL)
    {
	fprintf(file, "%s; %d; %d; ", plogs->name, plogs->number, plogs->year);
	fprintf(file, "%s; %s; %s;\n", plogs->fNameAutor, plogs->lNameAutor, plogs->article);

	plogs = plogs->next;
    }
    fclose(file);
}
