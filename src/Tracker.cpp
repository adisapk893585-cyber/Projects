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

    for(int i=0;i<problems.size();i++){
        nameIndex[toLowerCase(problems[i].name)] = i;
    }
}

void Tracker::run(){

    int choice;

    while(true){
        cout<<"\n=========================================================\n";
        cout<<"              LEETCODE PROGRESS TRACKER v1.0\n";
        cout<<"=========================================================\n\n";

        cout<<"\n----------- 📂 Problem Management -----------\n";
        cout<<setw(2)<<right<<1<<".  Add Problem\n";
        cout<<setw(2)<<right<<2<<".  Show Problems\n";
        cout<<setw(2)<<right<<3<<".  Mark Solved\n";
        cout<<setw(2)<<right<<7<<".  Delete Problem\n";
        cout<<setw(2)<<right<<16<<". Edit Problem\n";
        cout<<setw(2)<<right<<17<<". Mark Favorites\n";
        cout<<setw(2)<<right<<18<<". Show Favorites\n\n";

        cout<<"\n----------- 🔍 Search -----------\n";
        cout<<setw(2)<<right<<5<<".  Search Problem\n";
        cout<<setw(2)<<right<<15<<". Search By Topic\n";
        cout<<setw(2)<<right<<22<<". Advanced Search\n";
        cout<<setw(2)<<right<<30<<". Prefix Search\n\n";


        cout<<"\n----------- 📊 Analytics -----------\n";
        cout<<setw(2)<<right<<4<<".  Show Statistics\n";
        cout<<setw(2)<<right<<8<<".  Topic Statistics\n";
        cout<<setw(2)<<right<<9<<".  Difficulty Statistics\n";
        cout<<setw(2)<<right<<14<<". Difficulty-wise Solved Stats\n";
        cout<<setw(2)<<right<<24<<". Advanced Analytics\n";
        cout<<setw(2)<<right<<25<<". Topic Weakness Detector\n";
        cout<<setw(2)<<right<<28<<". Difficulty Heatmap\n";
        cout<<setw(2)<<right<<23<<". Recommend Problems\n\n";

        cout<<"\n----------- 🎯 Progress -----------\n";
        cout<<setw(2)<<right<<10<<". Show Solved Problems\n";
        cout<<setw(2)<<right<<11<<". Show Unsolved Problems\n";
        cout<<setw(2)<<right<<20<<". Recent Activity\n";
        cout<<setw(2)<<right<<21<<". Current Streak\n";
        cout<<setw(2)<<right<<26<<". Set Goal\n";
        cout<<setw(2)<<right<<27<<". Goal Tracker\n";
        cout<<setw(2)<<right<<29<<". Achievements\n\n";

        cout<<"\n----------- 💾 Data -----------\n";
        cout<<setw(2)<<right<<6<<".  Save Problems\n";
        cout<<setw(2)<<right<<19<<". Export to CSV\n";
        cout<<setw(2)<<right<<31<<". Exit\n";

        cout<<"\n=========================================================\n";


        cout<<"Enter your choice: ";

        cin>>choice;

        if(choice==1){
            
            Problem p;
            
            cin.ignore();

            cout<<"Problem Name: ";
            getline(cin,p.name);

            p.name=toLowerCase(p.name);

            cout<<"Difficulty: ";
            getline(cin,p.difficulty);

            p.difficulty = toLowerCase(p.difficulty);

            if(p.difficulty == "easy")
                p.difficulty = "Easy";
            else if(p.difficulty == "medium")
                p.difficulty = "Medium";
            else if(p.difficulty == "hard")
                p.difficulty = "Hard";

            cout<<"Topic: ";
            getline(cin,p.topic);

            p.topic=toLowerCase(p.topic);

            p.solved=false;

            p.solvedDate="Not Solved";

            p.favorite=false;

            problems.push_back(p);

            nameIndex[toLowerCase(p.name)] = problems.size()-1;

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
                cout<<"No Problems Added Yet!\n";
                continue;
            }

            string searchName;

            cin.ignore();

            cout<<"Enter Problem Name : ";
            getline(cin,searchName);

            searchName = toLowerCase(searchName);

            if(!nameIndex.count(searchName)){
                cout<<"Problem Not Found!\n";
                continue;
            }

            int idx = nameIndex[searchName];

            cout<<"\nProblem Found!\n";
            cout<<"Name: "<<problems[idx].name<<endl;
            cout<<"Difficulty: "<<problems[idx].difficulty<<endl;
            cout<<"Topic: "<<problems[idx].topic<<endl;
            cout<<"Status: "<<(problems[idx].solved ? "Solved" : "Unsolved")<<endl;
            cout<<"Solved Date: "<<problems[idx].solvedDate<<endl;
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

        for(auto &p : problems){

            if(p.solved &&
            p.solvedDate!="Not Solved" &&
            !p.solvedDate.empty()){

                activity.push_back({p.solvedDate,p.name});
            }
        }

        sort(activity.begin(),activity.end(),
        [](auto &a,auto &b){

            string key1=a.first.substr(6,4)+
                        a.first.substr(3,2)+
                        a.first.substr(0,2);

            string key2=b.first.substr(6,4)+
                        b.first.substr(3,2)+
                        b.first.substr(0,2);

            return key1>key2;
        });

        cout<<"\n=========================================================\n";
        cout<<"                  RECENT ACTIVITY\n";
        cout<<"=========================================================\n\n";

        if(activity.empty()){

            cout<<"No solved problems found.\n";
        }
        else{

            int cnt=0;

            for(auto &it:activity){

                cout<<"📅 "
                    <<left
                    <<setw(12)
                    <<it.first
                    <<"  ✓  "
                    <<it.second
                    <<endl;

                cnt++;

                if(cnt==10)
                    break;
            }
        }

        cout<<"\n=========================================================\n";
    }

    else if(choice==21){

        vector<string> dates;

        for(auto &p:problems){

            if(p.solved &&
            p.solvedDate!="Not Solved" &&
            !p.solvedDate.empty()){

                dates.push_back(p.solvedDate);
            }
        }

        if(dates.empty()){

            cout<<"\n=========================================================\n";
            cout<<"                  CURRENT STREAK\n";
            cout<<"=========================================================\n\n";

            cout<<"No solved problems found.\n";

            cout<<"\n=========================================================\n";
            continue;
        }

        sort(dates.begin(),dates.end(),
        [](string a,string b){

            string key1=a.substr(6,4)+
                        a.substr(3,2)+
                        a.substr(0,2);

            string key2=b.substr(6,4)+
                        b.substr(3,2)+
                        b.substr(0,2);

            return key1>key2;
        });

        int streak=1;

        for(int i=1;i<dates.size();i++){

            int curr=dateToNumber(dates[i-1]);
            int next=dateToNumber(dates[i]);

            if(curr-next==1)
                streak++;
            else
                break;
        }

        cout<<"\n=========================================================\n";
        cout<<"                  CURRENT STREAK\n";
        cout<<"=========================================================\n\n";

        if(streak==1)
            cout<<"🔥 Current Streak : 1 Day\n";
        else
            cout<<"🔥 Current Streak : "<<streak<<" Days\n";

        cout<<"\n";

        if(streak>=30)
            cout<<"🏆 Outstanding! You're on fire!\n";
        else if(streak>=15)
            cout<<"💪 Excellent consistency! Keep it going!\n";
        else if(streak>=7)
            cout<<"🚀 Great momentum! Don't break the streak!\n";
        else
            cout<<"✨ Solve one problem every day to build your streak.\n";

        cout<<"\n=========================================================\n";
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

        int solvedCount = 0;

        map<string,int> totalTopics;
        map<string,int> solvedTopics;

        for(auto &p : problems){

            totalTopics[p.topic]++;

            if(p.solved){
                solvedTopics[p.topic]++;
                solvedCount++;
            }
        }

        string weakTopic="";
        double lowestRate=101.0;

        for(auto &it : totalTopics){

            double rate=0;

            if(it.second>0)
                rate=(solvedTopics[it.first]*100.0)/it.second;

            if(rate<lowestRate){

                lowestRate=rate;
                weakTopic=it.first;
            }
        }

        int bestIndex=-1;
        int bestScore=-1;

        for(int i=0;i<problems.size();i++){

            if(problems[i].solved)
                continue;

            int score=0;

            if(problems[i].topic==weakTopic)
                score+=50;

            string diff=toLowerCase(problems[i].difficulty);

            if(diff=="medium")
                score+=40;
            else if(diff=="easy")
                score+=30;
            else
                score+=10;

            if(problems[i].favorite)
                score+=5;

            if(score>bestScore){

                bestScore=score;
                bestIndex=i;
            }
        }

        if(bestIndex==-1){

            cout<<"\nCongratulations!\n";
            cout<<"You have solved all the problems.\n";
            continue;
        }

        cout<<"\n=========================================================\n";
        cout<<"                 TODAY'S RECOMMENDATION\n";
        cout<<"=========================================================\n\n";

        cout<<"Problem        : "<<problems[bestIndex].name<<endl;

        string diff=toLowerCase(problems[bestIndex].difficulty);

        if(diff=="easy")
            cout<<"Difficulty     : Easy ★"<<endl;
        else if(diff=="medium")
            cout<<"Difficulty     : Medium ★★"<<endl;
        else
            cout<<"Difficulty     : Hard ★★★"<<endl;

        cout<<"Topic          : "<<problems[bestIndex].topic<<endl;

        cout<<fixed<<setprecision(1);

        cout<<"\n-------------------- Topic Analysis --------------------\n";

        cout<<"Weakest Topic  : "<<weakTopic<<endl;
        cout<<"Solved         : "
            <<solvedTopics[weakTopic]
            <<" / "
            <<totalTopics[weakTopic]
            <<endl;

        cout<<"Success Rate   : "
            <<lowestRate
            <<"%\n";

        cout<<"\n---------------- Recommendation ----------------\n";

        if(diff=="easy")
            cout<<"Priority       : Low\n";
        else if(diff=="medium")
            cout<<"Priority       : High\n";
        else
            cout<<"Priority       : Challenge\n";

        cout<<"\nWhy this recommendation?\n";
        cout<<"------------------------------------------------\n";

        if(problems[bestIndex].topic==weakTopic)
            cout<<"✓ This problem belongs to your weakest topic.\n";

        cout<<"✓ You haven't solved this problem yet.\n";

        if(diff=="easy")
            cout<<"✓ Good for building confidence.\n";
        else if(diff=="medium")
            cout<<"✓ Best difficulty for interview preparation.\n";
        else
            cout<<"✓ Excellent challenge to improve problem-solving.\n";

        cout<<"\n---------------- Overall Progress ----------------\n";

        cout<<"Solved Problems    : "
            <<solvedCount
            <<" / "
            <<problems.size()
            <<endl;

        cout<<"Remaining Problems : "
            <<problems.size()-solvedCount
            <<endl;

        cout<<"\nNext Step\n";
        cout<<"------------------------------------------------\n";

        cout<<"Solve this problem to strengthen your "
            <<weakTopic
            <<" skills.\n";

        cout<<"\n=========================================================\n";
    }
   else if(choice==24){

        if(problems.empty()){
            cout<<"No Problems Added Yet!\n";
            continue;
        }

        int solvedCount=0;
        int favoriteCount=0;

        map<string,int> topicSolved;
        map<string,int> difficultyCount;

        for(auto &p:problems){

            if(p.solved){
                solvedCount++;
                topicSolved[p.topic]++;
            }

            if(p.favorite){
                favoriteCount++;
            }

            difficultyCount[p.difficulty]++;
        }

        string bestTopic="None";
        int mx=0;

        for(auto &it:topicSolved){

            if(it.second>mx){
                mx=it.second;
                bestTopic=it.first;
            }
        }

        double successRate =
            (solvedCount*100.0)/problems.size();

        cout<<"\n=========================================\n";
        cout<<"        ANALYTICS DASHBOARD\n";
        cout<<"=========================================\n";

        cout<<"Total Problems      : "<<problems.size()<<endl;
        cout<<"Solved Problems     : "<<solvedCount<<endl;
        cout<<"Unsolved Problems   : "<<problems.size()-solvedCount<<endl;
        cout<<"Favorite Problems   : "<<favoriteCount<<endl;
        cout<<"Most Solved Topic   : "<<bestTopic<<endl;

        cout<<fixed<<setprecision(2);

        cout<<"\nOverall Success Rate : "
            <<successRate<<"%\n";

        int filled = (int)(successRate / 5);

        cout << "\n========== Progress ==========\n\n";

        for(int i = 0; i < 20; i++){

            if(i < filled)
                cout << "█";
            else
                cout << "░";
        }

        cout << "\n\n"
            << fixed
            << setprecision(2)
            << successRate
            << "% Completed\n";

        cout<<"\n========== Difficulty Distribution ==========\n";

        for(auto &it:difficultyCount){

            double percent =
                (it.second*100.0)/problems.size();

            cout<<left
                <<setw(10)
                <<it.first
                <<": "
                <<it.second
                <<" ("
                <<fixed
                <<setprecision(1)
                <<percent
                <<"%)\n";
        }

        cout<<"\n============= Goal Progress =============\n";

        cout<<"Solved : "
            <<solvedCount
            <<" / "
            <<goal
            <<endl;

        if(goal>0){

            double goalPercent=
                solvedCount*100.0/goal;

            cout<<"Completion : "
                <<fixed
                <<setprecision(2)
                <<goalPercent
                <<"%\n";
        }

        cout<<"=========================================\n";
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

        if(goal==0){

            cout<<"\nNo goal has been set yet!\n";
            continue;
        }

        int solvedCount=0;

        for(auto &p:problems){

            if(p.solved)
                solvedCount++;
        }

        double progress=(solvedCount*100.0)/goal;

        if(progress>100)
            progress=100;

        cout<<"\n=========================================================\n";
        cout<<"                     GOAL TRACKER\n";
        cout<<"=========================================================\n\n";

        cout<<"Goal             : "<<goal<<" Problems\n";
        cout<<"Solved           : "<<solvedCount<<" Problems\n";
        cout<<"Remaining        : "<<max(0,goal-solvedCount)<<" Problems\n\n";

        cout<<"Progress\n\n";

        int bars=(progress/100.0)*20;

        cout<<"[";

        for(int i=0;i<20;i++){

            if(i<bars)
                cout<<"■";
            else
                cout<<"□";
        }

        cout<<"] ";

        cout<<fixed<<setprecision(1)
            <<progress<<"%\n";

        cout<<"\n";

        if(progress>=100)
            cout<<"🏆 Congratulations! Goal Achieved!\n";
        else if(progress>=75)
            cout<<"🔥 Almost there! Keep pushing!\n";
        else if(progress>=50)
            cout<<"💪 Great progress! Stay consistent!\n";
        else
            cout<<"🚀 Keep solving problems every day!\n";

        cout<<"\n=========================================================\n";
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

        int filled = 0;

        if(total > 0)
            filled = (solved * 20) / total;

        cout<<"[";

        for(int i=0;i<20;i++){

            if(i < filled)
                cout << "█";
            else
                cout << "░";
        }

        cout<<"] ";

        cout<<fixed<<setprecision(1);

        if(total>0)
            cout<<(solved*100.0/total);
        else
            cout<<0.0;

        cout<<"% ("<<solved<<"/"<<total<<")\n";
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

            if(problems.empty()){
                cout<<"No Problems Added Yet!\n";
                continue;
            }

            int solvedCount=0;
            int favoriteCount=0;

            for(auto &p : problems){

                if(p.solved)
                    solvedCount++;

                if(p.favorite)
                    favoriteCount++;
            }

            double progress=(solvedCount*100.0)/problems.size();

            cout<<"\n=========================================================\n";
            cout<<"                 🏆 ACHIEVEMENTS 🏆\n";
            cout<<"=========================================================\n";

            auto achievement=[](bool unlocked,string name){

                cout<<(unlocked ? "🏆 " : "🔒 ");
                cout<<left<<setw(30)<<name;
                cout<<(unlocked ? "✅" : "❌")<<endl;
            };

            cout<<"\n[ Problem Solving ]\n\n";

            achievement(solvedCount>=1,"First Problem Solved");
            achievement(solvedCount>=10,"10 Problems Solved");
            achievement(solvedCount>=25,"25 Problems Solved");
            achievement(solvedCount>=50,"50 Problems Solved");
            achievement(solvedCount>=100,"Century Club");

            cout<<"\n--------------------------------------------\n";

            cout<<"\n[ Progress ]\n\n";

            achievement(progress>=50,"50% Completion");
            achievement(progress>=75,"75% Completion");
            achievement(progress>=100,"100% Completion");

            cout<<"\n--------------------------------------------\n";

            cout<<"\n[ Collection ]\n\n";

            achievement(favoriteCount>=5,"Favorite Collector");
            achievement(favoriteCount>=10,"Master Collector");

            cout<<"\n--------------------------------------------\n";

            cout<<"\n[ Summary ]\n\n";

            cout<<"Solved      : "<<solvedCount<<" / "<<problems.size()<<endl;
            cout<<"Favorites   : "<<favoriteCount<<endl;

            cout<<fixed<<setprecision(1);
            cout<<"Completion  : "<<progress<<"%\n";

            cout<<"\n--------------------------------------------\n";

            if(progress==100)
                cout<<"\n🏆 Congratulations! You've completed every problem!\n";
            else if(progress>=75)
                cout<<"\n🔥 Excellent! You're very close to full completion!\n";
            else if(progress>=50)
                cout<<"\n💪 Great job! Keep solving!\n";
            else
                cout<<"\n🚀 Keep practicing and unlock more achievements!\n";

            cout<<"\n=========================================================\n";
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

        vector<string> suggestions=
        trie.getSuggestions(prefix);

        if(suggestions.empty()){

            cout<<"No Problems Found!\n";
            continue;
        }

        cout<<"\n==== Suggestions ====\n\n";

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