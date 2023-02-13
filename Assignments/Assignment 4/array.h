/* File header
 * ===========
 * file:       array.h
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 4
 * date:       11/13/2022
 *
 * file content:
 * this is a header file for array that uses ref counting
 */

#ifndef ARRAY_H
#define ARRAY_H
#include "abstract-element.h"
#include "element-factory.h"
#include <iostream>

namespace DigiPen {

/*
 * Class Array implements a simple array-like data structure.
 * Objects inside the Array have to be derived from AbstractElement.
 */
	class Array {
		public:

			// constructor
			Array(int * array, unsigned int _size, 
					const ElementFactory* _pElementFactory
					);
			// copy constructor
			Array(const Array& rhs);

			// assignment operator
			Array& operator=(const Array& rhs);

			// destructor
			~Array();

			// get and set
			int Get(unsigned int pos) const;
			void Set(int id, int pos, int value);

			// other methods
			void DeepCopy();
			void Print() const;

		private:
			AbstractElement** data; // array of pointers to elements
			unsigned int size; 		// size of the array
			ElementFactory const* pElementFactory; // factory for creating elements
			
			int* ref_count; // reference count
	};
}
#endif
