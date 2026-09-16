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
    std::vector<int> scores
    {
     4200, 1800, 7600, 3500, 5900,
     2400, 8100, 4600, 3500, 6700
    };


    // Task 1
    cout << "Original scores: ";

    for (int s : scores)
    {
        cout << s << " ";
    }
    cout << endl;

    cout << "Number of scores: " << scores.size() << endl;
    cout << "First score: " << scores[0] << endl;
    cout << "Is empty: " << scores.empty() << endl;

    // Task 2
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

    // Q3A: std::sort is preferable here because it is already tested,
    // optimised and far less likely to contain bugs than a hand-written
    // sort..
}

