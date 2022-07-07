#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nbuf 128


int str_find_word(char * pStr, char ** pWord) // Find word function
{
    int count = 1;
    if (97 <= *pStr && *pStr <= 122) // The condition first lowercase letter
    {
	*pWord = pStr;
	count++;
    }
    for (int i = 0; i < strlen(pStr); i++)
        if (*(pStr + i) == 32 && (97 <= *(pStr + i + 1) && *(pStr + i + 1) <= 122)) // The condition for searching for words with a lowercase letter
	{
	    if( count != 1)
	    {
		pWord = realloc (pWord, (count) * sizeof(char *));
	    }
	    *(pWord + count - 1) = pStr + i + 1;
	    count++;
	}
    return count;
}


void text_editor(char * pStr, char **pWord, int nWord) // Text editor function
{
    char * pdStr = pStr;
    char ** pdWord = pWord;
    int len; // Length of new string
    if (nWord > 9)
	len = (strlen(pStr) + 4 * nWord - 9);
    else
	len = (strlen(pStr) + 3 * nWord);
    char pNewStr[len];

    for (int i = 0; i < len; i++)
    {
	if (pdStr == *pdWord) // The condition for numbering a word in a string
	{
			      // Numbering a word
	    *(pNewStr + i) = 40;
	    if (pdWord - pWord + 1 > 9)
	    {
		*(pNewStr + i + 1) = (pdWord - pWord + 1) / 10 + '0';
		i++;
	    }
	    *(pNewStr + i + 1) = (pdWord - pWord + 1) % 10 + '0';
	    *(pNewStr + i + 2) = 41;
	    i = i + 3;
	    pdWord++;
	}
	*(pNewStr + i) =  *pdStr; // Copy symbol in string
	pdStr++;
    }
    printf("%s\n", pNewStr);
    pStr = realloc(pStr, len * sizeof(char));
    strcpy(pStr,pNewStr);
}


int main()
{

    char ** pStr;
    int rows = 1;
    pStr = malloc(rows * sizeof(char *));

    printf ("!! end - stop input !!\n");
    printf ("Input your text: \n");
    char stopStr[3] = "end";

    // Input text
    for(int i = 0; i <= rows; i++)
    {
	char buffer[nbuf];
	gets(buffer); //Filling the buffer

        // The condition of stop input text
	if (buffer[0] == stopStr[0] && buffer[1] == stopStr[1] && buffer[2] == stopStr[2])
	{
	    if(rows == 1 && pStr[0] == NULL)
	    rows = 0;
	    break;
	}

	// Allocation of place for a string
	if( i == rows)
	{
	    rows++;
	    pStr = realloc(pStr, rows * sizeof(char *));
	}
	pStr[i] = malloc(strlen(buffer) * sizeof(char));

	strcpy(pStr[i],buffer); // Copy buffer in string
    }

    //Word search and numbering
    for (int i = 0; i < rows; i++)
    {
	char ** pWord = malloc(1 * sizeof(char *));
	int nWord = str_find_word(pStr[i], pWord);
	text_editor(pStr[i], pWord, nWord);
	free(pWord);
    }

    // Output text
    if(rows != 0)
	printf("Your text: \n");
    else
	printf("Not text!!!");
    for (int i = 0; i < rows; i++)
	printf ("%s\n", pStr[i]);

    // Clear mem
    if(rows != 0)
	for (int i = 0; i < rows; i++)
	    free(pStr[i]);
    free(pStr);
    return 0;
}
