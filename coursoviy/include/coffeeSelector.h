#pragma once
// подумати як зберіагати історію тестувань та показувати їх  
#include "coffee.h"
#include "coffeeCategory.h"
#include "myTest.h"
#include "resultTest.h"

class CoffeeSelector {
public:
    void run() const;
    void printCoffeeCards() const;

private:
    void runTest(
        const Test tests[],
        int testCount,
        const Coffee coffees[],
        int coffeeCount
    ) const;

    void calculateScores(
        int scores[],
        const Result results[],
        int resultCount,
        const Test tests[],
        int testCount
    ) const;

    Coffee selectBest(
        const Coffee coffees[],
        int coffeeCount,
        const int scores[]
    ) const;

    void printRecommendedCoffee(const Coffee& coffee) const;
    void printCoffeeCatalog(const Coffee coffees[], int coffeeCount) const;
};
