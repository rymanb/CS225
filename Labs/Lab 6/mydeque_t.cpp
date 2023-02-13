#include "mydeque_t.h"
#include <iostream>
#include <iomanip>

namespace DigiPen {

    // implemented
    template< typename T>
    Deque<T>::Deque() :  b(0), e(0), size(0), capacity(0), array(nullptr) {
    }

    // implemented
    template< typename T>
    Deque<T>::Deque(T * array_, unsigned int size_) : b(0), e(size_), size(e), capacity(size), array(new T [size]) {
        for (int i=0;i<e;++i) array[i]=array_[i];
        //for (int i=e;i<capacity;++i) array[i]=0;
    }

    // implemented
    // trim capacity to size when coping
    template< typename T>
    Deque<T>::Deque( Deque const& rhs) :  
        b(0), e(rhs.size), 
        size(e), capacity( size ), 
        array(size ? new T [size] : nullptr ) // size == 0 => array = nullptr in ctor
    {
        for (int i=0;i<e;++i) array[i]=rhs[i];
    }

    template<typename T>
    Deque<T>& Deque<T>::operator=(Deque rhs)
    {
        swap(rhs);
        return *this;
    }

    // implemented
    template< typename T>
    Deque<T>::~Deque() { delete [] array; }

    // implemented
    template< typename T>
    int Deque<T>::Size() const { return size; }

    // implemented
    template< typename T>
    bool Deque<T>::Empty() const { return not size; }

    // implemented
    template< typename T>
    void Deque<T>::Clear() { 
        b=e=0;
        capacity=0;
        reallocate(0); // delete array - STL does not do this (no automatic shrinking)
    }

    template< typename T>
    int Deque<T>::Capacity() const { return capacity; }

    template< typename T>
    void Deque<T>::Push_back(T val) {
        if ( size == capacity ) { // double the array size, or change size=0 to size=1
            reallocate( capacity ? capacity*2 : 1 );
        }

        array[e] = val;
        e++;
        size++;

        if (e == capacity) e = 0;
    }

    template< typename T>
    T Deque<T>::Pop_back() {
        if ( size==capacity/4 ) { // half the array
            reallocate(capacity/2);
        }

        --size;
        e--;

        if (e == -1) e = capacity - 1;



        return array[e];
    }

    template<typename T>
    T& Deque<T>::operator[](unsigned int pos)
    {
        return array[(b + pos) % capacity];
    }

    template<typename T>
    T Deque<T>::operator[](unsigned int pos) const
    {
        return array[(b + pos) % capacity];
    }

    template<typename T>
    void Deque<T>::swap(Deque<T>& other)
    {
        std::swap(b, other.b);
        std::swap(e, other.e);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        std::swap(array, other.array);
    }

    template<typename T>
    Deque<T>& Deque<T>::operator+=(const Deque<T>& rhs)
    {
        if (size + rhs.size > capacity) {
            reallocate(size + rhs.size);
        }
        for (int i = 0; i < rhs.size; ++i) {
            array[e++] = rhs[i];
        }

        return *this;
    }

    template<typename T>
    Deque<T> Deque<T>::operator+(const Deque<T>& rhs) const
    {
        Deque result;
        result.reallocate(size + rhs.size);
        for (int i = 0; i < size; ++i) result.array[i] = array[i];
        for (int i = 0; i < rhs.size; ++i) result.array[size + i] = rhs.array[i];
        result.size = size + rhs.size;
        result.e = result.size;
        return result;
    }

    template<typename T>
    Deque<T>& Deque<T>::reverse()
    {
        for (int i = 0; i < size / 2; ++i) {
            int tmp = array[i];
            array[i] = array[size - 1 - i];
            array[size - 1 - i] = tmp;
        }
        return *this;
    }

    template<typename T>
    Deque<T> Deque<T>::operator~() const
    {
        Deque cpy(*this);
        
        return cpy.reverse();
    }

    template< typename T>
    void Deque<T>::Push_front(T val) {
        if ( size == capacity ) { // double the array size, or change size=0 to size=1
            reallocate( capacity ? capacity*2 : 1 );
        }
        b--;
        ++size;

        if (b < 0) b = capacity - 1;

        array[b] = val;
    }

    template< typename T>
    T Deque<T>::Pop_front() {
        if ( size==capacity/4 ) { // half the array
            reallocate(capacity/2);
        }

        --size;
        b++;

        if (b == capacity) b = 0;

        return array[(b + capacity - 1) % capacity];
    }

    template< typename T>
    void Deque<T>::Print() const { 
        std::cout << "size = " << size << " capacity = " << capacity <<  std::endl;

        if ( array == nullptr ) {
            std::cout << "array=nullptr" << std::endl;
            return;
        }

        // deque may still be empty, but array is allocated, so print some data
        int width = 3;
        // line of indices
        for ( int i=0; i<capacity; ++i ) {
            std::cout << std::setw(width) << i;
        }
        std::cout << " indices" << std::endl;
        // line of data
        for ( int i=0; i<capacity; ++i ) {
            if ( (b<=i and i<e)                         //  ....b.....e.....
                    or (e<b and ( b<=i or i<e) )        //  ....e.....b.....
                    or ( b==e and size>0 ) )            //  ....be.......... either empty or full - look at size
                std::cout << std::setw(width) << array[i];
                else 
                std::cout << std::setw(width) << ".";
        }
        std::cout << " data" << std::endl;

        char ch1 = 'b', ch2 = 'e';
        int dist1 = b+1, dist2 = e-b;
        if( e<b ) {  ch1 = 'e'; ch2 = 'b'; dist1 = e+1; dist2 = b-e; }
        std::cout << std::setw(width*dist1) << ch1;
        std::cout << std::setw(width*dist2) << ch2;
        std::cout << std::endl;
    }

    template< typename T>
        void Deque<T>::reallocate( int new_capacity )  {
            // clean - dtor uses this
            if ( new_capacity == 0 ) {
                delete [] array;
                array = nullptr;
                b = 0;
                e = 0;
                size = 0; 
                capacity = 0;

            } else {

                // do not check whether new_capacity makes sense etc - it is caller's responsibility
                T * new_array = new T [new_capacity];
                for ( int i=0;i<size;++i ) {
                    new_array[i]=array[(b+i)%capacity]; // new b is 0
                }
                //for (int i=size;i<capacity;++i) new_array[i]=0;
                delete [] array;
                array = new_array;
                b = 0;
                e = size;
                // same size
                capacity = new_capacity;
            }
        }

    template< typename T>
    std::ostream & operator<<(std::ostream & os, Deque<T> const& d) {
        for (int i=0;i<d.Size();++i) os << d[i] << " ";
        return os;
    }
}
