#include "IndicationsPaymentsAtYear.h"

IndicationsPaymentsAtYear::IndicationsPaymentsAtYear(const double& rate) // TODO exception sdelano
{
	if (rate <= 0)
	{
		throw exception(("Тариф не может быть меньше 1"));
	}
	monthlyReadings = new int[MONTH];
	accruedPaymentsAtYear = new double[MONTH];

	for (int i = 0; i < MONTH; i++)
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

double IndicationsPaymentsAtYear::getTarif() const
{
	return rate;
}

 int IndicationsPaymentsAtYear::getYear() const
{
	return accountingYear;
}

 double IndicationsPaymentsAtYear::getTotalAmount() const
{
	return totalAmount;
}

double IndicationsPaymentsAtYear::getAverage() const
{
	return averageConsumptionPerMonth;
}

void IndicationsPaymentsAtYear::inputData(const unsigned int& monthNumber, const unsigned int& accountingYear, const unsigned int& readingAtMonth)
{
	tm currentDate = getCurrentDayTime();
	if (accountingYear > currentDate.tm_year || accountingYear < 1980)
	{
		throw exception((string("Введен неверный год")
			+ "! Пришло: "
			+ to_string(accountingYear)).c_str());
	}

	if (readingAtMonth > MAX_READINGS || readingAtMonth < 0)
	{
		throw exception((string("Введен неверный показатель счетчика")
			+ "! Пришло: "
			+ to_string(readingAtMonth)).c_str());
	}

	if (monthNumber >= MONTH || monthNumber < 1)
	{
		throw exception((string("Введен неверный номер месяца")
			+ "! Пришло: "
			+ to_string(monthNumber)).c_str());
	}

	if (accruedPaymentsAtYear[monthNumber - 1] > MAX_READINGS || accruedPaymentsAtYear[monthNumber - 1] < -1)
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
	
	this->rate = rate;
	this->accountingYear = accountingYear;
	
	
	monthlyReadings[monthNumber - 1] = readingAtMonth;
	accruedPaymentsAtYear[monthNumber - 1] = readingAtMonth * rate;
	
	
	int count = 0;
	totalAmount = 0;
	averageConsumptionPerMonth = 0;
	for (int i = 0; i < MONTH; i++)
	{
		if (monthlyReadings[i] == NOT_DEFINDE)
		{
			averageConsumptionPerMonth += monthlyReadings[i];
			count++;
		}
	}
	if (count != 0)
	{
		averageConsumptionPerMonth /= count;
	}
	for (int i = 0; i < MONTH; i++)
	{
		totalAmount += accruedPaymentsAtYear[i];
	}
	

}


void IndicationsPaymentsAtYear::outputData() const
{
	cout << "Год учета: " << accountingYear;
	cout << "\nТариф: " << rate;
	for (int i = 0; i < MONTH; i++)
	{
		if (monthlyReadings[i] != NOT_DEFINDE && accruedPaymentsAtYear[i] != NOT_DEFINDE)
		{
			cout << "\nМесяц:" << i + 1;
			cout << "\nПоказания:" << monthlyReadings[i];
			cout << "\nПлатеж:" << accruedPaymentsAtYear[i] << " руб.";

		}
	}
	cout << "\nИтоговая сумма:" << totalAmount << " руб.";
	cout << "Среднее потребление:" << (averageConsumptionPerMonth) << " кВтч.\n";
}

void IndicationsPaymentsAtYear::outputData(const unsigned int& monthNumber)
{
	if (monthNumber <= NOT_DEFINDE)
	{
		throw exception("Месяц не может быть отрицательным числом!Блинб, ну ты ваще");
	}
	else if (monthNumber == 0)
	{
		cout << "Год учета: " << accountingYear;
		cout << "\nТариф: " << rate;
		for (int i = 0; i < MONTH; i++)
		{
			if (monthlyReadings[i] != NOT_DEFINDE && accruedPaymentsAtYear[i] != NOT_DEFINDE)
			{
				cout << "\nМесяц:" << i + 1;
				cout << "\nПоказания:" << monthlyReadings[i];
				cout << "\nПлатеж:" << accruedPaymentsAtYear[i] << " руб.";

			}
		}
		cout << "\nИтоговая сумма:" << totalAmount << " руб.";
		cout << "Среднее потребление:" << (averageConsumptionPerMonth) << " кВтч.\n";
	}
	else if(monthNumber > 12)
	{
		throw exception("Ты где новые месяца нашел блинб ну ты ваще угарный чел!");
	}
	else
	{
		cout << "Год учета: " << accountingYear;
		cout << "\nТариф: " << rate;

		if (monthlyReadings[monthNumber - 1] != NOT_DEFINDE && accruedPaymentsAtYear[monthNumber - 1] != NOT_DEFINDE)
		{
			cout << "\nМесяц:" << monthNumber;
			cout << "\nПоказания:" << monthlyReadings[monthNumber - 1];
			cout << "\nПлатеж:" << accruedPaymentsAtYear[monthNumber - 1] << " руб.";
		}
		else
		{
			throw exception("Нет данных!");
		}
		cout << "\nИтоговая сумма:" << totalAmount << " руб.";
		cout << "Среднее потребление:" << (averageConsumptionPerMonth) << " кВтч.\n";
	}
}

// получение текущей даты-времени

 tm IndicationsPaymentsAtYear::getCurrentDayTime() {
	// хотим текущую дату время получить
	tm currentDayTime;
	// через chrono получаем текущее время-дату
	std::chrono::system_clock::time_point nowDateTime = std::chrono
		::system_clock::now();
	time_t intermediateDayTime = std::chrono
		::system_clock::to_time_t(nowDateTime);
	// рассчитываем время по текущему часовому поясу
	localtime_s(&currentDayTime, &intermediateDayTime);
	return currentDayTime;
}

