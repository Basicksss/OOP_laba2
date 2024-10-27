#include "IndicationsPaymentsAtYear.h"

IndicationsPaymentsAtYear::IndicationsPaymentsAtYear():rate(5.36)
{
	monthlyReadings = new int[MONTH];
	accruedPaymentsAtYear = new double[MONTH];

	for (int i = 0; i < 12; i++)
	{
		monthlyReadings[i] = NOT_DEFINDE;
		accruedPaymentsAtYear[i] = NOT_DEFINDE;
	}
}

IndicationsPaymentsAtYear::~IndicationsPaymentsAtYear()
{
	delete[] monthlyReadings;
	delete[] accruedPaymentsAtYear;
}

double IndicationsPaymentsAtYear::GetTarif() const
{
	return rate;
}

inline int IndicationsPaymentsAtYear::getYear() const
{
	return accountingYear;
}

void IndicationsPaymentsAtYear::inputData(const double& rate, const unsigned int& monthNumber, const unsigned int& accountingYear, const unsigned int& readingAtMonth)
{
	totalAmount = 0;
	if (accountingYear > 2024 || accountingYear < 1980)
	{
		throw exception((string("Введен неверный год")
			+ "! Пришло: "
			+ to_string(accountingYear)).c_str());
	}
	else
	{
		this->accountingYear = accountingYear;
	}

	if (readingAtMonth > 10000 || readingAtMonth < 0)
	{
		throw exception((string("Введен неверный показатель счетчика")
			+ "! Пришло: "
			+ to_string(readingAtMonth)).c_str());
	}

	if (monthNumber > 13 || monthNumber < 1)
	{
		throw exception((string("Введен неверный номер месяца")
			+ "! Пришло: "
			+ to_string(monthNumber)).c_str());
	}

	if (accruedPaymentsAtYear[monthNumber - 1] > 10000 || accruedPaymentsAtYear[monthNumber - 1] < -1)
	{
		throw exception((string("Неверный счет за электроэнергию")
			+ "! Пришло: "
			+ to_string(accruedPaymentsAtYear[monthNumber - 1])).c_str());
	}
	
	if (rate < 0 || rate >  10)
	{
		throw exception((string("Введен некоректный тариф")
			+ "! Пришло: "
			+ to_string(rate)).c_str());
	}
	else
	{
		this->rate = rate;

	}

	monthlyReadings[monthNumber - 1] = readingAtMonth;
	accruedPaymentsAtYear[monthNumber - 1] = readingAtMonth * rate;
}

double IndicationsPaymentsAtYear::getAverage()
{
	int count = 0;
	for (int i = 0; i < MONTH; i++)
	{
		if (monthlyReadings[i] > 0)
		{
			averageConsumptionPerMonth += monthlyReadings[i];
			count++;
		}
	}

	if (count == 0) throw exception((string("Отсутствуют показания по месяцам.")
		+ " Заполненно месяцев: "
		+ to_string(count)).c_str());
	return averageConsumptionPerMonth / count;
}


void IndicationsPaymentsAtYear::outputData()
{
	cout << "Год учета: " << accountingYear;
	cout << "\nТариф: " << rate;
	for (int i = 0; i < MONTH; i++)
	{
		if (monthlyReadings[i] != -1 && accruedPaymentsAtYear[i] != -1)
		{
			cout << "\nМесяц:" << i + 1;
			cout << "\nПоказания:" << monthlyReadings[i];
			cout << "\nПлатеж:" << accruedPaymentsAtYear[i] << " руб.";
			totalAmount += accruedPaymentsAtYear[i];
			monthlyReadings[i] = 0;
			accruedPaymentsAtYear[i] = 0;
		}
	}
	cout << "\nИтоговая сумма:" << totalAmount << " руб.";
	try
	{
		cout << "Среднее потребление:" << getAverage() << " кВтч.\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}

}

