#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char* pointer;
    unsigned lenght;
} string;

//===========================================================================================

unsigned size_of_file ();

char* read_file (unsigned size_f, unsigned* number_of_strings);

string* fill_strings (unsigned number_of_strings, unsigned size_f, char* text);

int compare_strings_and_skip_spaces (const void* string_1, const void* string_2);

void print_sorted_onegin (string* mass_of_strings, unsigned number_of_strings);

void skip_spaces (string* str1, string* str2);

//===========================================================================================

int main ()
{
    unsigned number_of_strings = 0;
    unsigned size_f = size_of_file ();

    char* text = read_file (size_f, &number_of_strings);

    string* mass_of_strings = fill_strings (number_of_strings, size_f, text);

    qsort (mass_of_strings, number_of_strings, sizeof(string), compare_strings_and_skip_spaces);

    print_sorted_onegin (mass_of_strings, number_of_strings);

    free (text);
    free (mass_of_strings);

    return 0;
}

//===========================================================================================

unsigned size_of_file ()
{
    struct stat file_info;
    stat ("onegin.txt", &file_info);
    return file_info.st_size;
}

//===========================================================================================

char* read_file (unsigned size_f, unsigned* number_of_strings)
{
    FILE* onegin = fopen ("onegin.txt", "r");
    assert (onegin != NULL);
    char* text = (char*) calloc (size_f, sizeof (char) );

    for (unsigned i = 0; i < size_f; i++)
    {
        text[i] = (char) fgetc (onegin);
        if (text[i] == '\n')
        {
            text[i] = '\0';
            (*number_of_strings)++;
        }
    }
    fclose (onegin);
    return text;
}

//===========================================================================================

string* fill_strings (unsigned number_of_strings, unsigned size_f, char* text)
{
    string* mass_of_strings = (string*) calloc (number_of_strings, sizeof (string) );
    unsigned i = 0;
    unsigned distance = 0;
    for (unsigned j = 0; j < size_f; j++)
        {
            if (text[j] == '\0')
            {
                mass_of_strings[i].pointer = text + distance;
                mass_of_strings[i].lenght = strlen (text + distance);
                i++;
                distance = j + 1;
            }
        }
    return mass_of_strings;
}

//===========================================================================================

int compare_strings_and_skip_spaces (const void* string_1, const void* string_2)
{
    string* str1 = (string*) string_1;
    string* str2 = (string*) string_2;

    skip_spaces (str1, str2);
    unsigned i = 0;

    while (tolower (*(str1->pointer + i)) == tolower (*(str2->pointer + i)) && (*(str1->pointer + i) != '\0') && (*(str2->pointer + i) != '\0'))
    {
        i++;
        skip_spaces (str1, str2);
    }
    return tolower (*(str1->pointer + i)) - tolower (*(str2->pointer + i));
}

//===========================================================================================

void print_sorted_onegin (string* mass_of_strings, unsigned number_of_strings)
{
    FILE* sorted_onegin = fopen ("sorted_onegin.txt", "w");

    for (unsigned i = 0; i < number_of_strings; i++)
        fprintf (sorted_onegin, "%s\n", mass_of_strings[i].pointer);

    fclose (sorted_onegin);
}

//===========================================================================================

void skip_spaces (string* str1, string* str2)
{
    while (isalpha (*(str1->pointer)) == 0)
        str1->pointer++;
    while (isalpha (*(str2->pointer)) == 0)
        str2->pointer++;
}
