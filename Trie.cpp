#include "Trie.h"

Trie::Trie(){
    root=new TrieNode();
}

void Trie::insert(string word){

    TrieNode* curr=root;

    word=toLowerCase(word);

    for(char ch:word){

        if(ch<'a' || ch>'z') continue;

        int idx=ch-'a';

        if(curr->child[idx]==NULL){
            curr->child[idx]=new TrieNode();
        }

        curr=curr->child[idx];

        curr->words.push_back(word);
    }

    curr->isEnd=true;
}

bool Trie::searchPrefix(string prefix){

    TrieNode* curr=root;

    prefix=toLowerCase(prefix);

    for(char ch:prefix){

        if(ch<'a' || ch>'z') continue;

        int idx=ch-'a';

        if(curr->child[idx]==NULL){
            return false;
        }

        curr=curr->child[idx];
    }

    return true;
}

vector<string> Trie::getSuggestions(string prefix){

    TrieNode* curr=root;

    prefix=toLowerCase(prefix);

    for(char ch:prefix){

        if(ch<'a' || ch>'z') continue;

        int idx=ch-'a';

        if(curr->child[idx]==NULL){
            return {};
        }

        curr=curr->child[idx];
    }

    return curr->words;
}