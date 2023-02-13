#ifndef SHAPES_H
#define SHAPES_H

#include <utility> //pair<T1,T2>, make_pair, p.first, p.second
#include <fstream>

class Ray {
    private:
        float  origin_x;
        float  origin_y;
        float  dir_x;
        float  dir_y;
    public:
        // compiler generated copy, assignment, destructor are OK
};

class BoundingCircle {
    private:
        float  center_x;
        float  center_y;
        float  radius;
    public:


};

class Box  {
    private:
        float center_x;
        float center_y;
        float side_x;
        float side_y;
    public:
        // compiler generated copy, assignment, destructor are OK
};

class Rhombus {
    private:
        float center_x;
        float center_y;
        float diag_x;
        float diag_y;
    public:
        // compiler generated copy, assignment, destructor are OK
};

#endif
