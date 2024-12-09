#include <iostream>
#include "IndicationsPaymentsAt.h"
#include "IndicationsPaymentsAtYear.h"
#include "IndicationsPaymentsWithPenalty.h"


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
    double penalties = 0;

    bool retry = true;
    bool choice = true;

    const int NUM_YEARS = 2;
    IndicationsPaymentsAt* payments[NUM_YEARS];
    payments[0] = new IndicationsPaymentsWithPenalty(2.22);
    payments[1] = new IndicationsPaymentsWithPenalty(5.22);
    //IndicationsPaymentsWithPenalty payments(12);
    //IndicationsPaymentsAtYear payments2(5);
    
    
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
        payments[0]->inputData(monthNumber, year, readingAtMonth);

        cout << "Если хотите добавить пени, введите 1, если нет, то 2";
        int penaltiesChoose;
        cin >> penaltiesChoose;
        if (penaltiesChoose == 1)
        {
            cout << "Введите пени: ";
            cin >> penalties;
            payments[0]->inputPenality(monthNumber, penalties);
        }

        char yesNo;
        cout << "Хотите добавить еще один месяц? Y (yes), N (No) : ";
        cin >> yesNo;

        if (yesNo != 'Y' && yesNo != 'y')
        {
            choice = false;
        }

    }

    cout << "Если хотите посмотреть информацию за определенный месяц, введите P.\n";
    cout << "Если хотите посмотреть информацию за весь год, введите A\n";
    cout << "Если хотите посмотреть только сводную информацию за весь год, введите S\n";

    cin >> symbolMonth;
    if (symbolMonth == 'A' || symbolMonth == 'a')
    {
        payments[0]->outputData();
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
    if (yesNo2 == 'Y' || yesNo2 == 'y')
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
            payments[1]->inputData(monthNumber, year, readingAtMonth);

            char yesNo;
            cout << "Хотите добавить еще один месяц? Y (yes), N (No) : ";
            cin >> yesNo;

            if (yesNo != 'Y' && yesNo != 'y')
            {
                choice = false;
            }

        }

        cout << "Если хотите посмотреть информацию за определенный месяц, введите P.\n";
        cout << "Если хотите посмотреть информацию за весь год, введите A\n";
        cout << "Если хотите посмотреть только сводную информацию за весь год, введите S\n";
        cout << "Если хотите посмотреть сумму средних значений за все года, введите Z\n";
        cin >> symbolMonth;
        if (symbolMonth == 'A' || symbolMonth == 'a')
        {
            payments[1]->outputData();
        }
        else if (symbolMonth == 'P' || symbolMonth == 'p')
        {
            cout << "Введите номер месяца";
            cin >> monthInt;
            if (monthInt >= 1 && monthInt <= 12)
            {
                payments[1][monthInt];

            }
        }
        else if (symbolMonth == 'S' || symbolMonth == 's')
        {
            cout << payments[1];
        }
        char symbolAverage;
        cin >> symbolAverage;
        if (symbolAverage == 'Z' || symbolAverage == 'z')
        {
            totalAverage += *payments[0];
            totalAverage += *payments[1];

            cout << "Общая сумма средних показаний: " << totalAverage;
        }
    }
    return 0;
}
