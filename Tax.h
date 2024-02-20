/*******************************************************************************
* Specification file for Tax class
*******************************************************************************/
#ifndef Tax_h
#define Tax_h
#include <string>

class Tax {

private:
  std::string name;
  float rate;

public:
  
  Tax(std::string name = "", float rate = 0.0) {
    this->name = name;
    this->rate = rate;
  }

  void setName(std::string name)
    { this->name = name; }

  void setRate(float rate)
    { this->rate = rate; }

  std::string getName()
    { return name; }

  float getRate()
    { return rate; }

  float calcTotal(float income)
    { return income * rate; }

};

#endif
