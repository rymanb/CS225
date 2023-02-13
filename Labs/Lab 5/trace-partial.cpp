#include "shapes.h" // Shape,Box,Rhombus,BoundingCircle,Ray
#include "trace.h"  // global Intersect
#include <limits>   // std::numeric_limits<T>::max(), std::numeric_limits<T>::min()
#include <utility>  // pair<T1,T2>, make_pair, p.first, p.second

std::pair<bool,float> 
Intersect( Shape const * const * shapes, int num_shapes, Ray const& ray) {
    bool intersect = false;
    float t = std::numeric_limits<float>::max(); //first intersection


    return std::make_pair( intersect, t );
}
