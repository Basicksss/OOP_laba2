#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "IndicationsPaymentsAt.h"

using namespace std;

template<typename T>
class IndicationsPaymentsAtYear : public IndicationsPaymentsAt<T>
{
public:
	//Конструктор
	IndicationsPaymentsAtYear(const double& rate, const unsigned int& startMonth);

	//Деструктор
	~IndicationsPaymentsAtYear();

	//Селектор
	T getTarif() const;
	T getYear() const;
	T getTotalAmount() const;
	T getAverage() const override;

	/// <summary>
	/// Ввод данных
	/// </summary>
	/// <param name="rate"></param>
	/// <param name="monthNumber"></param>
	/// <param name="accountingYear"></param>
	void inputData(const unsigned int& monthNumber, const unsigned int& accountingYear, const T& readingAtMonth);

	/// <summary>
	/// Вывод данных
	/// </summary>
	void outputData() const override;

	void outputData(const unsigned int& monthNumber) const;

	double operator [] (const unsigned int& monthNumber) const;

	friend ostream& operator << (ostream& out, const IndicationsPaymentsAtYear<T>& ourObject);


protected:
	double* accruedPaymentsAtYear; 	       /// <summary> Платежи за месяц(массив) </summary>

	static const unsigned int MONTH = 12;
	static const int NOT_DEFINDE = -1;
	unsigned int monthNumber = 0;		   ///<summary> Номер месяца </summary>
private:
	int* monthlyReadings;			       /// <summary> Показания за каждый месяц(массив) </summary>


	unsigned int accountingYear = 0;	   ///<summary> Год учета </summary>
	double totalAmount = 0;				   ///<summary> Итоговая сумма платежа </summary> 
	double rate;					       ///<summary> Тариф </summary>
	double averageConsumptionPerMonth = 0;	   ///<summary> Среднее потребление за месяц </summary> 
	T readingAtMonth = 0;				   ///<summary> Показание за месяц </summary> 

	unsigned int startMonth;

	static const unsigned int MAX_READINGS = 10000;

	// получение текущей даты-времени
	tm getCurrentDayTime();
};

template<typename T>
ostream& operator << (ostream& out, const IndicationsPaymentsAtYear<T>& ourObject)
{
	double payments = 0;
	out << "Год учета: " << ourObject.accountingYear;
	out << "\nТариф: " << ourObject.rate;
	for (int i = 0; i < ourObject.MONTH; i++)
	{
		if (ourObject.monthlyReadings[i] != ourObject.NOT_DEFINDE && ourObject.accruedPaymentsAtYear[i] != ourObject.NOT_DEFINDE)
		{
			payments += ourObject.accruedPaymentsAtYear[i];
		}
	}
	out << "\nИтоговая сумма:" << ourObject.totalAmount << " руб.";
	out << "Среднее потребление:" << (ourObject.averageConsumptionPerMonth) << " кВтч.\n";

	return out;
}

template<typename T>
IndicationsPaymentsAtYear<T>::IndicationsPaymentsAtYear(const double& rate, const unsigned int& startMonth)
{
	if (rate <= 0)
	{
		throw exception(("Тариф не может быть меньше 1"));
	}
	if (startMonth < 0 || startMonth >= MONTH)
	{
		throw exception(("Начальный месяц не может быть меньше 1 или больше 12"));
	}
	this->startMonth = startMonth;
	monthlyReadings = new int[MONTH];
	accruedPaymentsAtYear = new double[MONTH];

	for (int i = 0; i < MONTH; i++)
	{
		monthlyReadings[i] = NOT_DEFINDE;
		accruedPaymentsAtYear[i] = NOT_DEFINDE;
	}
}

template<typename T>
IndicationsPaymentsAtYear<T>::~IndicationsPaymentsAtYear()
{
	delete[] monthlyReadings;
	delete[] accruedPaymentsAtYear;
}

template<typename T>
T IndicationsPaymentsAtYear<T>::getTarif() const
{
	return rate;
}

template<typename T>
T IndicationsPaymentsAtYear<T>::getYear() const
{
	return accountingYear;
}

template<typename T>
T IndicationsPaymentsAtYear<T>::getTotalAmount() const
{
	return totalAmount;
}

template<typename T>
T IndicationsPaymentsAtYear<T>::getAverage() const
{
	return averageConsumptionPerMonth;
}

template<typename T>
void IndicationsPaymentsAtYear<T>::inputData(const unsigned int& monthNumber, const unsigned int& accountingYear, const T& readingAtMonth)
{
	tm currentDate = getCurrentDayTime();
	if (accountingYear > currentDate.tm_year + 1900 || accountingYear < 1980)
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

	int adjustedMonth = (monthNumber - startMonth + 12) % 12; //Коррекция индекса месяца с учетом начального
	monthlyReadings[adjustedMonth] = readingAtMonth;
	accruedPaymentsAtYear[adjustedMonth] = readingAtMonth * rate;


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

template<typename T>
void IndicationsPaymentsAtYear<T>::outputData() const
{
	cout << "Год учета: " << accountingYear;
	cout << "\nТариф: " << rate;
	cout << "\nНачальный месяц:" << startMonth;
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


template<typename T>
void IndicationsPaymentsAtYear<T>::outputData(const unsigned int& monthNumber) const
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
	else if (monthNumber > MONTH)
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

template<typename T>
tm IndicationsPaymentsAtYear<T>::getCurrentDayTime() {
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

template<typename T>
double IndicationsPaymentsAtYear<T>::operator [] (const unsigned int& monthNumber) const {
	if (accruedPaymentsAtYear[monthNumber - 1] != NOT_DEFINDE)
	{
		return accruedPaymentsAtYear[monthNumber - 1];
	}
	return 0;
};



//template<typename T>
//void IndicationsPaymentsAtYear<T>::setStartMonth(int startMonth) {
//	this->startMonth = startMonth;
//}


template<typename T>
double& operator += (double& sum, const IndicationsPaymentsAtYear<T>& ourObject)
{
	sum += ourObject.getAverage();
	return sum;
}
