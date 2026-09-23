// Week3_Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Week 3 Lab 1 — Game Entity Management with "std::vector"
// Nikola Prusac Manahy
// C00309098

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Enemy
{
    int id;
    string name;
    int health;
    int score;
};

void printSection(const string& title)
{
    cout << "\n============================================================\n";
    cout << title << "\n";
    cout << "============================================================\n";
}

void displayIntVector(const vector<int>& values)
{
    cout << "[ ";
    for (int value : values)
        cout << value << " ";
    cout << "]\n";
}

void displayEnemies(const vector<Enemy>& enemies)
{
    cout << left
        << setw(8) << "ID"
        << setw(15) << "Name"
        << setw(10) << "Health"
        << setw(10) << "Score"
        << "\n";
    cout << string(43, '-') << "\n";
    for (const Enemy& e : enemies)
    {
        cout << left
            << setw(8) << e.id
            << setw(15) << e.name
            << setw(10) << e.health
            << setw(10) << e.score
            << "\n";
    }
}

int main()
{
    // Part1
    std::vector<int> scores{ 50, 80, 40, 90 };
    printSection("Task 1.1 -> Display and Inspect");

    for (size_t i = 0; i < scores.size(); i++)
    {
        cout << "Index " << i << ": " << scores[i] << endl;
    }
    cout << "Size: " << scores.size() << endl;
    cout << "Capacity: " << scores.capacity() << endl;

    cout << "Front: " << scores.front() << endl;
    cout << "Back: " << scores.back() << endl;
    cout << "Index 2 (at): " << scores.at(2) << endl;
    cout << "Index 2 ([]): " << scores[2] << endl;

    printSection("Task 1.2 - Add, Remove, Modify");

    scores.push_back(70);
    displayIntVector(scores);
    cout << "Size: " << scores.size() << ", Capacity: " << scores.capacity() << endl;

    scores.push_back(100);
    displayIntVector(scores);
    cout << "Size: " << scores.size() << ", Capacity: " << scores.capacity() << endl;

    scores.pop_back();
    displayIntVector(scores);
    cout << "Size: " << scores.size() << ", Capacity: " << scores.capacity() << endl;

    scores[1] = 85;
    displayIntVector(scores);
    cout << "Size: " << scores.size() << ", Capacity: " << scores.capacity() << endl;

    // Checkpoint: size() = 5, so valid indices are 0, 1, 2, 3, 4 (size() - 1 = 4)

    // Part2
    printSection("Part 2 - Watching Capacity Change");

    vector<int> gameObjects;
    int newValues[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

    for (int v : newValues)
    {
        gameObjects.push_back(v);
        cout << "Added " << v << " -> Size: " << gameObjects.size()
            << ", Capacity: " << gameObjects.capacity() << endl;
    }

    // Q: At which additions did capacity change?
    // A: when we added 50, size became 5 and capacity became 6.
    //    also when we added 70, size became 7 and capacity became 9
    // Q: Why can capacity be larger than size?
    // A: capacity is the space the vector has prepared, size is how many
    //    elements are actually stored.
    // Q: Why should you not assume a fixed growth rule?
    // A: my results went 1,2,3,4,6,6,9,9 - that's not doubling (4->8) and
    //    not +1 each time either.

    printSection("Part 3 - reserve()");

    vector<int> enemyIDs;
    enemyIDs.reserve(20);

    cout << "After reserve(20) -> Size: " << enemyIDs.size()
        << ", Capacity: " << enemyIDs.capacity() << endl;

    for (int id = 101; id <= 110; id++)
    {
        enemyIDs.push_back(id);
        cout << "Added " << id << " -> Size: " << enemyIDs.size()
            << ", Capacity: " << enemyIDs.capacity() << endl;
    }

    // Q1: Did reserve(20) create 20 elements?
    // Answer: no. size is still 0 right after reserve(20), only capacity changed
    // Q2: Why did size remain 0 immediately after reserve(20)?
    // Answer: reserve only prepares storage space, it doesn't add any elements
    // Q3: What benefit did reserve(20) provide while adding IDs?
    // Answer: the vector didn't need to reallocate while pushing the 10 IDs,
    //         since space for 20 was already prepared in advance


    printSection("Part 4 - reserve() vs resize()");

    vector<int> slots;
    slots.reserve(5);
    cout << "After reserve(5) -> Size: " << slots.size()
        << ", Capacity: " << slots.capacity() << endl;

    slots.resize(5);
    cout << "After resize(5) -> Size: " << slots.size()
        << ", Capacity: " << slots.capacity() << endl;
    displayIntVector(slots);

    // reserve() means: prepare storage space, but create no elements. size stays 0
    // resize() means: actually create that many elements. size becomes 5,
    //                  and each new int is set to 0 by default


    printSection("Part 5 - Enemy Vector");

    vector<Enemy> enemies;
    enemies.push_back({ 101, "Goblin", 75, 120 });
    enemies.push_back({ 102, "Orc", 90, 300 });
    enemies.push_back({ 103, "Skeleton", 15, 220 });
    enemies.push_back({ 104, "Mage", 40, 550 });
    enemies.push_back({ 105, "Troll", 100, 450 });
    enemies.push_back({ 106, "Rogue", 18, 700 });

    displayEnemies(enemies);


    printSection("Part 6 - Traverse with Iterator");

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        cout << "ID: " << it->id << ", Name: " << it->name
            << ", Health: " << it->health << ", Score: " << it->score << endl;
    }

    auto it = enemies.begin();
    ++it;
    it->health = 70;

    cout << "After changing second enemy's health:" << endl;
    displayEnemies(enemies);

    // *it represents the whole Enemy object currently pointed to by the iterator

    printSection("Part 7 - Insert and Erase a Boss");

    Enemy boss{ 999, "Dragon", 200, 1500 };
    enemies.insert(enemies.begin(), boss);

    cout << "After inserting boss at begin():" << endl;
    displayEnemies(enemies);

    enemies.erase(enemies.begin());

    cout << "After erasing first element:" << endl;
    displayEnemies(enemies);

    printSection("Part 8 - find_if (health below 20)");

    auto criticalEnemy = find_if(enemies.begin(), enemies.end(),
        [](const Enemy& e)
        {
            return e.health < 20;
        });

    if (criticalEnemy != enemies.end())
    {
        cout << "Critical enemy found -> Name: " << criticalEnemy->name
            << ", Health: " << criticalEnemy->health
            << ", Score: " << criticalEnemy->score << endl;
    }
    else
    {
        cout << "No enemy with health below 20." << endl;
    }


    printSection("Part 9 - find_if with different conditions");

    auto highScore = find_if(enemies.begin(), enemies.end(),
        [](const Enemy& e)
        {
            return e.score > 500;
        });
    if (highScore != enemies.end())
        cout << "Score > 500 -> " << highScore->name << endl;
    else
        cout << "No enemy with score above 500." << endl;

    auto highHealth = find_if(enemies.begin(), enemies.end(),
        [](const Enemy& e)
        {
            return e.health >= 80;
        });
    if (highHealth != enemies.end())
        cout << "Health >= 80 -> " << highHealth->name << endl;
    else
        cout << "No enemy with health at least 80." << endl;

    auto lowHealthHighScore = find_if(enemies.begin(), enemies.end(),
        [](const Enemy& e)
        {
            return e.health < 30 && e.score > 500;
        });
    if (lowHealthHighScore != enemies.end())
        cout << "Health < 30 AND score > 500 -> " << lowHealthHighScore->name << endl;
    else
        cout << "No enemy matches health < 30 and score > 500." << endl;


    printSection("Part 10 - Search by Player Input");

    int searchID;
    cout << "Enter enemy ID to search: ";
    cin >> searchID;

    auto enemyByID = find_if(enemies.begin(), enemies.end(),
        [searchID](const Enemy& e)
        {
            return e.id == searchID;
        });

    if (enemyByID != enemies.end())
    {
        cout << "Found -> ID: " << enemyByID->id << ", Name: " << enemyByID->name
            << ", Health: " << enemyByID->health << ", Score: " << enemyByID->score << endl;
    }
    else
    {
        cout << "Enemy does not exist." << endl;
    }


    printSection("Part 11 - Remove Defeated Enemies");

    enemies[0].health = 0;
    enemies[2].health = -5;
    enemies[4].health = 0;

    size_t oldSize = enemies.size();

    auto newEnd = remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e)
        {
            return e.health <= 0;
        });
    enemies.erase(newEnd, enemies.end());

    size_t newSize = enemies.size();

    cout << "Removed " << (oldSize - newSize) << " defeated enemies." << endl;
    displayEnemies(enemies);


    printSection("Part 12 - Emergency Healing");

    auto healTarget = find_if(enemies.begin(), enemies.end(),
        [](const Enemy& e)
        {
            return e.health > 0 && e.health < 25;
        });

    if (healTarget != enemies.end())
    {
        int oldHealth = healTarget->health;
        healTarget->health += 20;
        if (healTarget->health > 100)
        {
            healTarget->health = 100;
        }

        cout << "Healed " << healTarget->name << " -> Old Health: " << oldHealth
            << ", New Health: " << healTarget->health << endl;
    }
    else
    {
        cout << "No enemy currently needs emergency healing." << endl;
    }

    return 0;
}
