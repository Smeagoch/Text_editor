#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define nbuf 128



int main()
{

    char ** pStr;
    int rows = 1;
    pStr = malloc(rows * sizeof(char *)/* + rows * nbuf * sizeof(char)*/);
    for ( int i = 0; i < rows; i++)
        pStr[i] = malloc(nbuf * sizeof(char));


    printf ("Input your text: \n");
    char stopStr[3] = "end";
    for(int i = 0; i <= rows; i++)
    {
	char buffer[nbuf];
	gets(buffer);

	if (buffer[0] == stopStr[0] && buffer[1] == stopStr[1] && buffer[2] == stopStr[2])
	    break;

	if( i == rows)
	{
	    rows++;
	    pStr = realloc(pStr, rows * sizeof(char *));
	    pStr[i] = malloc(nbuf * sizeof(char));
	}

	for(int j = 0; j < strlen(buffer); j++)
	    pStr[i][j] = buffer[j];
	printf("%s\n", pStr[i]);
    }

    printf("Your text: \n");
    for (int i = 0; i < rows; i++)
	printf ("%s %d\n", pStr[i], &pStr[i]);

    for (int i = 0; i < rows; i++)
	free(pStr[i]);
    free(pStr);
    return 0;
}
