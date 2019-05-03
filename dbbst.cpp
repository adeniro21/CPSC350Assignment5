#include "dbbst.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <string>

using namespace std;

BST masterStudent;
BST masterFaculty;
GenStack<Student> rollbackStudent(5);
GenStack<int> rollbackSint(5);
GenStack<Faculty> rollbackFaculty(5);
GenStack<int> rollbackFint(5);
string students;
string facultys;
ofstream wfile;

////implement TreeNode/////
TreeNode::TreeNode()
{
  left = NULL;
  right = NULL;
}

TreeNode::TreeNode(Student person)
{
  left = NULL;
  right = NULL;
  key = person.studentID;
  name = person.name;
  level = person.level;
  gpa = person.gpa;
  advisor = person.advisor;
}

TreeNode::TreeNode(Faculty person)
{
  left = NULL;
  right = NULL;
  fkey = person.facultyID;
  fname = person.fname;
  flevel = person.flevel;
  department = person.department;
  advisee = person.advisee;
}

TreeNode::~TreeNode()
{
  delete left;
  delete right;
}

/////implement bst///////
BST::BST()
{
  root = NULL; //empty tree
}

BST::~BST()
{
  // iterate and delete
  // on your own
  destroyRecursive(root);
}

void BST::destroyRecursive(TreeNode *node)
{
  if(node)
  {
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
  }
}

void BST::printStudentTree()
{
  recPrintStudent(root);
}

void BST::writeStudentTree(string file) //opening file, calling writeStudentTree
{
  ::wfile.open(file);
  filePrintStudent(root);
  ::wfile.close();
}

void BST::printFacultyTree()
{
  recPrintFaculty(root);
}

void BST::writeFacultyTree(string file) //opening file, calling writeStudentTree
{
  ::wfile.open(file);
  filePrintFaculty(root);
  ::wfile.close();
}

void BST::recPrintStudent(TreeNode *node)
{
  if(node == NULL)
    return;

  recPrintStudent(node->left);
  cout << node->key << "," << node->name << "," << node->level << "," << node->gpa << "," << node->advisor << endl;
  recPrintStudent(node->right);
}

void BST::filePrintStudent(TreeNode *node) //write students to studentTable.txt
{
  if(node == NULL)
    return;

  filePrintStudent(node->left);
  ::wfile << node->key << "," << node->name << "," << node->level << "," << node->gpa << "," << node->advisor << endl;
  filePrintStudent(node->right);
}

void BST::recPrintFaculty(TreeNode *node) //print for faculty
{
  if(node == NULL)
    return;

  recPrintFaculty(node->left);
  cout << node->fkey << "," << node->fname << "," << node->flevel << "," << node->department << ",";
  for(int i = 0; i < 5; i++)
  {
    if(i != 4)
    {
      cout << node->advisee[i] << ",";
    }
    else
    {
      cout << node->advisee[i] << endl;
    }
  }
  recPrintFaculty(node->right);
}

void BST::filePrintFaculty(TreeNode *node) //write students to facultyTable.txt
{
  if(node == NULL)
    return;

  filePrintFaculty(node->left);
  ::wfile << node->fkey << "," << node->fname << "," << node->flevel << "," << node->department << ",";
  for(int i = 0; i < 5; i++)
  {
    ::wfile << node->advisee[i] << ",";
  }
  ::wfile << "" << endl;
  filePrintFaculty(node->right);
}


bool BST::isEmpty()
{
  return (root == NULL);
}

TreeNode* BST::getMin()
{
  TreeNode *curr = root;
  while(curr->left != NULL)
  {
    curr = curr->left;
  }
  return curr;
}

TreeNode* BST::getMax()
{
  TreeNode *curr = root;
  while(curr->right != NULL)
  {
    curr = curr->right;
  }
  return curr;
}

