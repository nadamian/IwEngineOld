#include "IwPhysics\Collision\box_collider.h"

iwphysics::box_collider::box_collider(iwmath::vector3 center, iwmath::vector3 scale)
	: m_min(center - scale / 2), m_max(center + scale / 2)
{
	m_bounds = AABB(center, scale);
}

iwmath::vector3 iwphysics::box_collider::support(
	const iwmath::vector3& direction, 
	const iwmath::vector3& position, 
	const iwmath::quaternion& rotation) const
{
	iwmath::vector3 verts[8]{
		m_min,
		iwmath::vector3(m_min.x, m_max.y, m_min.z),
		iwmath::vector3(m_min.x, m_max.y, m_max.z),
		iwmath::vector3(m_min.x, m_min.y, m_max.z),
		iwmath::vector3(m_max.x, m_min.y, m_max.z),
		m_max,
		iwmath::vector3(m_max.x, m_max.y, m_min.z),
		iwmath::vector3(m_max.x, m_min.y, m_min.z)
	};

	unsigned char maxVert = 0;
	float maxDist = std::numeric_limits<float>::lowest();

	for (unsigned char i = 0; i < 8; i++) {
		iwmath::vector3 vert = verts[i] * rotation + position;
		float dist = vert.dot(vert);
		if (dist > maxDist) {
			maxDist = dist;
			maxVert = i; //TODO: May have to be vert * rot + pos
		}
	}

	return verts[maxVert];
}

float iwphysics::box_collider::volume() const {
	iwmath::vector3 lengths = m_max - m_min;
	return lengths.x * lengths.y * lengths.z;
}
