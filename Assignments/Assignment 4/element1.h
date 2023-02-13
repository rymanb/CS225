/* File header
 * ===========
 * file:       element1.h
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 4
 * date:       11/13/2022
 *
 * file content:
 * this is a header file for element 1 that has a value
 */

#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>
#include "abstract-element.h"

namespace DigiPen {
  // element 1 class uses virtual inheritance
  class Element1 : public DigiPen::AbstractElement {
    public:
      AbstractElement* Clone() const;
	  
      virtual ~Element1();
      Element1(int _val);
      Element1(const Element1& rhs);
      int Get() const;
      void Set(int new_val);
      void Print() const;
      
      static int GetAlive() {  return alive; }
      static int GetTotal() { return total;}
    private:
      int val; // value of element
      static int alive; // number of element1 alive
      static int total; // total number of element1 created
      

      
  };
}
#endif
