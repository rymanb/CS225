/* File header
 * ===========
 * file:       rangelist.c
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 2
 * date:       09/28/2022
 *
 * file content:
 * this is a source file for rangelist to insert values into a linked list, requires rangelist.h
 */

#include "rangelist.h"
#include <stdlib.h> /* NULL/malloc/free */
#include <stdio.h>  /* printf */

#define xDEBUG

/* helper function, prototyped in the implementation file, so NOT available in the main */
void dump_node(struct RangeNode *p);

/* your implementations: insert_value, get, delete */

/* insert a single value into the list
*  ppHead - pointer to the pointer to the head of the list
*  position - position to insert the value
*  value - value to insert
*
*  returns: 0 on success, 1 on error (allocation error)
*/
int insert_value(struct RangeNode **ppHead, int position, int value)
{
  struct RangeNode *p = *ppHead; /* pointer to the head of the list, for traversing */
  struct RangeNode *prev = NULL; /* pointer to previous node */
  struct RangeNode *new_node = NULL; /* pointer to new node to insert*/

  /* find the node that contains the position */
  while (p != NULL && p->begin < position)
  {
    prev = p; /* save the previous node */
    p = p->next; /* move to the next node */
  }

  /* if the node already exists with value do */
  if ( prev != NULL && prev->end > position + 1 && prev->begin <= position && prev->value == value)
  {
    return 0;
  }

  /* if value is 0 and the node is found, delete it */
  else if (value == 0)
  {
    /* if position is at start of node */
    if (p != NULL && p->begin == position)
    {
      /* if node is first node */
      if (prev == NULL)
      {
        *ppHead = p->next; /* set head to next node */
      }
      else
      {
        prev->next = p->next; /* set previous node to next node */
      }

      free(p); /* free node */
      return 0; /* return success */
    }

    return 1; /* return error */
  }

  /* if position is between two nodes, split the node */
  else if (prev != NULL && prev->begin <= position && prev->end > position && value != prev->value)
  {
    struct RangeNode *next_node; /* pointer to next node for insertion */
    new_node = malloc(sizeof(struct RangeNode)); /* allocate memory for new node */

    /* if allocation failed */
    if (new_node == NULL)
    {
      return 1; /* return error */
    }

    /* if position is at front of node, just insert the value */
    if (prev->begin == position)
    {
      /* set new node values */
      new_node->begin = position;
      new_node->end = position;
      new_node->value = value;
      new_node->next = p->next; /* set new node next to next node */
      prev->next = new_node;    /* set previous node next to new node */

      return 0; /* return success */
    }
    /* if position is at end of node*/
    else if (prev->end - 1 == position)
    {
      /* set new node values */
      new_node->begin = position;
      new_node->end = position + 1;
      new_node->value = value;
      new_node->next = p;   /* set new node next to curent node */
      prev->end--;          /* decrement previous node end */
      prev->next = new_node; /* set previous node to point at new node */

      return 0; /* return success */
    }
    /* otherwise, split the node */
    else
    {
      next_node = malloc(sizeof(struct RangeNode));

      if (next_node == NULL)
      {
        return 1; /* return error */
      }

      /* set new node values */
      new_node->begin = position;
      new_node->end = position + 1;
      new_node->value = value;
      new_node->next = next_node; /* next node is next node */

      /* set next node values */
      next_node->begin = new_node->end;
      next_node->end = prev->end;
      next_node->value = prev->value; /* set next node value to previous node value */
      next_node->next = p; /* point next node to current node */

      /* update prev node values to new split end */
      prev->end = position; 
      prev->next = new_node;

      return 0; /* return success */
    }

    return 1; /* return error */
  }
  /* if value is next to a node of the same value, extend the node */
  else if (p != NULL && p->begin - 1 == position && p->value == value)
  {
    /* if prev is the same value, merge the nodes */
    if (prev != NULL && prev->end == position && prev->value == value)
    {
      prev->end = p->end; /* set previous node end to current node end */
      prev->next = p->next; /* set previous node next to current node next */
      free(p); /* free node */
    }
    else
    {
      p->begin--; /* if you dont need to merge just decrement the begin */
    }

    return 0; /* return success */
  }
  /* if value is after a node of the same value, extend the node */
  else if (prev != NULL && prev->end == position && prev->value == value)
  {
    /* if next is the same value, merge the nodes */
    if (p != NULL && p->value == value)
    {
      prev->end = p->end;     /* set previous node end to current node end */
      prev->next = p->next;   /* set previous node next to current node next */
      free(p);                /* free node */
    }
    else
    {
      prev->end++; /* if you dont need to merge just increment the end */
    }

    return 0; /* return success */
  }
  /* if the node is not found, create a new one */
  else if (p == NULL || p->begin > position)
  {
    new_node = malloc(sizeof(struct RangeNode)); /* allocate memory for new node */

    /* if allocation failed */
    if (new_node == NULL)
    {
      return 1; /* return error */
    }
    else
    {
      /* set new node values */
      new_node->begin = position;
      new_node->end = position + 1;
      new_node->value = value;
      new_node->next = p; /* set new node next to current node */

      /* if prev is null, set head to new node */
      if (prev == NULL)
      {
        *ppHead = new_node;
      }
      else
      {
        prev->next = new_node; /* set previous node next to new node */
      }
    }

    return 0; /* return success */
  }
  else
  {
    /* if the position is found at start of node, insert new node */
    if (p->begin == position && p->end > position + 1)
    {
      /* insert before */
      new_node = malloc(sizeof(struct RangeNode));

      /* if allocation failed */
      if (new_node == NULL)
      {
        return 1; /* return error */
      }
      else
      {
        /* set new node values */
        new_node->begin = position;
        new_node->end = position + 1;
        new_node->value = value;
        p->begin = position + 1;
        new_node->next = p; /* set new node next to current node */

        /* if prev is null, set head to new node */
        if (prev == NULL)
        {
          *ppHead = new_node;
        }
        else
        {
          prev->next = new_node; /* set previous node next to new node */
        }
      }
    }
    /* otherwise just update value */
    else
    {
      /* the node is found, update the value */
      p->value = value;
    }

    return 0; /* return success */
  }

  return 1; /* return failure */
}

