/*******************************************************************************
* Implementation file for Tax class
*******************************************************************************/
#include <iostream>
#include "TaxProg.h"

void TaxProg::inflateBrackets(float inflation) {
  // std::cout << std::endl;
  for (int i = 0; i < size; i++) {
    brackets[i] *= (1 + inflation);
    // std::cout << brackets[i] << " ";
  }
}

float TaxProg::calcTotal(float income, float inflation) {
  float agi, total = 0;
  int i = 0;
  agi = (income > deduction) ? (agi = income - deduction) : agi = 0;
  // std::cout << "agi: " << agi << std::endl;

  inflateBrackets(inflation);
  // std::cout << deduction << std::endl;
  deduction *= (1 + inflation);
  // std::cout << deduction << std::endl;

  do {
    // Agi less than next bracket
    // std::cout << "i: " << i << " ";
    if ( agi < brackets[i + 1] ) {
      total += (agi - brackets[i]) * rates[i];
      // std::cout << "less than next bracket, total: " << total << std::endl;
    }

    // Agi greater than next bracket, which is NOT the last bracket
    else if ( agi > brackets[i + 1] && i + 1 < size ) {
      total += (brackets[i + 1] - brackets[i]) * rates[i];
      // std::cout << "greater than next bracket, not last, total: " << total << std::endl;
    }

    // Agi greater than next bracket, which IS the last bracket
    else {
      total += (agi - brackets[i + 1]) * rates[i + 1];
      // std::cout << "greater than next bracket, is last, total: " << total << std::endl;
    }

    i++;
  } while ( agi > brackets[i] && i < size );
  // std::cout << std:: endl;

  return total;
}
