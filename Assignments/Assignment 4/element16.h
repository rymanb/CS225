#ifndef ELEMENT3_H
#define ELEMENT3_H
#include "abstract-element.h"
namespace DigiPen {
    class Element17 : public AbstractElement {
        public:
            Element17(int _val);
            virtual int Get() const;
            virtual void Set(int new_val);
            virtual void Print() const;
            Element17* Make_Copy()       { return new Element17(*this); }
            Element17* Make_Copy() const { return new Element17(*this); }
            Element17* cloneElement()       { return new Element17(*this); }
            Element17* cloneElement() const { return new Element17(*this); }
            Element17* clone()       { return new Element17(*this); }
            Element17* clone() const { return new Element17(*this); }
            Element17* Clone()       { return new Element17(*this); }
            Element17* Clone() const     { return new Element17(*this); }
            Element17* CloneMe()     { return new Element17(*this); }
            Element17* CloneMe() const       { return new Element17(*this); }
            Element17* CloneElement()     { return new Element17(*this); }
            Element17* CloneElement() const       { return new Element17(*this); }
            Element17* deepCopy()        { return new Element17(*this); }
            Element17* deepCopy() const      { return new Element17(*this); }
            Element17* DeepCopy()        { return new Element17(*this); }
            Element17* DeepCopy() const      { return new Element17(*this); }
            Element17* copy()        { return new Element17(*this); }
            Element17* copy() const      { return new Element17(*this); }
            Element17* Copy()        { return new Element17(*this); }
            Element17* Copy() const      { return new Element17(*this); }
            Element17* mirror()      { return new Element17(*this); }
            Element17* mirror() const        { return new Element17(*this); }
            Element17* Duplicate()       { return new Element17(*this); }
            Element17* Duplicate() const     { return new Element17(*this); }
            Element17* duplicate()       { return new Element17(*this); }
            Element17* duplicate() const     { return new Element17(*this); }
            Element17* Value()       { return new Element17(*this); }
            Element17* Value() const     { return new Element17(*this); }
            Element17* Create()      { return new Element17(*this); }
            Element17* Create() const        { return new Element17(*this); }
            Element17* makeElement()     { return new Element17(*this); }
            Element17* makeElement() const       { return new Element17(*this); }
            Element17* lasun()       { return new Element17(*this); }
            Element17* lasun() const     { return new Element17(*this); }
            Element17* create()      { return new Element17(*this); }
            Element17* create() const       { return new Element17(*this); }
            Element17* judwa() { return new Element17(*this); }
            Element17* judwa() const        { return new Element17(*this); }
            Element17* Reproduce() { return new Element17(*this); }
            Element17* Reproduce() const        { return new Element17(*this); }
            Element17* Vconst() { return new Element17(*this); }
            Element17* Vconst() const        { return new Element17(*this); }
            Element17* bla() { return new Element17(*this); }
            Element17* bla() const        { return new Element17(*this); }
            Element17* virtConst() { return new Element17(*this); }
            Element17* virtConst() const        { return new Element17(*this); }
            Element17* virtualConstForEleFirstAndSecond() { return new Element17(*this); }
            Element17* virtualConstForEleFirstAndSecond() const        { return new Element17(*this); }
            Element17* virtualConstForElements() { return new Element17(*this); }
            Element17* virtualConstForElements() const        { return new Element17(*this); }
        private:
            int val;
    };
}
#endif
