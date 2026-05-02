#include "coffeeCatalog.h"

const Coffee* getDefaultCoffees(int& count) {
    static Coffee coffees[12] = {
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

    count = 12;
    return coffees;
}
