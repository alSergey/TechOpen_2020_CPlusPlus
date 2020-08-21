#pragma once

class Fighter {
 public:
    virtual ~Fighter() = default;
    virtual bool TakeHit(int dmg) = 0;
    virtual int PutDmg() = 0;
};
