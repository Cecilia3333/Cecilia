#include <iostream>
#include<assert.h>
using namespace std;

class Date{
public:
    int GetMonthDay(int year,int month){
        assert(year >= 1900 && month > 0 && month < 13);
        static int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        int day = days[month];
        if((month == 2) && (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
            day += 1;
        }
        return day;
    }

    void SetDate(int year,int month,int day){
        if(year >= 1900 && month > 0 && month < 13 && day > 0 && day <= GetMonthDay(year,month)){
            _year = year;
            _month = month;
            _day = day;
            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
        }
        else{
            cout<<"error set!"<<" "<<year<<"-"<<month<<"-"<<day<<endl;
        }
    }

private:
    int _year;
    int _month;
    int _day;
};

int main(){
    Date d;
//    d.SetDate(2018,6,28);
    d.SetDate(2018,6,32);
    return 0;
}
