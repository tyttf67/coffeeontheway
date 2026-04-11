#include <iostream>
#include "coffee.h"
#include "coffeeCategory.h"
#include "myTest.h"
#include "resultTest.h"
#include "user.h"

using namespace std;

int main() {
    cout << "Hello World!" << endl;

    // ==== Тест класу Result ====
    Result r1;          // конструктор без параметрів
    Result r2(3, 'C');  // конструктор з параметрами

    cout << "r1.show():" << endl;
    r1.show();          // покаже 0 і '\0'

    cout << "r2.show():" << endl;
    r2.show();          // покаже 3 і C

    // ==== Можна перевірити через геттери ====
    cout << "r2.getQuestionId(): " << r2.getQuestionId() << endl;
    cout << "r2.getChoice(): " << r2.getChoice() << endl;

    return 0;
}