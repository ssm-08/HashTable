#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "Node.h"
#include "Student.h"

using namespace std;

// Initialize functions
void add(Node**& table, int& size, Node* node);
void print(Node** table, int size);
void del(Node** table, Node* current, Node* prev, int key, int id);
void quit(Node**& table, int size);

Student* createStudent(int id);
bool checkId(Node** table, int size, int id);

void rehash(Node**& table, int& size);
int makeHash(int id, int size);

int main() {

  // Declare program variables
  srand(time(NULL));
  
  int size = 101;
  Node** hashtable = new Node*[size]{};
  
  bool run = true;

  int randomId = 1;
  
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

    int n = 0;
    
    if (strcmp(input, ADD) == 0) { // Add

      cout << "Enter first name: ";
      cin >> first;

      cout << "Enter last name: ";
      cin >> last;

      cout << "Enter id: ";
      cin >> id;

      cout << "Enter gpa: ";
      cin >> gpa;

      // Add if id is unique
      if (checkId(hashtable, size, id) == true) {
	cout << "Id in use." << endl;
      } else {
	Student* student = new Student(first, last, id, gpa);
	Node* node = new Node(student);
	add(hashtable, size, node);
      }
      
    } else if (strcmp(input, RAND) == 0) { // Generate Students

      cout << "Enter number of students: ";
      cin >> n;

      for (int i = 0; i < n; i++) {
	while (checkId(hashtable, size, randomId) == true) {
	  randomId++;
	}

	Student* student = createStudent(randomId);
	Node* node = new Node(student);
	add(hashtable, size, node);
      }

    } else if (strcmp(input, PRINT) == 0) { // Print Students
      print(hashtable, size);
    } else if (strcmp(input, DEL) == 0) { // Delete Student

      cout << "Enter id: ";
      cin >> id;

      int key = makeHash(id, size);
      Node* current = hashtable[key];
      Node* prev = NULL;

      del(hashtable, current, prev, key, id);
      
    } else if (strcmp(input, QUIT) == 0) { // Quit Program
      quit(hashtable, size);
      delete[] hashtable;
      run = false;
    }
  }  
}

// Create a random student using text files
Student* createStudent(int id) {

  int firstSize = 0;
  int lastSize = 0;

  fstream firstNames("firstNames.txt");
  fstream lastNames("lastNames.txt");

  firstNames.seekg(0, firstNames.end);
  firstSize = firstNames.tellg();
  firstSize++;
  firstNames.seekg(0, firstNames.beg);

  lastNames.seekg(0, lastNames.end);
  lastSize = lastNames.tellg();
  lastSize++;
  lastNames.seekg(0, lastNames.beg);

  char first[firstSize];
  char last[lastSize];

  firstNames.getline(first, firstSize);
  lastNames.getline(last, lastSize);

  int f = rand() % 51;
  int l = rand() % 51;
  
  char firstName[99];
  char lastName[99];

  char* name;
  
  name = strtok(first, ",");
  int i = 0;
  
  while (name != NULL) {
    if (i == f) {
      strcpy(firstName, name);
      break;
    }
    
    i++;
    name = strtok(NULL, ",");
  }

  name = strtok(last, ",");
  int j = 0;
  
  while (name != NULL) {
    if (j == l) {
      strcpy(lastName, name);
      break;
    }

    j++;
    name = strtok(NULL, ",");
  }

  float gpa = rand() % 5;

  Student* student = new Student(firstName, lastName, id, gpa);

  return student;
  
}

// Hash function
int makeHash(int id, int size) {
  return id % size;
}

// Rehash a new table with 100 more slots
void rehash(Node**&table, int& size) {

  // Resize and create new table
  int newSize = size + 100;
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

// Iterate through the table and check existing ids
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

// Add the node to the table and chain no more than thrice
void add(Node**& table, int& size, Node* node) {

  int id = node->getStudent()->getId();
  int key = makeHash(id, size);

  Node* head = table[key];

  node->getStudent()->getDisplay();
  
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

// Iterate through the hashtable and print out students
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

// Delete one node using recursive and adjust linked list
void del(Node** table, Node* current, Node* prev, int key, int id) {
  
  if (current != NULL) {
    Node* next = current->getNext();
    
    if (current->getStudent()->getId() == id) {
      if (prev != NULL) {
	prev->setNext(current->getNext());
      } else {
	table[key] = current->getNext();
      }
      
      delete current;
      
    } else {

      del(table, next, current, key, id);

    }
  }
}

// Clear all occupied slots in hashtable and delete nodes
void quit(Node**& table, int size) {

  Node* current = NULL;
  
  for (int i = 0; i < size; i++) {
    current = table[i];

    while (current != NULL) {
      Node* next = current->getNext();

      delete current;
      current = next;
    }

    table[i] = NULL;
  }
  
}
