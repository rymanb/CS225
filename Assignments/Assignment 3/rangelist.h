/* File header
 * ===========
 * file:       rangelist.h
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 3
 * date:       10/18/2022
 *
 * file content:
 * this is a header file for rangelist to insert values into a linked list, requires rangelist.cpp
 */

#ifndef RANGELIST_H
#define RANGELIST_H

// forward declaration
class NodeProxy;

// Linked List class
class RangeList {
public:
    // constructor
    RangeList();
    RangeList(const RangeList& other);

    // destructor
    ~RangeList();

    // bracket operator
    NodeProxy operator[]( int pos );

    // assignment opperator
    RangeList& operator=(const RangeList& other);

    // scalar multiplication
    int operator*(const RangeList& other) const;

    // vector addition
    RangeList operator+(const RangeList& other) const;

    int get(int position) const;
    int insert_value(int position, int value);
    int insert_nonoverlapping_range(int begin, int end, int value);
    void printf_elements(char const* format, int dimension, bool do_sanity_check, bool indices = true) const;
    void print_raw() const;

    friend class NodeProxy;
private:
    struct RangeNode {
        int begin;
        int end;
        int value;
        struct RangeNode* next;
        void dump_node() const;
        RangeNode(int b, int e, int v);
    };
    RangeNode* pHead;
private: // helpers
};

// NodeProxy class for bracket operator and handling indecies in the linked list
class NodeProxy {
public:
    // constructor
    NodeProxy( RangeList* pList, int pos );
    // assignment operator
    NodeProxy& operator=( int value );
    // conversion operator
    operator int() const;
    // vector addition
    NodeProxy& operator+=( int value );
    // scalar multiplication
    NodeProxy& operator*=( int value );
    

private:
    RangeList* m_pList; // pointer to the list
    int m_pos; // position in the list

};
#endif
