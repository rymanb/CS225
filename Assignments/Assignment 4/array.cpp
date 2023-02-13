/* File header
 * ===========
 * file:       array.cpp
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 4
 * date:       11/13/2022
 *
 * file content:
 * this is a source file for array that uses ref counting
 */

#include "array.h"
// if Factory is used cirrectly, there will be no more includes

// create an array of elements using the factory
DigiPen::Array::Array(int * array, 
		unsigned int _size, 
		const DigiPen::ElementFactory* _pElementFactory
		) 
: data(new AbstractElement*[_size]),
  size(_size),
	pElementFactory(_pElementFactory),
	ref_count(new int(1))
{
	for ( unsigned int i=0; i<size; ++i ) {
		//create Element with id = 1 (that is Element1 )
		data[i] = pElementFactory->MakeElement( 1, array[i] );
	}
}

// copy another array using a shallow copy
DigiPen::Array::Array(const DigiPen::Array& rhs) : data(rhs.data),
size(rhs.size),
pElementFactory(rhs.pElementFactory),
ref_count(rhs.ref_count)
{
	++* ref_count; // increment reference count
}

// destructor, if ref_count is 0, no one is using this array, so delete it
DigiPen::Array::~Array()
{
	// if decrementing the reference count makes it 0, delete the array
	if ( --*ref_count == 0 ) {
		// delete each element
		for ( unsigned int i=0; i<size; ++i ) {
			delete data[i];
		}
		// delete the array and the reference count
		delete [] data;
		delete ref_count;
	}
}


// Get an element from the array at position pos
int DigiPen::Array::Get(unsigned int pos) const
{
	// if pos is out of range, return 0
	if ( pos >= size ) {
		std::cout << "Array::Get() : index out of range" << std::endl;
		return 0;
	}
	// otherwise, return the element
	return data[pos]->Get();
}

// Set an element in the array at position pos, deep copy if necessary
void DigiPen::Array::Set( int id, int pos, int value ) { 

	// if others are using this array, deep copy it
	if (*ref_count != 1) {
		DeepCopy(); // modifying the data - need our own copy
	} 
	// delete old element
	delete data[pos]; 
	data[pos] = pElementFactory->MakeElement(id,value); // make sure is used 
	

}

// assignment operator using a shallow copy
DigiPen::Array& DigiPen::Array::operator=(const DigiPen::Array& rhs)
{
	// if this is not the same array
	if (this != &rhs && rhs.data != data) {

		// delete old array if no one is using it
		if (ref_count && --*ref_count == 0) 
		{
			// delete each element
			for (unsigned int i = 0; i < size; ++i) {
				delete data[i];
			}
			// delete the array and the reference count
			delete[] data;
			delete ref_count;
		}

		// shallow copy
		data = rhs.data;
		size = rhs.size;
		pElementFactory = rhs.pElementFactory;
		ref_count = rhs.ref_count;
		++* ref_count; // increment reference count
		
	}

	return *this;
}

// deep copy the array
void DigiPen::Array::DeepCopy() {
	// create a new array
	AbstractElement** newData = new AbstractElement * [size];
	
	// copy each element into the new array
	for (unsigned int i = 0; i < size; ++i) {
		newData[i] = data[i]->Clone();
	}
	
	// delete old array if no one is using it
	if (ref_count && -- * ref_count == 0) 
	{
		for (unsigned int i = 0; i < size; ++i) {
			delete data[i];
		}
		delete[] data;
		delete ref_count;
	}
	
	// set new array and reference count
	data = newData;
	ref_count = new int(1);
	
}

// print the array
void DigiPen::Array::Print() const {
	for (unsigned int i=0;i<size;++i) data[i]->Print(); 
	std::cout << std::endl;
}

