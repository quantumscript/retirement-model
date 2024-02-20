/*******************************************************************************
* Specification file for Savings class
*******************************************************************************/
#ifndef Savings_h
#define Savings_h

class Savings {

private:
  float annual_savings;
  float current_savings;
  float goal_savings;

public:
  Savings(float annual_savings = 0.0, float current_savings = 0.0, float goal_savings = 0.0) {
    this->annual_savings = annual_savings;
    this->current_savings = current_savings;
    this->goal_savings = goal_savings;
  }

  void setAnnualSavings(float annual_savings)
    { this->annual_savings = annual_savings; }

  float getAnnualSavings()
    { return annual_savings; }

  void setCurrentSavings(float current_savings)
    { this->current_savings = current_savings; }

  float getCurrentSavings()
    { return current_savings; }

  void setGoalSavings(float goal_savings)
    { this->goal_savings = goal_savings; }

  float getGoalSavings()
    { return goal_savings; }

};
#endif
