/*******************************************************************************
* Specification file for Tax class
*******************************************************************************/
#ifndef TaxProg_h
#define TaxProg_h
#include <string>
#include "Tax.h"

class TaxProg : public Tax {

private:
  const float* rates;
  float* brackets;
  int size;
  float deduction;

public:

  TaxProg(std::string name = "", const float* rates = NULL, float* brackets = NULL, int size = 0, float deduction = 0.0) :
  Tax(name) {
    this->rates = rates;
    this->brackets = brackets;
    this->size = size;
    this->deduction = deduction;
  }

  // Setters and getters
  void setRates(const float* rates)
    { this->rates = rates; }

  const float* getRates()
    { return rates; }

  void setBrackets(float* brackets)
    { this->brackets = brackets; }

  float* getBrackets()
    { return brackets; }

  void setSize(int size)
    { this->size = size; }

  int getSize()
    { return size; }

  void setDeduction(float deduction)
    { this->deduction = deduction; }

  float getDeduction()
    { return deduction; }

  // Computational functions
  float calcTotal(float income, float inflation);

  void inflateBrackets(float inflation);
};
#endif
