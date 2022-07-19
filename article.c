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
    printf("Exit -----------------------------4\n");
    printf("Enter number: ");
}

/*void init(struct journal **logs)
{
    char name[5][10] = {"what ", "what ", "Never", "Never", "Do it"};
    int num = 1;
    int year = 2015;
    char fname[5][10] = {"Nikita ", "Egor ", "Grisha ", "Nikita ", "Egor "};
    char lname[5][10] = {"Shutov ", "Smolencev", "Nikolaev ", "Shutov ", "Smolencev"};
    char article[5][11] = {"Sleep ", "Programmer", "Zoo ", "Never ", "Do it "};

    char **Name= (char **)malloc(5 * sizeof(char *));
    char **Fname= (char **)malloc(5 * sizeof(char *));
    char **Lname= (char **)malloc(5 * sizeof(char *));
    char **Article= (char **)malloc(5 * sizeof(char *));

    for (int i = 0; i < 5; i++)
    {
    	Name[i] = (char *)malloc (strlen(name[i]) * sizeof(char));
    	Fname[i] = (char *)malloc (strlen(fname[i]) * sizeof(char));
    	Lname[i] = (char *)malloc (strlen(lname[i]) * sizeof(char));
    	Article[i] = (char *)malloc (strlen(article[i]) * sizeof(char));

    	strcpy(Name[i],name[i]);
    	strcpy(Fname[i], fname[i]);
	strcpy(Lname[i], lname[i]);
	strcpy(Article[i], article[i]);

	logs[i] = addjournal(Name[i], num, year, Fname[i], Lname[i], Article[i]);

	free(Name[i]); free(Fname[i]); free(Lname[i]); free(Article[i]);
    }
    free(Name); free(Fname); free(Lname); free(Article);
}*/

int main()
{
    system("clear");
    int n = 0;
    struct journal **logs = (struct journal **)malloc(n + 1 * sizeof(struct journal *));
    char ch;
    while (ch != 4 + '0')
    {
	menu();
	ch = getchar();
	char buffer[128];
	switch(ch - '0')
	{
	    case 1:
		getchar();
		n++;

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

		if (n != 1)
		    logs = (struct journal **)realloc(logs, n + 1 * sizeof(struct journal *));
		logs[n - 1] = addjournal(name, num, year, fname, lname, article);

		free(name); free(fname); free(lname); free(article);
		sortjournal(logs, n);
		break;

	    case 2:
		getchar();
		infojournal(logs, n);
		break;

	    case 3:
		getchar();
		char buffer[NBUF];
		struct journal **slogs = (struct journal **)malloc(sizeof(struct journal *));
		printf("Enter author for search: ");
		fgets (buffer, NBUF, stdin);
		buffer[strlen(buffer) - 1] = 0;
		int size = search(logs, n, buffer, slogs);
		if (size != 0)
		    infojournal(slogs, size);
		else
		    printf("Not found!!!\n");
		free(slogs);
		break;

	    default:
		getchar();
		printf("Invalid number entered!!! Repeat the input!!!\n");
		break;
	}
    }
    freejournal(logs, n);
    return 0;
}
