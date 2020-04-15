#pragma once
#include "ECS.h"
#include "Components.h"

class Food : public Entity
{

public:

    Manager* manager;


    Food() {}
    Food(Manager* mManager) {
        manager = mManager;
    }

    void speak() override
    {
        std::cout << "Food is speaking!" << std::endl;
    }

    void init() override
    {
        std::cout << "Food is speaking!" << std::endl;
        addGroup(groupFood);
        addComponent<TransformComponent>(0, 0, 128, 128, 0.125);
        addComponent<SpriteComponent>("assets/apple.png");
        addComponent<ColliderComponent>("apple");
    }

};
class Blob : public Entity
{

public:

    Manager* manager;


    Blob() {}
    Blob(Manager* mManager) {
        manager = mManager;
    }

    void speak() override
    {
        std::cout << "Blob is speaking!" << std::endl;
    }

    void init() override
    {
        addGroup(groupBlobsActive);
        energy = 1000;
        addComponent<TransformComponent>(0, 0, 128, 128, 0.25);
        addComponent<SpriteComponent>("assets/blob_anim.png", true);
        addComponent<ColliderComponent>("blob");
        addComponent<RandomWalkComponent>(45.00);
        addComponent<MovementSpriteChanger>();
        getComponent<TransformComponent>().speed = 3;
        getComponent<TransformComponent>().activate();
        getComponent<TransformComponent>().velocity.setAngle(0);
    }

};