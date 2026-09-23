# Week 3 Lab 2 — Arena Survival: STL Enemy Wave Challenge

Solution and explanation, written against `Week3_Lab2.cpp`. This is the independent/ability-testing lab, so each part below states which STL operation was chosen and why it's the correct one for that requirement — tying back to Lecture 3 (Vector & STL Algorithms) and the lab's own instructions.

## Starter code

The `Enemy` struct and `displayEnemies()` function are copied verbatim from the lab sheet, unchanged, as instructed ("Copy the following starter code. All remaining logic must be completed by you").

---

## Part 1 — Create the Arena and Spawn Wave 1

```cpp
vector<Enemy> enemies;
enemies.reserve(10);
```

`reserve(10)` is used instead of `resize(10)` because the task says "reserve space" — this only prepares storage, it does not create 10 blank enemies (Lecture 3, Slide 10: "reserve() prepares storage capacity in advance; it does not create actual vector elements").

All 8 enemies are added with `push_back()` (Slide 3/4 — `push_back()` adds to the end of the vector).

The unused-capacity check is computed, not hard-coded, per the lab's explicit rule:

```cpp
int unusedCapacity = enemies.capacity() - enemies.size();
if (unusedCapacity >= 1) { ... }
```

This directly follows Slide 9's self-check: "if size = 5 and capacity = 8, can we add one more element without reallocation? Yes" — the same size-vs-capacity comparison, done in code instead of by eye.

## Part 2 — Reinforcement Wave and Capacity Behaviour

Each reinforcement is added one at a time in a loop, recording `size()`/`capacity()` before and after each `push_back()`, then comparing:

```cpp
if (capacityAfter != capacityBefore)
{
    cout << "Reallocation occurred." << endl;
}
```

The lab explicitly warns "Do not assume capacity will double" — matching Slide 9's note that reallocation happens unpredictably and Part 2's own instruction to "observe what your implementation actually reports." No capacity number is assumed or hard-coded; it's read live from `capacity()` each time.

## Part 3 — Player Target Search by ID

```cpp
auto targetIt = find_if(enemies.begin(), enemies.end(),
    [targetID](const Enemy& e) { return e.id == targetID; });
```

`find_if()` is required by the task ("A manual search loop is not allowed"). Since `targetID` is read from `cin` *outside* the lambda, it must be captured — `[targetID]` — for the lambda to use it. This matches Lecture 3 Slide 18's Class Check and the Week 2 lab's Part 10 pattern (`[searchID](const Enemy& e){ ... }`), which is the taught way to pass an outside value into a lambda.

## Part 4 — Iterator Mission: Arena Hazard

```cpp
for (auto it = enemies.begin(); it != enemies.end(); ++it)
{
    if (it->health > 0)
    {
        it->health -= 5;
    }
}
```

The lab explicitly requires an iterator loop here, not an index loop or range-based `for`. This matches Lecture 3 Slide 12 (`auto it = scores.begin(); ... *it = 25;` — reading/modifying through an iterator) and Slide 6 of Week 3's guided Lab 1 (`it->health`, `it->name` for accessing struct fields through an iterator). Only living enemies (`health > 0`) take damage, and health is allowed to drop to 0 or below without being removed yet — cleanup happens later in Part 9, as instructed.

## Part 5 — Critical Enemy Detection

```cpp
auto criticalIt = find_if(enemies.begin(), enemies.end(),
    [](const Enemy& e) { return e.health > 0 && e.health < 20; });
```

Two conditions combined with `&&` inside one lambda — same pattern as Lecture 3 Slide 18 and the Week 3 Lab 1 "health < 30 AND score > 500" task. `find_if()` naturally stops at the *first* match, which is what's required ("does not return every matching enemy").

## Part 6 — High-Value Vulnerable Target

```cpp
auto highValueIt = find_if(enemies.begin(), enemies.end(),
    [](const Enemy& e) { return e.health > 0 && e.health < 30 && e.score >= 500; });
```

Three conditions chained with `&&`. Directly extends the two-condition pattern from Part 5 and Lecture 3 Slide 18 — no new construct, just one more `&&` clause.

## Part 7 — Emergency Healing Decision

```cpp
auto healIt = find_if(enemies.begin(), enemies.end(),
    [](const Enemy& e) { return e.health > 0 && e.health < 25 && e.score >= 500; });

if (healIt != enemies.end())
{
    int oldHealth = healIt->health;
    healIt->health += 20;
    if (healIt->health > 100) { healIt->health = 100; }
    ...
}
```

Same structure as Week 3 Lab 1's Part 12 (Emergency Healing), which used an identical store-old-value → increase → cap-at-100 pattern. Mutating `healIt->health` directly is valid because `find_if()` here is called on a non-`const` iterator range, so the returned iterator can modify the underlying vector — same as Part 4's iterator loop.

