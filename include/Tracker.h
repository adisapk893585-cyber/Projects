#pragma once

#include <vector>
#include <unordered_map>

#include "Problem.h"
#include "Trie.h"

using namespace std;

class Tracker{

private:

    vector<Problem> problems;
    unordered_map<string,vector<int>> topicIndex;
    unordered_map<string,int> nameIndex;
    Trie trie;
    int goal;

public:

    Tracker();

    void run();
};