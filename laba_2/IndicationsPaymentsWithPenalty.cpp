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
		throw std::out_of_range("Ќедопустимый номер мес€ца");
	}
	if (penalty < 0)
	{
		throw std::invalid_argument("ѕен€ не может быть отрицательной");
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
			cout << "ћес€ц " << (i + 1) << ": ѕен€ = " << penalties[i] << "\n";
		}
	}
}
