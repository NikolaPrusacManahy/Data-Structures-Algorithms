// LAB2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// NIKOLA PRUSAC MANAHY
// C00309098

// LAB 2 for Data Structure & AI Algorithm -- Applied STL Challenge

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> scores
    {
     4200, 1800, 7600, 3500, 5900,
     2400, 8100, 4600, 3500, 6700
    };

    vector<int> originalScores = scores; // snapshot for the report later


    // task 1
    cout << "Original scores: ";

    for (int s : scores)
    {
        cout << s << " ";
    }
    cout << endl;

    cout << "Number of scores: " << scores.size() << endl;
    cout << "First score: " << scores.front() << endl;
    cout << "Is empty: " << scores.empty() << endl;

    // TAsk 2
    auto it = scores.begin();
    cout << "First Value: " << *it << endl;
    ++it;
    cout << "Next Value: " << *it << endl;

    cout << "All scores: ";
    for (auto loopIt = scores.begin(); loopIt != scores.end(); ++loopIt)
    {
        cout << *loopIt << " ";
    }

    cout << endl;

    // task 3
    sort(scores.begin(), scores.end());

    cout << "Sorted scores: "; // ascending
    for (int s : scores)
    {
        cout << s << " ";
    }
    cout << endl;

    reverse(scores.begin(), scores.end());

    cout << "Leaderboard: "; // highest first
    for (int s : scores)
    {
        cout << s << " ";
    }
    cout << endl;

    // Q3A: std::sort is much better here because it is already tested,
    // optimised and far less likely to contain bugs than a hand-written sort

    // task 4
    int searchValue;
    cout << "Enter a score to search for: ";
    cin >> searchValue;

    auto foundIt = find(scores.begin(), scores.end(), searchValue);

    if (foundIt != scores.end())
    {
        cout << "-->Score found!" << endl;
    }
    else
    {
        cout << "-->Score not found!" << endl;
    }

    // tAsk 5
    cout << "All scores: ";
    for_each(scores.begin(), scores.end(), [](int n) {
        cout << n << " ";
        });
    cout << endl;

    cout << "All scores with points label: ";
    for_each(scores.begin(), scores.end(), [](int n) {
        cout << n << " points ";
        });
    cout << endl;

    for_each(scores.begin(), scores.end(), [](int& n) {
        n += 250;
        });

    cout << "Scores after 250-point bonus: ";
    for_each(scores.begin(), scores.end(), [](int n) {
        cout << n << " ";
        });
    cout << endl;



    //   task 6
    cout << endl << "Reports" << endl;

    cout << endl << "Original Scores" << endl;
    for_each(originalScores.begin(), originalScores.end(), [](int n) {
        cout << n << " ";
        });
    cout << endl;

    cout << "Number of scores: " << originalScores.size() << endl;
    cout << "First score: " << originalScores.front() << endl;

    cout << endl << "Leaderboard" << endl;
    for_each(scores.begin(), scores.end(), [](int n) {
        cout << n << " ";
        });
    cout << endl;

    cout << endl << "-Search Result" << endl;
    if (foundIt != scores.end())
    {
        cout << "-->Score found!" << endl;
    }
    else
    {
        cout << "-->Score not found!" << endl;
    }

    return 0;
}