/* File header
 * ===========
 * file:       rangelist.c
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 3
 * date:       10/18/2022
 *
 * file content:
 * this is a source file for rangelist to insert values into a linked list, requires rangelist.h
 */

#include "rangelist.h"
#include <cstdlib>    /* new/delete */
#include <cstddef>    /* NULL */
#include <cstdio>     /* printf */
#include <algorithm>  /* std::swap */
#include <iostream>   /* std::cout */

#define xDEBUG

/* constructor
*  pList: pointer to the list
*  pos: position in the list
*/
NodeProxy::NodeProxy(RangeList* pList, int pos)
    : m_pList(pList), m_pos(pos)
{
}

/* conversion to int */
NodeProxy::operator int() const
{
    return m_pList->get(m_pos);
}

/* assignment operator
*  value: the value to assign to the this node
*
*  returns: a reference self
*/
NodeProxy& NodeProxy::operator=(int value)
{
    m_pList->insert_value(m_pos, value);
    return *this;
}

/* add value to the current value
*  value: value to add
*
*  returns: reference to self
*/
NodeProxy& NodeProxy::operator+=(int value)
{
    m_pList->insert_value(m_pos, m_pList->get(m_pos) + value);
    return *this;
}

/* multiply the value at the given position by the given value
*  value: the value to multiply by
*
*  returns: ref to seld
*/
NodeProxy& NodeProxy::operator*=(int value)
{
    m_pList->insert_value(m_pos, m_pList->get(m_pos) * value);
    return *this;
}

/* implementations - DO NOT MODIFY*/
void RangeList::RangeNode::dump_node() const
{
    printf("+--------------------------\n");
    printf("| %p | %i [ %i, %i ) --> %p\n", reinterpret_cast<void const*>(this), value, begin, end, reinterpret_cast<void const*>(next));
    printf("+--------------------------\n");
}

/* constructor 
*  b: begin
*  e: end
*  v: value
*/
RangeList::RangeNode::RangeNode(int b, int e, int v)
    : begin(b), end(e), value(v), next(NULL)
{
}

/* default constructor */
RangeList::RangeList()
    : pHead(NULL)
{
}

/* destructor */
RangeList::~RangeList()
{
    RangeNode* pCurrent = pHead;
    // delete all nodes
    while (pCurrent != NULL)
    {
        RangeNode* pNext = pCurrent->next;
        delete pCurrent;
        pCurrent = pNext;
    }
}

/* copy constructor to copy other list into this one
*  other: the list to copy
*/
RangeList::RangeList(const RangeList& other)
    : pHead(NULL)
{
    RangeNode* pOther = other.pHead;

    // go through other list and copy each node
    while (pOther != NULL) {
        insert_nonoverlapping_range(pOther->begin, pOther->end, pOther->value);
        pOther = pOther->next;
    }
}

/* copy other list into this one
*  other: the list to copy
*
*  returns: ref to this list
*/
RangeList& RangeList::operator=(const RangeList& other)
{
    // check for self-assignment
    if (this != &other) {
        RangeList tmp(other);
        // swap the contents of this list with the temporary list
        std::swap(pHead, tmp.pHead);
    }

    return *this;
}

NodeProxy RangeList::operator[](int pos) {
    return NodeProxy(this, pos); // tell proxy about RangeList (this) and the position 
}

/* scalar multiplication
*  other: the list to multiply by
*
*  returns: the sum of the products of the elements
*/
int RangeList::operator*(const RangeList& other) const
{
    int dimension = 0; // dimension of the vector
    RangeNode* pThis = pHead; // pointer to this list
    RangeNode* pOther = other.pHead; // pointer to other list

    // find the dimension of the lists
    while (pThis->next != NULL) {
        
        pThis = pThis->next;
    }
    while (pOther->next != NULL)
    {
        pOther = pOther->next;
    }

    int thisS = pThis->end; // size of this list
    int otherS = pOther->end; // size of other list
    dimension = (thisS > otherS ? thisS : otherS); // find the larger size

    int result = 0; // result of the multiplication
    // go through both lists and multiply the values
    for (int i = 0; i <= dimension; ++i) {
        int value = (*this).get(i);
        int other_value = other.get(i);
        result += value * other_value;
    }

    return result; // return the result
}

