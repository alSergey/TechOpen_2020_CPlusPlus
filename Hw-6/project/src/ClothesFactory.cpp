#include "ClothesFactory.h"

ClothesFactory &ClothesFactory::GetInstance() {
    static ClothesFactory instance;
    instance.clothesKeyMap.insert(std::make_pair("T-Shirt", std::function<Clothes()>(GetTShirt)));
    instance.clothesKeyMap.insert(std::make_pair("armor",   std::function<Clothes()>(GetArmor)));
    instance.clothesKeyMap.insert(std::make_pair("helmet",  std::function<Clothes()>(GetHelmet)));
    instance.clothesKeyMap.insert(std::make_pair("shield",  std::function<Clothes()>(GetShield)));
    instance.clothesKeyMap.insert(std::make_pair("pants",   std::function<Clothes()>(GetPants)));
    return instance;
}

Clothes ClothesFactory::GetClothes(const std::string& name) {
    if (clothesKeyMap.find(name) == clothesKeyMap.end()) {
        return Clothes("", 0, 0);
    }

    return clothesKeyMap[name]();
}

Clothes ClothesFactory::GetTShirt() {
    return Clothes("T-Shirt", 1, 1);
}

Clothes ClothesFactory::GetArmor() {
    return Clothes("armor", 3, 3);
}

Clothes ClothesFactory::GetHelmet() {
    return Clothes("helmet", 2, 3);
}

Clothes ClothesFactory::GetShield() {
    return Clothes("shield", 7, 5);
}

Clothes ClothesFactory::GetPants() {
    return Clothes("pants", 1, 1);
}
