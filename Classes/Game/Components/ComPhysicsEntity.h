
#ifndef __ComPhysicsBody_h__
#define __ComPhysicsBody_h__

#include "Component.h"
#include "Constants.h"

class ComShipBody;
class ComPhysicsEntity : public ComponentBace {
    
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
        ComPhysicsEntity *com = new ComPhysicsEntity(false, radius, mass, resistance);
        com->autorelease();
        return com;
    }
    
    static ComPhysicsEntity*  createFixed(float radius, cc::Vec2 location) {
        ComPhysicsEntity *com = new ComPhysicsEntity(true ,radius, constants::MaxMass, 0);
        com->setLocation(location);
        com->autorelease();
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
    
    void    setVelocity(const cc::Vec2& v) {
        _velocity = v;
    }
    
    const cc::Vec2&    getVelocity() const {
        return _velocity;
    }
    
    void    setLocation(const cc::Vec2& location)  {
        _location = location;
    }
    
    const cc::Vec2& getLocation() const {
        return _location;
    }
    
    bool    getIsFixed() const {
        return _isFixed;
    }
    
    void setCollisionResistance(float value) {
        _collisionResistance = value;
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
    
    cc::Vec2    _location;
    
    bool        _isFixed = false;
    
    TagSet::TagBit      _physicsEntityMask;
    
    typedef std::pair<cc::Vec2, float>  ForceTimePair;
    std::vector<ForceTimePair>          _constantForces;
};

#endif
