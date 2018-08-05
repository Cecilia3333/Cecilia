
#include<iostream>
using namespace std;

class Date{
public:
    Date(int year,int month,int day)
        :_year(year),_month(month),_day(day)
    {
        if(!(year >= 1900 && month > 0 && month < 13 && day > 0 && day <= GetMonthDay(year,month))){
            cout<< "非法日期"<<endl;
        }
    }

    ~Date(){}

    Date(const Date& date){
        _year = date._year;
        _month = date._month;
        _day = date._day;
    }

    Date& operator=(const Date& date){
        if(this != &date){
            _year = date._year;
            _month = date._month;
            _day = date._day;
        }
        return *this;
    }

    void SetDate(int year,int month,int day){
        if(year < 1900 || month < 1 || month > 12 || day < 1 || day > GetMonthDay(year,month)){
            return;
        }
        _year = year;
        _month = month;
        _day = day;
    }

    void Display(){
        printf("<h3>%d-%d-%d</h3>",_year,_month,_day);
    }

    int GetMonthDay(const int& year,const int& month){
        if(year < 1900 || month < 1 || month > 12)
            return -1;
        int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if(month == 2){
            if((year % 4 == 0 && year % 100 != 0)||year % 400 == 0)
                return days[2]+1;
        }
        return days[month];
    }

    Date operator+(int days){//日期+天数
        if(days == 0)
            return *this;
        Date ret = *this;
        ret._day += days;
        while(ret._day > GetMonthDay(ret._year,ret._month)){
            ret._day -= GetMonthDay(ret._year,ret._month);
            ++ret._month;
            if(ret._month > 12){
                ++ret._year;
                ret._month = 1;
            }
        }
        return ret;
    }

    Date& operator+=(int days){
        *this = *this + days;
        return *this;
    }

    bool operator!=(const Date& d){
        return !(*this == d);
    }

    Date operator-(int days){
        Date ret(*this);
        ret._day -= days;
        while(ret._day <= 0){
            --ret._month;
            if(ret._month == 0)
                --ret._year;
            ret._day += GetMonthDay(ret._year,ret._month);
        }
        return ret;
    }

    int operator-(const Date& d){//日期-日期
        if(this == &d)
            return 0;
        Date min(d);//拷贝构造
        Date max(*this);
        int count = 0;
        while(min != max){
            min++;
            ++count;
        }
        return count;
    }

    Date operator++(int){
        *this += 1;
        return *this;
    }

    bool operator>(const Date& x){
        if(_year < x._year)
            return false;
        else if(_year > x._year)
            return true;
        else
        {
            if(_month < x._month)
                return false;
            else if(_month > x._month)
                return true;
            else
            {
                if(_day <= x._day)
                    return false;
                else if(_day > x._day)
                    return true;
            }
        }
        return false;
    }

    bool operator< (const Date& d)
    {
        return !(*this == d || *this > d);

    }

    bool operator==(const Date& x)
    {
        return _year == x._year &&
            _month == x._month &&
            _day == x._day;

    }

    bool operator>=(const Date& x)
    {
        return !(*this < x);

    }

    bool operator<=(const Date& x)
    {
        return !(*this > x);

    }

    Date* operator&(const Date& x)
    {
        return this;
        // return NULL;         
    }

private:
    int _year;
    int _month;
    int _day;
};

