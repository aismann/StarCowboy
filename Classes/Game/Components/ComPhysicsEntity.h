
#ifndef __ComPhysicsBody_h__
#define __ComPhysicsBody_h__

#include "ComEntity.h"
#include "Constants.h"

class ComShipBody;
class ComPhysicsEntity : public ComEntity {
    
    struct CollisionTargetInfo {
        cc::Vec2    velocity;
        cc::Vec2    location;
        float       mass;
    };

    ComPhysicsEntity( bool fixed, float radius, float mass, float resistance)
    :_isFixed(fixed)
    ,_radius(radius)
    ,_mass(mass)
    ,_resistance(resistance)
    ,_collisionResistance(constants::DefaultCollisionResistanceFactor){}
    
public:
    
    virtual ~ComPhysicsEntity() override {}

    static ComPhysicsEntity*  create(float radius, float mass = 1, float resistance = constants::DefaultAirResistanceFactor) {
        ComPhysicsEntity *com = NewEx(ComPhysicsEntity, false, radius, mass, resistance);
        return com;
    }
    
    static ComPhysicsEntity*  createFixed(float radius, cc::Vec2 location) {
        ComPhysicsEntity *com = NewEx(ComPhysicsEntity, true ,radius, constants::MaxMass, 0);
        com->setLocation(location);
        return com;
    }
    
    void appliedInstantaneousForce(const cc::Vec2& force) {
        _constantForces.push_back(std::make_pair(force, 0.001));
    }
    
    void appliedConstantForce(const cc::Vec2& force, float lastTime) {
        _constantForces.push_back(std::make_pair(force, lastTime));
    }
    
    float   getRadius() const {
        return _radius;
    }
    
    float   getMass() const {
        return _mass;
    }
    
    ComPhysicsEntity*    setVelocity(const cc::Vec2& v) {
        _velocity = v;
        return this;
    }
    
    const cc::Vec2&    getVelocity() const {
        return _velocity;
    }
    
    bool    getIsFixed() const {
        return _isFixed;
    }
    
    ComPhysicsEntity* setCollisionResistance(float value) {
        _collisionResistance = value;
        return this;
    }
    
    const float getCollisionResistance() const {
        return _collisionResistance;
    }

protected:

    virtual void start() override;
    virtual void update(float dt) override;
    
    virtual void onMessage(const GameMessage& msg) override;
    
    cc::Vec2    calculateForce(float dt);
    
    float       _radius = 0;
    
    float       _mass = 0;
    float       _resistance = 0;
    float       _collisionResistance = 0;
    
    cc::Vec2    _force;
    cc::Vec2    _velocity;
    
    bool        _isFixed = false;
    
    TagSet::TagBit      _physicsEntityMask;
    
    typedef std::pair<cc::Vec2, float>  ForceTimePair;
    std::vector<ForceTimePair>          _constantForces;
};

#endif
