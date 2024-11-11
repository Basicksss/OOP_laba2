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
    char symbolMonth;
    int monthInt;
    double totalAverage = 0;

    bool retry = true;
    bool choice = true;

    IndicationsPaymentsAtYear payments(12);
    IndicationsPaymentsAtYear payments2(5);
    
    
    cout << "Здравствуйте, вас приветствует программа по планированию уплаты счетов по электроэнергии!\n";

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
        payments.inputData(monthNumber, year, readingAtMonth);

        char yesNo;
        cout << "Хотите добавить еще один месяц? Y (yes), N (No) : ";
        cin >> yesNo;

        if (yesNo != 'Y' && yesNo != 'y')
        {
            choice = false;
        }

    }

    cout << "Если хотите посмотреть информацию за определенный месяц, введите P.";
    cout << "Если хотите посмотреть информацию за весь год, введите A";
    cout << "Если хотите посмотреть только сводную информацию за весь год, введите S";

    cin >> symbolMonth;
    if (symbolMonth == 'A' || symbolMonth == 'a')
    {
        payments.outputData();
    }
    else if (symbolMonth == 'P' || symbolMonth == 'p')
    {
        cout << "Введите номер месяца";
        cin >> monthInt;
        if (monthInt >= 1 && monthInt <= 12)
        {
            payments[monthInt];

        }
    }
    else if (symbolMonth == 'S' || symbolMonth == 's')
    {
        cout << payments;
    }
    char yesNo2;
    cout << "Хотите добавить еще один год? Y (yes), N (No) : ";
    cin >> yesNo2;
    if (yesNo2 == 'Y' && yesNo2 == 'y')
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
            payments2.inputData(monthNumber, year, readingAtMonth);

            char yesNo;
            cout << "Хотите добавить еще один месяц? Y (yes), N (No) : ";
            cin >> yesNo;

            if (yesNo != 'Y' && yesNo != 'y')
            {
                choice = false;
            }

        }

        cout << "Если хотите посмотреть информацию за определенный месяц, введите P.";
        cout << "Если хотите посмотреть информацию за весь год, введите A";
        cout << "Если хотите посмотреть только сводную информацию за весь год, введите S";

        cin >> symbolMonth;
        if (symbolMonth == 'A' || symbolMonth == 'a')
        {
            payments2.outputData();
        }
        else if (symbolMonth == 'P' || symbolMonth == 'p')
        {
            cout << "Введите номер месяца";
            cin >> monthInt;
            if (monthInt >= 1 && monthInt <= 12)
            {
                payments2[monthInt];

            }
        }
        else if (symbolMonth == 'S' || symbolMonth == 's')
        {
            cout << payments2;
        }

        /*cout << "Если хотите посмотреть сумму средних значений за все года, введите Z";
        char symbolAverage;
        cin >> symbolAverage;
        if (symbolAverage == 'Z' || symbolAverage == 'z')
        {
            totalAverage += payments;
            totalAverage += payments2;

            cout << "Общая сумма средних показаний: " << totalAverage;
        }*/
    }
    return 0;
}
