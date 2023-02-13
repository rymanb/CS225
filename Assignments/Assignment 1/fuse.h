/* File header
 * ===========
 * file:       fuse.h
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 1
 * date:       09/09/2022
 *
 * file content:
 * this is a header file for fuse and unfuse functions
 */

#ifndef FUSE_H
#define FUSE_H

#include <stddef.h> /* size_t definition */

enum 
{E_BAD_SOURCE=1, E_BAD_DESTINATION, E_NO_MEMORY };
#ifdef __cplusplus
extern "C" 
{ 
#endif

int unfuse( char const * filename );
int fuse( char const ** filenames, int num_files, char const * output);
#ifdef __cplusplus 
} 
#endif


#endif 

/* 
+-------------+--------+-----------+-------------+--------+-----------+....
|filename1    |filesize|data ......|filename1    |filesize|data ......|....
|\0 terminated| int    |           |\0 terminated| int    |           |....
+-------------+--------+-----------+-------------+--------+-----------+....
*/
