#pragma once

#include <iostream>
#include <string>


using namespace std;

class IndicationsPaymentsAtYear
{
public:
	//Конструктор
	IndicationsPaymentsAtYear();

	//Деструктор
	~IndicationsPaymentsAtYear();

	//Селектор
	double GetTarif() const;
	int getYear() const;


	/// <summary>
	/// Ввод данных
	/// </summary>
	/// <param name="rate"></param>
	/// <param name="monthNumber"></param>
	/// <param name="accountingYear"></param>
	void inputData(const double& rate, const unsigned int& monthNumber, const unsigned int& accountingYear, const unsigned int& readingAtMonth);

	/// <summary>
	/// Получение среднего показателя
	/// </summary>
	/// <returns></returns>
	double getAverage();


	/// <summary>
	/// Вывод данных
	/// </summary>
	void outputData();

private:
	int* monthlyReadings;			/// <summary> Показания за каждый месяц(массив) </summary>
	double* accruedPaymentsAtYear; 	/// <summary> Платежи за месяц(массив) </summary>


	unsigned int accountingYear;	   ///<summary> Год учета </summary>
	double totalAmount;				   ///<summary> Итоговая сумма платежа </summary> 
	double rate;					   ///<summary> Тариф </summary>
	double averageConsumptionPerMonth; ///<summary> Среднее потребление за месяц </summary> 
	unsigned int monthNumber;		   ///<summary> Номер месяца </summary>
	unsigned int readingAtMonth;	   ///<summary> Показание за месяц </summary> 


	static const unsigned int MONTH = 12;
	static const int NOT_DEFINDE = 0;

};

