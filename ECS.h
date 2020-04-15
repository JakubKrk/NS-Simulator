#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>
#include "groups.h"
#include <iostream>


//#include "Components.h"

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

class Component
{
public:
	Entity* entity;

	virtual void init(){

	}
	virtual void update() {

	}
	virtual void draw() {

	}
	void activate()
	{
		active = true;
	}
	void deactivate()
	{
		active = false;
	}
	bool isActive()
	{
		return active;
	}

	virtual ~Component(){}
private:
	bool active;
};

class Entity
{
private:

	bool active = true;
	std::vector < std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:

	int eaten = 0;
	float energy = 0;
	Manager* manager;

	Entity() {}
	Entity(Manager* mManager)
	{
		manager = mManager;
	}
	void setManager(Manager* mManager)
	{
		manager = mManager;
	}
	void update()
	{
		for (auto& c : components) c->update();
	}

	virtual void init(){}

	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}
	
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	virtual void speak()
	{
		std::cout << "Entity is speaking!" << std::endl;
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;

	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast <T*>(ptr);
	}
};


class Manager
{
public:

	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

	Manager()
	{
	}

	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive();
					}),
				std::end(v));
		}
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void addToGroup(Entity* mEntity, Group mGroup)
	{
		//std::unique_ptr<Entity> uPtr{ mEntity };
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*> getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}
	

	template <typename T, typename... TArgs>
	T* addEntity(TArgs&&... mArgs)
	{
		T* e(new T());
		e->setManager(this);
		e->init();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return e;
	}

};