## Part 8 — Boss Arrival and Iterator Safety

```cpp
auto selectedEnemy = enemies.begin();
cout << "Selected enemy before boss arrives: " << selectedEnemy->name << endl;

Enemy boss {999, "Ancient Dragon", 250, 5000};
enemies.insert(enemies.begin(), boss);

// selectedEnemy was taken before insert(). insert() may shift every
// element and can even force the vector to reallocate its storage,
// so selectedEnemy could now point at the wrong element or at freed
// memory. It must not be dereferenced after this point.
```

`selectedEnemy` is read once, safely, *before* the insert (so the variable isn't dead code), then deliberately never touched again afterward — exactly what the lab asks for. The explanatory comment matches Lecture 3 Slide 14 word-for-word in concept: "If the vector reallocates its storage, old iterators may point to old memory... do not blindly reuse old iterators," and Slide 13's observation that inserting near the front shifts every following element.

`insert(enemies.begin(), boss)` and `erase(enemies.begin())` are the exact calls shown on Slide 13.

## Part 9 — Defeated Enemy Cleanup

```cpp
size_t sizeBeforeCleanup = enemies.size();

auto newEnd = remove_if(enemies.begin(), enemies.end(),
    [](const Enemy& e) { return e.health <= 0; });
enemies.erase(newEnd, enemies.end());

size_t sizeAfterCleanup = enemies.size();
```

This is the erase-remove idiom exactly as shown on Lecture 3 Slide 20: `remove_if()` rearranges the elements to keep and returns a new logical end; `erase()` then physically removes the leftover tail. The lab explicitly forbids removing enemies one at a time with repeated `erase()` calls — this satisfies that by using the idiom in one pass. The removed count is calculated from the size difference, not guessed.

## Part 10 — Spawn Slot Experiment: reserve() vs resize()

```cpp
vector<int> spawnSlots;
spawnSlots.reserve(5);
// size stays 0, spawnSlots[0] does not exist yet

spawnSlots.resize(5);
// size becomes 5, spawnSlots[0..4] now exist as 0
```

This is a direct repeat of Lecture 3 Slide 11's comparison (`reserve(100)` → size 0, capacity ≥ 100 vs `resize(100)` → size 100, real elements created) and Week 3 Lab 1's Part 4. All three comment answers are filled in based on that slide's explanation rather than guessed.

## Part 11 — Custom Tactical Search

```cpp
int minScore, maxHealth;
cin >> minScore >> maxHealth;

auto tacticalIt = find_if(enemies.begin(), enemies.end(),
    [minScore, maxHealth](const Enemy& e)
    {
        return e.score >= minScore && e.health <= maxHealth && e.health > 0;
    });
```

Two outside variables are needed inside the lambda, so both are placed in the capture list: `[minScore, maxHealth]`. This is the same capture mechanism as Part 3, just capturing two values instead of one — nothing new is introduced, only extended.

## Part 12 — Final Challenge: Prepare the Next Wave

```cpp
size_t currentUnused = enemies.capacity() - enemies.size();

if (currentUnused < 6)
{
    enemies.reserve(enemies.size() + 6);
}
```

The decision is computed from live `size()`/`capacity()` values, not hard-coded, per the lab's "Ability check" rule from Part 1 and the Final Checklist's "final wave capacity decision is computed rather than hard-coded."

`reserve()` is chosen over `resize()` here because the wave hasn't been added yet — `resize()` would immediately create 6 blank `Enemy` objects (all fields zeroed/empty), which would show up in `displayEnemies()` before real data exists. `reserve()` only prepares the space, matching the reasoning from Part 10 and Slide 11's Q&A ("Which one would you use before adding many enemies with push_back()? Answer: use reserve(100)").

The battle summary at the end reuses `find_if()` twice more (first low-health enemy, first enemy scoring above 1000) — same pattern as every earlier search, just applied to new conditions.

---

## Restrictions checklist (from the lab sheet)

| Restriction | How it's satisfied |
|---|---|
| No manual index search where `find_if()` is required | Every search (Parts 3, 5, 6, 7, 11, 12) uses `find_if()` with a lambda |
| No one-by-one enemy removal | Part 9 uses `remove_if()` + `erase()` (erase-remove idiom) |
| No dereferencing a possibly-invalid iterator | `selectedEnemy` in Part 8 is read once before the insert, never after |
| No assumed fixed capacity growth | Part 2 reads and prints actual `capacity()` values instead of predicting them |
| Compiles and runs without errors | Confirmed — compiles clean with `-Wall`, no warnings, exit code 0 |
