#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include "journal.h"

void menu()
{
    printf("Add new journal ------------------1\n");
    printf("Print logs -----------------------2\n");
    printf("Search articles ------------------3\n");
    printf("Delete journsl -------------------4\n");
    printf("Exit -----------------------------5\n");
    printf("Enter number: ");
}

int main()
{
    system("clear");
    struct journal *logs;
    char ch;
    logs = journal_out_file("journal.txt");
    if (logs == NULL)
    {
	printf("File empty!!!\n");
	printf("Enter first journal!!!\n");
	ch = 1 + '0';
    }
    else
    {
	menu();
	ch = getchar();
	getchar();
    }
    while (ch != 5 + '0')
    {
	char buffer[NBUF];
	switch(ch - '0')
	{
	    case 1:
		char *name; int num; int year;
		char *fname; char *lname; char *article;

		printf ("Enter name of the journal: ");
		fgets (buffer, NBUF, stdin);
    		buffer[strlen(buffer) - 1] = 0;
    		name = (char *)malloc (strlen(buffer) * sizeof (char));
    		strcpy(name, buffer);
		strcat(name, "\0");

		printf ("Enter number of the journal: ");
		scanf ("%d", &num);

		printf ("Enter year of issue of the journal: ");
		scanf ("%d", &year);
		getchar();

		printf ("Enter the author's first name: ");
                fgets (buffer, NBUF, stdin);
                buffer[strlen(buffer) - 1] = 0;
                fname = (char *)malloc (strlen(buffer) * sizeof (char));
                strcpy(fname, buffer);
                strcat(fname, "\0");

		printf ("Enter the author's last name: ");
                fgets (buffer, NBUF, stdin);
                buffer[strlen(buffer) - 1] = 0;
                lname = (char *)malloc (strlen(buffer) * sizeof (char));
                strcpy(lname, buffer);
                strcat(lname, "\0");

		printf ("Enter the title of the article: ");
                fgets (buffer, NBUF, stdin);
                buffer[strlen(buffer) - 1] = 0;
                article = (char *)malloc (strlen(buffer) * sizeof (char));
                strcpy(article, buffer);
                strcat(article, "\0");

		struct journal *p = logs;
		if (p != NULL)
		{
		    while ((*p).next != NULL)
		        p = (*p).next;
		    (*p).next = addjournal(name, num, year, fname, lname, article);
		}
		else
		    logs = addjournal(name, num, year, fname, lname, article);

		free(name); free(fname); free(lname); free(article);
//		sortjournal(logs, n);
		break;

	    case 2:
		infojournal(logs);
		break;

	    case 3:
		struct journal *slogs;

		printf("Enter author for search: ");
		fgets (buffer, NBUF, stdin);
		buffer[strlen(buffer) - 1] = 0;

		slogs = search(logs, buffer);
		infojournal(slogs);

		if (slogs == NULL)
		    printf("Not found!!!\n");

		if (slogs != NULL)
		    freejournal(slogs);
		break;

	    case 4:
		printf("Enter author and article for delete: ");
		fgets(buffer, NBUF, stdin);
		buffer[strlen(buffer) - 1] = 0;
		struct journal *log = find_for_delete(logs, buffer);
		if (log != NULL)
		logs = delete_journal(logs, log);
		else
		    printf("This article not found!!!\n");
		break;

	    case 5:
		printf("Goodbye!!!\n");
		break;

	    default:
		printf("Invalid number entered!!! Repeat the input!!!\n");
		break;
	}
	menu();
	ch = getchar();
	getchar();
    }
    printf("Do you want to save the data to a file (y/n): ");
    ch = getchar();
    switch(ch - '0')
    {
	case 41:
	case 73:
	    getchar();
	    journal_in_file(logs, "journal.txt");
	    printf("Data saved!!!\n");
	    break;
	default: break;
    }
    freejournal(logs);
    return 0;
}