void BST::insertStudent(Student value)
{
  // check if value exists, if not continue
  // iterative
  TreeNode *node = new TreeNode(value);

  if(isEmpty()) //empty tree
  {
    root = node;
  }
  else // not an empty tree, continue to add
  {
    TreeNode *current = root;
    TreeNode *parent; // empty node

    while(true) //lets look at our insertion point
    {
      parent = current;
      if(value.studentID < current->key) // go left
      {
        current = current->left;
        if(current == NULL) //we found out location
        {
          parent->left = node;
          break;
        }
      }
      else //go right
      {
        current = current->right;
        if(current == NULL) // found new node home
        {
          parent->right = node;
          break;
        }
      }
    }
  }
}

void BST::insertFaculty(Faculty value)
{
  // check if value exists, if not continue
  // iterative
  TreeNode *node = new TreeNode(value);

  if(isEmpty()) //empty tree
  {
    root = node;
  }
  else // not an empty tree, continue to add
  {
    TreeNode *current = root;
    TreeNode *parent; // empty node

    while(true) //lets look at our insertion point
    {
      parent = current;
      if(value.facultyID < current->fkey) // go left
      {
        current = current->left;
        if(current == NULL) //we found out location
        {
          parent->left = node;
          break;
        }
      }
      else //go right
      {
        current = current->right;
        if(current == NULL) // found new node home
        {
          parent->right = node;
          break;
        }
      }
    }
  }
}

bool BST::containsS(int value)
{
  if(isEmpty()) //empty tree, nothing exists
  {
    return false;
  }

  TreeNode *current = root;
  while(current->key != value)
  {
    if(value < current->key)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }

    if(current == NULL) //value not in tree
    {
      return false;
    }
  }
  return true;
}

bool BST::containsF(int value)
{
  if(isEmpty()) //empty tree, nothing exists
  {
    return false;
  }

  TreeNode *current = root;
  while(current->fkey != value)
  {
    if(value < current->fkey)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }

    if(current == NULL) //value not in tree
    {
      return false;
    }
  }
  return true;
}

