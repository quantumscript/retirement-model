# Retirement Savings Model

###### Using OOP to model complete retirement financials including total expenses, income, and savings given economic variables.

## UML Diagram
![Retirement UML Diagram](Resources/UML.png)

## Requirements
1a. Up to date expense recompiling from the current budget can only be done on OS X operating system with Numbers installed.
> If not on an Apple computer, a space delimited text file of monthly expenses called `expenses.txt` must be included.   
>
> Example contents of expenses.txt:  
> `300 55 25 150 1000 75 40 40`

1b. A Numbers file called "budget" with sheet "Raw Expenses".

## Usage
Command line operation in terminal from shell script that runs the makefile and executes the program.

#### Option 1: Default data
Skip recompiling expenses and skip user input of age and income.
1. Run `./run_retirement.sh 0 0`  

#### Option 2: Recompile expenses
Data output to text file from OSX Numbers budget document run by update_expenses.scpt. *Note: not available outside OS X.*
1. Run `./run_retirement.sh 1 0`

#### Option 3: User input age and income
User enters age and income on command line.
1. Run `./run_retirement.sh 0 1`

#### Option 4: Recompile expenses and get user input
Reprocess expense data and user input includes age and current income. *Note: not available outside OS X.*
1. Run `./run_retirement.sh 1 1`

## Output

A table with columns detailing income, expenses, goal savings and more as
adjusted by inflation, raise, and other model parameters. The final statement tells you how many years until retirement and how old you will be when you can retire. This model assumes you are subject to US and NYS taxes and maintain a consistent standard of living over time.

![Output](Resources/output.png)
