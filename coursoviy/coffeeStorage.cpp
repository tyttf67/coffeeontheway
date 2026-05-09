#include "storage.h"
#include "coffeeCatalog.h"

#include <fstream>
#include <iostream>
#include <cctype>
#include <cstring>

CoffeeStorage::CoffeeStorage(int maxCount) : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) arr_ = new Coffee[maxCount_];
    else maxCount_ = 0;
}

CoffeeStorage::~CoffeeStorage() { delete[] arr_; }

bool CoffeeStorage::saveToFile(const char* fileName) const {
    if (!fileName || !arr_) return false;
    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;

    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;

    for (int i = 0; i < count_; ++i) {
        out.write(reinterpret_cast<const char*>(&arr_[i]), sizeof(Coffee));
        if (!out.good()) return false;
    }

    return true;
}

bool CoffeeStorage::loadFromFile(const char* fileName) {
    count_ = 0;
    if (!fileName || !arr_ || maxCount_ <= 0) return false;

    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open()) return false;

    int countInFile = 0;
    in.read(reinterpret_cast<char*>(&countInFile), sizeof(countInFile));
    if (!in.good() || countInFile < 0 || countInFile > maxCount_) return false;

    for (int i = 0; i < countInFile; ++i) {
        in.read(reinterpret_cast<char*>(&arr_[i]), sizeof(Coffee));
        if (!in.good()) return false;
        if (arr_[i].getId() <= 0 || arr_[i].getCategoryId() < 1 || arr_[i].getCategoryId() > 7) {
            count_ = 0;
            return false;
        }
    }

    count_ = countInFile;
    return true;
}

bool CoffeeStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const { return saveToFile(mainFile) && saveToFile(backupFile); }
bool CoffeeStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) { return loadFromFile(mainFile) || loadFromFile(backupFile); }

bool CoffeeStorage::addCoffee(const Coffee& coffee) {
    if (!arr_ || count_ < 0 || count_ >= maxCount_) return false;
    arr_[count_++] = coffee;
    return true;
}

void CoffeeStorage::loadDefaultsIfEmpty() {
    if (count_ > 0) return;

    int defaultCount = 0;
    const Coffee* defaults = getDefaultCoffees(defaultCount);
    for (int i = 0; i < defaultCount && count_ < maxCount_; ++i) {
        addCoffee(defaults[i]);
    }
}

int CoffeeStorage::findById(int id) const {
    if (!arr_ || count_ <= 0) return -1;
    for (int i = 0; i < count_; ++i) if (arr_[i].getId() == id) return i;
    return -1;
}

const Coffee* CoffeeStorage::getByIndex(int index) const {
    if (!arr_ || index < 0 || index >= count_) return nullptr;
    return &arr_[index];
}

int CoffeeStorage::findByNameContains(const char* query, int indexes[], int maxResults) const { // Я шукаю всі об’єкти Coffee, у яких name містить введений текст без урахування регістру.
    if (!arr_ || count_ <= 0 || !query || query[0] == '\0' || !indexes || maxResults <= 0) return 0;

    char loweredQuery[128];
    int qi = 0;
    for (; query[qi] != '\0' && qi < 127; ++qi) {
        loweredQuery[qi] = static_cast<char>(std::tolower(static_cast<unsigned char>(query[qi])));
    }
    loweredQuery[qi] = '\0';

    int foundCount = 0;
    for (int i = 0; i < count_ && foundCount < maxResults; ++i) {
        const char* name = arr_[i].getName();
        char loweredName[128];
        int ni = 0;
        for (; name[ni] != '\0' && ni < 127; ++ni) {
            loweredName[ni] = static_cast<char>(std::tolower(static_cast<unsigned char>(name[ni])));
        }
        loweredName[ni] = '\0';

        if (std::strstr(loweredName, loweredQuery) != nullptr) {
            indexes[foundCount++] = i;
        }
    }

    return foundCount;
}

bool CoffeeStorage::removeCoffeeById(int id) {
    int pos = findById(id);
    if (pos == -1) return false;
    for (int i = pos; i < count_ - 1; ++i) arr_[i] = arr_[i + 1];
    --count_;
    return true;
}

bool CoffeeStorage::updateCoffee(const Coffee& coffee) {
    int pos = findById(coffee.getId());
    if (pos == -1) return false;
    arr_[pos] = coffee;
    return true;
}

bool CoffeeStorage::searchAndPrintByName(const char* query) const {
    if (!arr_ || count_ <= 0 || !query || query[0] == '\0') return false;

    char loweredQuery[128];
    int qi = 0;
    for (; query[qi] != '\0' && qi < 127; ++qi) {
        loweredQuery[qi] = static_cast<char>(std::tolower(static_cast<unsigned char>(query[qi])));
    }
    loweredQuery[qi] = '\0';

    bool found = false;
    for (int i = 0; i < count_; ++i) {
        const char* name = arr_[i].getName();
        char loweredName[128];
        int ni = 0;
        for (; name[ni] != '\0' && ni < 127; ++ni) {
            loweredName[ni] = static_cast<char>(std::tolower(static_cast<unsigned char>(name[ni])));
        }
        loweredName[ni] = '\0';

        if (std::strstr(loweredName, loweredQuery) != nullptr) {
            arr_[i].show();
            std::cout << "-------------------------\n";
            found = true;
        }
    }

    return found;
}

bool CoffeeStorage::searchAndPrintByName(const char* query, const CoffeeCategoryStorage& categoryStorage) const {
    if (!arr_ || count_ <= 0 || !query || query[0] == '\0') return false;

    char loweredQuery[128];
    int qi = 0;
    for (; query[qi] != '\0' && qi < 127; ++qi) {
        loweredQuery[qi] = static_cast<char>(std::tolower(static_cast<unsigned char>(query[qi])));
    }
    loweredQuery[qi] = '\0';

    bool found = false;
    for (int i = 0; i < count_; ++i) {
        const char* name = arr_[i].getName();
        char loweredName[128];
        int ni = 0;
        for (; name[ni] != '\0' && ni < 127; ++ni) {
            loweredName[ni] = static_cast<char>(std::tolower(static_cast<unsigned char>(name[ni])));
        }
        loweredName[ni] = '\0';

        if (std::strstr(loweredName, loweredQuery) != nullptr) {
            arr_[i].show();
            std::cout << "Group: " << categoryStorage.getNameById(arr_[i].getCategoryId()) << '\n';
            std::cout << "-------------------------\n";
            found = true;
        }
    }

    return found;
}

void CoffeeStorage::printAll() const {
    if (!arr_ || count_ <= 0) { std::cout << "No data\n"; return; }
    for (int i = 0; i < count_; ++i) { arr_[i].show(); std::cout << "----------------\n"; }
}

void CoffeeStorage::printAll(const CoffeeCategoryStorage& categoryStorage) const {
    if (!arr_ || count_ <= 0) { std::cout << "No data\n"; return; }
    for (int i = 0; i < count_; ++i) {
        arr_[i].show();
        std::cout << "Group: " << categoryStorage.getNameById(arr_[i].getCategoryId()) << '\n';
        std::cout << "----------------\n";
    }
}

int CoffeeStorage::getCount() const { return count_; }
