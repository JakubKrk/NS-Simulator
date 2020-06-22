#pragma once
#include "ECS.h"
#include "Components.h"


static enum blobstates : std::size_t
{
    reproducing,
    surviving,
    hunting,
    dead,
};


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
    }

    void init() override
    {
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
        this->state == hunting;
    }

    void speak() override
    {
        std::cout << "Blob is speaking!" << std::endl;
    }

    
    void init() override
    {
        energy = Game::startingEnergy;
        eaten = 1.0;
        speed = 1.0;
        sight = 1.0;
        size = 1.0;
        this->state = hunting;
        addComponent<TransformComponent>(0, 0, 128, 128, size*0.25);
        addComponent<SpriteComponent>("assets/blob_anim.png", true);
        addComponent<ColliderComponent>("blob");
        addComponent<RandomWalkComponent>(30.00);
        addComponent<SightComponent>();
        //addComponent<SightAreaComponent>("assets/sightarea.png");
        addComponent<MovementSpriteChanger>();
        addComponent<DestinationComponent>();
        addComponent<ColorChangeComponent>();
        getComponent<ColorChangeComponent>().updateColor();
        getComponent<DestinationComponent>().deactivate();
        getComponent<MovementSpriteChanger>().activate();
        getComponent<TransformComponent>().activate();
        getComponent<TransformComponent>().velocity.setAngle(0);

    }

};