/* ********************************
Description: Calculates the componund interest on investments
against retirement needs.
******************************** */
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "Expenses.h"
#include "Economy.h"
#include "User.h"
#include "Income.h"
#include "Savings.h"
#include "Tax.h"
#include "TaxProg.h"

using namespace std;

int main(int argc, char* argv[]) {

  // Model inputs
  float market_growth, inflation, raise, safe_withdrawal_rate, expense_factor, income;
  market_growth = inflation = raise = safe_withdrawal_rate = expense_factor = income = -1.0;
  int age = -1;
  // Model variables
  float annual_growth = 0;
  float tax1, tax2, tax3 = 0;
  User user;
  Economy economy;
  // Model outputs
  int years_until_retirement = 0;

  // Create taxes
  // FICA
  const float FICA_TAX_RATE = 0.0765;
  Tax fica("social_security_and_medicaid", FICA_TAX_RATE);

  // Federal income tax
  const int FED_SIZE = 7;
  const float FEDERAL_INCOME_TAX_RATES[FED_SIZE] = {0.10, 0.12, 0.22, 0.24, 0.32, 0.35, 0.37};
  float FEDERAL_INCOME_TAX_BRACKETS_SINGLE[FED_SIZE] = {0, 9875, 40125, 85525, 163300, 207350, 518400};
  float FEDERAL_STANDARD_DEDUCATION_SINGLE = 12200;
  TaxProg federal("federal_income_tax", FEDERAL_INCOME_TAX_RATES, FEDERAL_INCOME_TAX_BRACKETS_SINGLE, FED_SIZE, FEDERAL_STANDARD_DEDUCATION_SINGLE);

  // State income tax using NYS numbers
  const int STATE_SIZE = 8;
  const float STATE_INCOME_TAX_RATES[] = {0.04, 0.045, 0.0525, 0.059, 0.0621, 0.0649, 0.0685, 0.0882};
  float STATE_INCOME_TAX_BRACKETS_SINGLE[STATE_SIZE] = {0, 8500, 11700, 13900, 21400, 80650, 215400, 1077550};
  float STATE_STANDARD_DEDUCATION_SINGLE = 8000;
  TaxProg state("state_income_tax", STATE_INCOME_TAX_RATES, STATE_INCOME_TAX_BRACKETS_SINGLE, STATE_SIZE, STATE_STANDARD_DEDUCATION_SINGLE);

  // Print top program boundary
  string boundary;
  int boundary_len = 76;
  boundary.assign(boundary_len, '%');
  cout << endl << boundary << endl;

  // Get age and income from shell script
  if (argc == 8) {
    expense_factor = stof(argv[1]);
    inflation = stof(argv[2]);
    market_growth = stof(argv[3]);
    raise = stof(argv[4]);
    safe_withdrawal_rate = stof(argv[5]);
    age = stoi(argv[6]);
    income = stof(argv[7]);

    economy.setInflation(inflation);
    economy.setMarketGrowth(market_growth);
    economy.setRaise(raise);
    user.getExpenses().setExpenseFactor(expense_factor);
    user.setAge(age);
    user.getIncome().setGross(income);
    cout << "Model parameters" << endl;
    cout << "expense_factor = " << expense_factor << ", inflation = " << inflation
      << ", market_growth = " << market_growth << endl << "raise = " << raise
      << ", safe_withdrawal_rate = " << safe_withdrawal_rate << endl;
    cout << endl << "Age: " << age << " Income: $" << income << endl;
  }

  // Get age and income from user input for age and income
  else {
    expense_factor = stof(argv[1]);
    inflation = stof(argv[2]);
    market_growth = stof(argv[3]);
    raise = stof(argv[4]);
    safe_withdrawal_rate = stof(argv[5]);
    economy.setInflation(inflation);
    economy.setMarketGrowth(market_growth);
    economy.setRaise(raise);
    
    do {
      cout << "How old are you? ";
      cin >> age;
    } while ( age < 0);
    user.setAge(age);

    while ( income < 0 ) {
      cout << "What is your income? ";
      cin >> income;
      user.getIncome().setGross(income);
    }
  }

  // Open expenses_file and update user's expenses
  ifstream expenses_file;
  expenses_file.open("expenses.txt");
  if ( expenses_file ) {
    user.getExpenses().setTotal(expenses_file);
    expenses_file.close();
  }

  else {
    cout << "Error opening expenses.txt." << endl;
    return 1;
  }

  // Set total retirement savings needed
  user.getSavings().setGoalSavings( user.getExpenses().getTotal() / safe_withdrawal_rate );
  cout << "You need this much to retire today: "
    << "$" << user.getSavings().getGoalSavings() << endl << endl;

  // Calculate and display savings, annual growth, and total savings per year
  string dashes;
  int numDashes = 76;
  dashes.assign(numDashes, '-');

  cout << left << setw(4) << "Year"
    << right << setw(10) << "Income"
    << setw(10) << "Expenses"
    << setw(10) << "Savings"
    << setw(10) << "Growth"
    << setw(16) << "Total Savings"
    << setw(16) << "Goal Savings" << endl;
  cout << dashes << endl;

  // Run the model
  while ( user.getSavings().getCurrentSavings() < user.getSavings().getGoalSavings() ) {

    // Update gross income with raise
    user.getIncome().setGross(user.getIncome().getGross() * (1 + economy.getRaise()));

    // Get after tax income
    tax1 = federal.calcTotal(user.getIncome().getGross(), economy.getInflation());
    tax2 = state.calcTotal(user.getIncome().getGross(), economy.getInflation());
    tax3 = fica.calcTotal(user.getIncome().getGross());
    user.getIncome().setAfterTax(user.getIncome().getGross() - tax1 - tax2 - tax3);

    // Update expenses with inflation
    user.getExpenses().setTotal( user.getExpenses().getTotal() * (1 + economy.getInflation()) );

    // Update goal savings with inflation on expenses
    user.getSavings().setGoalSavings( user.getExpenses().getTotal() / safe_withdrawal_rate );

    // Update savings
    user.getSavings().setAnnualSavings( user.getIncome().getAfterTax() - user.getExpenses().getTotal() );
    user.getSavings().setCurrentSavings( user.getSavings().getCurrentSavings() + user.getSavings().getAnnualSavings() );

    // Update growth
    if (user.getSavings().getCurrentSavings() > 0) {
      annual_growth = user.getSavings().getCurrentSavings() * economy.getMarketGrowth();
      user.getSavings().setCurrentSavings( user.getSavings().getCurrentSavings() + annual_growth );
    }

    years_until_retirement++;

    // Display year, annual savings, annual growth, and total savings
    cout << left << setw(4) << years_until_retirement
      << right << setw(10) << setprecision(0) << user.getIncome().getGross()
      << setw(10) << user.getExpenses().getTotal()
      << setw(10) << user.getSavings().getAnnualSavings()
      << setw(10) << annual_growth
      << setw(16) << user.getSavings().getCurrentSavings()
      << setw(16) << user.getSavings().getGoalSavings() << endl;
  }

  // Display retirement age
  user.setRetirementAge( user.getAge() + years_until_retirement );
  cout << endl << "It will take you " << years_until_retirement
    << " years to reach retirement at age " << user.getRetirementAge() << "."
    << endl << endl;

  return 0;
}
