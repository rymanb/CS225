#include "element16.h"
#include <iostream>
DigiPen::Element17::Element17(int _val) : val(_val) { }

int  DigiPen::Element17::Get() const      { return val; }
void DigiPen::Element17::Set(int new_val) { val=new_val; }
void DigiPen::Element17::Print() const    { std::cout << "{" << Get() << "} "; }
