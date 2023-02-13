/* File header
 * ===========
 * file:       abstract-element.h
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 4
 * date:       11/13/2022
 *
 * file content:
 * this is a header file for virtual element class
 */

#ifndef ABSTRACT_H
#define ABSTRACT_H

namespace DigiPen {

    // virtual class for all elements
    class AbstractElement
    {
    public:
        // clone element
        virtual AbstractElement* Clone() const = 0;

        // virtual destructor
        virtual ~AbstractElement() {};

        // other methods
        virtual int Get() const = 0;
        virtual void Set(int new_val) = 0;
        virtual void Print() const = 0;


    protected:
        // protected constructor
        AbstractElement() { }
    };
}
#endif