/* vector addition
*  other: the list to add to this one
*
*  returns: resulting list
*/
RangeList RangeList::operator+(const RangeList& other) const
{
    int dimension = 0; // dimension of the resulting list
    RangeNode* pThis = pHead; // pointer to this list
    RangeNode* pOther = other.pHead; // pointer to other list

    // find the dimension of the resulting list
    while (pThis->next != NULL) {
        
        pThis = pThis->next;
    }
    while (pOther->next != NULL)
    {
        pOther = pOther->next;
    }

    int thisS = pThis->end; // size of this list
    int otherS = pOther->end; // size of other list
    dimension = (thisS > otherS ? thisS : otherS); // dimension is the larger of the two

    RangeList result; // resulting list
    // add the values of the two lists
    for (int i = 0; i < dimension; ++i) {
        int value = (*this).get(i);
        int other_value = other.get(i);
        result[i] = value + other_value;
    }

    return result; // return the resulting list
}

/* return value at position (index) 
*  position is position in list to find value of
*  p is head of list
*
*  returns value at position, or 0 if position is not found
*/
int RangeList::get(int position) const
{
    int value = 0; // value to return
    RangeNode* p = pHead; // pointer to head of list

    // loop through list until position is found
    while (p != NULL && p->begin <= position)
    {
        // if position is in range, return value
        if (p->begin <= position && p->end > position)
        {
            value = p->value;
            break;
        }
        p = p->next;
    }

    return value; // return value
}

