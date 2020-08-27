//
// Created by tsv on 18.04.19.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H


#include <memory>

class GameObject {
public:
    GameObject();

    uint get_id() const;

    virtual
    void update(float dt) = 0;

protected:
    uint m_id;

private:
    static uint next_id;
};

using GameObjectPtr = std::shared_ptr<GameObject>;

#endif //GAME_GAMEOBJECT_H
