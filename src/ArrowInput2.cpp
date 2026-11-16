
#include <termios.h>
#include <unistd.h>

#include <iostream>

#include "../include/Employee.hpp"
#include "../include/Stack.hpp"
using namespace std;
extern char menu[3][10];
const int EmployeeSize = 5;
int currentsize = EmployeeSize;
int count = 0;
Employee emp;
Employee* empArr = new Employee[EmployeeSize];
Stack s(EmployeeSize);
bool isNotString(char* arr) {
  if (arr[0] == '\0') {
    return false;
  } else {
    for (int i = 0; (arr[i] != '\0'); i++) {
      if (!((arr[i] >= 'a' && arr[i] <= 'z') ||
            (arr[i] >= 'A' && arr[i] <= 'Z'))) {
        return true;
      }
    }
    return false;
  }
}

void stringCopy(char arr1[], char arr2[], int size) {
  int i = 0;

  while (arr1[i] != '\0') {
    arr2[i] = arr1[i];
    i++;
  }
  arr2[i] = '\0';
  cout << endl;
}

int stringLength(char arr[]) {
  int size = 0;
  char* ptr = arr;
  while (*ptr != '\0') {
    size += 1;
    ptr++;
  }
  return size;
}
char* stringCopy2(char arr[]) {
  char* arr2 = new char[stringLength(arr) + 1];

  int i = 0;
  while (arr[i] != '\0') {
    arr2[i] = arr[i];
    i++;
  }
  arr2[i] = '\0';
  return arr2;
}

char getch_linux() {
  char buf = 0;
  struct termios old = {0};

  tcgetattr(0, &old);

  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;

  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;

  tcsetattr(0, TCSANOW, &old);

  read(0, &buf, 1);

  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;

  tcsetattr(0, TCSADRAIN, &old);

  return buf;
}

void clear() {
  cout << "\033[2J\033[H";
  cout.flush();
}

void drawMenu(char arr[][10], int size, int line) {
  for (int i = 0; i < size; i++) {
    if (i == line) {
      cout << ">";
    }
    cout << arr[i] << endl;
  }
}

void Escape() {
  while (true) {
    char key = getch_linux();

    if (key == '\033') {
      return;
    }
  }
}

void arrowkey(int line) {
  char byte1 = 'q';
  char byte2 = 'q';
  char byte3 = 'q';

  do {
    byte1 = getch_linux();

    if (byte1 == '\033') {
      byte2 = getch_linux();

      if (byte2 == '[') {
        byte3 = getch_linux();

        switch (byte3) {
          case 'A':
            if (line != 0) {
              line--;
              clear();
              drawMenu(menu, 3, line);
            }
            break;

          case 'B':
            if (line != 2) {
              line++;
              clear();
              drawMenu(menu, 3, line);
            }
            break;
        }
      }
    }

    if (byte1 == '\n' || byte1 == '\r') {
      switch (line) {
        case 0: {
          if (count >= currentsize) {
            int newsize = currentsize * 2;
            Employee Emp;
            Stack s2(currentsize);
            while (s.pop(&Emp)) {
              s2.push(Emp);
            }
            s = Stack(newsize);
            while (s2.pop(&Emp)) {
              s.push(Emp);
            }
            currentsize = newsize;
          }

          cout << "ADD a new Employee:" << endl;
          int Eid, sal;
          char name[50];

          cout << "Enter ID: " << endl;
          while (!(cin >> Eid)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number for ID: "
                 << endl;
          }

          cout << "Enter Name: " << endl;
          cin >> name;
          while (isNotString(name)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid name, please enter a string: " << endl;
            cin >> name;
          }
          cout << "Enter Salary: " << endl;
          while (!(cin >> sal)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number for Salary: "
                 << endl;
          }
          Employee newEmployee;
          newEmployee.setEmployee(Eid, name, sal);
          s.push(newEmployee);
          cout << "Employee added successfully" << endl;
          count++;

          Escape();
          clear();
          cout << endl;
          drawMenu(menu, 3, line);
          break;
        }
        case 1:
          clear();
          if (count == 0) {
            cout << "No Employees found";
          } else {
            s.display();
          }

          cout << "\nPress ESC to return to the main menu" << endl;
          Escape();
          clear();
          cout << endl;
          drawMenu(menu, 3, line);
          break;

        case 2:
          byte1 = 'q';
          break;
      }
    }
  } while (byte1 != 'q' && byte1 != 'Q');
}
