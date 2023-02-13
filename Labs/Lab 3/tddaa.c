/*
2x3x4
+----------------------------------------+
|+------------------++------------------+|
||+----++----++----+||+----++----++----+||
|||1234||1234||1234||||1234||1234||1234|||
||+----++----++----+||+----++----++----+||
|+------------------++------------------+|
+----------------------------------------+

+------+
|abcdef| 6 pointers to 1's ( array of row pointers )
+------+

+--+
|mn| 2 pointers to a and d above ( array of pointers to slices )
+--+

a[i][j][k]
i chooses which slice
j chooses which row within the slice
k chooses within element with the row
*/

#include "tddaa.h"
#include <stdlib.h>

int*** allocate(int d1, int d2, int d3)
{
    int i, j;
    
    /* allocate the array of pointers to slices*/
    int*** array = malloc(d1* sizeof(int**));

    /* allocate the array of pointers to rows*/
    array[0] = malloc(d1 * d2* sizeof(int*));

    /* allocate the array of elements*/
    array[0][0] = malloc(d1 * d2 * d3* sizeof(int));

    /* set the pointers to rows*/
    for (i = 0; i < d1; i++)
    {
        /* set the pointers to slices*/
        array[i] = array[0] + i * d2;

        /* set the pointers to elements*/
        for (j = 0; j < d2; j++)
        {
            array[i][j] = array[0][0] + i * d2 * d3 + j * d3;
        }
    }

    return array;

}

void deallocate(int*** ppp)
{
    free(ppp[0][0]);
    free(ppp[0]);
    free(ppp);
}


