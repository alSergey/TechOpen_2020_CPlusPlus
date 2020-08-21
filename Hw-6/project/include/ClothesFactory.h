#pragma once

#include "Clothes.h"
#include <functional>
#include <string>
#include <map>

class ClothesFactory {
 public:
    Clothes GetClothes(const std::string& name);
    static ClothesFactory& GetInstance();
 private:
    ClothesFactory() = default;
    ~ClothesFactory() = default;
    ClothesFactory(const ClothesFactory&);
    ClothesFactory& operator=(const ClothesFactory&);
    static Clothes GetTShirt();
    static Clothes GetArmor();
    static Clothes GetHelmet();
    static Clothes GetShield();
    static Clothes GetPants();
    std::map<std::string, std::function<Clothes()>> clothesKeyMap;
};
