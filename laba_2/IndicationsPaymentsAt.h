#pragma once
class IndicationsPaymentsAt
{
public:
	virtual void inputData(const unsigned int& monthNumber, const unsigned int& accountingYear, const unsigned int& readingAtMonth) = 0;
	virtual void outputData() const = 0;
	virtual double getAverage() const = 0;
	virtual void inputPenality(const unsigned int& monthNumber, const double& penalty) = 0; 

	virtual ~IndicationsPaymentsAt() {};
};
double& operator += (double& sum, const IndicationsPaymentsAt& ourObject);



