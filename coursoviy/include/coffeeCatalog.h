#pragma once
#include "coffee.h"

inline const Coffee* getDefaultCoffees(int& count) {
    static const Coffee coffees[] = {
        Coffee(1,  1, "Еспресо",       "dark",   5, "Концентрований класичний шот. Чистий смак кави без домішок.", "none",      false, false),
        Coffee(2,  2, "Капучіно",      "medium", 3, "Збалансований еспресо з повітряною молочною пінкою.", "none",      false, true),
        Coffee(3,  2, "Лате",          "light",  2, "М'яка кава з великою кількістю молока. Ніжна та кремова.", "vanilla",   true,  true),
        Coffee(4,  3, "Американо",     "medium", 4, "Еспресо розбавлений гарячою водою. Класика на кожен день.", "none",      false, false),
        Coffee(5,  2, "Флет Вайт",     "medium", 4, "Насичений смак з оксамитовою текстурою молока.", "none",      false, true),
        Coffee(6,  1, "Рістрето",      "dark",   5, "Короткий та інтенсивний шот еспресо. Для справжніх поціновувачів.", "none",      false, false),
        Coffee(7,  4, "Раф Кава",      "light",  2, "Вершкова солодка кава з карамельним відтінком.", "caramel",   true,  true),
        Coffee(8,  4, "Моко",          "medium", 3, "Кава з шоколадним профілем та молоком.", "chocolate", true,  true),
        Coffee(9,  5, "Фрапе",         "light",  2, "Холодна пінна кава для спекотного дня.", "none",      true,  true),
        Coffee(10, 5, "Айс Лате",      "light",  2, "Холодний лате з льодом та молоком.", "vanilla",   true,  true),
        Coffee(11, 6, "Аффогато",      "medium", 3, "Еспресо з морозивом — справжній десерт.", "none",      true,  false),
        Coffee(12, 7, "Колд Брю",      "medium", 4, "Повільна холодна екстракція. М'який та освіжаючий смак.", "none",      false, false)
    };

    count = sizeof(coffees) / sizeof(coffees[0]);
    return coffees;
}