void BST::viewStudent(int value)
{
  TreeNode *current = root;
  while(current->key != value)
  {
    if(value < current->key)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  cout << current->key << "," << current->name << "," << current->level << "," << current->gpa << "," << current->advisor << endl;
}

void BST::viewFaculty(int value)
{
  TreeNode *current = root;
  while(current->fkey != value)
  {
    if(value < current->fkey)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  cout << current->fkey << "," << current->fname << "," << current->flevel << "," << current->department << ",";
  for(int i = 0; i < 5; i++)
  {
    if(i != 4)
    {
      cout << current->advisee[i] << ",";
    }
    else
    {
      cout << current->advisee[i];
    }
  }
}

int BST::getAdvisor(int value)
{
  TreeNode *current = root;
  while(current->key != value)
  {
    if(value < current->key)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  int adv = current->advisor;
  return adv;
}

int* BST::getStudents(int value)
{
  TreeNode *current = root;
  while(current->fkey != value)
  {
    if(value < current->fkey)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  int* adv = current->advisee;
  return adv;
}

void BST::changeAdvsior(int value, int newfid)
{
  TreeNode *current = root;
  while(current->key != value)
  {
    if(value < current->key)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  /*int adv = current->advisor; //trying to change faculty advisee list as well but keep getting seg fault errors
  int* students = getStudents(adv);
  for(int i = 0; i < 5; i++) //removing student from advisor list
  {
    if(value == students[i])
    {
      students[i] = 0;
    }
  }*/
  Student stud(current->key, current->name, current->level, current->gpa, newfid);
  deleteS(current->key); //deleting current student
  insertStudent(stud); //replacing with updated advisor
}

void BST::removeStudent(int value, int sid) //removing student from advisee list
{
  TreeNode *current = root;
  while(current->fkey != value)
  {
    if(value < current->fkey)
    {
        current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  int* students = current->advisee;
  for(int i = 0; i < 5; i++)
  {
    if(sid == students[i])
    {
      students[i] = 0;
    }
  }
}

bool BST::deleteS(int k)
{
  if(isEmpty())
  {
    return false;
  }

  //check if key/value exists in the tree

  TreeNode *current = root;
  TreeNode *parent = root;
  bool isLeft = true;

  //now let's iterate and update our pointers
  while(current->key != k)
  {
    parent = current;

    if(k < current->key)
    {
      isLeft = true;
      current = current->left;
    }
    else
    {
      isLeft = false;
      current = current->right;
    }

    if(current == NULL)
    {
      return false;
    }
  }
  //we found our node to be deleted
  Student stud(current->key, current->name, current->level, current->gpa, current->advisor); //creating student for rollback
  rollbackStudent.push(stud);
  rollbackSint.push(8);

  if(current->left == NULL && current->right == NULL) //leaf node, no children
  {
    if(current == root)
    {
      root = NULL;
    }
    else if(isLeft)
    {
      parent->left == NULL;
    }
    else
    {
      parent->right == NULL;
    }
  }
  //need to check if node to be deleted has one child
  else if(current->right == NULL) //no right child
  {
    if(current == root)
    {
      root = current->left;
    }
    else if(isLeft)
    {
      parent->left = current->left;
    }
    else
    {
      parent->right = current->left;
    }
  }
  else if(current->left == NULL) //no left child
  {
    if(current == root)
    {
      root = current->right;
    }
    else if(isLeft)
    {
      parent->left = current->right;
    }
    else
    {
      parent->right = current->right;
    }
  }
  else //the node to be deleted has 2 children
  {
    //find successor of the node to be deleted (current)
    TreeNode *successor = getSuccessor(current);

    if(current == root)
    {
      root = successor;
    }
    else if(isLeft)
    {
      parent->left = successor;
    }
    else
    {
      parent->right = successor;
    }

    successor->left = current->left;
  }
  return true;
}
//might want to null current pointers out before you delete them
//figure out when to delete nodes

bool BST::deleteF(int k)
{
  if(isEmpty())
  {
    return false;
  }

  //check if key/value exists in the tree

  TreeNode *current = root;
  TreeNode *parent = root;
  bool isLeft = true;

  //now let's iterate and update our pointers
  while(current->fkey != k)
  {
    parent = current;

    if(k < current->fkey)
    {
      isLeft = true;
      current = current->left;
    }
    else
    {
      isLeft = false;
      current = current->right;
    }

    if(current == NULL)
    {
      return false;
    }
  }
  //we found our node to be deleted
  Faculty fud(current->fkey, current->fname, current->flevel, current->department, current->advisee); //creating student for rollback
  rollbackFaculty.push(fud);
  rollbackFint.push(10);

  if(current->left == NULL && current->right == NULL) //leaf node, no children
  {
    if(current == root)
    {
      root = NULL;
    }
    else if(isLeft)
    {
      parent->left == NULL;
    }
    else
    {
      parent->right == NULL;
    }
  }
  //need to check if node to be deleted has one child
  else if(current->right == NULL) //no right child
  {
    if(current == root)
    {
      root = current->left;
    }
    else if(isLeft)
    {
      parent->left = current->left;
    }
    else
    {
      parent->right = current->left;
    }
  }
  else if(current->left == NULL) //no left child
  {
    if(current == root)
    {
      root = current->right;
    }
    else if(isLeft)
    {
      parent->left = current->right;
    }
    else
    {
      parent->right = current->right;
    }
  }
  else //the node to be deleted has 2 children
  {
    //find successor of the node to be deleted (current)
    TreeNode *successor = getSuccessor(current);

    if(current == root)
    {
      root = successor;
    }
    else if(isLeft)
    {
      parent->left = successor;
    }
    else
    {
      parent->right = successor;
    }

    successor->left = current->left;
  }
  return true;
}

TreeNode* BST::getSuccessor(TreeNode *d) //d is the node to be deleted
{
  TreeNode *sp = d; //successor's parent
  TreeNode *successor = d;
  TreeNode *current = d->right; //smallest value larger than the root

  while(current != NULL)
  {
    sp = successor;
    successor = current;
    current = current->left;
  }

  //we need to check if successor is a descendant of right child
  if(successor != d->right)
  {
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}

////student class implementation////
Student::Student()
{

}

Student::Student(int id, string names, string levels, double gpas, int advisors)
{
  studentID = id;
  name = names;
  level = levels;
  gpa = gpas;
  advisor = advisors;
}

Student::~Student()
{

}

Faculty::Faculty()
{
  advisee = new int[5];
}

Faculty::Faculty(int fid, string nam, string lev, string dep, int* adv)
{
  facultyID = fid;
  fname = nam;
  flevel = lev;
  department = dep;
  advisee = adv; //think resizeable array
}

Faculty::~Faculty()
{
  //delete[] advisee;
}

Prog::Prog()
{

}

Prog::~Prog()
{
  delete[] makeArray();
}

void Prog::readInStudent()
{
  int studentLines = -1;
  string line;
  ifstream locFile;
  string location = "studentTable.txt";
  locFile.open(location, ios::in);
  if (locFile.is_open())
  {
    while(!locFile.eof())
    {
      getline(locFile, line);
      string st = line.substr(0, line.size());
      ::students.append(st);
      if(st != "")
      {
        ::students.append("|"); //parsing lines apart in the string
      }
      studentLines++;
    }
  }
  else
  {
    cout << location << " does not exist in the current directory" << endl;
    cout << "initializing empty tree" << endl;
  }
  locFile.close();
  if(studentLines == 0)
  {
    cout << "student database is empty" << endl;
  }
}

void Prog::readInFaculty()
{
  int facultyLines = -1;
  string line;
  ifstream loc;
  string location2 = "facultytable.txt";
  loc.open(location2, ios::in);
  if (loc.is_open())
  {
    while(!loc.eof())
    {
      getline(loc, line);
      string st = line.substr(0, line.size());
      ::facultys.append(st);
      if(st != "")
      {
        ::facultys.append("|"); //parsing lines apart in the string
      }
      facultyLines++;
    }
  }
  else
  {
    cout << location2 << " does not exist in the current directory" << endl;
    cout << "initializing empty tree" << endl;
  }
  loc.close();
  if(facultyLines == 0)
  {
    cout << "faculty database is empty" << endl;
  }
}

void Prog::enterStudents() //entering students into student database
{
  //cout << ::students << endl;
  int commaCount = 0;
  string ids;
  int id = 0;
  string name;
  string level;
  string gpas;
  double gpa = 0.0;
  string ads;
  int advisor = 0;
  for (int i = 0; i < ::students.size(); i++)
  {
    if(::students[i] == ',')
    {
      commaCount++;
    }
    if(commaCount == 0 && ::students[i] != ',')
    {
      ids += ::students[i];
    }
    else if(commaCount == 1 && ::students[i] != ',')
    {
      name += ::students[i];
    }
    else if(commaCount == 2 && ::students[i] != ',')
    {
      level += ::students[i];
    }
    else if(commaCount == 3 && ::students[i] != ',')
    {
      gpas += ::students[i];
    }
    else if(commaCount == 4 && ::students[i] != ',')
    {
      ads += ::students[i];
    }
    if(::students[i] == '|')
    {
      stringstream input1(ids);
      input1 >> id;
      gpa = atof(gpas.c_str());
      stringstream input3(ads);
      input3 >> advisor;
      if(id != 0)
      {
        Student stud(id, name, level, gpa, advisor);
        masterStudent.insertStudent(stud);
      }
      id = 0;
      gpa = 0.0;
      advisor = 0;
      commaCount = 0;
      ids = "";
      name = "";
      level = "";
      gpas = "";
      ads = "";
    }
  }
}

void Prog::enterFaculty() //entering faculty into faculty database
{
  //cout << ::facultys << endl;

  int commaCount = 0;
  string ids;
  int id = 0;
  string name;
  string level;
  string deps;
  string advisees;
  int* advs = new int[5]; //limit 5 advisees per advisor
  for(int i = 0; i < 5; i++)
  {
    advs[i] = 0;
  }
  int adv = 0;
  for (int i = 0; i < ::facultys.size(); i++)
  {
    if(::facultys[i] == ',') //values separted by commas, keep track of which attribute we're making
    {
      commaCount++;
    }
    if(commaCount == 0 && ::facultys[i] != ',')
    {
      ids += ::facultys[i];
    }
    else if(commaCount == 1 && ::facultys[i] != ',')
    {
      name += ::facultys[i];
    }
    else if(commaCount == 2 && ::facultys[i] != ',')
    {
      level += ::facultys[i];
    }
    else if(commaCount == 3 && ::facultys[i] != ',')
    {
      deps += ::facultys[i];
    }
    else if(commaCount >= 4)
    {
      if(commaCount > 4 && ::facultys[i] == ',')
      {
        stringstream input(advisees);
        input >> adv;
        for (int i = 0; i < 5; i++)
        {
          if(advs[i] == 0)
          {
            advs[i] = adv;
            break;
          }
        }
        advisees = "";
        adv = 0;
      }
      else if(::facultys[i] != ',' && ::facultys[i] != '|')
      {
        advisees += ::facultys[i];
      }
    }
    if(::facultys[i] == '|')
    {
      stringstream input1(ids);
      input1 >> id;
      if(id != 0)
      {
        Faculty fud(id, name, level, deps, advs);
        masterFaculty.insertFaculty(fud);
      }
      id = 0;
      adv = 0;
      commaCount = 0;
      ids = "";
      name = "";
      level = "";
      deps = "";
      advisees = "";
      int* newArray = makeArray();
      advs = newArray;
    }
  }
}

int* Prog::makeArray()
{
  int* empty = new int[5];
  for(int i = 0; i < 5; i++)
  {
    empty[i] = 0;
  }
  return empty;
}

void Prog::printStudents()
{
  masterStudent.printStudentTree();
}

void Prog::printFaculty()
{
  masterFaculty.printFacultyTree();
}

void Prog::displayStudent()
{
  int answer;
  cout << "what is the student ID? ";
  cin >> answer;
  if(masterStudent.containsS(answer))
  {
    masterStudent.viewStudent(answer);
  }
  else
  {
    cout << "Student does not exist in database with student ID" << answer << ". Cannot execute command" << endl;
  }
  if(cin.fail())
  {
    cin.clear();
    cin.ignore();
  }
}

void Prog::displayFaculty()
{
  int answer;
  cout << "what is the faculty ID? ";
  cin >> answer;
  if(masterFaculty.containsF(answer))
  {
    masterFaculty.viewFaculty(answer);
  }
  else
  {
    cout << "Faculty member does not exist in database with faculty ID " << answer << ". Cannot execute command" << endl;
  }
  if(cin.fail())
  {
    cin.clear();
    cin.ignore();
  }
}

void Prog::printAdvisor()
{
  int answer;
  cout << "what is the student ID? ";
  cin >> answer;
  if(masterStudent.containsS(answer))
  {
    masterFaculty.viewFaculty(masterStudent.getAdvisor(answer));
  }
  else
  {
    cout << "Student does not exist in database with student ID " << answer << ". Cannot execute command" << endl;
  }
  if(cin.fail())
  {
    cin.clear();
    cin.ignore();
  }
}

void Prog::printStudent()
{
  int answer;
  cout << "what is the faculty ID? ";
  cin >> answer;
  if(masterFaculty.containsF(answer))
  {
    int* students = masterFaculty.getStudents(answer);
    for(int i = 0; i < 5; i++)
    {
      if(masterStudent.containsS(students[i]))
      {
        masterStudent.viewStudent(students[i]);
      }
    }
  }
  else
  {
    cout << "Faculty member does not exist with faculty ID " << answer << ". Cannot execute command" << endl;
  }
  if(cin.fail())
  {
    cin.clear();
    cin.ignore();
  }
}

void Prog::addStudent()
{
  int num = 1;
  int answer1;
  string answer2;
  string answer3;
  double answer4;
  int answer5;
  while(num == 1)
  {
    cout << "what is the ID of the student? ";
    cin >> answer1;
    if(masterStudent.containsS(answer1) == true)
    {
      cout << "Database already contains student with student ID " << answer1 << ". Cannot add student." << endl;
      break;
    }
    cout << "what is the last name of the student? ";
    cin >> answer2;
    cout << "what is the level (Freshman, Sophmore, Junior, Senior) of the student? ";
    cin >> answer3;
    cout << "what is the GPA of the student? ";
    cin >> answer4;
    cout << "what is the faculty ID of their advisor? ";
    cin >> answer5;
    if(masterFaculty.containsF(answer5) == false && masterFaculty.isEmpty() == false)
    {
      cout << "There is no faculty member with faculty ID " << answer5 << ". Cannot add student." << endl;
      break;
    }
    if(cin.fail())
    {
      cout << "Not a valid option. Cannot add student.";
      cin.clear();
      cin.ignore();
      break;
    }
    Student stud(answer1, answer2, answer3, answer4, answer5);
    masterStudent.insertStudent(stud);
    rollbackStudent.push(stud);
    rollbackSint.push(7);
    num = 0;
  }
}

void Prog::deleteStudent()
{
  int id = 0;
  cout << "what is the student ID of the student you want to delete? ";
  cin >> id;
  if(masterStudent.containsS(id) == true)
  {
    masterStudent.deleteS(id);
  }
  else
  {
    cout << "Student does not exist in the student database" << endl;
  }
}

void Prog::addFaculty()
{
  int num = 1;
  int answer1;
  string answer2;
  string answer3;
  string answer4;
  int answer5;
  int* adv = new int[5];
  for(int i = 0; i < 5; i++)
  {
    adv[i] = 0;
  }
  while(num == 1)
  {
    cout << "what is the ID of the faculty member? ";
    cin >> answer1;
    if(masterFaculty.containsF(answer1) == true)
    {
      cout << "Database already contains faculty member with faculty ID " << answer1 << ". Cannot add faculty." << endl;
      break;
    }
    cout << "what is the last name of the faculty member? ";
    cin >> answer2;
    cout << "what is the level (Lecturer, Professor, Assitant, etc.) of the faculty member? ";
    cin >> answer3;
    cout << "what is the department of the faculty member? ";
    cin >> answer4;
    cout << "what is the student ID of their advisee? ";
    cin >> answer5;
    if(masterStudent.containsS(answer5) == false && masterStudent.isEmpty() == false)
    {
      cout << "There is no student with student ID " << answer5 << ". Cannot add faculty." << endl;
      break;
    }
    else
    {
      adv[0] = answer5;
    }
    if(cin.fail())
    {
      cout << "Not a valid option. Cannot add faculty.";
      cin.clear();
      cin.ignore();
      break;
    }
    Faculty fud(answer1, answer2, answer3, answer4, adv);
    masterFaculty.insertFaculty(fud);
    rollbackFaculty.push(fud);
    rollbackFint.push(9);
    num = 0;
  }
}

void Prog::deleteFaculty()
{
  int id = 0;
  cout << "what is the faculty ID of the faculty member you want to delete? ";
  cin >> id;
  if(masterFaculty.containsF(id) == true)
  {
    masterFaculty.deleteF(id);
  }
  else
  {
    cout << "Faculty member does not exist in the faculty database" << endl;
  }
}

void Prog::changeStudentAdvisor()
{
  int answer1;
  int answer2;
  cout << "what is the studentID? ";
  cin >> answer1;
  cout << "what is the faculty ID of the faculty member you want to change to? ";
  cin >> answer2;
  if(masterStudent.containsS(answer1))
  {
    if(masterFaculty.containsF(answer2))
    {
      masterStudent.changeAdvsior(answer1, answer2);
    }
    else
    {
      cout << "Faculty database does not contain faculty member with ID " << answer2 << ". Cannot exectue command";
    }
  }
  else
  {
    cout << "Student database does not contain student with ID " << answer1 << ". Cannot exectue command";
  }
  if(cin.fail())
  {
    cout << "Not a valid option. Cannot execute command.";
    cin.clear();
    cin.ignore();
  }
}

void Prog::removeAdvisee()
{
  int answer1;
  int answer2;
  cout << "what is the student ID? ";
  cin >> answer1;
  cout << "what is the faculty ID? ";
  cin >> answer2;
  masterFaculty.removeStudent(answer2, answer1);
  if(cin.fail())
  {
    cout << "Not a valid option. Cannot execute command.";
    cin.clear();
    cin.ignore();
  }
}

void Prog::rollback()
{
  int num = 1;
  int answer = 0;
  while(num == 1)
  {
    cout << "are you trying to undo a (1) student change or (2) faculty change? ";
    cin >> answer;
    if(answer == 1)
    {
      Student stud = rollbackStudent.pop();
      int sint = rollbackSint.pop();
      if(sint == 7)
      {
        //cout << "hi" << endl;
        masterStudent.deleteS(stud.studentID);
      }
      else if(sint == 8)
      {
        masterStudent.insertStudent(stud);
      }
      num = 0;
    }
    else if(answer == 2)
    {
      Faculty fud = rollbackFaculty.pop();
      int fint = rollbackFint.pop();
      if(fint == 9)
      {
        masterFaculty.deleteF(fud.facultyID);
      }
      else if(fint == 10)
      {
        masterFaculty.insertFaculty(fud);
      }
      num = 0;
    }
    else
    {
      cout << "not a valid input" << endl;
    }
    if(cin.fail())
    {
      cout << "Cannot execute command.";
      cin.clear();
      cin.ignore();
      break;
    }
  }
}

void Prog::displayOptions()
{
  int stopper = 1;
  int option = 0;
  while(stopper == 1)
  {
    cout << "" << endl;
    cout << "(1) Print all students and their information" << endl;
    cout << "(2) Print all faculty and their information" << endl;
    cout << "(3) Find and display student information" << endl;
    cout << "(4) Find and display faculty information" << endl;
    cout << "(5) Given student, print the name and info of faculty advisor" << endl;
    cout << "(6) Given a faculty, print ALL the names and info of his/her advisees" << endl;
    cout << "(7) Add a new student" << endl;
    cout << "(8) Delete a student" << endl;
    cout << "(9) Add a new faculty member" << endl;
    cout << "(10) Delete a faculty member" << endl;
    cout << "(11) Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << "(12) Remove an advisee from a faculty member given the ids" << endl;
    cout << "(13) Rollback" << endl;
    cout << "(14) Exit" << endl;
    cout << "" << endl;
    cout << "choose an option by selecting the number: ";
    cin >> option;
    if(option == 1)
    {
      printStudents();
    }
    else if(option == 2)
    {
      printFaculty();
    }
    else if(option == 3)
    {
      displayStudent();
    }
    else if(option == 4)
    {
      displayFaculty();
    }
    else if(option == 5)
    {
      printAdvisor();
    }
    else if(option == 6)
    {
      printStudent();
    }
    else if(option == 7)
    {
      addStudent();
    }
    else if(option == 8)
    {
      deleteStudent();
    }
    else if(option == 9)
    {
      addFaculty();
    }
    else if(option == 10)
    {
      deleteFaculty();
    }
    else if(option == 11)
    {
      changeStudentAdvisor();
    }
    else if(option == 12)
    {
      removeAdvisee();
    }
    else if(option == 13)
    {
      rollback();
    }
    else if(option == 14)
    {
      stopper = 0;
      writeFile();
    }
    else
    {
      if(cin.fail())
      {
        cout << "not a valid option" << endl;
        cin.clear();
        cin.ignore();
      }
    }
  }
}

void Prog::writeFile()
{
  masterStudent.writeStudentTree("studentTable.txt");
  masterFaculty.writeFacultyTree("facultyTable.txt");
}
