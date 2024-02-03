#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 1024

typedef struct UserInput
{
    char * text;
    char * words;
}UserInput_t;

void menu(UserInput_t*);
int countWords(UserInput_t*, int*);

int main(int argc, char * argv[])
{
    UserInput_t userInput;
    int * wordsCounter = (int*)malloc(sizeof(int) * 4);

    menu(&userInput);
    int size = countWords(&userInput, wordsCounter);

    for (int i = 0; i < size; i++)
    {
        printf("\nWORD%d=%d", i, *(wordsCounter+i));
    }

    return 0;
}

void menu(UserInput_t * userInput)
{
    char * str1 = (char*)malloc(sizeof(char) * (STRING_SIZE + 1));

    printf("Put your text in here: ");
    fgets(str1, STRING_SIZE, stdin);
    str1[strcspn(str1, "\n")] = 0;
    userInput->text = str1;

    char * str2 = (char*)malloc(sizeof(char) * (STRING_SIZE + 1));

    printf("Put the words here: ");
    fgets(str2, STRING_SIZE, stdin);
    str2[strcspn(str2, "\n")] = 0;
    userInput->words = str2;
}

int countWords(UserInput_t * userInput, int * wordsCounter)
{
    char * str = (char*)malloc(sizeof(char) * (STRING_SIZE + 1));
    int index = 0;

    for (int i = 0, s = -1; i <= strlen(userInput->words); i++)
    {
        s++;
        
        if (userInput->words[i] == ' ' || userInput->words[i] == '\0')
        {
            wordsCounter[index] = 0;

            str[s] = '\0';

            for (int j = 0, k = 0; j <= strlen(userInput->text); j++)
            {           
                if (str[k] == userInput->text[j])
                {
                    k++;
                }
                else 
                {
                    k = 0;
                }

                if (k == strlen(str) && (userInput->text[j + 1] == ' ' || userInput->text[j + 1] == '\0') &&(userInput->text[j - k] == ' ' || j - k == -1))
                {
                    
                    wordsCounter[index]+=1;

                    k = 0;
                }
            }

            free(str);
            str = (char*)malloc(sizeof(char));

            s = -1;
            index++;

            continue;
        }

        str[s] = userInput->words[i];
    }

    return index;
}