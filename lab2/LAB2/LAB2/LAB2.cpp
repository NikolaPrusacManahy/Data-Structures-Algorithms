// LAB2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// NIKOLA PRUSAC MANAHY
// C00309098

// LAB 1 & 2 for Data Structure & AI Algorithm -- Applied STL Challenge

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
    // optimised and far less likely to contain bugs than a hand-written sort

    // task 4
    int searchValue;
    cout << "Enter a score to search for: ";
    cin >> searchValue;

    auto foundIt = std::find(scores.begin(), scores.end(), searchValue);

    if (foundIt != scores.end())
    {
        cout << "Score found." << endl;
    }
    else
    {
        cout << "Score not found." << endl;
    }

    // Task 5 - Process every score with a lambda
    std::cout << "All scores (for_each): ";
    std::for_each(scores.begin(), scores.end(), [](int n) {
        std::cout << n << " ";
        });
    std::cout << std::endl;

    std::cout << "All scores with points label: ";
    std::for_each(scores.begin(), scores.end(), [](int n) {
        std::cout << n << " points ";
        });
    std::cout << std::endl;

    // int& parameter modifies each element in place
    std::for_each(scores.begin(), scores.end(), [](int& n) {
        n += 250;
        });

    std::cout << "Scores after 250-point bonus: ";
    std::for_each(scores.begin(), scores.end(), [](int n) {
        std::cout << n << " ";
        });
    std::cout << std::endl;



    // Task 6 - Build one complete report
    std::cout << std::endl << "Reports" << std::endl;

    std::cout << std::endl << "Original Scores" << std::endl;
    std::cout << "(see Task 1 output above)" << std::endl;

    std::cout << std::endl << "Leaderboard" << std::endl;
    std::for_each(scores.begin(), scores.end(), [](int n) {
        std::cout << n << " ";
        });
    std::cout << std::endl;

    std::cout << std::endl << "Search Result" << std::endl;
    std::cout << (foundIt != scores.end() ? "Score found." : "Score not found.") << std::endl;

    std::cout << std::endl << "After Bonus" << std::endl;
    std::for_each(scores.begin(), scores.end(), [](int n) {
        std::cout << n << " ";
        });
    std::cout << std::endl;


}

