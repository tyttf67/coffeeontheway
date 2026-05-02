#include <iostream>
#include <cctype>
#include <cstring>
#include "coffeeSelector.h"

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
    // First 8 drinks are used in test scoring, extra drinks are informational cards.
    Coffee coffees[12] = {
        Coffee(1, "espresso-based", "Espresso", "dark", 5, "Pure concentrated coffee shot.", "none", false, false),
        Coffee(2, "milk-based", "Cappuccino", "medium", 3, "Balanced espresso with milk foam.", "none", false, true),
        Coffee(3, "milk-based", "Latte", "light", 2, "Soft coffee with high milk ratio.", "vanilla", true, true),
        Coffee(4, "black coffee", "Americano", "medium", 4, "Espresso diluted with hot water.", "none", false, false),
        Coffee(5, "milk-based", "Flat White", "medium", 4, "Strong taste with velvety milk texture.", "none", false, true),
        Coffee(6, "espresso-based", "Ristretto", "dark", 5, "Short and intense espresso extraction.", "none", false, false),
        Coffee(7, "dessert coffee", "Raf Coffee", "light", 2, "Creamy sweet coffee drink.", "caramel", true, true),
        Coffee(8, "dessert coffee", "Mocha", "medium", 3, "Coffee with chocolate profile.", "chocolate", true, true),
        Coffee(9, "cold coffee", "Frappe", "light", 2, "Cold foamy coffee for summer.", "none", true, true),
        Coffee(10, "cold coffee", "Iced Latte", "light", 2, "Cold latte with ice and milk.", "vanilla", true, true),
        Coffee(11, "specialty", "Affogato", "medium", 3, "Espresso with ice cream dessert style.", "none", true, false),
        Coffee(12, "alternative", "Cold Brew", "medium", 4, "Slow extraction cold coffee.", "none", false, false)
    };

    int testCount = 0;
    const Test* tests = getDefaultTests(testCount);
    runTest(tests, testCount, coffees, 12);
}

void CoffeeSelector::printCoffeeCards() const {
    Coffee coffees[12] = {
        Coffee(1, "espresso-based", "Espresso", "dark", 5, "Pure concentrated coffee shot.", "none", false, false),
        Coffee(2, "milk-based", "Cappuccino", "medium", 3, "Balanced espresso with milk foam.", "none", false, true),
        Coffee(3, "milk-based", "Latte", "light", 2, "Soft coffee with high milk ratio.", "vanilla", true, true),
        Coffee(4, "black coffee", "Americano", "medium", 4, "Espresso diluted with hot water.", "none", false, false),
        Coffee(5, "milk-based", "Flat White", "medium", 4, "Strong taste with velvety milk texture.", "none", false, true),
        Coffee(6, "espresso-based", "Ristretto", "dark", 5, "Short and intense espresso extraction.", "none", false, false),
        Coffee(7, "dessert coffee", "Raf Coffee", "light", 2, "Creamy sweet coffee drink.", "caramel", true, true),
        Coffee(8, "dessert coffee", "Mocha", "medium", 3, "Coffee with chocolate profile.", "chocolate", true, true),
        Coffee(9, "cold coffee", "Frappe", "light", 2, "Cold foamy coffee for summer.", "none", true, true),
        Coffee(10, "cold coffee", "Iced Latte", "light", 2, "Cold latte with ice and milk.", "vanilla", true, true),
        Coffee(11, "specialty", "Affogato", "medium", 3, "Espresso with ice cream dessert style.", "none", true, false),
        Coffee(12, "alternative", "Cold Brew", "medium", 4, "Slow extraction cold coffee.", "none", false, false)
    };

    std::cout << "\n=== Coffee cards ===\n";
    for (int i = 0; i < 12; ++i) {
        std::cout << coffees[i].getId() << ". "
            << coffees[i].getName()
            << " | Group: " << coffees[i].getCoffeeArray() << '\n';
    }
}

bool CoffeeSelector::showCoffeeCardById(int id) const {
    Coffee coffees[12] = {
        Coffee(1, "espresso-based", "Espresso", "dark", 5, "Pure concentrated coffee shot.", "none", false, false),
        Coffee(2, "milk-based", "Cappuccino", "medium", 3, "Balanced espresso with milk foam.", "none", false, true),
        Coffee(3, "milk-based", "Latte", "light", 2, "Soft coffee with high milk ratio.", "vanilla", true, true),
        Coffee(4, "black coffee", "Americano", "medium", 4, "Espresso diluted with hot water.", "none", false, false),
        Coffee(5, "milk-based", "Flat White", "medium", 4, "Strong taste with velvety milk texture.", "none", false, true),
        Coffee(6, "espresso-based", "Ristretto", "dark", 5, "Short and intense espresso extraction.", "none", false, false),
        Coffee(7, "dessert coffee", "Raf Coffee", "light", 2, "Creamy sweet coffee drink.", "caramel", true, true),
        Coffee(8, "dessert coffee", "Mocha", "medium", 3, "Coffee with chocolate profile.", "chocolate", true, true),
        Coffee(9, "cold coffee", "Frappe", "light", 2, "Cold foamy coffee for summer.", "none", true, true),
        Coffee(10, "cold coffee", "Iced Latte", "light", 2, "Cold latte with ice and milk.", "vanilla", true, true),
        Coffee(11, "specialty", "Affogato", "medium", 3, "Espresso with ice cream dessert style.", "none", true, false),
        Coffee(12, "alternative", "Cold Brew", "medium", 4, "Slow extraction cold coffee.", "none", false, false)
    };

    for (int i = 0; i < 12; ++i) {
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

    Coffee coffees[12] = {
        Coffee(1, "espresso-based", "Espresso", "dark", 5, "Pure concentrated coffee shot.", "none", false, false),
        Coffee(2, "milk-based", "Cappuccino", "medium", 3, "Balanced espresso with milk foam.", "none", false, true),
        Coffee(3, "milk-based", "Latte", "light", 2, "Soft coffee with high milk ratio.", "vanilla", true, true),
        Coffee(4, "black coffee", "Americano", "medium", 4, "Espresso diluted with hot water.", "none", false, false),
        Coffee(5, "milk-based", "Flat White", "medium", 4, "Strong taste with velvety milk texture.", "none", false, true),
        Coffee(6, "espresso-based", "Ristretto", "dark", 5, "Short and intense espresso extraction.", "none", false, false),
        Coffee(7, "dessert coffee", "Raf Coffee", "light", 2, "Creamy sweet coffee drink.", "caramel", true, true),
        Coffee(8, "dessert coffee", "Mocha", "medium", 3, "Coffee with chocolate profile.", "chocolate", true, true),
        Coffee(9, "cold coffee", "Frappe", "light", 2, "Cold foamy coffee for summer.", "none", true, true),
        Coffee(10, "cold coffee", "Iced Latte", "light", 2, "Cold latte with ice and milk.", "vanilla", true, true),
        Coffee(11, "specialty", "Affogato", "medium", 3, "Espresso with ice cream dessert style.", "none", true, false),
        Coffee(12, "alternative", "Cold Brew", "medium", 4, "Slow extraction cold coffee.", "none", false, false)
    };

    char loweredQuery[128];
    int qi = 0;
    for (; query[qi] != '\0' && qi < 127; ++qi) {
        loweredQuery[qi] = static_cast<char>(std::tolower(static_cast<unsigned char>(query[qi])));
    }
    loweredQuery[qi] = '\0';

    bool found = false;
    for (int i = 0; i < 12; ++i) {
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
}\n
