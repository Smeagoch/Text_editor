#include <stdio.h>
#include <string.h>

int string_comparison(char first_word[32], char second_word[32])
{

    char ch;
    int  count = 1;

    for(int i = 0; i < 32; i++)
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
    return count;
}

int main()
{
    char first_word[32];
    char second_word[32];

    printf ("Intput first word: ");
    scanf ("%s", first_word);

    printf ("Intput second word: ");
    scanf ("%s", second_word);

    int count = string_comparison(first_word, second_word);
    if(count == 1)
    {
        printf("This words match");
    }
    else
    {
        printf("this word no match");
    }
    return 0;
}
