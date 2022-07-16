#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "journal.h"

int main()
{
    system("clear");
    struct journal *logs = (struct journal *)malloc(1 * sizeof(struct journal));
    for (int i = 0; i < 1; i++)
    {
	logs[i].name = malloc(1);
	logs[i].number = (int *)malloc(sizeof(int));
	logs[i].year = (int *)malloc(sizeof(int));
	logs[i].lNameAutor = malloc(1);
	logs[i].fNameAutor = malloc(1);
	logs[i].article = malloc(1);
	addjournal(logs[i]);
    }
    sortjournal(logs);

    infojournal(logs);

    freejournal(logs);
    return 0;
}
