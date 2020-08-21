#include "Clothes.h"
#include <utility>

Clothes::Clothes(std::string name, int wgt, int arm)
    : clothesName(std::move(name))
    , clothesWgt(wgt)
    , clothesArm(arm) {
}

std::string Clothes::GetClothesName() const {
    return clothesName;
}

int Clothes::GetClothesWgt() const {
    return clothesWgt;
}

int Clothes::GetClothesArm() const {
    return clothesArm;
}

void Clothes::SetEmpty() {
    clothesName = "";
    clothesWgt = 0;
    clothesArm = 0;
}

bool Clothes::operator==(const Clothes& clothes) const {
    return this->GetClothesName() == clothes.GetClothesName();
}
