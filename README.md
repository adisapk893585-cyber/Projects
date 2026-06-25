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
- Modular Project Structure
- Fast Prefix Search using Trie


## Technologies Used

- C++
- STL
- Vector
- Map
- Unordered Map
- Trie
- File Handling
- StringStream
- Lambda Functions


## File Structure

```text
LeetCode-Progress-Tracker
│
├── data
│   ├── problems.txt
│   ├── goal.txt
│   └── problems.csv
│
├── include
│   ├── Problem.h
│   ├── Tracker.h
│   ├── Trie.h
│   ├── Utils.h
│   └── FileManager.h
│
├── src
│   ├── main.cpp
│   ├── Tracker.cpp
│   ├── Trie.cpp
│   ├── Utils.cpp
│   └── FileManager.cpp
│
├── README.md
└── .gitignore
```

---

## How to Run

### Compile

```bash
g++ src/*.cpp -I include -o LeetCodeTracker
```

### Run

#### Windows

```bash
LeetCodeTracker.exe
```

#### Linux / macOS

```bash
./LeetCodeTracker
```

## Data Storage

All application data is stored inside the `data/` folder.

- `problems.txt` → Stores all problems
- `goal.txt` → Stores user's goal
- `problems.csv` → Exported CSV file

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

- Modular C++ Project Structure
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
- Database Support (SQLite/MySQL)
- Dark Mode GUI
- Cloud Backup
- Multiple User Profiles


---

## Author

**Aditya Kumar**

- IIT Kharagpur

## Screenshots

### Main Menu

(Add Screenshot)

### Analytics Dashboard

(Add Screenshot)

### Prefix Search

(Add Screenshot)