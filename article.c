#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include <time.h>
#include "journal.h"

void greeting()
{
    printf("Welcome to the Library's client application!!!\n\n");
    printf("To load data from a file ---------1\n");
    printf("For initial input ----------------2\n");
    printf("Enter number: ");
}

void menu()
{
    printf("Add new journal ------------------1\n");
    printf("Print logs -----------------------2\n");
    printf("Search articles ------------------3\n");
    printf("Search debtors -------------------4\n");
    printf("Delete journal -------------------5\n");
    printf("Exit -----------------------------6\n");
    printf("Enter number: ");
}

int main()
{
    system("clear");
    const time_t timer = time(NULL);
    struct tm *today_date = localtime(&timer);
    today_date->tm_mon++;
    today_date->tm_year += 1900;

    struct journal *logs = NULL;
    char ch;

    greeting();
    ch = getchar(); getchar();
    char file_name[NBUF];
    while(1)
    {
	int count = 1;
	switch(ch - '0')
	{
	    case 1:
		printf("Enter file name: ");
		fgets(file_name, NBUF, stdin);
		file_name[strlen(file_name) - 1] = 0;
		logs = journal_out_file(file_name);
    		if (logs == NULL)
    		{
    		    printf("File empty!!!\n");
    		    printf("Would you like to choose another file?(1 - yes/ 2 - no)\n");
		    ch = getchar(); getchar();
		}
    		else
    		{
		    count = 0;
    		}
		break;
	    case 2:
		count = 0;
		break;
	    default:
		printf("Invalid number entered!!! Repeat the input!!!\n");
		ch = getchar();
		getchar();
		break;
	}
	if (count == 0)
	    break;
    }
    if (logs == NULL)
    {
	ch = 1 + '0';
    }
    else
    {
	menu();
	ch = getchar(); getchar();
    }

    while (ch != 6 + '0')
    {
	char buffer[NBUF];
	switch(ch - '0')
	{
	    case 1:
		char *name; int num; int year_of_issue;
		char *fname; char *lname; char *article;

		printf ("Enter name of the journal: ");
		fgets (buffer, NBUF, stdin);
    		buffer[strlen(buffer) - 1] = 0;
    		name = (char *) malloc(strlen(buffer) * sizeof (char));
    		strcpy(name, buffer);
		strcat(name, "\0");

		printf("Enter number of the journal: ");
		scanf("%d", &num);

		printf("Enter year of issue of the journal: ");
		scanf("%d", &year_of_issue);
		getchar();

		printf("Enter the author's first name: ");
                fgets(buffer, NBUF, stdin);
                buffer[strlen(buffer) - 1] = 0;
                fname = (char *) malloc(strlen(buffer) * sizeof (char));
                strcpy(fname, buffer);
                strcat(fname, "\0");

		printf("Enter the author's last name: ");
                fgets(buffer, NBUF, stdin);
                buffer[strlen(buffer) - 1] = 0;
                lname = (char *) malloc(strlen(buffer) * sizeof (char));
                strcpy(lname, buffer);
                strcat(lname, "\0");

		printf("Enter the title of the article: ");
                fgets(buffer, NBUF, stdin);
                buffer[strlen(buffer) - 1] = 0;
                article = (char *) malloc(strlen(buffer) * sizeof (char));
                strcpy(article, buffer);
                strcat(article, "\0");

		int day, month, year;
		printf("Enter date(d m y): ");
		scanf("%d %d %d", &day, &month, &year);
		getchar();

		int term;
		printf("Enter the period for which the journal is issued(months): ");
		scanf("%d", &term);
		getchar();

		struct journal *p = logs;
		if (p != NULL)
		{
		    while (p->next != NULL)
		        p = p->next;
		    p->next = add_journal(name, num, year_of_issue, fname, lname, article, day, month, year, term);
		}
		else
		    logs = add_journal(name, num, year, fname, lname, article, day, month, year, term);

		free(name); free(fname); free(lname); free(article);
		logs = sort_journal(logs);
		break;

	    case 2:
		info_journal(logs, today_date);
		break;

	    case 3:
		struct journal *slogs;

		printf("Enter author for search: ");
		fgets(buffer, NBUF, stdin);
		buffer[strlen(buffer) - 1] = 0;

		slogs = search_author(logs, buffer);
		info_journal(slogs, today_date);

		if (slogs == NULL)
		    printf("Not found!!!\n");

		if (slogs != NULL)
		    free_journal(slogs);
		break;

	    case 5:
		printf("Enter author and article for delete: ");
		fgets(buffer, NBUF, stdin);
		buffer[strlen(buffer) - 1] = 0;
		struct journal *log = find_for_delete(logs, buffer);
		if (log != NULL)
		    logs = delete_journal(logs, log);
		else
		    printf("This article not found!!!\n");
		break;

	    case 4:
		struct journal *debtors = search_debtors(logs, today_date);
		if (debtors != NULL)
		{
		    info_journal(debtors, today_date);
		    free_journal(debtors);
		}
		else
		    printf("Not found debtors!!!\n");
		break;

	    case 6:
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
    while(1)
    {
	int count = 1;
	ch = getchar();
	getchar();
	switch(ch - '0')
	{
	    case 41:
	    case 73:
		printf("Enter file name: ");
		fgets(file_name, NBUF, stdin);
		file_name[strlen(file_name) - 1] = 0;
		journal_in_file(logs, file_name);
		printf("Data saved!!!\n");
		count = 0;
		break;
	    case 30:
	    case 62:
		count = 0;
		break;
	    default:
		printf("%d\n", ch - '0');
		printf("Invalid number entered!!! Repeat the input!!!\n");
		printf("Save?(y/n): ");
		break;
	}
	if (count == 0)
	    break;
	ch = getchar();
	getchar();
    }
    free_journal(logs);
    return 0;
}
