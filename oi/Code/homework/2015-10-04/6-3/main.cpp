#include <iostream>

using namespace std;

struct Date {
    int Year=1;
    int Month=1;
    int Day=1;
};  // struct Date

int daysInNormalYear[]={-1,31,28,31,30,31,30,31,31,30,31,30,31};
int daysInLeapYear[]={-1,31,29,31,30,31,30,31,31,30,31,30,31};

bool IsLeapYear(const Date &date){
	return (date.Year % 4 == 0 && date.Year % 100 != 0) || date.Year % 400 == 0;
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	Date d;
	cin>>d.Year>>d.Month>>d.Day;

	int *days=daysInNormalYear;
	if (IsLeapYear(d)) {
	    days=daysInLeapYear;
	}

	int numbersOfDay=0;
	for (int i=1;
	     i<d.Month;
	     i++) {
	    numbersOfDay+=days[i];
	}  // for

	cout<<numbersOfDay+d.Day<<'\n';

	return 0;
}