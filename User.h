/***********************************************
*  Specification file for user class
***********************************************/
#ifndef User_h
#define User_h
#include "Expenses.h"
#include "Income.h"
#include "Savings.h"

class User {

private:
  int age;
  int retirement_age;
  Expenses expenses;
  Income income;
  Savings savings;

public:

  User(int age = 0)  {
    Expenses expenses;    // No initialization needed
    Income income;        // Optional initalizatoin of (float gross, float afterTax)
    Savings savings;      // Optional initalization of (float annual_savings, float current_savings, float goal_savings)
    retirement_age = 0;
    this->age = age;
    this->savings = savings;
    this->expenses = expenses;
    this->income = income;
  }

  void setAge(int age)
    { this->age = age; }

  int getAge()
    { return age; }

  void setRetirementAge(int age)
    { retirement_age = age; }

  int getRetirementAge()
    { return retirement_age; }

  Expenses& getExpenses()
    { return expenses; }

  Income& getIncome()
    { return income; }

  Savings& getSavings()
    { return savings; }
};

#endif
