#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>
#include "groups.h"
#include <iostream>
#include <list>


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

	virtual void reproduce() {}

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

using State = size_t;

class Entity
{
private:

	bool active = true;
	std::vector < std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:

	State state;
	int eaten = 0;
	float energy = 0;
	float speed = 0;
	float sight = 0.0;
	float size = 0.0;

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
	virtual void reproduce() {}

	void draw() {

		if (!components.empty()) {
			for (auto& c : components) c->draw();
		}
		
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
	void switchGroup(Group mGroup);

	std::vector < std::unique_ptr<Component>>& getComponents()
	{
		return components;
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
		c->activate();
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

	std::array<std::list<std::unique_ptr<Entity>>, maxGroups> groupedEntities;

	Manager()
	{
	}

	void update()
	{
		for (Group group = 0u; group < maxGroups; group++) {
			if (!groupedEntities[group].empty()) {
				for (auto& e : groupedEntities[group]) e->update();
			}
		}
	}

	void draw()
	{
		for (Group group = 0u; group < maxGroups; group++) {
			if (!groupedEntities[group].empty()) {
				for (auto& e : groupedEntities[group]) e->draw();
			}
		}
	}

	void refresh()
	{

		for (Group group = 0u; group < maxGroups; group++) {

			if (!groupedEntities[group].empty()) {
				for (auto it = groupedEntities[group].begin(); it != groupedEntities[group].end();) {
					if (!((**it).isActive())) {

					
						it = groupedEntities[group].erase(it);
					}
					else
					{
						++it;
					}
				}
			}
		}
	}

	void addToGroup(Entity* mEntity, Group mGroup)
	{
		std::unique_ptr<Entity> uPtr{ mEntity };
		groupedEntities[mGroup].emplace_back(std::move(uPtr));
	}


	std::list<std::unique_ptr<Entity>>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	template <typename T, typename... TArgs>
	T* addEntity(Group group)
	{
		T* e(new T());
		e->setManager(this);
		e->init();
		std::unique_ptr<Entity> uPtr{ e };
		groupedEntities[group].emplace_back(std::move(uPtr));
		return e;
	}

};


