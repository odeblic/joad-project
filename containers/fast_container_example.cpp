#include "fast_container.hpp"

#include <cassert>
#include <iostream>

/*
class OrderBook
{
  typedef short OrderId;
  typedef short Reference;

  class Parameters {};

  FastContainer<Person, 5, short, short> orderBook;

  void newOrder();
  void newOrderAck();
  void newOrderReject();
};
*/

struct Person;

typedef FastContainer<Person, 5, int, int> Container;

struct Person //: public Container::Element
{
  Person(std::string name = "") : name(name) {}
  std::string name;
  Person& operator=(const Person& person)
  {
    this->name = person.name;
    return *this;
  }
};

int main(int argc, char * argv[])
{
  Container contacts;

  Person person("olivier");

  int referenceA = 32;
  int referenceB = 51;

  contacts.addElementWithIndexA(referenceA, (const Container::Element&)person);

  return 0;
}
