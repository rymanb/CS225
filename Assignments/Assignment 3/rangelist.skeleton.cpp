#include "rangelist.h"
#include <cstdlib>    /* new/delete */
#include <cstddef>    /* NULL */
#include <cstdio>     /* printf */
#include <algorithm>  /* std::swap */
#include <iostream>

#define xDEBUG

void RangeList::RangeNode::dump_node (  ) const
{
  printf( "+--------------------------\n" );
  printf( "| %p | %i [ %i, %i ) --> %p\n", reinterpret_cast<void const*>(this), value, begin, end, reinterpret_cast<void const*>(next) );
  printf( "+--------------------------\n" );
}

int RangeList::insert_nonoverlapping_range( int begin, int end, int value )
{
  RangeNode ** ppHead = &pHead;

  /* main logic */
  if ( !*ppHead || end < (*ppHead)->begin ) { /* empty or in-front (short circuit) */
    // front next to old head same value
    if ( *ppHead && (*ppHead)->value == value && end == (*ppHead)->begin ) {
      (*ppHead)->begin = begin;
    } else {
      RangeNode * old_head = *ppHead;
      *ppHead = new RangeNode( begin, end, value );
      (*ppHead)->next = old_head;
    }
    return 0;  
  } else { /* insert in the middle or tail */
    RangeNode * p = *ppHead;
    while ( p->next && p->next->end <= begin ) { /* find the right place */
      p = p->next;
    }

    if ( !p->next ) { /* insert in the end */
      if ( p->value == value && p->end == begin ) { // if inserting same value next to exising node
        p->end = end;                               // just change the end
      } else {
        p->next = new RangeNode( begin, end, value ); /* make tail */
      }
      return 0; 
    } else { /* insert between p and p->next */
      RangeNode * old_p_next = p->next; 
      p->next = new RangeNode( begin, end, value );
      p->next->next = old_p_next;
    }
  }
  return 0;
}

void RangeList::printf_elements( char const * format, int dimension, bool do_sanity_check, bool indices ) const
{
  RangeNode const * p = pHead;
  int i, last_pos = 0;
  bool zeroes     = 0;
  bool non_merged = 0;
  bool overlapping_ranges = 0;
  /* indices */
  if ( indices ) {
    for ( i = 0; i < dimension; ++i ) { printf( format, i ); }
    printf( "\n" );
  }
  /* data */
  while ( p ) {
    for ( i = last_pos; i < p->begin; ++i ) { printf( format, 0 ); }          /* print leading zeros */
    if ( p->value == 0 ) { zeroes = 1; } /* sanity check */
    for ( i = p->begin; i < p->end;   ++i ) { printf( format, p->value ); }   /* print value */
    last_pos = p->end;
    if ( p->next && p->end >  p->next->begin ) { overlapping_ranges = 1; }    /* sanity check */
    if ( p->next && p->end == p->next->begin && p->value == p->next->value) { non_merged = 1; } /* sanity check */
    p = p->next;
  }
  for ( i = last_pos ; i < dimension; ++i ) { printf( format, 0 ); }

  /* sanity reporting */
  if ( do_sanity_check && zeroes ) {
    printf( "zero values should not be stored\n" );
  }
  if ( do_sanity_check && overlapping_ranges ) {
    printf( "overlapping ranges\n" );
  }
  if ( do_sanity_check && non_merged ) {
    printf( "ranges with the same value and next to each other - should be merged\n" );
  }
}

void RangeList::print_raw( ) const
{
  RangeNode const * p = pHead;
  while ( p ) {
    printf( "%i [ %i, %i ) --> ", p->value, p->begin, p->end );
    p = p->next;
  }
  printf( "NULL" );
}

