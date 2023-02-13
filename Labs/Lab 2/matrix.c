#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

void  matrix_print( Matrix m, int num_rows, int num_columns ) {
    int i, j;
    for ( i=0; i<num_rows; ++i ) {
        for ( j=0; j<num_columns; ++j ) {
            printf( "%4i ", m[i][j] );
        }
        printf( "\n" );
    }
}

/* allocate 2-dimentional array with the specified dimensions */
Matrix matrix_create( int num_rows, int num_columns )
{
    Matrix m = malloc( num_rows * sizeof(int*) );
    if (m)
    {
        int i;
        for (i = 0; i < num_rows; i++)
        {
            m[i] = malloc( num_columns * sizeof(int) );
            if (!m[i])
            {
                matrix_delete( m, i );
                return NULL;
            }
        }
    }

    return m;
}

/* matrix addition, assume result matrix is already allocated */
void matrix_add( Matrix m1, Matrix m2, Matrix result, int num_rows, int num_columns )
{
    int i, j;

    for (i = 0; i < num_rows; i++)
    {
        for (j = 0; j < num_columns; j++)
        {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

/* matrix transposition, returns a new matrix, does not delete the original */
Matrix matrix_transpose( Matrix m, int num_rows, int num_columns )
{
    Matrix result = matrix_create( num_columns, num_rows );
    int i,j;

    for (i = 0; i < num_rows; i++)
    {
        for (j = 0; j < num_columns; j++)
        {
            result[j][i] = m[i][j];
        }
    }

    return result;
}

/* deallocate matrix */
void   matrix_delete( Matrix m, int num_rows )
{
    int i;

    for (i = 0; i < num_rows; i++)
    {
        free( m[i] );
        m[i] = NULL;
    }

    free( m );
}

/* delete one row (index r) from matrix */
void   matrix_delete_row( Matrix m, int r, int num_rows )
{
    int i;

    free(m[r]);
    m[r] = NULL;

    for (i = r; i < num_rows - 1; i++)
    {
        m[i] = m[i + 1];
    }
}

/* delete one column (index c) from matrix */
void   matrix_delete_column( Matrix m, int c, int num_rows, int num_columns )
{
    int i, j;
    
    for (i = 0; i < num_rows; i++)
    {
        for (j = c; j < num_columns - 1; j++)
        {
            m[i][j] = m[i][j + 1];
        }
    }

}