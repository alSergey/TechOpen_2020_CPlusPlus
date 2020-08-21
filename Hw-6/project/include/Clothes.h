#pragma once

#include <string>

class Clothes {
 public:
    explicit Clothes(std::string name = "", int wgt = 0, int arm = 0);
    ~Clothes() = default;
    std::string GetClothesName() const;
    int GetClothesWgt() const;
    int GetClothesArm() const;
    void SetEmpty();
    bool operator==(const Clothes& clothes) const;
 private:
    std::string clothesName;
    int clothesWgt;
    int clothesArm;
};
