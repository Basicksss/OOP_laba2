#include "IndicationsPaymentsAtYear.h"

IndicationsPaymentsAtYear::IndicationsPaymentsAtYear(const double& rate)
{
	if (rate <= 0)
	{
		throw exception(("����� �� ����� ���� ������ 1"));
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
	if (accountingYear > currentDate.tm_year+1900 || accountingYear < 1980)
	{
		throw exception((string("������ �������� ���")
			+ "! ������: "
			+ to_string(accountingYear)).c_str());
	}

	if (readingAtMonth > MAX_READINGS || readingAtMonth < 0)
	{
		throw exception((string("������ �������� ���������� ��������")
			+ "! ������: "
			+ to_string(readingAtMonth)).c_str());
	}

	if (monthNumber >= MONTH || monthNumber < 1)
	{
		throw exception((string("������ �������� ����� ������")
			+ "! ������: "
			+ to_string(monthNumber)).c_str());
	}

	if (accruedPaymentsAtYear[monthNumber - 1] > MAX_READINGS || accruedPaymentsAtYear[monthNumber - 1] < -1)
	{
		throw exception((string("�������� ���� �� ��������������")
			+ "! ������: "
			+ to_string(accruedPaymentsAtYear[monthNumber - 1])).c_str());
	}
	
	if (rate < 0 || rate >  10)
	{
		throw exception((string("������ ����������� �����")
			+ "! ������: "
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
	cout << "��� �����: " << accountingYear;
	cout << "\n�����: " << rate;
	for (int i = 0; i < MONTH; i++)
	{
		if (monthlyReadings[i] != NOT_DEFINDE && accruedPaymentsAtYear[i] != NOT_DEFINDE)
		{
			cout << "\n�����:" << i + 1;
			cout << "\n���������:" << monthlyReadings[i];
			cout << "\n������:" << accruedPaymentsAtYear[i] << " ���.";

		}
	}
	cout << "\n�������� �����:" << totalAmount << " ���.";
	cout << "������� �����������:" << (averageConsumptionPerMonth) << " ����.\n";
}

void IndicationsPaymentsAtYear::outputData(const unsigned int& monthNumber ) const
{
	if (monthNumber <= NOT_DEFINDE)
	{
		throw exception("����� �� ����� ���� ������������� ������!�����, �� �� ����");
	}
	else if (monthNumber == 0)
	{
		cout << "��� �����: " << accountingYear;
		cout << "\n�����: " << rate;
		for (int i = 0; i < MONTH; i++)
		{
			if (monthlyReadings[i] != NOT_DEFINDE && accruedPaymentsAtYear[i] != NOT_DEFINDE)
			{
				cout << "\n�����:" << i + 1;
				cout << "\n���������:" << monthlyReadings[i];
				cout << "\n������:" << accruedPaymentsAtYear[i] << " ���.";

			}
		}
		cout << "\n�������� �����:" << totalAmount << " ���.";
		cout << "������� �����������:" << (averageConsumptionPerMonth) << " ����.\n";
	}
	else if (monthNumber > MONTH)
	{
		throw exception("�� ��� ����� ������ ����� ����� �� �� ���� ������� ���!");
	}
	else
	{
	cout << "��� �����: " << accountingYear;
	cout << "\n�����: " << rate;

	if (monthlyReadings[monthNumber - 1] != NOT_DEFINDE && accruedPaymentsAtYear[monthNumber - 1] != NOT_DEFINDE)
	{
	cout << "\n�����:" << monthNumber;
	cout << "\n���������:" << monthlyReadings[monthNumber - 1];
	cout << "\n������:" << accruedPaymentsAtYear[monthNumber - 1] << " ���.";
	}
	else
	{
	throw exception("��� ������!");
	}
	cout << "\n�������� �����:" << totalAmount << " ���.";
	cout << "������� �����������:" << (averageConsumptionPerMonth) << " ����.\n";
	}
}

// ��������� ������� ����-�������

 tm IndicationsPaymentsAtYear::getCurrentDayTime() {
	// ����� ������� ���� ����� ��������
	tm currentDayTime;
	// ����� chrono �������� ������� �����-����
	std::chrono::system_clock::time_point nowDateTime = std::chrono
		::system_clock::now();
	time_t intermediateDayTime = std::chrono
		::system_clock::to_time_t(nowDateTime);
	// ������������ ����� �� �������� �������� �����
	localtime_s(&currentDayTime, &intermediateDayTime);
	return currentDayTime;
}

 double IndicationsPaymentsAtYear::operator [] (const unsigned int& monthNumber) const {
	 if (accruedPaymentsAtYear[monthNumber - 1] != NOT_DEFINDE)
	 {
		 return accruedPaymentsAtYear[monthNumber - 1];
	 }
	 return 0;
 };

 ostream& operator<<(ostream& out, const IndicationsPaymentsAtYear& ourObject)
 {
	 double payments = 0;
	 out << "��� �����: " << ourObject.accountingYear;
	 out << "\n�����: " << ourObject.rate;
	 for (int i = 0; i < ourObject.MONTH; i++)
	 {
		 if (ourObject.monthlyReadings[i] != ourObject.NOT_DEFINDE && ourObject.accruedPaymentsAtYear[i] != ourObject.NOT_DEFINDE)
		 {
			 payments += ourObject.accruedPaymentsAtYear[i] ;
		 }
	 }
	 out << "\n�������� �����:" << ourObject.totalAmount << " ���.";
	 out << "������� �����������:" << (ourObject.averageConsumptionPerMonth) << " ����.\n";

	 return out;
 }

 double& operator += (double& sum, const IndicationsPaymentsAtYear& ourObject)
 {
	 sum += ourObject.getAverage();
	 return sum;
 }


