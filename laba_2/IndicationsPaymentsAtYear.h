#pragma once

#include <iostream>
#include <string>


using namespace std;

class IndicationsPaymentsAtYear
{
public:
	//�����������
	IndicationsPaymentsAtYear();

	//����������
	~IndicationsPaymentsAtYear();

	//��������
	double GetTarif() const;
	int getYear() const;


	/// <summary>
	/// ���� ������
	/// </summary>
	/// <param name="rate"></param>
	/// <param name="monthNumber"></param>
	/// <param name="accountingYear"></param>
	void inputData(const double& rate, const unsigned int& monthNumber, const unsigned int& accountingYear, const unsigned int& readingAtMonth);

	/// <summary>
	/// ��������� �������� ����������
	/// </summary>
	/// <returns></returns>
	double getAverage();


	/// <summary>
	/// ����� ������
	/// </summary>
	void outputData();

private:
	int* monthlyReadings;			/// <summary> ��������� �� ������ �����(������) </summary>
	double* accruedPaymentsAtYear; 	/// <summary> ������� �� �����(������) </summary>


	unsigned int accountingYear;	   ///<summary> ��� ����� </summary>
	double totalAmount;				   ///<summary> �������� ����� ������� </summary> 
	double rate;					   ///<summary> ����� </summary>
	double averageConsumptionPerMonth; ///<summary> ������� ����������� �� ����� </summary> 
	unsigned int monthNumber;		   ///<summary> ����� ������ </summary>
	unsigned int readingAtMonth;	   ///<summary> ��������� �� ����� </summary> 


	static const unsigned int MONTH = 12;
	static const int NOT_DEFINDE = 0;

};

