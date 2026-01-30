#include <iostream>
#include <cstring>
#include <fstream>

#include "Node.h"
#include "Student.h"

using namespace std;

void add(Node** table, Node* node);
void random(Node** table, int n);
void print(Node** table);
void del();
void quit();

Student createStudent();
void rehash(Node**& table);
int makeHash(Node* node, int size);

int main() {
  //Hashtable

  Node** hashtable[101];
  
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

    Student* student = new Student(first, last, id, gpa);
    Node* node = new Node(student);
    
    if (strcmp(input, ADD) == 0) { // Add
    } else if (strcmp(input, PRINT) == 0) { // Print Students
    } else if (strcmp(input, DEL) == 0) { // Delete Student
    } else if (strcmp(input, QUIT) == 0) { // Quit Program
      run = false;
    }
  }  
}
