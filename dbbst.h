#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <string>

using namespace std;

//stack class///
template <class T>
class GenStack
{
  public:
    GenStack(); //constructor
    GenStack(int maxSize); //overloading constructor
    ~GenStack(); //deconstructor
    void push(T d);
    void newArray();
    T pop();
    T peek(); //top
    bool isFull();
    bool isEmpty();

    int size;
    int top;
    T *myArray; //declaring pointer to a char
    T *temp;
};

class Student
{
  public:
    Student();
    Student(int id, string names, string levels, double gpas, int advisors);
    ~Student();
    int studentID;
    string name;
    string level;
    double gpa;
    int advisor;
};

class Faculty
{
  public:
    Faculty();
    Faculty(int fid, string nam, string lev, string dep, int* adv);
    ~Faculty();
    int facultyID;
    string fname;
    string flevel;
    string department;
    int* advisee;
};

//define treenode class
class TreeNode
{
  public:
    TreeNode();
    TreeNode(Student person);
    TreeNode(Faculty person);
    virtual ~TreeNode(); // figure out on your own

    int key;
    int fkey;
    string name;
    string fname;
    string level;
    string flevel;
    double gpa;
    int advisor;
    string department;
    int* advisee;
    TreeNode *left;
    TreeNode *right;
};

/// define tree class
class BST
{
  public:
    BST();
    virtual ~BST();
    void destroyRecursive(TreeNode* node);
    void insertStudent(Student person);
    void insertFaculty(Faculty person);
    bool containsS(int value); /// AKA search()
    bool containsF(int value);
    void viewStudent(int value);
    void viewFaculty(int value);
    int getAdvisor(int value);
    int* getStudents(int value);
    void changeAdvsior(int value, int newfid);
    void removeStudent(int value, int sid);
    TreeNode* getSuccessor(TreeNode* d);
    bool deleteS(int k);
    bool deleteF(int k);

    TreeNode* getMin();
    TreeNode* getMax();
    bool isEmpty();
    void printStudentTree();
    void printFacultyTree();
    void writeStudentTree(string file);
    void writeFacultyTree(string file);
    void recPrintFaculty(TreeNode *node);
    void recPrintStudent(TreeNode *node);
    void filePrintStudent(TreeNode *node);
    void filePrintFaculty(TreeNode *node);
    TreeNode *root;
};

class Prog
{
  public:
    Prog();
    ~Prog();
    void readInStudent();
    void readInFaculty();
    void enterStudents();
    void enterFaculty();
    int* makeArray();
    void printStudents();
    void printFaculty();
    void displayStudent();
    void displayFaculty();
    void printAdvisor();
    void printStudent();
    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeStudentAdvisor();
    void removeAdvisee();
    void rollback();
    void displayOptions();
    void writeFile();
};

//stack implementation////
template <class T>
GenStack<T>::GenStack() //defualt constructor
{
  //initialization of default values
  myArray = new T[10]; //"new" allocates memory dynamically on the heap. need to delete memory before you exit program with deconstructor
  size = 10;
  top = -1;
}

template <class T>
GenStack<T>::GenStack(int maxSize)
{
  myArray = new T[maxSize]; //"new" allocates memory dynamically on the heap. need to delete memory before you exit program with deconstructor
  size = maxSize;
  top = -1;
}

template <class T>
GenStack<T>::~GenStack()
{
  delete [] myArray;
  delete [] temp;
}

template <class T>
void GenStack<T>::push(T d)
{
  //neeed to error boundary check
  //add to a new stack of increased size
  if(isFull() != true)
  {
    myArray[++top] = d;
  }
  else
  {
    newArray();
    myArray[++top] = d;
  }
}

template <class T>
void GenStack<T>::newArray()
{
  temp = new T[2*size];
  for (int i = 0; i < size; i++)
  {
    temp[i] = myArray[i];
  }
  size *= 2;
  delete [] myArray;
  myArray = temp;
}

template <class T>
T GenStack<T>::pop()
{
  //error checking, make sure its not isEmpty
  if(isEmpty() != true)
  {
    return myArray[top--];
  }
  else
  {
    cout << "The stack is empty." << endl;
  }
}

template <class T>
T GenStack<T>::peek()
{
  //check if empty
  if(isEmpty() != true)
  {
    return myArray[top];
  }
  else
  {
    cout << "The stack is empty" << endl;
  }
}

template <class T>
bool GenStack<T>::isFull()
{
  return (top == size-1);
}

template <class T>
bool GenStack<T>::isEmpty()
{
  return (top == -1);
}
