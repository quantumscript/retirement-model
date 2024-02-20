# Shell script to run retirement program
#!/bin/bash -e

# 1. Run applescript updateExpenses to get new expense data
# First command line arg set to 1 to call applescript to update expenses
if [ $1 == 1 ]
then osascript update_expenses.scpt
fi

# 2. Compile retirement executable
make
make clean

# 3. Run retirement executable
# Second command line arg set to 1 to allow user input for age and income
# expense_factor, inflation, market_growth, raise, safe_withdrawal_rate, age, income
if [ $2 == 1 ]
then
  ./retirement 1.0 0.025 0.09 0.03 0.04
else
  ./retirement 1.0 0.025 0.09 0.03 0.04 28 50000.00
  ./retirement 1.0 0.03 0.09 0.03 0.04 28 50000.00

fi
