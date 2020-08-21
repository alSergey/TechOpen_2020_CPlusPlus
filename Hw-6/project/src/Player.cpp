#include "Player.h"
#include <algorithm>

Player::Player()
    : playerHp(100)
    , playerDmg(1)
    , playerWgt(0)
    , playerArm(0)
    , playerClothes(5)
    , x(0)
    , y(0)
    , isFighting(false)
    , isTaking(false) {
}

bool Player::TakeHit(int getDmg) {
    if (playerArm >= getDmg) {
        playerHp -= 1;
    } else {
        playerHp -= (getDmg - playerArm);
    }

    return playerHp <= 0;
}

int Player::PutDmg() {
    return playerDmg;
}

int Player::GetPlayerHp() const {
    return playerHp;
}

int Player::GetPlayerArm() const {
    return playerArm;
}

Clothes Player::GetClothes(int i) {
    return playerClothes[i];
}

size_t Player::GetClothesSize() {
    return playerClothes.size();
}

static bool ClothesCmp(const Clothes& lhs, const Clothes& rhs) {
    return lhs.GetClothesName() < rhs.GetClothesName();
}

int Player::PickClothes(const Clothes& clothes) {
    if ((clothes.GetClothesWgt() + playerWgt) > playerMaxWgt) {
        return -1;
    }

    playerClothes.push_back(clothes);
    playerWgt += clothes.GetClothesWgt();
    playerArm += clothes.GetClothesArm();

    std::sort(playerClothes.begin(), playerClothes.end(), ClothesCmp);

    return 0;
}

void Player::ThrowClothes(const Clothes &clothes) {
    auto throwClothes = std::find(playerClothes.begin(), playerClothes.end(), clothes);
    playerWgt -= throwClothes->GetClothesWgt();
    playerArm -= throwClothes->GetClothesArm();

    playerClothes.erase(throwClothes);

    std::sort(playerClothes.begin(), playerClothes.end(), ClothesCmp);
}

size_t Player::GetXPosition() const {
    return x;
}

size_t Player::GetYPosition() const {
    return y;
}

void Player::Move(size_t getX, size_t getY) {
    this->x += getX;
    this->y += getY;
}

bool Player::IsFighting() const {
    return isFighting;
}

void Player::Fighting(bool isFighting) {
    this->isFighting = isFighting;
}

bool Player::IsTaking() const {
    return isTaking;
}

void Player::Taking(bool isTaking) {
    this->isTaking = isTaking;
}

