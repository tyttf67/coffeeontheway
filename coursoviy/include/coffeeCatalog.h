#pragma once
#include "coffee.h"

inline const Coffee* getDefaultCoffees(int& count) {
    static const Coffee coffees[] = {
        Coffee(1, 1, "Espresso", "dark", 5, "Pure concentrated coffee shot.", "none", false, false),
        Coffee(2, 2, "Cappuccino", "medium", 3, "Balanced espresso with milk foam.", "none", false, true),
        Coffee(3, 2, "Latte", "light", 2, "Soft coffee with high milk ratio.", "vanilla", true, true),
        Coffee(4, 3, "Americano", "medium", 4, "Espresso diluted with hot water.", "none", false, false),
        Coffee(5, 2, "Flat White", "medium", 4, "Strong taste with velvety milk texture.", "none", false, true),
        Coffee(6, 1, "Ristretto", "dark", 5, "Short and intense espresso extraction.", "none", false, false),
        Coffee(7, 4, "Raf Coffee", "light", 2, "Creamy sweet coffee drink.", "caramel", true, true),
        Coffee(8, 4, "Mocha", "medium", 3, "Coffee with chocolate profile.", "chocolate", true, true),
        Coffee(9, 5, "Frappe", "light", 2, "Cold foamy coffee for summer.", "none", true, true),
        Coffee(10, 5, "Iced Latte", "light", 2, "Cold latte with ice and milk.", "vanilla", true, true),
        Coffee(11, 6, "Affogato", "medium", 3, "Espresso with ice cream dessert style.", "none", true, false),
        Coffee(12, 7, "Cold Brew", "medium", 4, "Slow extraction cold coffee.", "none", false, false)
    };

    count = sizeof(coffees) / sizeof(coffees[0]);
    return coffees;
}
