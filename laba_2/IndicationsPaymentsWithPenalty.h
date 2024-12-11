#pragma once

#include <iostream>
#include "IndicationsPaymentsAtYear.h"

using namespace std;

template <typename T>
class IndicationsPaymentsWithPenalty :
	public IndicationsPaymentsAtYear<T>
{
public:

	IndicationsPaymentsWithPenalty(const double& rate, const unsigned int& startMonth) ;


	~IndicationsPaymentsWithPenalty();


	void inputPenality(const unsigned int& monthNumber, const T& penalty) override;

	void outputData() const;


private:
	double* penalties;

};
	//template <typename T>
	//IndicationsPaymentsWithPenalty<T>::IndicationsPaymentsWithPenalty(const double& rate) : IndicationsPaymentsAtYear<T>(rate)
	//{
	//	penalties = new double[IndicationsPaymentsAtYear<T>::MONTH];
	//	for (int i = 0; i < IndicationsPaymentsAtYear<T>::MONTH; i++)
	//	{
	//		penalties[i] = IndicationsPaymentsAtYear<T>::NOT_DEFINDE;
	//	}
	//}
template <typename T>
IndicationsPaymentsWithPenalty<T>::IndicationsPaymentsWithPenalty(const double& rate, const unsigned int& startMonth) : IndicationsPaymentsAtYear<T>(rate, startMonth)
{
	penalties = new double[IndicationsPaymentsAtYear<T>::MONTH];
	for (int i = 0; i < IndicationsPaymentsAtYear<T>::MONTH; i++)
	{
		penalties[i] = IndicationsPaymentsAtYear<T>::NOT_DEFINDE;
	}
}

	template <typename T>
	IndicationsPaymentsWithPenalty<T>::~IndicationsPaymentsWithPenalty() {

		delete[] penalties;
	}

	template <typename T>
	void IndicationsPaymentsWithPenalty<T>::inputPenality(const unsigned int& monthNumber, const T& penalty)
	{
		if (monthNumber < 1 || monthNumber >= IndicationsPaymentsAtYear<T>::MONTH)
		{
			throw std::out_of_range("Ќедопустимый номер мес€ца");
		}
		if (penalty < 0)
		{
			throw std::invalid_argument("ѕен€ не может быть отрицательной");
		}

		penalties[monthNumber - 1] = penalty;


		double currentPayment = (*this)[monthNumber];
		double newPayment = currentPayment + penalty;

		IndicationsPaymentsAtYear<T>::accruedPaymentsAtYear[monthNumber - 1] = newPayment;
	}

	template <typename T>
	void IndicationsPaymentsWithPenalty<T>::outputData() const {
		IndicationsPaymentsAtYear<T>::outputData();

		for (int i = 0; i < IndicationsPaymentsAtYear<T>::MONTH; i++) {
			if (penalties[i] > 0) {
				cout << "ћес€ц " << (i + 1) << ": ѕен€ = " << penalties[i] << "\n";
			}
		}
	}
