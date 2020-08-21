#pragma once

#include "Fighter.h"
#include "Clothes.h"
#include <iosfwd>
#include <vector>

class Player: public Fighter {
 public:
    Player();
    ~Player() override = default;
    bool TakeHit(int dmg) override;
    int PutDmg() override;
    int GetPlayerHp() const;
    int GetPlayerArm() const;
    Clothes GetClothes(int i);
    size_t GetClothesSize();
    int PickClothes(const Clothes& clothes);
    void ThrowClothes(const Clothes& clothes);
    size_t GetXPosition() const;
    size_t GetYPosition() const;
    void Move(size_t x, size_t y);
    bool IsFighting() const;
    void Fighting(bool isFighting);
    bool IsTaking() const;
    void Taking(bool isTaking);

 private:
    int playerHp;
    int playerDmg;
    int playerWgt;
    int playerArm;
    static const int playerMaxWgt = 20;
    std::vector<Clothes> playerClothes;
    size_t x;
    size_t y;
    bool isFighting;
    bool isTaking;
};
