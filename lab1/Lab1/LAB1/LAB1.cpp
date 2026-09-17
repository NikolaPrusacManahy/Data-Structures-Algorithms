// LAB 1 -> Data Structures & Algorithms - Game Data Analyzer 
// Nikola Prusac Manahy
// C00309098

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T largest(vector<T> values)
{
    T largestValue = values[0];

    for (T value : values)
    {
        if (value > largestValue)
        {
            largestValue = value;
        }
    }

    return largestValue;
}

template <typename T>
T smallest(vector<T> values)
{
    T smallestValue = values[0];

    for (T value : values)
    {
        if (value < smallestValue)
        {
            smallestValue = value;
        }
    }

    return smallestValue;
}

template <typename T>
T total(vector<T> values)
{
    T totalValue = values[0];

    for (T value : values)
    {
        totalValue += value;
    }

    return totalValue;
}

int main()
{
    vector<int> scores = { 120, 450, 230, 900, 340 };

    vector<float> speeds = { 3.5f, 7.2f, 4.8f, 9.1f };

    //int totalVal = 0;
    int count = 0;

    for (int score : scores)
    {
        //totalVal += score;

        if (score > 300)
        {
            count++;
        }

        cout << score << endl;
    }

    cout << "The total is " << total(scores) << endl;
    cout << "There is/are " << count << " score(s) above 300" << endl;

    cout << "Highest score: " << largest(scores) << endl;
    cout << "Smallest score: " << smallest(scores) << endl;

    cout << "Fastest speed: " << largest(speeds) << endl;
    cout << "Slowest speed: " << smallest(speeds) << endl;

    return 0;
}

