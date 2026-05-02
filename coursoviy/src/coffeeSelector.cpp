#include <iostream>
#include <cctype>
#include <cstring>

#include "coffeeSelector.h"
#include "coffeeCatalog.h"

void CoffeeSelector::calculateScores(
    int scores[],
    const Result results[],
    int resultCount,
    const Test tests[],
    int testCount
) const {
    for (int i = 0; i < resultCount; ++i) {
        const int questionId = results[i].getQuestionId();
        const char choice = results[i].getChoice();

        for (int j = 0; j < testCount; ++j) {
            if (tests[j].getId() == questionId) {
                const int coffeeIndex = tests[j].getCoffeeIndexForChoice(choice);
                if (coffeeIndex >= 0) {
                    scores[coffeeIndex] += 1;
                }
                break;
            }
        }
    }
}

Coffee CoffeeSelector::selectBest(
    const Coffee coffees[],
    int coffeeCount,
    const int scores[]
) const {
    int bestIndex = 0;
    for (int i = 1; i < coffeeCount; ++i) {
        if (scores[i] > scores[bestIndex]) {
            bestIndex = i;
        }
    }
    return coffees[bestIndex];
}

void CoffeeSelector::printRecommendedCoffee(const Coffee& coffee) const {
    std::cout << "\n=== Your recommended coffee ===\n";
    coffee.show();
}

void CoffeeSelector::printCoffeeCatalog(const Coffee coffees[], int coffeeCount) const {
    std::cout << "\n=== Coffee cards for main page ===\n";
    for (int i = 0; i < coffeeCount; ++i) {
        std::cout << coffees[i].getId() << ". " << coffees[i].getName()
            << " | Group: " << coffees[i].getCoffeeArray() << '\n';
    }
}

void CoffeeSelector::runTest(
    const Test tests[],
    int testCount,
    const Coffee coffees[],
    int coffeeCount
) const {
    Result results[10];
    int resultCount = (testCount < 10) ? testCount : 10;
    int scores[20] = { 0 };

    for (int i = 0; i < resultCount; ++i) {
        tests[i].show();

        char answer = 0;
        bool valid = false;
        while (!valid) {
            std::cout << "Your answer (A/B/C): ";
            std::cin >> answer;
            answer = static_cast<char>(std::toupper(static_cast<unsigned char>(answer)));

            if (tests[i].getCoffeeIndexForChoice(answer) != -1) {
                valid = true;
            } else {
                std::cout << "Please enter only A, B, or C.\n";
            }
        }

        results[i] = Result(tests[i].getId(), answer);
        std::cout << "-------------------------\n";
    }

    calculateScores(scores, results, resultCount, tests, testCount);
    Coffee best = selectBest(coffees, coffeeCount, scores);
    printRecommendedCoffee(best);
    printCoffeeCatalog(coffees, coffeeCount);
}

void CoffeeSelector::run() const {
    int coffeeCount = 0;
    const Coffee* coffees = getDefaultCoffees(coffeeCount);

    int testCount = 0;
    const Test* tests = getDefaultTests(testCount);
    runTest(tests, testCount, coffees, coffeeCount);
}

void CoffeeSelector::printCoffeeCards() const {
    int coffeeCount = 0;
    const Coffee* coffees = getDefaultCoffees(coffeeCount);

    std::cout << "\n=== Coffee cards ===\n";
    for (int i = 0; i < coffeeCount; ++i) {
        std::cout << coffees[i].getId() << ". "
            << coffees[i].getName()
            << " | Group: " << coffees[i].getCoffeeArray() << '\n';
    }
}

bool CoffeeSelector::showCoffeeCardById(int id) const {
    int coffeeCount = 0;
    const Coffee* coffees = getDefaultCoffees(coffeeCount);

    for (int i = 0; i < coffeeCount; ++i) {
        if (coffees[i].getId() == id) {
            coffees[i].show();
            return true;
        }
    }
    return false;
}

bool CoffeeSelector::searchCoffeeCards(const char* query) const {
    if (query == nullptr || query[0] == '\0') {
        return false;
    }

    int coffeeCount = 0;
    const Coffee* coffees = getDefaultCoffees(coffeeCount);

    char loweredQuery[128];
    int qi = 0;
    for (; query[qi] != '\0' && qi < 127; ++qi) {
        loweredQuery[qi] = static_cast<char>(std::tolower(static_cast<unsigned char>(query[qi])));
    }
    loweredQuery[qi] = '\0';

    bool found = false;
    for (int i = 0; i < coffeeCount; ++i) {
        const char* name = coffees[i].getName();
        char loweredName[128];
        int ni = 0;
        for (; name[ni] != '\0' && ni < 127; ++ni) {
            loweredName[ni] = static_cast<char>(std::tolower(static_cast<unsigned char>(name[ni])));
        }
        loweredName[ni] = '\0';

        if (std::strstr(loweredName, loweredQuery) != nullptr) {
            coffees[i].show();
            std::cout << "-------------------------\n";
            found = true;
        }
    }

    return found;
}
