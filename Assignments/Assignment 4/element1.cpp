/* File header
 * ===========
 * file:       element1.cpp
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 4
 * date:       11/13/2022
 *
 * file content:
 * this is a source file for element 1 that has a value
 */

#include "element1.h"

int DigiPen::Element1::alive = 0; // initialize static variable
int DigiPen::Element1::total = 0; // initialize static variable

// constructor
DigiPen::Element1::Element1(int _val) : val(_val) { 
  // one more element so increment alive and total
  ++total;
  ++alive;
}

// copy constructor no need to increment alive or total
DigiPen::Element1::Element1(const Element1& rhs) 
  : AbstractElement(), val(rhs.val)
{
}

// destructor, one less element so decrement alive
DigiPen::Element1::~Element1() { 
  --alive;
}

// clone element
DigiPen::AbstractElement* DigiPen::Element1::Clone() const {
	alive++; // one more element so increment alive
	total++; // one more element so increment total
  return new Element1(*this); // return a copy of this element
}

// get value
int DigiPen::Element1::Get() const { return val; }

// set value
void DigiPen::Element1::Set(int new_val) { val=new_val; }

// print value
void DigiPen::Element1::Print() const { 
  std::cout << "[" << Get() << "] "; 
}

