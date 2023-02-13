/* File header
 * ===========
 * file:       fuse.cpp
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 1
 * date:       09/09/2022
 *
 * file content:
 * this is a source file for fuse and unfuse functions, requires fuse.h
 */

#include "fuse.h"
#include <stdio.h>    /* fopen/fclose/fread/fwrite */
#include <stdlib.h>   /* malloc/free */
#include <string.h>   /* strlen */

#define xDEBUG

 /* Function: Fuse
  *    Given an array of file names, the number of files, and output file name.
  *    Read all files in the array and write the Name, size and contents to the output file.
  *
  *    Parameters:
  *     char const** filenames - list of file names
  *     int num_files          - number of files in list
  *     char const* output     - output file
  *
  *    Returns: 0 on success, 1 on failure.
  */
int fuse(char const** filenames, int num_files, char const* output)
{
    int BUFFER_SIZE = 1 << 16; /* 65 Kb */
    int NAME_SIZE = 1 << 8;    /* 256 bytes */
    int i; /* loop counter */
    char* buffer = NULL; /* buffer for reading/writing */
    char* nameBuffer = NULL; /* buffer for reading/writing name */
    FILE* out = NULL; /* output file */

    /* if no files, return */
    if (!filenames || !output)
    {
        printf("Error: Input or output filenames specified");
        return 1;
    }

    out = fopen(output, "wb"); /* open output file */

    /*if output file is not opened*/
    if (!out)
    {
        printf("Error: Could not open output file %s", output);
        return 1;
    }

    /* for each file */
    for (i = 0; i < num_files; i++) {
        /* open input file */
        FILE* input = fopen(filenames[i], "rb");
        int len = 0; /* byte read counter */

        /* if input file is not opened */
        if (input == NULL)
        {
            fclose(out); /* close output file */
            printf("Error: cannot open file %s", filenames[i]);

            return 1;
        }

        /* buffer for output */
        nameBuffer = (char*)malloc(NAME_SIZE);

        /* if buffer is not allocated */
        if (!nameBuffer)
        {
            fclose(out); /* close output file */
            fclose(input); /* close input file */
            printf("Error: cannot allocate memory");

            return 1;
        }

        /* write name of file to output */
        strncpy(nameBuffer, filenames[i], NAME_SIZE);
        len = strlen(filenames[i]); /* length of filename */
        nameBuffer[len++] = '\0'; /* null terminate */

        /* write filename to output */
        fwrite(nameBuffer, sizeof(char), len, out);

        free(nameBuffer);

        /* buffer for output */
        buffer = (char*)malloc(BUFFER_SIZE);

        /* if buffer is not allocated */
        if (!buffer)
        {
            fclose(out); /* close output file */
            fclose(input); /* close input file */
            printf("Error: cannot allocate memory");

            return 1;
        }

        len = 0;

        while (!feof(input))
        {
            char* newbuf; /* for buffer extending */

            /* read file contents to buffer and store num of bytes read*/
            len += fread(buffer + len, sizeof(char), BUFFER_SIZE - len, input);

            /* check if buffer is full */
            if (len == BUFFER_SIZE && !feof(input))
            {
                /* double buffer size */
                BUFFER_SIZE *= 2; 
                newbuf = (char*)malloc(BUFFER_SIZE);
                
                if (!newbuf)
                {
                    free(buffer); /* free buffer */
                    fclose(out); /* close output file */
                    fclose(input); /* close input file */
                    printf("Error: cannot allocate memory");

                    return 1;
                }

                /* copy buffer */
                memcpy(newbuf, buffer, BUFFER_SIZE / 2);

                /*exchange pointer*/
                free(buffer);
                buffer = newbuf;
            }
        }

        /* write bytes read to output */
        fwrite(&len, sizeof(int), 1, out);

        fwrite(buffer, sizeof(char), len, out); /* write buffer to output */

        free(buffer); /* free buffer */
        fclose(input); /* close readfile */
    }

    fclose(out); /* close output file */

    return 0;
}

/* Function: Unfuse
*    Given an input file name, read the fused file contents and write the 
*    contents to separate files.
*
*    Parameters:
*     char const* filename - name of file to unfuse
*
*    Returns: 0 on success, 1 on failure.
*/
int unfuse(char const* filename)
{
    int NAME_SIZE = 1 << 8;    /* 256 bytes */
    FILE* input = NULL;         /* input file */

    /* if no file, return */
    if (!filename)
    {
        printf("Error: Input filename not specified");
        return 1;
    }
    
    input = fopen(filename, "rb"); /* open input file */

    if (!input)
    {
        printf("Error: Could not open input file %s", filename);
        return 1;
    }

    /* while not end of file */
    while (!feof(input))
    {
        char* buffer = NULL; /* buffer for reading/writing */
        int size; /* size of file to write*/
        FILE* out = NULL; /* output file */
        int name_len = 0; /* length of filename */

        char* name_buffer = (char*)calloc(NAME_SIZE, sizeof(char));

        if (name_buffer == NULL)
        {
            printf("Error: Could not allocate memory");
            return 1;
        }

        /* read name of file */
        for (name_len = 0; name_len < NAME_SIZE; name_len++)
        {
            name_buffer[name_len] = fgetc(input); /* read char from input */

            if (feof(input)) /* if end of file */
            {
                fclose(input); /* close input file */
                free(name_buffer);
                return 1;
            }

            /*if end of name stop reading*/
            if (name_buffer[name_len] == '\0')
            {
                break;
            }
        }
        
        /* open output file */
        out = fopen(name_buffer, "wb");

        if (!out)
        {
            fclose(input); /* close input file */
            free(name_buffer);
            printf("Error: Could not open output file %s", name_buffer);
            return 1;
        }

        /* read size of file */
        fread(&size, sizeof(int), 1, input);

        /* read file contents */
        buffer = (char*)calloc(size, sizeof(char));

        if (!buffer)
        {
            free(name_buffer);
            fclose(input);
            fclose(out);
            printf("Error: Could not allocate memory");
            return 1;
        }

        /* read file contents */
        fread(buffer, sizeof(char), size, input);
        /* write file contents */
        fwrite(buffer, sizeof(char), size, out);

        /* free buffers */
        free(buffer);
        free(name_buffer);

        /* close output file */
        fclose(out);
    }

    fclose(input); /* close input file */

    return 0; /* success */
}
