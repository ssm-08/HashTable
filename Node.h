#ifndef NODE_H
#define NODE_H


#include <iostream>
#include <cstring>

#include "Student.h"

using namespace std;

class Node {
 public:
  // Constructors & Destructors
  Node(Student* s);
  ~Node();

  // Getters & Setters for next Node
  void setNext(Node* n);
  Node* getNext();

  // Getter for Student value
  Student* getStudent();
 private:
  Student* student = NULL;
  Node* next = NULL;
};

#endif
