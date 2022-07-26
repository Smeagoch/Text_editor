#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include <math.h>
#include <time.h>
#include "journal.h"


struct journal *add_journal(char *name, int num, int year_of_issue, char *fnamea, char *lnamea, char *article, int day, int mon, int year, int term)
{
    struct journal *log = (struct journal *) malloc(sizeof(struct journal));

    log->name = (char *) malloc(strlen(name) * sizeof(char));
    strcpy(log->name, name);

    log->number = num;

    log->year = year_of_issue;

    log->fNameAutor = (char *) malloc(strlen(fnamea) * sizeof(char));
    strcpy(log->fNameAutor, fnamea);

    log->lNameAutor = (char *) malloc(strlen(lnamea) * sizeof(char));
    strcpy(log->lNameAutor, lnamea);

    log->article = (char *) malloc(strlen(article) * sizeof(char));
    strcpy(log->article, article);

    log->date.tm_mday = day;
    log->date.tm_mon = mon;
    log->date.tm_year = year;

    log->term = term;

    log->next = NULL;
    return log;
}

struct journal cpy_journal(struct journal *log)
{
    struct journal p;
    p.name = (char *) malloc(strlen(log->name) * sizeof(char));
    strcpy(p.name, log->name);
    p.number = log->number;
    p.year = log->year;
    p.fNameAutor = (char *) malloc(strlen(log->fNameAutor) * sizeof(char));
    strcpy(p.fNameAutor, log->fNameAutor);
    p.lNameAutor = (char *) malloc(strlen(log->lNameAutor) * sizeof(char));
    strcpy(p.lNameAutor, log->lNameAutor);
    p.article = (char *) malloc(strlen(log->article) * sizeof(char));
    strcpy(p.article, log->article);
    p.date.tm_mday = log->date.tm_mday;
    p.date.tm_mon = log->date.tm_mon;
    p.date.tm_year = log->date.tm_year;
    p.term = log->term;
    return p;
}

void sort_journal(struct journal *logs)
{
    struct journal *iback = logs;
    if (logs != NULL)
    {
    for (struct journal *i = logs; i->next != NULL; i = i->next)
    {
	struct journal *jback = i->next;
	for (struct journal *j = i->next; j != NULL; j = j->next)
	{
	    if (strcmp(i->name, j->name) > 0)
	    {
		if (iback == i)
		{
		    struct journal *inext = i->next;
		    i->next = j->next;
		    j->next = inext;
		    jback->next = i;
		    logs = j;
		    i = j;
		    j = jback->next;
		}
		else
		{
		    struct journal *inext = i->next;
		    iback->next = j;
		    i->next = j->next;
		    j->next = inext;
		    jback->next = i;
		    i = j;
		    j = jback->next;
		}
		jback = j;
	    }
	}
	iback = i;
    }

    iback = logs;
    for (struct journal *i = logs; i->next != NULL; i = i->next)
    {
	struct journal *jback = i->next;
	for (struct journal *j = i->next; j != NULL; j = j->next)
	{
            if (strcmp(i->name, j->name) == 0)
	    {
		if (i->number > j->number)
                {
                    if (iback == i)
                    {
			struct journal *inext = i->next;
                        i->next = j->next;
                        j->next = inext;
                        logs = j;
			jback->next = i;
			i = j;
			j = jback->next;
                    }
                    else
                    {
			struct journal *inext = i->next;
                        iback->next = j;
                        i->next = j->next;
                        j->next = inext;
			jback->next = i;
                        i = j;
                        j = jback->next;
                    }
		}
            }
	    jback = j;
	}
	iback = i;
    }

    iback = logs;
    for (struct journal *i = logs; i->next != NULL; i = i->next)
    {
	struct journal *jback = i->next;
        for (struct journal *j = i->next; j != NULL; j = j->next)
        {
            if ((strcmp(i->name, j->name) == 0) && (i->number == j->number))
            {
	        if (i->year < j->year)
	        {
			struct journal *inext = i->next;
                        iback->next = j;
                        i->next = j->next;
                        j->next = inext;
			jback->next = i;
                        i = j;
                        j = jback->next;
	        }
            }
        }
	iback = i;
    }
    }
}

int comparise_info(struct journal log1, struct journal log2)
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

