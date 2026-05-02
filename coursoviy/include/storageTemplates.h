#pragma once

#include <string>
#include "binaryStorage.h"
#include "coffee.h"
#include "coffeeCategory.h"
#include "myTest.h"
#include "resultTest.h"
#include "user.h"

// Keys for find/remove/edit
inline int coffeeKey(const Coffee& x) { return x.getId(); }
inline int coffeeCategoryKey(const CoffeeCategory& x) { return x.getId(); }
inline int myTestKey(const Test& x) { return x.getId(); }
inline int resultTestKey(const Result& x) { return x.getQuestionId(); }
inline std::string userKey(const User& x) { return std::string(x.getLogin()); }

// Ready-to-use aliases
using CoffeeBinaryStorage = BinaryStorage<Coffee, int>;
using CoffeeCategoryBinaryStorage = BinaryStorage<CoffeeCategory, int>;
using MyTestBinaryStorage = BinaryStorage<Test, int>;
using ResultTestBinaryStorage = BinaryStorage<Result, int>;
using UserBinaryStorage = BinaryStorage<User, std::string>;
