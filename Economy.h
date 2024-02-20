/************************************************************
*  Specification file for Economy class
************************************************************/
#ifndef Economy_h
#define Economy_h

class Economy {

private:
  float inflation;
  float market_growth;
  float raise;

public:
  Economy(float market_growth = 0.0, float inflation = 0.0, float raise = 0.0) {
    this->market_growth = market_growth;
    this->inflation = inflation;
    this->raise = raise;
  }

  void setInflation(float inflation)
    { this->inflation = inflation; }

  float getInflation()
    { return inflation; }

  void setMarketGrowth(float growth)
    { this->market_growth = growth; }

  float getMarketGrowth()
    { return market_growth; }

  void setRaise(float raise)
    { this->raise = raise; }

  float getRaise()
    { return raise; }
};

#endif
