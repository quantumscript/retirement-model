/************************************************************
*  Implementation file for setExpenses
*  Input: none
*  Process: get the sum of all expenses
*  Output: float total_expenses
************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include "Expenses.h"

using namespace std;

void Expenses::setTotal(ifstream& expenses_file) {
  float total_expenses = 0;
  float value = 0;
  string input = "";

  while (expenses_file) {
    expenses_file >> input;

    // Ignore blank lines and add the value to the total_expenses
    if (!input.empty()) {
      value = stof(input);
      // cout << "value: " << fixed << setprecision(2) << value << endl;
      total_expenses += value;
      input = "";
    }
  }

  total_expenses *= 12;    // Monthly to annual expenses

  // Set object's total attribute
  total = total_expenses * expense_factor;
  cout << "Annual expenses: " << fixed << setprecision(2) << total << endl;
}

void Expenses::setTotal(float total)
  { this->total = total; }
