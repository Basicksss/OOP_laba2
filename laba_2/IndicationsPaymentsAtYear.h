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
	//�����������
	IndicationsPaymentsAtYear(const double& rate);

	//����������
	~IndicationsPaymentsAtYear();

	//��������
	double getTarif() const;
	int getYear() const;
	double getTotalAmount() const;
	double getAverage() const;

	/// <summary>
	/// ���� ������
	/// </summary>
	/// <param name="rate"></param>
	/// <param name="monthNumber"></param>
	/// <param name="accountingYear"></param>
	void inputData(const unsigned int& monthNumber, const unsigned int& accountingYear, const unsigned int& readingAtMonth);

	/// <summary>
	/// ����� ������
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
		out << "��� �����: " << ourObject.accountingYear;
		out << "\n�����: " << ourObject.rate;
		for (int i = 0; i < MONTH; i++)
		{
			if (ourObject.monthlyReadings[i] != NOT_DEFINDE && ourObject.accruedPaymentsAtYear[i] != NOT_DEFINDE)
			{
				payments =+ ourObject.accruedPaymentsAtYear[i];
			}
		}
		out << "\n�������� �����:" << ourObject.totalAmount << " ���.";
		out << "������� �����������:" << (ourObject.averageConsumptionPerMonth) << " ����.\n";

		return out;
	}

private:
	int* monthlyReadings;			/// <summary> ��������� �� ������ �����(������) </summary>
	double* accruedPaymentsAtYear; 	/// <summary> ������� �� �����(������) </summary>


	unsigned int accountingYear = 0;	   ///<summary> ��� ����� </summary>
	double totalAmount = 0;				   ///<summary> �������� ����� ������� </summary> 
	double rate;					   ///<summary> ����� </summary>
	double averageConsumptionPerMonth = 0; ///<summary> ������� ����������� �� ����� </summary> 
	unsigned int monthNumber = 0;		   ///<summary> ����� ������ </summary>
	unsigned int readingAtMonth = 0;	   ///<summary> ��������� �� ����� </summary> 


	static const unsigned int MONTH = 12;
	static const int NOT_DEFINDE = -1;
	static const unsigned int MAX_READINGS = 10000;

	// ��������� ������� ����-�������
	tm getCurrentDayTime();
};

double& operator += (double& sum, IndicationsPaymentsAtYear& ourObject)
{
	sum += ourObject.getAverage();
	return sum;
}

