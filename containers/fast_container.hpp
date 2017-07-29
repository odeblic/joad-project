#pragma once

#include <cassert>
#include <iostream>

template <typename TYPE, int SIZE_MAX>
class Stack
{
  public:

  const TYPE notavalue;

  inline Stack(const TYPE& notavalue = 0) throw() : notavalue(notavalue), _cursor(0)
  {
    _stack[0] = notavalue;
  }

  inline bool isEmpty() const throw()
  {
    return _cursor == 0;
  }

  inline short getSize() const throw()
  {
    return _cursor;
  }

  inline void push(const TYPE& element) throw()
  {
    _stack[++_cursor] = element;
  }

  inline TYPE pop() throw()
  {
    if(_cursor > 0) // likely true
    {
      return _stack[_cursor--]; // double if ?
    }
    else
    {
      return _stack[0];
      //return notavalue;
    }
  }

  inline void debugPush(const TYPE& element) throw()
  {
    std::cout << "I push '" << element << "' on the stack" << std::endl;
    push(element);
  }

  inline TYPE debugPop() throw()
  {
    TYPE element = pop();
    std::cout << "I pop '" << element << "' from the stack" << std::endl;
    return element;
  }

  inline void debugReport() const throw()
  {
    if(isEmpty())
    {
      std::cout << "Stack is empty" << std::endl;
    }
    else
    {
      std::cout << "Stack contains " << getSize() << " element(s) :" << std::endl;
      for(int i = 1; i <= _cursor; ++i)
      {
        std::cout << "  [" << i << "]" << _stack[i] << std::endl;
      }
    }
  }

  static void unitTest() throw()
  {
    Stack<short, 10> stack(-1);

    stack.debugReport();

    stack.debugPush(51);
    stack.debugReport();

    stack.debugPush(33);
    stack.debugReport();

    stack.debugPush(17);
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();

    stack.debugPush(2);
    stack.debugReport();

    stack.debugPush(101);
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();

    stack.debugPop();
    stack.debugReport();
  }

  private:

  short _cursor; // cursor to the top of the stack, null when stack is empty
  TYPE _stack[SIZE_MAX+1];
};



template <typename T_KEY, typename T_VAL, int SIZE>
class Array
{
  public:

  inline Array() throw()
  {
    for(int i = 0; i < SIZE; ++i)
    {
      _array[i] = 0;
    }
  }

  inline T_VAL& operator[](const T_KEY& reference) throw()
  {
    assert(reference >= 0);
    assert(reference < SIZE);
    return _array[reference];
  }

  inline const T_VAL& operator[](const T_KEY& reference) const throw()
  {
    assert(reference >= 0);
    assert(reference < SIZE);
    return _array[reference];
  }

  inline void display() const throw()
  {
    std::cout << "Array content :" << std::endl;
    for(int i = 0; i < SIZE; ++i)
    {
      std::cout << "  [" << i << "]" << _array[i] << std::endl;
    }
  }

  static void unitTest() throw()
  {
    Array<T_KEY, T_VAL, 10> array;

    array.display();
    array[0] = 15;
    array.display();
    array[2] = 51;
    array.display();
    array[3] = 77;
    array.display();
    //array[SIZE] = -1;
    //array.display();
  }

  private:

  T_VAL _array[SIZE];
};



// replace REF by KEY (naming)
template <typename ELEMENT, int SIZE_MAX = 10, typename REF_A = unsigned short, typename REF_B = unsigned short>
class FastContainer
{
  public:

  // reference and offset 0 are not allowed

