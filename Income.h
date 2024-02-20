/*************************************
* Specification file for Income
*************************************/
#ifndef Income_h
#define Income_h

class Income {

private:
  float gross;
  float after_tax;

public:
  Income(float gross = 0.0, float after_tax = 0.0) {
    this->gross = gross;
    this->after_tax = after_tax;
  }

  void setGross(float gross)
    { this->gross = gross; }

  float getGross()
    { return gross; }

  void setAfterTax(float after_tax)
    { this->after_tax = after_tax; }

  float getAfterTax()
    { return after_tax; }
};

#endif
