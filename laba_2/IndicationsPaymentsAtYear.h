#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "IndicationsPaymentsAt.h"




using namespace std;

class IndicationsPaymentsAtYear : public IndicationsPaymentsAt
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
	double getAverage() const override ;

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
	void outputData() const override;

	void outputData(const unsigned int& monthNumber) const ;

	double operator [] (const unsigned int& monthNumber) const;

	friend ostream& operator << (ostream& out, const IndicationsPaymentsAtYear& ourObject);


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
	double averageConsumptionPerMonth = 0; ///<summary> Среднее потребление за месяц </summary> 
	unsigned int readingAtMonth = 0;	   ///<summary> Показание за месяц </summary> 


	static const unsigned int MAX_READINGS = 10000;

	// получение текущей даты-времени
	tm getCurrentDayTime();
};

double& operator += (double& sum, const IndicationsPaymentsAtYear& ourObject);

