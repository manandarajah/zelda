#include "vec2.hpp"
#include "../graphic/collision.hpp"

#pragma once

class Mob;
class Rectangle {
public:
    Rectangle(float x, float y, float width, float height);

    float x();
    float y();
    vec2f position() const;
    vec2f top_center() const;
    vec2f center() const;
    vec2f bottom_right() const;
    vec2f bottom_right(const vec2f &pos) const;
    float width() const;
    float height() const;

    virtual bool IsHitbox() const;
    virtual bool IsEntity() const;
    virtual bool CanCollideWith(Rectangle* rectangle) const;
    virtual bool CollidesWith(Rectangle* rectangle) const;
    virtual bool HandleCollisionWith(Mob* mob);
    virtual Collision CollisionType(Rectangle* rectangle) const;

    void set_position(const vec2f& position);
    void set_position(float x, float y);
    void Render(float r, float g, float b) const;
    void Print() const;

protected:
    vec2f position_;
    float width_;
    float height_;
};