/* insert a single value into the list
*  ppHead - pointer to the pointer to the head of the list
*  position - position to insert the value
*  value - value to insert
*
*  returns: 0 on success, 1 on error (allocation error)
*/
int RangeList::insert_value(int position, int value)
{
    RangeNode* p = pHead;
    RangeNode* prev = NULL;
    RangeNode* new_node = NULL;

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
        pHead = p->next; /* set head to next node */
      }
      else
      {
        prev->next = p->next; /* set previous node to next node */
      }

      delete p; /* free node */
    }

    return 0; /* return success */
  }

  /* if position is between two nodes, split the node */
  else if (prev != NULL && prev->begin <= position && prev->end > position && value != prev->value)
  {
    RangeNode *next_node;

    /* if position is at front of node, just insert the value */
    if (prev->begin == position)
    {
      new_node = new RangeNode(position, position, value); /* allocate memory for new node */
      /* set new node values */
      new_node->next = p->next; /* set new node next to next node */
      prev->next = new_node;    /* set previous node next to new node */

      return 0; /* return success */
    }
    /* if position is at end of node*/
    else if (prev->end - 1 == position)
    {
      /* set new node values */
      new_node = new RangeNode(position, position + 1, value);
      new_node->next = p;   /* set new node next to curent node */
      prev->end--;          /* decrement previous node end */
      prev->next = new_node; /* set previous node to point at new node */

      return 0; /* return success */
    }
    /* otherwise, split the node */
    else
    {
      new_node = new RangeNode(position, position + 1, value);
      next_node = new RangeNode(new_node->end, prev->end, prev->value);

      /* set new node values */
      new_node->next = next_node; /* next node is next node */

      /* set next node values */
      next_node->next = p; /* point next node to current node */

      /* update prev node values to new split end */
      prev->end = position; 
      prev->next = new_node;
    }

    return 0; /* return success */
  }
  /* if value is next to a node of the same value, extend the node */
  else if (p != NULL && p->begin - 1 == position && p->value == value)
  {
    /* if prev is the same value, merge the nodes */
    if (prev != NULL && prev->end == position && prev->value == value)
    {
      prev->end = p->end; /* set previous node end to current node end */
      prev->next = p->next; /* set previous node next to current node next */
      delete p; /* free node */
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
    if (p != NULL && p->value == value && p->begin <= position + 1)
    {
      prev->end = p->end;     /* set previous node end to current node end */
      prev->next = p->next;   /* set previous node next to current node next */
      delete p;                /* free node */
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
    new_node = new RangeNode(position, position + 1, value); /* allocate memory for new node */

    /* if allocation failed */
    if (new_node == NULL)
    {
      return 1; /* return error */
    }
    else
    {
      /* set new node values */
      new_node->next = p; /* set new node next to current node */

      /* if prev is null, set head to new node */
      if (prev == NULL)
      {
        pHead = new_node;
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
      new_node = new RangeNode(position, position + 1, value);

      /* if allocation failed */
      if (new_node == NULL)
      {
        return 1; /* return error */
      }
      else
      {
        /* set new node values */
        p->begin = position + 1;
        new_node->next = p; /* set new node next to current node */

        /* if prev is null, set head to new node */
        if (prev == NULL)
        {
          pHead = new_node;
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

/* insert a single value into the list that dosent overlap
*  begin - start of range
*  end - end of range
*  value - value to insert
*
*  returns: 0 on success, 1 on error
*/
int RangeList::insert_nonoverlapping_range(int begin, int end, int value)
{
    RangeNode** ppHead = &pHead;

    /* main logic */
    if (!*ppHead || end < (*ppHead)->begin) { /* empty or in-front (short circuit) */
      // front next to old head same value
        if (*ppHead && (*ppHead)->value == value && end == (*ppHead)->begin) {
            (*ppHead)->begin = begin;
        }
        else {
            RangeNode* old_head = *ppHead;
            *ppHead = new RangeNode(begin, end, value);
            (*ppHead)->next = old_head;
        }
        return 0;
    }
    else { /* insert in the middle or tail */
        RangeNode* p = *ppHead;
        while (p->next && p->next->end <= begin) { /* find the right place */
            p = p->next;
        }

        if (!p->next) { /* insert in the end */
            if (p->value == value && p->end == begin) { // if inserting same value next to exising node
                p->end = end;                               // just change the end
            }
            else {
                p->next = new RangeNode(begin, end, value); /* make tail */
            }
            return 0;
        }
        else { /* insert between p and p->next */
            RangeNode* old_p_next = p->next;
            p->next = new RangeNode(begin, end, value);
            p->next->next = old_p_next;
        }
    }
    return 0;
}

/* print elements as a vector, print 0's for non-existing positions
 * assume the length of the vector = dim (third argument)
 * doesn't check if the list contains positions beyond dim 
 * if do_sanity_check is non-zero thie function will do some 
 * error checking (notie - this is not a complete analysis) 
 * not ll errors will be detected */
void RangeList::printf_elements(char const* format, int dimension, bool do_sanity_check, bool indices) const
{
    RangeNode const* p = pHead;
    int i, last_pos = 0;
    bool zeroes = 0;
    bool non_merged = 0;
    bool overlapping_ranges = 0;
    /* indices */
    if (indices) {
        for (i = 0; i < dimension; ++i) { printf(format, i); }
        printf("\n");
    }
    /* data */
    while (p) {
        for (i = last_pos; i < p->begin; ++i) { printf(format, 0); }          /* print leading zeros */
        if (p->value == 0) { zeroes = 1; } /* sanity check */
        for (i = p->begin; i < p->end; ++i) { printf(format, p->value); }   /* print value */
        last_pos = p->end;
        if (p->next && p->end > p->next->begin) { overlapping_ranges = 1; }    /* sanity check */
        if (p->next && p->end == p->next->begin && p->value == p->next->value) { non_merged = 1; } /* sanity check */
        p = p->next;
    }
    for (i = last_pos; i < dimension; ++i) { printf(format, 0); }

    /* sanity reporting */
    if (do_sanity_check && zeroes) {
        printf("zero values should not be stored\n");
    }
    if (do_sanity_check && overlapping_ranges) {
        printf("overlapping ranges\n");
    }
    if (do_sanity_check && non_merged) {
        printf("ranges with the same value and next to each other - should be merged\n");
    }
}


/* raw dump of the list data */
void RangeList::print_raw() const
{
    RangeNode const* p = pHead;
    while (p) {
        printf("%i [ %i, %i ) --> ", p->value, p->begin, p->end);
        p = p->next;
    }
    printf("NULL");
}

