#pragma once

#include <string>
#include <vector>

using namespace std;

string toLowerCase(string s);

struct TrieNode{

    TrieNode* child[26];
    bool isEnd;
    vector<string> words;

    TrieNode(){

        isEnd=false;

        for(int i=0;i<26;i++){
            child[i]=NULL;
        }
    }
};

class Trie{

public:

    TrieNode* root;

    Trie();

    void insert(string word);

    bool searchPrefix(string prefix);

    vector<string> getSuggestions(string prefix);
};