  /*
  struct Element : public ELEMENT
  {
    static const int size = 32;

    inline Element() throw()
    {
      for(int i = 0; i < size; ++i)
      {
        _string[i] = 0;
      }
    }

    inline Element(const char * string) throw()
    {
      int i = 0;
      while(i < size && _string[i] != 0)
      {
        _string[i] = string[i]; ++i;
      }
      _string[i] = 0;
    }

    inline void display() const throw()
    {
      std::cout << "Element content : " << _string << std::endl;
    }

    char _string[size];
  };

  typedef REF_A ReferenceA;
  typedef REF_B ReferenceB;

  // check memory alignment

  struct Element_A : virtual public Element
  {
    ReferenceA refA;
  };

  struct Element_B : virtual public Element
  {
    ReferenceB refB;
  };

  // split references from element or bundle them ? (cache issue)

  struct Element_AB : public Element_A, public Element_B
  {
  };
  */

  typedef REF_A ReferenceA;
  typedef REF_B ReferenceB;

  typedef short Offset;

  struct Element : public ELEMENT
  {
    Element& operator=(const Element& element)
    {
      this->name = element.name;
      return *this;
    }

    mutable ReferenceA referenceA;
    mutable ReferenceB referenceB;
  };

  inline FastContainer() throw()
  {
    // what error when setting a big array on stack ? (automatic variable)
  }

  inline bool isFull() const throw()
  {
    return _free.isEmpty(); // likely false
  }

  inline void addElementWithIndexA(const ReferenceA& referenceA, const Element& element) throw()
  {
    const Offset offset = _free.pop();
    _elements[offset] = element;

    element.referenceA = referenceA;
    _indexA[referenceA] = offset;
  }

  inline void addElementWithIndexB(const ReferenceB& referenceB, const Element& element) throw()
  {
    const Offset offset = _free.pop();
    _elements[offset] = element;

    element.referenceB = referenceB;
    _indexA[referenceB] = offset;
  }

  inline const Element& getElementByIndexA(const ReferenceA& referenceA) const throw()
  {
    const Offset offset = _indexA[referenceA];
    return _elements[offset];
  }

  inline const Element& getElementByIndexB(const ReferenceB& referenceB) const throw()
  {
    const Offset offset = _indexB[referenceB];
    return _elements[offset];
  }

  inline void setElementByIndexA(const ReferenceA& referenceA, const Element& element) throw()
  {
    const Offset offset = _indexA[referenceA];
    _elements[offset] = element;
  }

  inline void setElementByIndexB(const ReferenceB& referenceB, const Element& element) throw()
  {
    const Offset offset = _indexB[referenceB];
    _elements[offset] = element;
  }

  inline void updateIndexA(const ReferenceB& referenceB, const ReferenceA& referenceA) throw()
  {
    const Offset offset = _indexB[referenceB];
    Element& element = _elements[offset];
    element.referenceA = referenceA;

    _indexA[referenceA] = offset;
  }

  inline void updateIndexB(const ReferenceA& referenceA, const ReferenceB& referenceB) throw()
  {
    const Offset offset = _indexA[referenceA];
    Element& element = _elements[offset];
    element.referenceB = referenceB;

    _indexB[referenceB] = offset;
  }

  inline void removeElementByIndexA(const ReferenceA& referenceA) throw()
  {
    const Offset offset = _indexA[referenceA];
    const Element& element = _elements[offset];
    const ReferenceB& referenceB = element.referenceB;

    _indexA[referenceA] = 0;
    _indexA[referenceB] = 0;

    _free.push(offset);
  }

  inline void removeElementByIndexB(const ReferenceB& referenceB) throw()
  {
    const Offset offset = _indexB[referenceB];
    const Element& element = _elements[offset];
    const ReferenceA& referenceA = element.referenceA;

    _indexA[referenceA] = 0;
    _indexA[referenceB] = 0;

    _free.push(offset);
  }

  private:

  Array<ReferenceA, Offset, SIZE_MAX> _indexA;   // clear at start
  Array<ReferenceB, Offset, SIZE_MAX> _indexB;   // clear at start
  Stack<Offset, SIZE_MAX>             _free;               // init at start
  Element                             _elements[SIZE_MAX]; // what at start ???
};
