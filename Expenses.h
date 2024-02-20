/************************************************************
*  Header file for setExpenses
*  Input: none
*  Process: get the sum of all expenses
*  Output: float total_expenses
************************************************************/
#include <fstream>

using namespace std;

#ifndef Expenses_h
#define Expenses_h

class Expenses {

private:
  float total;
  float expense_factor;

public:
  Expenses() {
    total = 0;
    expense_factor = 1;
  }

  void setExpenseFactor(float expense_factor)
    { this->expense_factor = expense_factor; }

  float getExpenseFactor()
    { return expense_factor; }

  float getTotal()
    { return total; }

  void setTotal(ifstream& expenses_file);

  void setTotal(float total);
};

#endif
