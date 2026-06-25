#include "Utils.h"

string toLowerCase(string s){

    for(int i=0;i<s.length();i++){
        s[i]=tolower(s[i]);
    }

    return s;
}

int getRank(string s){

    s=toLowerCase(s);

    if(s=="easy") return 1;
    if(s=="medium") return 2;

    return 3;
}

bool isLeapYear(int year){

    if(year%400==0) return true;
    if(year%100==0) return false;
    if(year%4==0) return true;

    return false;
}

int daysInMonth(int month,int year){

    int days[]={31,28,31,30,31,30,31,31,30,31,30,31};

    if(month==2 && isLeapYear(year))
        return 29;

    return days[month-1];
}

int dateToNumber(string date){

    int day=stoi(date.substr(0,2));
    int month=stoi(date.substr(3,2));
    int year=stoi(date.substr(6,4));

    int totalDays=0;

    for(int y=1;y<year;y++){

        if(isLeapYear(y))
            totalDays+=366;
        else
            totalDays+=365;
    }

    for(int m=1;m<month;m++)
        totalDays+=daysInMonth(m,year);

    totalDays+=day;

    return totalDays;
}

void rebuildTopicIndex(
    vector<Problem>& problems,
    unordered_map<string,vector<int>>& topicIndex){

    topicIndex.clear();

    for(int i=0;i<problems.size();i++){

        topicIndex[
            toLowerCase(problems[i].topic)
        ].push_back(i);
    }
}