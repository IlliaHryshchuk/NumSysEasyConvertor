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
	char s[80] = { 0 };
	char vhidnevar[80] = { 0 };
	int SysOfCount, SystemOfCountBase;
	system("chcp 1251");
	int yn = 1;
	while (yn != 0)
	{
		system("cls");
		cout << "Введіть основу систми числення базового числа: ";
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
		}
		else if (SystemOfCountBase >=2 && SystemOfCountBase != 10 && SystemOfCountBase <= 16)
		{
			cin >> vhidnevar;
			yn = 1;
			bool isdot = false;
			while (vhidnevar[yn-1] != '\0')
			{
				if (vhidnevar[yn-1] == '.')
				{
					isdot = true;
					break;
				}
				yn++;
			}
			if (isdot != true)
			{
				vhidnevar[yn-1] = '.';
				vhidnevar[yn] = '0';
				vhidnevar[yn+1] = '\0';
			}
			var = convert_any_to_dec(vhidnevar, SystemOfCountBase);
		}
		else
		{
			cout << "\nДана система числення не підтримується! Використайте іншу! (від 2 до 16)\n";
			system("pause");
			continue;
		}
		cout << "Введіть основу системи числення вихідного числа: ";
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
		if (SysOfCount == 2)
		{
			yn = 1;
			cout << "\nПрямий код: ";
			int k = convert_int((int)var, SysOfCount, s);
			s[k++] = '.';
			convert_double(var - (int)var, SysOfCount, &s[k]);
			cout << s;
			cout << "\nОбернений код: ";
			while (s[yn-1] != '\0')
			{
				if (s[yn - 1] == '0')
					s[yn - 1] = '1';
				else if(s[yn-1] == '1')
					s[yn - 1] = '0';
				yn++;
			}
			cout << s;
			cout << "\nДодатковий код: ";
			for (yn = 0; yn < 80; yn++)
				if (s[yn] == '.') break;
			for (int i = yn; i >= 0; i--)
			{
				if (s[i] == '1')
				{
					s[i] = '0';
					continue;
				}
				if (s[i] == '0')
				{
					s[i] = '1';
					break;
				}
			}
			cout << s;
		}
		else
		{
			int k = convert_int((int)var, SysOfCount, s);
			s[k++] = '.';
			convert_double(var - (int)var, SysOfCount, &s[k]);
			cout << "\nРезультат: " << s;
		}
		cout << "\n\n1 - Виконати ще одне перетворення | 0 - Завершити роботу\n\n";
		cin >> yn;
	}
	system("cls");
	system("pause");
	return 0;
}