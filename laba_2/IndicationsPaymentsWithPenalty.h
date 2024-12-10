#pragma once
#include "IndicationsPaymentsAtYear.h"

template <typename T>
class IndicationsPaymentsWithPenalty :
    public IndicationsPaymentsAtYear<T>
{
public:

	IndicationsPaymentsWithPenalty(const double& rate);

	~IndicationsPaymentsWithPenalty();


	void inputPenality(const unsigned int& monthNumber, const double& penalty);

	void outputData() const;


private:
	double* penalties;
};