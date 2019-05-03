#include "dbbst.h"
#include <iostream>

using namespace std;

int main()
{
  Prog p;
  p.readInStudent();
  p.readInFaculty();
  p.enterStudents();
  p.enterFaculty();
  p.displayOptions();
  return 0;
}
