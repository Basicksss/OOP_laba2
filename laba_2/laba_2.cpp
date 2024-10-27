#include <iostream>
#include "IndicationsPaymentsAtYear.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    int year;
    double rate;
    int monthNumber;
    int readingAtMonth;

    bool retry = true;
    bool choice = true;

    IndicationsPaymentsAtYear payments;
    cout << "Здравствуйте, вас приветствует программа по планированию уплаты счетов по электроэнергии!\n";
    while (retry)
    {
        cout << "Введите год учета счета: ";
        cin >> year;
        cout << "Введите тариф: ";
        cin >> rate;
        choice = true;
        while (choice)
        {
            cout << "Введите номер месяца за который производится оплата: ";
            cin >> monthNumber;
            cout << "Введите показания счетчика: ";
            cin >> readingAtMonth;
            payments.inputData(rate,monthNumber,year,readingAtMonth);

            char yesNo;
            cout << "Хотите добавить еще один месяц? Y (yes), N (No) : ";
            cin >> yesNo;

            if (yesNo != 'Y' && yesNo != 'y')
            {
                choice = false;
            }

        }
        payments.outputData();
        char yesNo2;
        cout << "Хотите добавить еще один год? Y (yes), N (No) : ";
        cin >> yesNo2;
        if (yesNo2 != 'Y' && yesNo2 != 'y')
        {
            retry = false;
        }

    }

    return 0;
}