/* return value at position (index) 
*  position is position in list to find value of
*  p is head of list
*
*  returns value at position, or 0 if position is not found
*/
int get(struct RangeNode const *p, int position)
{
  int value = 0; /* value to return */

  /* go through list until position is found */
  while (p != NULL && p->begin <= position)
  {
    /* if position is found, return value */
    if (p->begin <= position && p->end > position)
    {
      value = p->value;
      break;
    }
    p = p->next; /* go to next node */
  }

  return value; /* return value */
}

/* deallocate all nodes
*  p is the head of the list
*/
void delete (struct RangeNode *p)
{
  struct RangeNode *next = NULL; /* next node */

  /* go through list and free each node */
  while (p != NULL)
  {
    next = p->next;
    free(p);
    p = next; /* go to next node */
  }
}

/* implementations - DO NOT MODIFY*/
void dump_node(struct RangeNode *p)
{
  printf("+--------------------------\n");
  printf("| %p | %i [ %i, %i ) --> %p\n", (void *)p, p->value, p->begin, p->end, (void *)p->next);
  printf("+--------------------------\n");
}

/* print elements as a vector, print 0's for non-existing positions
 * assume the length of the vector = dim (third argument)
 * doesn't check if the list contains positions beyond dim 
 * if do_sanity_check is non-zero thie function will do some 
 * error checking (notie - this is not a complete analysis) 
 * not ll errors will be detected */
void printf_elements(struct RangeNode const *p, char *format, int dimension, int do_sanity_check)
{
  int i, last_pos = 0;
  typedef int boolean;
  boolean zeroes = 0;
  boolean non_merged = 0;
  boolean overlapping_ranges = 0;
  /* indices */
  for (i = 0; i < dimension; ++i)
  {
    printf(format, i);
  }
  printf("\n");
  /* data */
  while (p)
  {
    for (i = last_pos; i < p->begin; ++i)
    {
      printf(format, 0);
    } /* print leading zeros */
    if (p->value == 0)
    {
      zeroes = 1;
    } /* sanity check */
    for (i = p->begin; i < p->end; ++i)
    {
      printf(format, p->value);
    } /* print value */
    last_pos = p->end;
    if (p->next && p->end > p->next->begin)
    {
      overlapping_ranges = 1;
    } /* sanity check */
    if (p->next && p->end == p->next->begin && p->value == p->next->value)
    {
      non_merged = 1;
    } /* sanity check */
    p = p->next;
  }
  for (i = last_pos; i < dimension; ++i)
  {
    printf(format, 0);
  }

  /* sanity reporting */
  if (do_sanity_check && zeroes)
  {
    printf("zero values should not be stored\n");
  }
  if (do_sanity_check && overlapping_ranges)
  {
    printf("overlapping ranges\n");
  }
  if (do_sanity_check && non_merged)
  {
    printf("ranges with the same value and next to each other - should be merged\n");
  }
}

/* raw dump of the list data */
void print_raw(struct RangeNode const *p)
{
  while (p)
  {
    printf("%i [ %i, %i ) --> ", p->value, p->begin, p->end);
    p = p->next;
  }
  printf("NULL");
}

/* insert a range, assume there are no overlaps with the existing ranges
 * this is a dangerous function, it better be a hidden helper function 
 * (private in C++ or declared in the header file in C)
 * I will use this function to test your code in the case you did 
 * not implement / or incompletely the insert_value above
 *
 * Return value: error code (1 = allocation error, 0 - OK 
 */
int insert_nonoverlapping_range(struct RangeNode **ppHead, int begin, int end, int value)
{
  struct RangeNode *new_node = (struct RangeNode *)malloc(sizeof(struct RangeNode));
  if (new_node == NULL)
  {
    return 1;
  }

  new_node->begin = begin;
  new_node->end = end;
  new_node->value = value;

  /* main logic */
  if (!*ppHead || end < (*ppHead)->begin)
  { /* empty or in-front (short circuit) */
    new_node->next = *ppHead;
    *ppHead = new_node;
    return 0;
  }
  else
  { /* insert in the middle or tail */
    struct RangeNode *p = *ppHead;
    while (p->next && p->next->end <= begin)
    { /* find the right place */
      p = p->next;
    }

    if (!p->next)
    { /* insert in the end */
      new_node->next = NULL;
      p->next = new_node; /* make tail */
      return 0;
    }
    else
    { /* insert between p and p->next */
      new_node->next = p->next;
      p->next = new_node;
    }
  }
  return 0;
}
