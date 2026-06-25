# LeetCode Progress Tracker

## Overview

A feature-rich C++ console application for tracking, organizing, and analyzing LeetCode problem-solving progress. It helps users manage coding practice efficiently with statistics, analytics, streak tracking, goals, favorites, and persistent file storage.

## Features
- Add, Edit, Delete, and View Problems
- Search Problems (Case-Insensitive)
- Prefix Search using Trie
- Search Problems by Topic
- Advanced Search (Topic + Status)
- Mark Problems as Solved
- Store Solved Date
- Mark Favorite Problems
- Show Favorite Problems
- Show Solved Problems
- Show Unsolved Problems
- Sort Problems by Name
- Sort Problems by Difficulty
- Topic-wise Statistics
- Difficulty-wise Statistics
- Difficulty-wise Solved Statistics
- Progress Percentage Tracking
- Goal Setting & Goal Tracker
- Recent Activity Tracking
- Current Streak Counter
- Topic Weakness Detector
- Problem Recommendation System
- Analytics Dashboard
- Difficulty Heatmap
- Achievement System
- Export Data to CSV
- Persistent Storage using File Handling
- Automatic Data Loading at Startup
- Automatic Data Saving on Exit


## Technologies Used

- Vector
- Map
- Unordered Map
- Trie
- StringStream
- Lambda Functions


## File Structure

```
main.cpp
problems.txt
goal.txt
problems.csv
README.md
```

---

## How to Run

**Compile:** g`++` main.cpp -o `tracker`

**Run:** `./tracker`

## Data Storage

All problem data is stored in: **`problems.txt`**

Goal is stored in: **`goal.txt`**

CSV Export: **`problems.csv`**

## Data Format

```
ProblemName|Difficulty|Topic|SolvedStatus|SolvedDate|Favorite
```

### Example:

```
Two Sum|Easy|Array|1|22-06-2026|1
Coin Change|Medium|DP|0|Not Solved|0
```

## Key Highlights

- Trie-based Prefix Search
- Goal Tracking System
- Coding Streak Calculation
- Analytics Dashboard
- Topic Weakness Detection
- Difficulty Heatmap
- Achievement Unlock System
- CSV Export Support
- Fast Topic Search using Hash Map
- Automatic Data Persistence

## Future Improvements

- Login System
- Password Protection
- Graphical User Interface (GUI)
- Online LeetCode API Integration
- Difficulty-based Daily Challenge
- Progress Charts and Graphs


---

## Author

Aditya Kumar
