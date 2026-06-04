#pragma once

#include "coffee.h"
#include "coffeeCategory.h"
#include "myTest.h"
#include "resultTest.h"

class CoffeeCategoryStorage;

class CoffeeSelector {
public:
    void run(const CoffeeCategoryStorage& categoryStorage) const;
    void printCoffeeCards(const CoffeeCategoryStorage& categoryStorage) const;

    void runTest(
        const Test tests[],
        int testCount,
        const Coffee coffees[],
        int coffeeCount,
        const CoffeeCategoryStorage& categoryStorage
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

    void printRecommendedCoffee(const Coffee& coffee, const CoffeeCategoryStorage& categoryStorage) const;
    void printCoffeeCatalog(const Coffee coffees[], int coffeeCount, const CoffeeCategoryStorage& categoryStorage) const;
};