void info_journal(struct journal *logs, struct tm *today_date)
{
    printf("Today: %d.%d.%d\n", today_date->tm_mday, today_date->tm_mon, today_date->tm_year);
    struct journal *p = logs;
    while (p != NULL)
    {
        printf("%s\n", p->name);
        printf("Issue number: %d\n", p->number);
        printf("Year of release: %d\n", p->year);
        printf("Articles:\n");
        struct journal *oldp = p;
        printf("____________________");
        while (p != NULL)
        {
            printf("____________________");
            if (p != NULL)
		if (p->next != NULL)
                    if (comparise_info(*p, *p->next) == 0)
                    {
			p = p->next;
                        break;
                    }
	    p = p->next;
        }
        printf("\n");
        printf("|Author's name     |");
	struct journal *pd = oldp;
        while (pd != p)
	{
            printf("|%-8s %-9s|", pd->fNameAutor, pd->lNameAutor);
            pd = pd->next;
	}
	printf("\n");
	pd = oldp;
        while (pd != p)
	{
            printf("|__________________|");
            pd = pd->next;
	}
	printf("|__________________|");
	printf("\n");
        printf("|Title of article  |");
	pd = oldp;
	while (pd != p)
	{
            printf("|%-18s|", pd->article);
            pd = pd->next;
	}
	printf("\n");
	pd = oldp;
	while (pd != p)
	{
            printf("|__________________|");
            pd = pd->next;
	}
        printf("|__________________|");
	printf("\n");
	printf("|Date of issue     |");
	pd = oldp;
        while (pd != p)
        {
            printf("|%-2d.%-2d.%-4d %-2dmon. |", pd->date.tm_mday, pd->date.tm_mon, pd->date.tm_year, pd->term);
            pd = pd->next;
        }
	printf("\n");
	pd = oldp;
        while (pd != p)
        {
            printf("|__________________|");
            pd = pd->next;
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

struct journal *search_author(struct journal *logs, char *str)
{
    struct journal *slogs = NULL;
    struct journal *pslogs = NULL;
    struct journal *plogs = logs;
    while (plogs != NULL)
    {
	if (search_comparise(*plogs, str))
	{
	    struct journal *p = (struct journal *) malloc(sizeof(struct journal));
	    *p = cpy_journal(plogs);

	    p->next = NULL;
	    if (pslogs != NULL)
	    {
		pslogs->next = p;
		pslogs = pslogs->next;
	    }
	    else
	    {
		slogs = p;
		pslogs = slogs;
	    }
	}
	plogs = plogs->next;
    }
    return slogs;
}

struct journal *search_debtors(struct journal *logs, struct tm *today_date)
{
    struct journal *plogs = logs;
    struct journal *slogs = NULL;
    struct journal *pslogs;
    while(plogs != NULL)
    {
	int sum1 = plogs->date.tm_mday + 31 * plogs->date.tm_mon + 365 * plogs->date.tm_year;
	int sum2 = today_date->tm_mday + 31 * today_date->tm_mon + 365 * today_date->tm_year;
	int elapsed_time = sum2 - sum1;
	if (elapsed_time > (plogs->term * 31))
	{
	    struct journal *p = (struct journal *) malloc(sizeof(struct journal));
	    *p = cpy_journal(plogs);
	    p->next = NULL;

	    if(slogs == NULL)
	    {
		slogs = p;
		pslogs = slogs;
	    }
	    else
	    {
		pslogs->next = p;
		pslogs = pslogs->next;
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

void free_journal(struct journal *logs)
{
    struct journal *next;
    if (logs != NULL)
        for (struct journal *i = logs; i != NULL; i = next)
        {
            free(i->name);
            free(i->fNameAutor);
            free(i->lNameAutor);
            free(i->article);
	    next = i->next;
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
    struct journal *logs = NULL;
    struct journal *plog = NULL;
    char str[NBUF];

    while (estr != NULL)
    {
        int i = 0;

	struct journal *p = (struct journal *) malloc(sizeof(struct journal));

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
        p->name = (char *) malloc(strlen(str) * sizeof(char));
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
        p->fNameAutor = (char *) malloc(strlen(str) * sizeof(char));
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
        p->lNameAutor = (char *) malloc(strlen(str) * sizeof(char));
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
        p->article = (char *) malloc(strlen(str) * sizeof(char));
        strcpy(p->article, str);

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
        p->date.tm_mday = num;

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
        p->date.tm_mon = num;

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
        p->date.tm_year = num;

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
	p->term = num;

	p->next = NULL;

	if (logs == NULL)
	{
	    logs = p;
	    plog = logs;
	}
	else
	{
	    plog->next = p;
	    plog = p;
	}
	estr = fgets(buffer, NBUF, file);
    }
    fclose(file);
    return logs;
}

void journal_in_file(struct journal *logs, char *file_name)
{
    FILE *file = fopen(file_name, "w");

    struct journal *plogs = logs;
    while (plogs != NULL)
    {
	fprintf(file, "%s; %d; %d; ", plogs->name, plogs->number, plogs->year);
	fprintf(file, "%s; %s; %s; ", plogs->fNameAutor, plogs->lNameAutor, plogs->article);
	fprintf(file, "%d; %d; %d; %d;\n", plogs->date.tm_mday, plogs->date.tm_mon, plogs->date.tm_year, plogs->term);
	plogs = plogs->next;
    }
    fclose(file);
}
