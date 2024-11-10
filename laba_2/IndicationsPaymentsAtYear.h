#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <chrono>



using namespace std;

class IndicationsPaymentsAtYear
{
public:
	//Конструктор
	IndicationsPaymentsAtYear(const double& rate);

	//Деструктор
	~IndicationsPaymentsAtYear();

	//Селектор
	double getTarif() const;
	int getYear() const;
	double getTotalAmount() const;
	double getAverage() const;

	/// <summary>
	/// Ввод данных
	/// </summary>
	/// <param name="rate"></param>
	/// <param name="monthNumber"></param>
	/// <param name="accountingYear"></param>
	void inputData(const unsigned int& monthNumber, const unsigned int& accountingYear, const unsigned int& readingAtMonth);

	/// <summary>
	/// Вывод данных
	/// </summary>
	void outputData() const;

	void outputData(const unsigned int& monthNumber) const;

	double operator [] (const unsigned int& monthNumber) const {
		if (accruedPaymentsAtYear[monthNumber - 1] != NOT_DEFINDE)
		{
			return accruedPaymentsAtYear[monthNumber - 1];
		}
	};

	friend ostream& operator << (ostream& out, IndicationsPaymentsAtYear& ourObject)
	{
		int payments = 0;
		out << "Год учета: " << ourObject.accountingYear;
		out << "\nТариф: " << ourObject.rate;
		for (int i = 0; i < MONTH; i++)
		{
			if (ourObject.monthlyReadings[i] != NOT_DEFINDE && ourObject.accruedPaymentsAtYear[i] != NOT_DEFINDE)
			{
				payments =+ ourObject.accruedPaymentsAtYear[i];
			}
		}
		out << "\nИтоговая сумма:" << ourObject.totalAmount << " руб.";
		out << "Среднее потребление:" << (ourObject.averageConsumptionPerMonth) << " кВтч.\n";

		return out;
	}

private:
	int* monthlyReadings;			/// <summary> Показания за каждый месяц(массив) </summary>
	double* accruedPaymentsAtYear; 	/// <summary> Платежи за месяц(массив) </summary>


	unsigned int accountingYear = 0;	   ///<summary> Год учета </summary>
	double totalAmount = 0;				   ///<summary> Итоговая сумма платежа </summary> 
	double rate;					   ///<summary> Тариф </summary>
	double averageConsumptionPerMonth = 0; ///<summary> Среднее потребление за месяц </summary> 
	unsigned int monthNumber = 0;		   ///<summary> Номер месяца </summary>
	unsigned int readingAtMonth = 0;	   ///<summary> Показание за месяц </summary> 


	static const unsigned int MONTH = 12;
	static const int NOT_DEFINDE = -1;
	static const unsigned int MAX_READINGS = 10000;

	// получение текущей даты-времени
	tm getCurrentDayTime();
};

double& operator += (double& sum, IndicationsPaymentsAtYear& ourObject)
{
	sum += ourObject.getAverage();
	return sum;
}

