#pragma once

#include "Component.h"
#include <memory>

class LevelUpdate;
class PlayerUpdate;

class Update : public Component
{
public:
    Update();
    virtual void assemble(
        std::shared_ptr<LevelUpdate> levelUpdate,
        std::shared_ptr<PlayerUpdate> playerUpdate) = 0;
    virtual void update(float timeSinceLastUpdate) = 0;
};
