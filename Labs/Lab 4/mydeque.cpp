#include "mydeque.h"
#include <iostream>
#include <iomanip>

namespace DigiPen {

    // implemented
    Deque::Deque() : b(0), e(0), size(0), capacity(0), array(nullptr) {
    }

    // implemented
    Deque::Deque(int* array_, unsigned int size_) : b(0), e(size_), size(e), capacity(size), array(new int[size]) {
        for (int i = 0; i < e; ++i) array[i] = array_[i];
    }

    // implemented
    // trim capacity to size when coping
    Deque::Deque(const Deque& rhs) :
        b(0), e(rhs.size),
        size(e), capacity(size),
        array(size ? new int[size] : nullptr) // size == 0 => array = nullptr in ctor
    {
        for (int i = 0; i < e; ++i) array[i] = rhs[i];
    }

    Deque::~Deque() {
        delete[] array;
    }

    // implemented
    int Deque::Size() const { return size; }

    // implemented
    bool Deque::Empty() const { return (size == 0); }

    // implemented
    int Deque::Capacity() const { return capacity; }

    void Deque::Push_back(int val) {
        if (size == capacity) { // double the array size, or change size=0 to size=1
            reallocate(capacity ? capacity * 2 : 1);
        }

        array[e] = val;
        e++;
        size++;

        if (e == capacity) e = 0;
    }

    Deque& Deque::operator=(Deque rhs)
    {
        swap(rhs);
        return *this;
    }

    int& Deque::operator[](unsigned int pos)
    {
        return array[(b + pos) % capacity];
    }
    int Deque::operator[](unsigned int pos) const
    {
        return array[(b + pos) % capacity];
    }

    Deque Deque::operator+(const Deque& rhs) const  // concatenate 2 deques
    {
        Deque result;
        result.reallocate(size + rhs.size);
        for (int i = 0; i < size; ++i) result.array[i] = array[i];
        for (int i = 0; i < rhs.size; ++i) result.array[size + i] = rhs.array[i];
        result.size = size + rhs.size;
        result.e = result.size;
        return result;
    }
    Deque& Deque::reverse()                 // reverse in-place
    {
        for (int i = 0; i < size / 2; ++i) {
            int tmp = array[i];
            array[i] = array[size - 1 - i];
            array[size - 1 - i] = tmp;
        }
        return *this;
    }
    Deque Deque::operator~() const                 // return new reverse
    {
        Deque result;
        result.reallocate(size);
        for (int i = 0; i < size; ++i) result.array[i] = array[size - 1 - i];
        result.size = size;
        result.e = result.size;
        return result;
    }

    void Deque::swap(Deque& other)
    {
        std::swap(b, other.b);
        std::swap(e, other.e);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        std::swap(array, other.array);
    }

    int Deque::Pop_back() {
        if (size == capacity / 4) { // half the array
            reallocate(capacity / 2);
            //capacity /= 2;
        }

        --size;
        e--;

        if (e == -1) e = capacity - 1;



        return array[e];
    }

    void Deque::Push_front(int val) {
        if (size == capacity) { // double the array size, or change size=0 to size=1
            reallocate(capacity ? capacity * 2 : 1);
        }

        b--;
        ++size;

        if (b < 0) b = capacity - 1;

        array[b] = val;


    }

    int Deque::Pop_front() {
        if (size == capacity / 4) { // half the array
            reallocate(capacity / 2);
        }

        --size;
        b++;

        if (b == capacity) b = 0;

        return array[(b + capacity - 1) % capacity];
    }

    // if current capacity is not enough for the combined:
    // reallocate and trim, else do not reallocate at all
    Deque& Deque::operator+=(const Deque& op2) {
        if (size + op2.size > capacity) {
            reallocate(size + op2.size);
        }
        for (int i = 0; i < op2.size; ++i) {
            array[e++] = op2[i];
        }

        return *this;
    }

    // implemented
    void Deque::Print() const {
        std::cout << "size = " << size << " capacity = " << capacity << std::endl;

        if (array == nullptr) {
            std::cout << "array=nullptr" << std::endl;
            return;
        }

        // deque may still be empty, but array is allocated, so print some data
        int width = 3;
        // line of indices
        for (int i = 0; i < capacity; ++i) {
            std::cout << std::setw(width) << i;
        }
        std::cout << " indices" << std::endl;
        // line of data
        for (int i = 0; i < capacity; ++i) {
            if ((b <= i and i < e)                         //  ....b.....e.....
                or (e < b and (b <= i or i < e))        //  ....e.....b.....
                or (b == e and size > 0))            //  ....be.......... either empty or full - look at size
                std::cout << std::setw(width) << array[i];
            else
                std::cout << std::setw(width) << ".";
        }
        std::cout << " data" << std::endl;

        char ch1 = 'b', ch2 = 'e';
        int dist1 = b + 1, dist2 = e - b;
        if (e < b) { ch1 = 'e'; ch2 = 'b'; dist1 = e + 1; dist2 = b - e; }
        std::cout << std::setw(width * dist1) << ch1;
        std::cout << std::setw(width * dist2) << ch2;
        std::cout << std::endl;
    }

    // implemented
    void Deque::reallocate(int new_capacity) {

        // clean - dtor uses this
        if (new_capacity == 0) {
            delete[] array;
            array = nullptr;
            b = 0;
            e = 0;
            size = 0;
            capacity = 0;
        }
        else {

            // do not check whether new_capacity makes sense etc - it is caller's responsibility
            int* new_array = new int[new_capacity];
            for (int i = 0; i < size; ++i) {
                new_array[i] = array[(b + i) % capacity]; // new b is 0
            }
            //for (int i=size;i<capacity;++i) new_array[i]=0;
            delete[] array;
            array = new_array;
            b = 0;
            e = size;
            // same size
            capacity = new_capacity;
        }
    }

    // implemented
    std::ostream& operator<<(std::ostream& os, const Deque& d) {
        for (int i = 0; i < d.Size(); ++i) os << d[i] << " "; // this is public Deque::operator[], operator<< does not need to be friend
        return os;
    }
}
