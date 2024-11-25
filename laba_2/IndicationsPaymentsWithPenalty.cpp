#include "IndicationsPaymentsWithPenalty.h"

IndicationsPaymentsWithPenalty::IndicationsPaymentsWithPenalty(const double& rate) : IndicationsPaymentsAtYear(rate)
{
	penalties = new double[MONTH];
	for (int i = 0; i < MONTH; i++)
	{
		penalties[i] = NOT_DEFINDE;
	}
}

IndicationsPaymentsWithPenalty::~IndicationsPaymentsWithPenalty() {

	delete[] penalties;
}

void IndicationsPaymentsWithPenalty::inputPenality(const unsigned int& monthNumber, const double& penalty)
{
	if (monthNumber < 1 || monthNumber >= MONTH)
	{
		throw std::out_of_range("������������ ����� ������");
	}
	if (penalty < 0)
	{
		throw std::invalid_argument("���� �� ����� ���� �������������");
	}

	penalties[monthNumber - 1] = penalty;


	double currentPayment = (*this)[monthNumber];
	double newPayment = currentPayment + penalty;

	accruedPaymentsAtYear[monthNumber - 1] = newPayment;
}

void IndicationsPaymentsWithPenalty::outputData() const {
	IndicationsPaymentsAtYear::outputData();

	for (int i = 0; i < MONTH; i++) {
		if (penalties[i] > 0) {
			cout << "����� " << (i + 1) << ": ���� = " << penalties[i] << "\n";
		}
	}
}
