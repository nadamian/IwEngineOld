#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Math\Vector3.h"

namespace Physics {
	class IWENGINE_API CollisionMesh {
	public:
		CollisionMesh(int count) {
			Math::Vector3* _collider = new Math::Vector3[count];
		}
	};
}