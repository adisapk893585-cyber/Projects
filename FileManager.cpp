#include "FileManager.h"
#include "Utils.h"

#include <fstream>
#include <sstream>

void FileManager::loadProblems(
    vector<Problem>& problems,
    unordered_map<string,vector<int>>& topicIndex,
    Trie& trie){

    ifstream fin("problems.txt");

    if(!fin.is_open())
        return;

    string line;

    while(getline(fin,line)){

        stringstream ss(line);

        Problem p;

        string solvedStr;
        string favorite;

        getline(ss,p.name,'|');
        getline(ss,p.difficulty,'|');
        getline(ss,p.topic,'|');
        getline(ss,solvedStr,'|');
        getline(ss,p.solvedDate,'|');
        getline(ss,favorite);

        p.solved=(solvedStr=="1");
        p.favorite=(favorite=="1");

        problems.push_back(p);

        trie.insert(p.name);

        topicIndex[toLowerCase(p.topic)].push_back(
            problems.size()-1
        );
    }

    fin.close();
}

void FileManager::saveProblems(
    vector<Problem>& problems){

    ofstream fout("problems.txt");

    for(auto &p:problems){

        fout<<p.name<<"|"
            <<p.difficulty<<"|"
            <<p.topic<<"|"
            <<p.solved<<"|"
            <<p.solvedDate<<"|"
            <<p.favorite<<"\n";
    }

    fout.close();
}

int FileManager::loadGoal(){

    int goal=0;

    ifstream fin("goal.txt");

    if(fin.is_open()){

        fin>>goal;
        fin.close();
    }

    return goal;
}

void FileManager::saveGoal(int goal){

    ofstream fout("goal.txt");

    fout<<goal;

    fout.close();
}