#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	//group = mGroup;
	manager->addToGroup(this, mGroup);
}


void Entity::switchGroup(Group mGroup)
{
	//manager->switchGroup(this, mGroup);
}
