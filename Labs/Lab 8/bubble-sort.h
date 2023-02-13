#include <algorithm>

// The idea of bubble sort is:
// for n-1 passes
//     scan left-to-right
//         swap if 2 adjacent elements are not in order 
template < typename ForwardIt >
void bubblesort( ForwardIt begin, ForwardIt end )
{
    for ( ForwardIt i = begin; i != end; ++i )
        for ( ForwardIt j = begin; j != end; ++j )
            if ( *i < *j )
                std::swap( *i, *j );

}
