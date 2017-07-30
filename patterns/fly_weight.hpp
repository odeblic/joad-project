#pragma once

template <typename T>
class LazyObject
{
  int refCount;
  T data;
};

template <typename T>
class FlyWeight
{
  LazyObject<T> * object;

  FlyWeight()
  {
    // allocation of new object
  }

  ~FlyWeight()
  {
    // deallocation of the object
  }

  FlyWeight(const FlyWeight& other)
  {
    // copy of pointer
  }

  FlyWeight& operator=(const FlyWeight& other)
  {
    // copy of pointer
  }

  void modify()
  {
    // allocation of new object copied from the original
  }
};

// when copied, just add a reference

// when modified, create a new object and apply modification

// use smart pointers
