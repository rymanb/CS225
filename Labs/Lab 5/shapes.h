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
        Ray( float o_x, float o_y, float d_x, float d_y );
        float const&  Origin_x() const;
        float const&  Origin_y() const;
        float const&  Direction_x() const;
        float const&  Direction_y() const;

        std::pair<bool,float>  IntersectSegment( float p1x, float p1y, float p2x, float p2y ) const;

        // stream insertion operator
        friend std::ostream& operator<<( std::ostream& os, Ray const& ray );
        
};

class BoundingCircle {
    private:
        float  center_x;
        float  center_y;
        float  radius;
    public:

        // compiler generated copy, assignment, destructor are OK
        BoundingCircle(float c_x, float c_y, float r);


        // stream insertion operator
        friend std::ostream& operator<<( std::ostream& os, BoundingCircle const& circle );


        bool IntersectTest(Ray const& ray) const;

};

class Shape {
public:
    virtual ~Shape() = 0;
    virtual BoundingCircle GetBoundingCircle() const = 0;
    virtual std::pair<bool,float> Intersect( Ray const& ray ) const = 0;

    // print shape
    virtual void Print() const = 0;


};

class Box : public Shape {
    private:
        float center_x;
        float center_y;
        float side_x;
        float side_y;
    public:
        // compiler generated copy, assignment, destructor are OK

        Box(float c_x, float c_y, float s_x, float s_y);

        // stream insertion operator
        friend std::ostream& operator<<( std::ostream& os, Box const& box );


        BoundingCircle GetBoundingCircle() const;

        std::pair<bool, float> Intersect(Ray const& ray) const;

        void Print() const;

};

class Rhombus : public Shape {
    private:
        float center_x;
        float center_y;
        float diag_x;
        float diag_y;
    public:
        // compiler generated copy, assignment, destructor are OK

        Rhombus(float c_x, float c_y, float d_x, float d_y);


        // stream insertion operator
        friend std::ostream& operator<<( std::ostream& os, Rhombus const& rhombus );

        BoundingCircle GetBoundingCircle() const;

        std::pair<bool, float> Intersect(Ray const& ray) const;

        void Print() const;

};

#endif
