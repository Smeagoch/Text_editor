#include <stdio.h>
#include <string.h>
#define N 128

int string_comparison(char first_word[N], char second_word[N])
{
    int  count = 1;
    if (strlen(first_word) != strlen(second_word))
    {
	count = 0;
    }
    else
    {
        int n = strlen(first_word);
        for(int i = 0; i < n; i++)
        {
            if (first_word[i] == second_word[i])
            {
  	        count = 1;
	    }
	    else
       	    {
	        count = 0;
	        break;
	    }
        }
    }
    return count;
}

int main()
{
    char first_word[N];
    char second_word[N];

    printf ("Input first word: ");
    scanf ("%s", first_word);

    printf ("Input second word: ");
    scanf ("%s", second_word);

    int count = string_comparison(first_word, second_word);

    if(count == 1)
    {
        printf("This words match\n");
    }
    else
    {
        printf("this word no match\n");
    }
    return 0;
}
