/* File header
 * ===========
 * file:       element2.h
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 4
 * date:       11/13/2022
 *
 * file content:
 * this is a header file for element 2 that has a alllocated value
 */

#ifndef ELEMENT2_H
#define ELEMENT2_H
#include <iostream>
#include "abstract-element.h"

namespace DigiPen {

	// element 2 class uses virtual inheritance and has allocated value
  class Element2 : public DigiPen::AbstractElement {
    public:
      AbstractElement* Clone() const;
      Element2(int _val);
      Element2(const Element2& rhs);
	  // assignment
	  Element2& operator=(const Element2& rhs);
	
      int Get() const;
      void Set(int new_val);
      void Print() const;
      static int GetAlive() { return alive;}
      static int GetTotal() { return total;}
      virtual ~Element2();
	
    private:
      int * p_val; // pointer to value of element
      static int alive; // number of element2 alive
      static int total; // total number of element2 created
  };
}
#endif
