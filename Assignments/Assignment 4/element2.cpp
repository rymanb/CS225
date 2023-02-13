/* File header
 * ===========
 * file:       element2.cpp
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 4
 * date:       11/13/2022
 *
 * file content:
 * this is a source file for element 2 that has a alllocated value
 */

#include "element2.h"

int DigiPen::Element2::alive = 0; // initialize static variable
int DigiPen::Element2::total = 0; // initialize static variable

// constructor
DigiPen::Element2::Element2(int _val) : p_val(new int(_val)) {
	++total; // one more element so increment total
	++alive; // one more element so increment alive
}

// copy constructor no need to increment alive or total
DigiPen::Element2::Element2(const Element2& rhs) 
	: AbstractElement(), p_val(new int(*rhs.p_val)) 
{ }

// destructor, one less element so decrement alive
DigiPen::Element2::~Element2() {
	--alive;
	delete p_val;
}

// assignment
DigiPen::Element2& DigiPen::Element2::operator=(const Element2 & rhs)
{
	// check for self assignment
	if (this != &rhs) {
		*p_val = *rhs.p_val; // copy value 
	}
	return *this;
}

// clone element
DigiPen::AbstractElement* DigiPen::Element2::Clone() const {
	alive++; // one more element so increment alive
	total++; // one more element so increment total
	return new Element2(*this); // return a copy of this element

}

// get value
int DigiPen::Element2::Get() const {
	return *p_val;
}

// print value
void DigiPen::Element2::Print() const { 
  std::cout << "(" << *p_val << ") "; 
}

// set value
void DigiPen::Element2::Set(int new_val) { 
	*p_val = new_val; 
}
