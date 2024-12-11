#pragma once
template<typename T>
class IndicationsPaymentsAt
{
public:
	virtual void inputData(const unsigned int& monthNumber, const unsigned int& accountingYear, const T& readingAtMonth) = 0;
	virtual void outputData() const = 0;
	virtual T getAverage() const = 0;
	virtual void inputPenality(const unsigned int& monthNumber, const T& penalty) = 0;

	virtual ~IndicationsPaymentsAt() {};
};
//double& operator += (double& sum, const IndicationsPaymentsAt<T>& ourObject);
template <typename T>
double& operator += (double& sum, const IndicationsPaymentsAt<T>& ourObject)
{
	sum += ourObject.getAverage();
	return sum;
}


