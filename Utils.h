#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Problem.h"

using namespace std;

string toLowerCase(string s);

int getRank(string s);

bool isLeapYear(int year);

int daysInMonth(int month,int year);

int dateToNumber(string date);

void rebuildTopicIndex(
    vector<Problem>& problems,
    unordered_map<string,vector<int>>& topicIndex
);