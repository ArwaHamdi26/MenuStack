#include "../include/Employee.hpp"

#include <iostream>

#include "../include/ArrowInput.hpp"
#include "../include/Stack.hpp"
using namespace std;

Employee::Employee() {
  id = 0;
  name = nullptr;
  salary = 0;
}
void Employee::setEmployee(int Eid, char arr[], int s) {
  id = Eid;
  name = stringCopy2(arr);
  salary = s;
};

int Employee::getID() { return id; }
const char* Employee::getName() const { return name; }
int Employee::getSalary() { return salary; }
void Employee::DisplayEmployee() {
  cout << " Employee Info" << endl;
  cout << "ID: " << id << endl;
  cout << "Name: " << (name != nullptr ? name : "No Name Entered") << endl;
  cout << "Salary: " << salary << endl;
}

Employee::~Employee() { delete[] name; }
