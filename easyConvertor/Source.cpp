#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

char digit(int num)
{
	switch (num) {
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	case 10: return 'A';
	case 11: return 'B';
	case 12: return 'C';
	case 13: return 'D';
	case 14: return 'E';
	case 15: return 'F';
	}
}

int character(char chr)
{
	switch (chr) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	}
}

long double convert_any_to_dec(char *s, int systemOfCount)
{
	long double num = 0;
	int j = 0, i = 0, stepin = 0;
	while (s[i] != '.') i++;
	for (j = i - 1; j >= 0; j--)
	{
		num = num + character(s[j])*pow(systemOfCount, stepin);
		stepin++;
	}
	stepin = -1;
	j = i + 1;
	while (s[j] != '\0')
	{
		num = num + character(s[j])*pow(systemOfCount, stepin);
		stepin--;
		j++;
	}
	return num;
}

int convert_int(int variiable, int SystemOfCounting, char *s)
{
	int num = (int)variiable;
	int rest = num % SystemOfCounting;
	num /= SystemOfCounting;
	if (num == 0)
	{
		s[0] = digit(rest); return 1;
	}
	int k = convert_int(num, SystemOfCounting, s);
	s[k++] = digit(rest);
	return k;
}

void convert_double(long double variable, int SystemOfCounting, char *s)
{
	int iter = 0;
	int k = 0;
	long double a1 = variable;
	do {
		a1 = a1 * SystemOfCounting;
		int num = (int)(a1);
		s[k++] = digit(num);
		a1 -= (int)a1;
		iter++;
	} while (a1 > 0.00000001 && iter < 10);
	s[k] = '\0';
}
int main()
{
	long double var;
	bool minus = false;
	char s[80] = { 0 };
	char vhidnevar[80] = { 0 };
	int SysOfCount, SystemOfCountBase;
	system("chcp 1251");
	int yn = 1;
	while (yn != 0)
	{
		system("cls");
		cout << "1 - Конвертор систем числення\n2 - Прямий, обернений, та додатковий код числа\n";
		cin >> yn;
		if (yn == 1)
		{
			system("cls");
			cout << "Введіть основу систми числення вашого числа: ";
			cin >> SystemOfCountBase;
			if (SystemOfCountBase < 2 || SystemOfCountBase >16)
			{
				cout << "\nДана система числення не підтримується! Використайте іншу! (від 2 до 16)\n";
				system("pause");
				continue;
			}
			cout << "Введіть число(дроби через крапку): ";
			if (SystemOfCountBase == 10)
			{
				cin >> var;
				if (var < 0)
				{
					minus = true;
					var = var * (-1);
				}
			}
			else if (SystemOfCountBase >= 2 && SystemOfCountBase != 10 && SystemOfCountBase <= 16)
			{
				cin >> vhidnevar;
				yn = 1;
				if (vhidnevar[0] == '-')
				{
					minus = true;
					while (vhidnevar[yn - 1] != '\0')
					{
						vhidnevar[yn - 1] = vhidnevar[yn];
						yn++;
					}
				}
				yn = 1;
				bool isdot = false;
				while (vhidnevar[yn - 1] != '\0')
				{
					if (vhidnevar[yn - 1] == '.')
					{
						isdot = true;
						break;
					}
					yn++;
				}
				if (isdot != true)
				{
					vhidnevar[yn - 1] = '.';
					vhidnevar[yn] = '0';
					vhidnevar[yn + 1] = '\0';
				}
				var = convert_any_to_dec(vhidnevar, SystemOfCountBase);
			}
			else
			{
				cout << "\nДана система числення не підтримується! Використайте іншу! (від 2 до 16)\n";
				system("pause");
				continue;
			}
			cout << "Введіть вихідну основу системи числення: ";
			cin >> SysOfCount;
			if (SysOfCount < 2 || SysOfCount >16)
			{
				cout << "\nДана система числення не підтримується! Використайте іншу! (від 2 до 16)\n";
				system("pause");
				continue;
			}
			if (SysOfCount == SystemOfCountBase)
			{
				cout << "\nПомилка перетворення! Однакові системи числення!\n";
				system("pause");
				continue;
			}
			int k = convert_int((int)var, SysOfCount, s);
			s[k++] = '.';
			convert_double(var - (int)var, SysOfCount, &s[k]);
			if (minus == true)
			{
				cout << "\nРезультат: -" << s;
			}
			else
			{
				cout << "\nРезультат: " << s;
			}
			minus = false;
		}
		else if (yn == 2)
		{
			system("cls");
			cout << "Введіть число у двійковій системі числення: ";
			cin >> vhidnevar;
			cout << "\n\nПрямий код:     ";
			if (vhidnevar[0] == '-')
			{
				vhidnevar[0] = ' ';
				vhidnevar[1] = '1';
			}
			cout << vhidnevar;
			cout << "\nОбернений код:  ";
			if (vhidnevar[0] == ' ')
			{
				yn = 3;
				while (vhidnevar[yn] != '\0')
				{
					if (vhidnevar[yn] == '0')
						vhidnevar[yn] = '1';
					else if (vhidnevar[yn] == '1')
						vhidnevar[yn] = '0';
					yn++;
				}
			}
			cout << vhidnevar;
			cout << "\nДодатковий код: ";
			if (vhidnevar[0] == ' ')
			{
				for (int i = yn; i >= 3; i--)
				{
					if (vhidnevar[i] == '1')
					{
						vhidnevar[i] = '0';
						continue;
					}
					if (vhidnevar[i] == '0')
					{
						vhidnevar[i] = '1';
						cout << vhidnevar;
						break;
					}
				}
			}
			else
			{
				cout << vhidnevar;
			}
		}
		else
		{
			cout << "\nСпробуйте ще раз!\n";
			system("pause");
			continue;
		}
		cout << "\n\n1 - Виконати ще одну дію | 0 - Завершити роботу\n\n";
		cin >> yn;
	}
	system("cls");
	system("pause");
	return 0;
}