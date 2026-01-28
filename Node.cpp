#include "Node.h"

Node::Node(Student* s) {
  student = s;
}

Node::~Node() {
  delete student;
  student = NULL;
  next = NULL;
}

void Node::setNext(Node* n) {
  next = n;
}

Node* Node::getNext() {
  return next;
}

Student* Node::getStudent() {
  return student;
}
