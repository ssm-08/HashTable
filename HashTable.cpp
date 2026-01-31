#include <iostream>
#include <cstring>
#include <fstream>

#include "Node.h"
#include "Student.h"

using namespace std;

void add(Node**& table, int& size, Node* node);
void random(Node** table, int n);
void print(Node** table, int size);
void del();
void quit();

Student createStudent();
bool checkId(Node** table, int size, int id);

void rehash(Node**& table, int& size);
int makeHash(int id, int size);

int main() {

  int size = 101;
  Node** hashtable = new Node*[size]{};
  
  bool run = true;

  char input[99] = "";
  
  const char* ADD = "ADD";
  const char* PRINT = "PRINT";
  const char* DEL = "DELETE";
  const char* RAND = "RANDOM";
  const char* QUIT = "QUIT";
  
  while (run == true) {

    // Get input
    cout << "\n";
    cout << "Enter Command: ";
    cin >> input;
    cout << "\n";

    char first[99] = "";
    char last[99] = "";
    int id = 0;
    float gpa = 0;

    if (strcmp(input, ADD) == 0) { // Add

      cout << "Enter first name: ";
      cin >> first;

      cout << "Enter last name: ";
      cin >> last;

      cout << "Enter id: ";
      cin >> id;

      cout << "Enter gpa: ";
      cin >> gpa;

      if (checkId(hashtable, size, id) == true) {
	cout << "Id in use." << endl;
      } else {
	Student* student = new Student(first, last, id, gpa);
	Node* node = new Node(student);
      }
    } else if (strcmp(input, RAND) == 0) { // Generate Students
    } else if (strcmp(input, PRINT) == 0) { // Print Students
      print(hashtable, size);
    } else if (strcmp(input, DEL) == 0) { // Delete Student
    } else if (strcmp(input, QUIT) == 0) { // Quit Program
      run = false;
    }
  }  
}

int makeHash(int id, int size) {
  return id % size;
}

void rehash(Node**&table, int& size) {

  // Resize and create new table
  int newSize = size + 101;
  Node** newTable = new Node*[newSize]{};

  // Temp variables
  Node* current = NULL;
  int id;
  int key;

  // Iterate through old hash table
  for (int i = 0; i < size; i++) {
    // Store current space
    current = table[i];

    // Go through linked list
    while (current != NULL) {

      //Store next node
      Node* next = current->getNext();
      
      id = current->getStudent()->getId();
      key = makeHash(id, newSize);

      Node* head = newTable[key];

      //Add current node to linked list in new table

      if (head == NULL) {
       	newTable[key] = current;
      } else {
	while (head->getNext() != NULL) {
	  head = head->getNext();
	}

	head->setNext(current);
      }

      // Delink
      current->setNext(NULL);
      
      // Set next node
      current = next;
      
    }
  }

  // Switch tables
  
  delete[] table;
  
  size = newSize;
  table = newTable;
}

bool checkId(Node** table, int size, int id) {
  
  int key = makeHash(id, size);
  Node* current = table[key];

  while (current != NULL) {
    if (current->getStudent()->getId() == id) {
      return true;
    }

    current = current->getNext();
  }
  
  return false;
}

void add(Node**& table, int& size, Node* node) {

  int id = node->getStudent()->getId();
  int key = makeHash(id, size);

  Node* head = table[key];

  if (head == NULL) {
    table[key] = node;
  } else if (head->getNext() == NULL) {
    head->setNext(node);
  } else if (head->getNext()->getNext() == NULL) {
    head->getNext()->setNext(node);
  } else {
    rehash(table, size);
    add(table, size, node);
  }
}

void print(Node** table, int size) {

  Node* current = NULL;
  
  for (int i = 0; i < size; i++) {
    current = table[i];

    while (current != NULL) {

      current->getStudent()->getDisplay();
      current = current->getNext();

    }
  }
}
