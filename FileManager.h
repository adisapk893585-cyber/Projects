#pragma once

#include <vector>
#include <unordered_map>
#include "Problem.h"
#include "Trie.h"

using namespace std;

class FileManager{

public:

    static void loadProblems(
        vector<Problem>& problems,
        unordered_map<string,vector<int>>& topicIndex,
        Trie& trie
    );

    static void saveProblems(
        vector<Problem>& problems
    );

    static int loadGoal();

    static void saveGoal(int goal);
};