#pragma once

#include <fstream>
#include <utility>

// Generic binary storage with all binary I/O inside storage layer.
template <typename T, typename Key>
class BinaryStorage {
public:
    using KeyGetter = Key (*)(const T&);

    explicit BinaryStorage(int maxCount, KeyGetter keyGetter)
        : arr_(nullptr), maxCount_(maxCount), count_(0), keyGetter_(keyGetter) {
        if (maxCount_ > 0) {
            arr_ = new T[maxCount_];
        } else {
            maxCount_ = 0;
        }
    }

    ~BinaryStorage() {
        delete[] arr_;
    }

    BinaryStorage(const BinaryStorage&) = delete;
    BinaryStorage& operator=(const BinaryStorage&) = delete;

    bool saveToFile(const char* fileName) const {
        if (fileName == nullptr || arr_ == nullptr || count_ < 0) {
            return false;
        }

        std::ofstream out(fileName, std::ios::binary);
        if (!out.is_open()) {
            return false;
        }

        out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
        if (!out.good()) {
            return false;
        }

        for (int i = 0; i < count_; ++i) {
            out.write(reinterpret_cast<const char*>(&arr_[i]), sizeof(T));
            if (!out.good()) return false;
        }

        return true;
    }

    bool loadFromFile(const char* fileName) {
        count_ = 0;

        if (fileName == nullptr || arr_ == nullptr || maxCount_ <= 0) {
            return false;
        }

        std::ifstream in(fileName, std::ios::binary);
        if (!in.is_open()) {
            return false;
        }

        int countInFile = 0;
        in.read(reinterpret_cast<char*>(&countInFile), sizeof(countInFile));
        if (!in.good() || countInFile < 0 || countInFile > maxCount_) {
            return false;
        }

        for (int i = 0; i < countInFile; ++i) {
            in.read(reinterpret_cast<char*>(&arr_[i]), sizeof(T));
            if (!in.good()) return false;
        }

        count_ = countInFile;
        return true;
    }

    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const {
        return saveToFile(mainFile) && saveToFile(backupFile);
    }

    bool loadFromAnyFile(const char* mainFile, const char* backupFile) {
        if (loadFromFile(mainFile)) {
            return true;
        }

        return loadFromFile(backupFile);
    }

    bool add(const T& entity) {
        if (arr_ == nullptr || maxCount_ <= 0 || count_ < 0 || count_ >= maxCount_) {
            return false;
        }

        arr_[count_] = entity;
        ++count_;
        return true;
    }

    int findByKey(const Key& key) const {
        if (arr_ == nullptr || count_ <= 0 || keyGetter_ == nullptr) {
            return -1;
        }

        for (int i = 0; i < count_; ++i) {
            if (keyGetter_(arr_[i]) == key) {
                return i;
            }
        }

        return -1;
    }

    bool removeByKey(const Key& key) {
        const int index = findByKey(key);
        if (index == -1) {
            return false;
        }

        for (int i = index; i < count_ - 1; ++i) {
            arr_[i] = arr_[i + 1];
        }

        --count_;
        return true;
    }

    bool editByKey(const Key& key, const T& updatedEntity) {
        const int index = findByKey(key);
        if (index == -1) {
            return false;
        }

        arr_[index] = updatedEntity;
        return true;
    }

    bool removeByIndex(int index) {
        if (arr_ == nullptr || count_ <= 0 || index < 0 || index >= count_) {
            return false;
        }

        for (int i = index; i < count_ - 1; ++i) {
            arr_[i] = arr_[i + 1];
        }

        --count_;
        return true;
    }

    bool editByIndex(int index, const T& updatedEntity) {
        if (arr_ == nullptr || index < 0 || index >= count_) {
            return false;
        }

        arr_[index] = updatedEntity;
        return true;
    }

    const T* data() const { return arr_; }
    T* data() { return arr_; }

    int getCount() const { return count_; }
    int getMaxCount() const { return maxCount_; }

private:
    T* arr_;
    int maxCount_;
    int count_;
    KeyGetter keyGetter_;
};
