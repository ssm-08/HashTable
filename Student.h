#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

class Student {
 public:
  // Constructor and Destructor
  Student(char f[99], char l[99], int i, float g);
  ~Student();

  // Print Student name & grade
  void getDisplay();

  // Getters
  int getId();
  float getGpa();
  
 private:
  char firstName[99];
  char lastName[99];
  int id = 0;
  float gpa = 0;
};

#endif
