#pragma once

#include "Component.h"
#include "GameObject.h"
#include <vector>
#include "Math\Vector3.h"

class Collider : public Component {
private:
	std::vector <Math::Vector3> position; 
public:
	Collider(GameObject& gameObject) : Component(gameObject) {}
};