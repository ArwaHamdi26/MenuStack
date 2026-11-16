#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP
class Employee {
 private:
  int id;
  char* name;
  int salary;

 public:
  Employee();

  ~Employee();
  void setEmployee(int Eid, char arr[], int s);
  int getID();
  const char* getName() const;
  int getSalary();
  void DisplayEmployee();
};
#endif