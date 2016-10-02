#pragma once

#include "Box2D/Collision/Shapes/b2CircleShape.h"

#include "collider.h"

namespace og
{
class Entity;

class CircleCollider : public og::Collider
{
public:
    CircleCollider(float a_radius, const og::Entity* a_entity);

private:
    bool OverlapPoint(const QVector2D& a_point) const;

private:
    b2CircleShape m_shape;
    const og::Entity* m_entity;
};
}