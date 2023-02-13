#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"

char * readline( FILE *stream )
{
    unsigned size = 0;     // The number of elements in the array
    unsigned capacity = 2; // The allocated size of the array
    char *array = calloc(capacity, sizeof(char*));        // The allocated array
    while ((fgets(array + size, capacity - size, stream)) != NULL) { /* read till end-of-file or till the first error */
        size = strlen(array);
        if (size + 1 >= capacity)
        {
            capacity *= 2;
            char* temp = calloc(capacity, sizeof(char*));  ;

            for (unsigned i = 0; i < size; ++i)
            {
                *(temp + i) = *(array + i);
            }

            free(array);

            array = temp;
        }
        if (array[size - 1] == '\n')
        {
            array[size - 1] = '\0';
            break;
        }
    }

    return array;
}