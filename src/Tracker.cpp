#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <string>
#include "../include/Tracker.h"
#include "../include/FileManager.h"
#include "../include/Utils.h"

using namespace std;
Tracker::Tracker(){

    goal = FileManager::loadGoal();

    FileManager::loadProblems(
        problems,
        topicIndex,
        trie
    );
}

void Tracker::run(){

    int choice;

    while(true){
        cout<<"\n======= LEETCODE TRACKER =======\n";
        cout<<"1.  Add a problem\n";
        cout<<"2.  show problems\n";
        cout<<"3.  Mark solved\n";
        cout<<"4.  Show Statistics\n";
        cout<<"5.  Search Problem\n";
        cout<<"6.  Save Problems\n";
        cout<<"7.  Delete Problem\n";
        cout<<"8.  Topic Statistics\n";
        cout<<"9.  Difficulty Statistics\n";
        cout<<"10. Show Solved Problems\n";
        cout<<"11. Show Unsolved Problems\n";
        cout<<"12. Sort by Name\n";
        cout<<"13. Sort by Difficulty\n";
        cout<<"14. Difficulty-wise Solved Stats\n";
        cout<<"15. Search By Topic\n";
        cout<<"16. Edit Problem\n";
        cout<<"17. Mark Favorites\n";
        cout<<"18. Show Favorites\n";
        cout<<"19. Export to CSV\n";
        cout<<"20. Recent Activity\n";
        cout<<"21. Streak Counter\n";
        cout<<"22. Advanced Search\n";
        cout<<"23. Recommend Problems\n";
        cout<<"24. Advanced Analytics\n";
        cout<<"25. Topic Weakness Detector\n";
        cout<<"26. Set GOAL\n";
        cout<<"27. GOAL TRACKER\n";
        cout<<"28. Difficulty Heatmap\n";
        cout<<"29. Achievements\n";
        cout<<"30. Prefix Search\n";
        cout<<"31. Exit\n";


        cout<<"Enter your choice: ";

        cin>>choice;

        if(choice==1){
            
            Problem p;
            
            cin.ignore();

            cout<<"Problem Name: ";
            getline(cin,p.name);

            cout<<"Difficulty: ";
            getline(cin,p.difficulty);

            cout<<"Topic ";
            getline(cin,p.topic);

            p.solved=false;

            p.solvedDate="Not Solved";

            p.favorite=false;

            problems.push_back(p);
            topicIndex[toLowerCase(p.topic)].push_back(problems.size()-1);
            trie.insert(p.name);
            
            cout<<"Problem Added!\n";

        }

        else if(choice==2){
            if(problems.empty()){
                cout<<"No Problems Added Yet!\n";
                continue;
            }

            for(int i=0;i<problems.size();i++){
                cout<< i+1 <<". "
                    <<problems[i].name
                    <<" | "
                    <<problems[i].difficulty
                    <<" | "
                    <<problems[i].topic
                    <<" | "
                    <<(problems[i].solved ? "Solved" : "Unsolved")
                    <<" | "
                    <<problems[i].solvedDate
                    <<" | "
                    <<(problems[i].favorite ? "Favorite" : "Not Favorite")
                    <<"\n";
            }
        }

        else if(choice==3){
            if(problems.empty()){
                cout<<"No Problems Added Yet!\n";
                continue;
            }

            cout<<"\nProblems:\n";

            for(int i=0;i<problems.size();i++){
                cout<<i+1<<". "
                <<problems[i].name
                <<"\n";
            }

            int idx;

            cout<<"Enter Problem number to mark solved: ";
            cin>>idx;

            if(idx>=1 && idx<=problems.size()){
                problems[idx-1].solved=true;

                cin.ignore();

                cout<<"Enter solved Date (DD-MM-YYYY): ";
                getline(cin,problems[idx-1].solvedDate);

                cout<<"Marked as Solved!\n";
            }
            else{
                cout<<"Invalid Problem Number!\n";
            }
        }
        else if(choice==4){
            
            int solvedCount=0;

            for(int i=0;i<problems.size();i++){
                if(problems[i].solved){
                    solvedCount++;
                }
            }

            cout<<"\n====== Statistics ======\n";
            cout<<"Total Problems : "<<problems.size()<<"\n";
            cout<<"Solved Problems : "<<solvedCount<<"\n";
            cout<<"Unsolved Problems : "<<problems.size()-solvedCount<<"\n";

            double progress=0;

            if(problems.size()>0){
                progress = (solvedCount*100.0)/problems.size();
            }

            cout<<fixed<<setprecision(2);
            cout<<"Progress : "<<progress<<"%\n";
        }
        else if(choice==5){
            
            if(problems.empty()){
                cout << "No Problems Added Yet!\n";
                continue;
            }

            string searchName;

            cin.ignore();

            cout<<"Enter Problem Name : ";
            getline(cin,searchName);

            bool found=false;

            for(int i = 0; i < problems.size(); i++){

            if(toLowerCase(problems[i].name) == toLowerCase(searchName)){

                cout << "\nProblem Found!\n";
                cout << "Name: " << problems[i].name << endl;
                cout << "Difficulty: " << problems[i].difficulty << endl;
                cout << "Topic: " << problems[i].topic << endl;
                cout << "Status: " << (problems[i].solved ? "Solved" : "Unsolved")<<endl;
                cout <<"Solved Date: " <<problems[i].solvedDate
                     <<endl;

                found = true;
                break;
            }
        }

        if(!found){
            cout << "Problem Not Found!\n";
        }

        }
        else if(choice==6){
            FileManager::saveProblems(problems);

            cout<<"Problems Saved Successfully!\n";
        }
        else if(choice==7){

            if(problems.empty()){
                cout << "No Problems Added Yet!\n";
                continue;
            }

            cout << "\nProblems:\n";

            for(int i = 0; i < problems.size(); i++){
                cout << i + 1 << ". "
                    << problems[i].name
                    << "\n";
            }

            int idx;
            cout<<"Enter problem number to delete : ";
            cin>>idx;

            if(idx >= 1 && idx <= problems.size()){

                problems.erase(problems.begin() + (idx - 1));
                rebuildTopicIndex(problems,topicIndex);
                cout << "Problem Deleted Successfully!\n";
            }
            else{
                cout << "Invalid Problem Number!\n";
            }

        }
        else if(choice==8){
            
            if(problems.empty()){
                cout << "No Problems Added Yet!\n";
                continue;
            }

            map<string,int> topicCount;

            for(int i=0;i<problems.size();i++){
                topicCount[problems[i].topic]++;
            }

            cout<<"\n==== Topic Statistics ====\n";

            for(auto &it:topicCount){
                cout<<it.first<<" : "<<it.second<<"\n";
            }
        }
        else if(choice==9){

            if(problems.empty()){
                cout << "No Problems Added Yet!\n";
                continue;
            }

            map<string,int> difficultyCount;

            for(int i=0;i<problems.size();i++){
                difficultyCount[problems[i].difficulty]++;
            }

            cout<<"\n==== Difficulty Statistics ====\n";

            for(auto &it:difficultyCount){
                cout<<it.first<<" : "<<it.second<<"\n";
            }
        }
        else if(choice==10){

            if(problems.empty()){
                cout<<"No Problems Added Yet!\n";
                continue;
            }

            cout<<"\n==== Solved Problems ====\n";

            bool found=false;

            for(int i=0;i<problems.size();i++){

                if(problems[i].solved){

                    cout<<i+1<<". "
                        <<problems[i].name
                        <<" | "
                        <<problems[i].difficulty
                        <<" | "
                        <<problems[i].topic
                        <<"\n";

                    found=true;
                }
            }

            if(!found){
                cout<<"No Solved Problems Found!\n";
            }
    }
    else if(choice==11){

        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        cout<<"\n==== Unsolved Problems ====\n";

        bool found=false;

        for(int i=0;i<problems.size();i++){

            if(!problems[i].solved){

                cout<<i+1<<". "
                    <<problems[i].name
                    <<" | "
                    <<problems[i].difficulty
                    <<" | "
                    <<problems[i].topic
                    <<"\n";

                found=true;
            }
        }

        if(!found){
            cout<<"No Unsolved Problems Found!\n";
        }
    }
    else if(choice==12){
        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        sort(problems.begin(),problems.end(),
            [](Problem &a,Problem &b){
                return a.name<b.name;
            }); 

        cout<<"Problems Sorted By Name!\n";    
    }
    else if(choice==13){
        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        sort(problems.begin(), problems.end(),
            [](Problem &a, Problem &b){
                
                return getRank(a.difficulty) < getRank(b.difficulty);
            
        });

        cout<<"Problems Sorted By Difficulty!\n"; 

    }
    else if(choice==14){

        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        int easyTotal=0, mediumTotal=0, hardTotal=0;
        int easySolved=0, mediumSolved=0, hardSolved=0;

        for(int i=0;i<problems.size();i++){

            string diff = toLowerCase(problems[i].difficulty);

            if(diff=="easy"){
                easyTotal++;
                if(problems[i].solved) easySolved++;
            }

            else if(diff=="medium"){
                mediumTotal++;
                if(problems[i].solved) mediumSolved++;
            }

            else if(diff=="hard"){
                hardTotal++;
                if(problems[i].solved) hardSolved++;
            }
        }

        cout<<"\n==== Difficulty-wise Solved Stats ====\n";

        cout<<"Easy   : "<<easySolved<<"/"<<easyTotal<<"\n";
        cout<<"Medium : "<<mediumSolved<<"/"<<mediumTotal<<"\n";
        cout<<"Hard   : "<<hardSolved<<"/"<<hardTotal<<"\n";
    }
    else if(choice==15){

        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        string searchTopic;

        cin.ignore();

        cout<<"Enter Topic : ";
        getline(cin,searchTopic);


        string key = toLowerCase(searchTopic);

        if(topicIndex.find(key)==topicIndex.end()){
            cout<<"No Problems Found!\n";
            continue;
        }

        cout<<"\n==== Matching Problems ====\n";

        for(int idx : topicIndex[key]){

            cout<<problems[idx].name
                <<" | "
                <<problems[idx].difficulty
                <<" | "
                <<(problems[idx].solved ? "Solved" : "Unsolved")
                <<"\n";
        }

    }
    else if(choice==16){
        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        cout<<"\nProblems:\n";

        for(int i=0;i<problems.size();i++){
            cout<<i+1<<". "
            <<problems[i].name
            <<"\n";
        }

        int idx;

        cout<<"Enter Probelm number to edit : ";
        cin>>idx;

        if(idx>=1 && idx<=problems.size()){

            cin.ignore();

            cout<<"New Problem Name : ";
            getline(cin,problems[idx-1].name);

            cout<<"New Difficulty : ";
            getline(cin,problems[idx-1].difficulty);

            cout<<"New Topic : ";
            getline(cin,problems[idx-1].topic);

            rebuildTopicIndex(problems,topicIndex);

            cout<<"Problem Updated Successfully!\n";
        }
        else{
            cout<<"Invalid Problem Number!\n";
        }
    }
    else if(choice==17){
        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        cout<<"\nProblems:\n";

        for(int i=0;i<problems.size();i++){
            cout<<i+1<<". "
                <<problems[i].name
                <<"\n";
        }
        int idx;
        cout<<"Enter problem number to mark favorite : ";
        cin>>idx;

        if(idx>=1 && idx<=problems.size()){
            if(problems[idx-1].favorite){
            cout<<"Already Favorite!\n";
        }
        else{
            problems[idx-1].favorite=true;
            cout<<"Problem Marked as Favorite!\n";
        }
        }
        else{
            cout<<"Invalid Problem Number!\n";
        }
    }
    else if(choice==18){
        cout<<"\n==== Favorite Problems ====\n";

        for(int i=0;i<problems.size();i++){
            if(problems[i].favorite==true){
                cout<<problems[i].name<<" | "
                    <<problems[i].difficulty<<" | "
                    <<problems[i].topic<<" | "
                    <<(problems[i].solved ? "Solved" : "Unsolved")<<" | "
                    <<problems[i].solvedDate
                    <<"\n";
            }
        }
    }
    else if(choice==19){
        ofstream csv("../data/problems.csv");
        csv<<"Name,Difficulty,Topic,Solved,SolvedDate,Favorite\n";
        for(int i=0;i<problems.size();i++){
            csv<<problems[i].name<<","
                <<problems[i].difficulty<<","
                <<problems[i].topic<<","
                <<problems[i].solved<<","
                <<problems[i].solvedDate<<","
                <<problems[i].favorite<<"\n";
        }

        csv.close();
        cout<<"CSV Export Successful!\n";
    }
    else if(choice==20){

        vector<pair<string,string>> activity;
        for(int i=0;i<problems.size();i++){
            if(problems[i].solved && problems[i].solvedDate != "Not Solved" && problems[i].solvedDate != ""){
                activity.push_back({problems[i].solvedDate,problems[i].name});
            }
        }

        sort(activity.begin(),activity.end(),
            [](auto &a,auto &b){
                string d1=a.first;
                string d2=b.first;

                string key1=d1.substr(6,4)+d1.substr(3,2)+d1.substr(0,2);
                string key2=d2.substr(6,4)+d2.substr(3,2)+d2.substr(0,2);

                return key1>key2;
            });
            
        cout<<"\n==== Recent Activity ====\n";

        bool found=false;

        for(auto &it:activity){
            cout<<it.first
                <<" : "
                <<it.second
                <<"\n";
            
                found=true;
        }

        if(!found){
            cout<<"No Solved Problems Found!\n";
        }
    }

    else if(choice==21){
         vector<string> dates;

        for(int i=0;i<problems.size();i++){

            if(problems[i].solved &&
            problems[i].solvedDate!="Not Solved" &&
            !problems[i].solvedDate.empty()){

                dates.push_back(problems[i].solvedDate);
            }
        }

        if(dates.empty()){
            cout<<"No Solved Problems Found!\n";
            continue;
        }

        sort(dates.begin(),dates.end(),
            [](string a,string b){

                string key1=a.substr(6,4)+a.substr(3,2)+a.substr(0,2);
                string key2=b.substr(6,4)+b.substr(3,2)+b.substr(0,2);

                return key1>key2;
            });

        int streak=1;

        for(int i=1;i<dates.size();i++){

            int curr=dateToNumber(dates[i-1]);
            int next=dateToNumber(dates[i]);

            if(curr-next==1){
                streak++;
            }
            else{
                break;
            }

        }
        cout<<"\n==== Current Streak ====\n";
        
        if(streak==1){
            cout<<"Current Streak : 1 Day\n";
        }
        else{
            cout<<"Current Streak : "<<streak<<" Days\n";
        }
}
    else if(choice==22){
       string topic;
       string status;

       cin.ignore();

       cout<<"Enter Topic : ";
       getline(cin,topic);

       cout<<"Enter Status (Solved/Unsolved) : ";
       getline(cin,status);

       string key=toLowerCase(topic);

       if(topicIndex.find(key)==topicIndex.end()){
        cout<<"No Problems Found!\n";
       }

       bool found=false;

       for(int idx :topicIndex[key]){
            bool wantSolved=(toLowerCase(status)=="solved");

            if(problems[idx].solved==wantSolved){
                
                cout<<problems[idx].name
                    <<" | "
                    <<problems[idx].difficulty
                    <<" | "
                    <<problems[idx].topic
                    <<"\n";

                found=true;
            }
       }
       if(!found){
            cout<<"No Problems Found!\n";
        }
    }
    else if(choice==23){

        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        map<string,int> solvedTopics;

        for(int i=0;i<problems.size();i++){

            if(problems[i].solved){

                solvedTopics[problems[i].topic]++;
            }
        }

        if(solvedTopics.empty()){

            cout<<"Solve some problems first!\n";
            continue;
        }

        string bestTopic;
        int mx=0;

        for(auto &it : solvedTopics){

            if(it.second > mx){

                mx = it.second;
                bestTopic = it.first;
            }
        }

        cout<<"\n==== Recommended Problems ====\n";
        cout<<"Strongest Topic : "
            <<bestTopic<<"\n\n";

        bool found=false;

        for(int i=0;i<problems.size();i++){

            if(problems[i].topic==bestTopic &&
            !problems[i].solved){

                cout<<problems[i].name
                    <<" | "
                    <<problems[i].difficulty
                    <<"\n";

                found=true;
            }
        }

        if(!found){

            cout<<"No pending problems in "
                <<bestTopic
                <<" topic.\n";
        }
    }
    else if(choice==24){

        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        int solvedCount=0;
        int favoriteCount=0;

        map<string,int> topicSolved;

        for(int i=0;i<problems.size();i++){

            if(problems[i].solved){

                solvedCount++;

                topicSolved[problems[i].topic]++;
            }

            if(problems[i].favorite){
                favoriteCount++;
            }
        }

        string bestTopic="None";
        int mx=0;

        for(auto &it: topicSolved){

            if(it.second>mx){

                mx=it.second;
                bestTopic=it.first;
            }
        }

        double successRate=0;

        if(problems.size()>0){

            successRate=
                (solvedCount*100.0)/problems.size();
        }

        cout<<"\n====== Analytics Dashboard ======\n";

        cout<<"Total Problems : "
            <<problems.size()<<"\n";

        cout<<"Solved Problems : "
            <<solvedCount<<"\n";

        cout<<"Favorite Problems : "
            <<favoriteCount<<"\n";

        cout<<"Most Solved Topic : "
            <<bestTopic<<"\n";

        cout<<fixed<<setprecision(2);

        cout<<"Success Rate : "
            <<successRate
            <<"%\n";
    }
    else if(choice==25){
        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }


        map<string,int> solvedCount;
        map<string,int> unsolvedCount;

        for(int i=0;i<problems.size();i++){

            if(problems[i].solved){
                solvedCount[problems[i].topic]++;
            }
            else{
                unsolvedCount[problems[i].topic]++;
            }
        }

        string weakestTopic="None";
        int mxUnsolved=0;

        for(auto &it : unsolvedCount){

            if(it.second > mxUnsolved){

                mxUnsolved = it.second;
                weakestTopic = it.first;
            }
        }

        cout<<"\n==== Topic Weakness Detector ====\n";

        cout<<"\nWeakest Topic : "
            <<weakestTopic<<"\n";

        cout<<"Solved : "
            <<solvedCount[weakestTopic]
            <<"\n";

        cout<<"Unsolved : "
            <<unsolvedCount[weakestTopic]
            <<"\n";

        cout<<"\nRecommendation:\n";

        cout<<"\nFocus more on " <<weakestTopic <<" problems.\n";
    }
     else if(choice==26){

        cout<<"Enter Goal : ";
        cin>>goal;

        FileManager::saveGoal(goal);

        cout<<"Goal Set Successfully!\n";
    }

   
    
    else if(choice==27){

        int solvedCount=0;

        for(int i=0;i<problems.size();i++){

            if(problems[i].solved){
                solvedCount++;
            }
        }

        double progress=0;

        if(goal>0){
            progress=(solvedCount*100.0)/goal;
        }

        cout<<"\n==== Goal Tracker ====\n";

        cout<<"Goal : "
            <<goal
            <<" Problems\n";

        cout<<"Solved : "
            <<solvedCount
            <<" Problems\n";

        cout<<fixed<<setprecision(2);

        cout<<"Progress : "
            <<progress
            <<"%\n";

        if(solvedCount>=goal){

            cout<<"Goal Achieved! \n";
        }
}
    else if(choice==28){

        int easyTotal=0, mediumTotal=0, hardTotal=0;
        int easySolved=0, mediumSolved=0, hardSolved=0;

        for(int i=0;i<problems.size();i++){

            string diff=toLowerCase(problems[i].difficulty);

            if(diff=="easy"){
                easyTotal++;
                if(problems[i].solved) easySolved++;
            }
            else if(diff=="medium"){
                mediumTotal++;
                if(problems[i].solved) mediumSolved++;
            }
            else if(diff=="hard"){
                hardTotal++;
                if(problems[i].solved) hardSolved++;
            }
        }

        cout<<"\n==== Difficulty Heatmap ====\n";

        auto printBar = [](int solved,int total){

            int bars=0;

            if(total>0){
                bars=(solved*20)/total;
            }

            for(int i=0;i<bars;i++){
                cout<<"=";
            }

            cout<<" ("<<solved<<"/"<<total<<")";
        };

        cout<<"Easy   : ";
        printBar(easySolved,easyTotal);
        cout<<"\n";

        cout<<"Medium : ";
        printBar(mediumSolved,mediumTotal);
        cout<<"\n";

        cout<<"Hard   : ";
        printBar(hardSolved,hardTotal);
        cout<<"\n";
}
    else if(choice==29){

        int solvedCount=0;

        for(int i=0;i<problems.size();i++){

            if(problems[i].solved){
                solvedCount++;
            }
        }

        cout<<"\n==== Achievements ====\n";

        if(solvedCount>=1)
            cout<<"[UNLOCKED] First Problem Solved\n";

        if(solvedCount>=10)
            cout<<"[UNLOCKED] 10 Problems Solved\n";

        if(solvedCount>=25)
            cout<<"[UNLOCKED] 25 Problems Solved\n";

        if(solvedCount>=50)
            cout<<"[UNLOCKED] 50 Problems Solved\n";

        if(solvedCount>=100)
            cout<<"[UNLOCKED] Century Club (100 Problems)\n";

        int favoriteCount=0;

        for(int i=0;i<problems.size();i++){
            if(problems[i].favorite)
                favoriteCount++;
        }

        if(favoriteCount>=5) cout<<"[UNLOCKED] Collector (5 Favorites)\n";
}
    else if(choice==30){

        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        string prefix;

        cin.ignore();

        cout<<"Enter Prefix : ";
        getline(cin,prefix);

        prefix = toLowerCase(prefix);

        bool found=false;

        cout<<"\n==== Matching Problems ====\n";

        vector<string> suggestions=
        trie.getSuggestions(prefix);

        if(suggestions.empty()){

            cout<<"No Problems Found!\n";
            continue;
        }

        cout<<"\n==== Suggestions ====\n";

        for(auto &s:suggestions){
            cout<<s<<"\n";
        }

}
    else if(choice==31){
        FileManager::saveProblems(problems);
        break;
    }
    else{
        cout<<"Invalid Choice\n";
    }
}
}