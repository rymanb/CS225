#ifndef RANGELIST_H
#define RANGELIST_H

// forward declaration
class NodeProxy; 

class RangeList {
  public:
    

    int get( int position ) const;
    int insert_value( int position, int value );
    int insert_nonoverlapping_range( int begin, int end, int value );
    void printf_elements( char const * format, int dimension, bool do_sanity_check, bool indices = true ) const; 
    void print_raw( ) const;

    friend class NodeProxy;
  private:
    struct RangeNode {
      int begin;
      int end;
      int value;
      struct RangeNode * next;
      void dump_node ( ) const;
      RangeNode( int b, int e, int v );
    };
    RangeNode * pHead;
  private: // helpers
};

class NodeProxy {


};
#endif
