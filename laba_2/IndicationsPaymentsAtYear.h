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
	//�����������
	IndicationsPaymentsAtYear(const double& rate);

	//����������
	~IndicationsPaymentsAtYear();

	//��������
	double getTarif() const;
	int getYear() const;
	double getTotalAmount() const;
	double getAverage() const override ;

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
	void outputData() const override;

	void outputData(const unsigned int& monthNumber) const ;

	double operator [] (const unsigned int& monthNumber) const;

	friend ostream& operator << (ostream& out, const IndicationsPaymentsAtYear& ourObject);


protected:
	double* accruedPaymentsAtYear; 	       /// <summary> ������� �� �����(������) </summary>

	static const unsigned int MONTH = 12;
	static const int NOT_DEFINDE = -1;
	unsigned int monthNumber = 0;		   ///<summary> ����� ������ </summary>
private:
	int* monthlyReadings;			       /// <summary> ��������� �� ������ �����(������) </summary>


	unsigned int accountingYear = 0;	   ///<summary> ��� ����� </summary>
	double totalAmount = 0;				   ///<summary> �������� ����� ������� </summary> 
	double rate;					       ///<summary> ����� </summary>
	double averageConsumptionPerMonth = 0; ///<summary> ������� ����������� �� ����� </summary> 
	unsigned int readingAtMonth = 0;	   ///<summary> ��������� �� ����� </summary> 


	static const unsigned int MAX_READINGS = 10000;

	// ��������� ������� ����-�������
	tm getCurrentDayTime();
};

double& operator += (double& sum, const IndicationsPaymentsAtYear& ourObject);

