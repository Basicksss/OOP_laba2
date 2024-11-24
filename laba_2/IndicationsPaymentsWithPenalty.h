#pragma once
#include "IndicationsPaymentsAtYear.h"
class IndicationsPaymentsWithPenalty :
    public IndicationsPaymentsAtYear
{
public:

	IndicationsPaymentsWithPenalty(const double& rate);

	~IndicationsPaymentsWithPenalty();

	void inputPenality(const unsigned int& monthNumber, const double& penalty);

	void displayInfo() const;


private:
	double* penalties;
};