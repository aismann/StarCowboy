
#ifndef __ComParticleEmiter__
#define __ComParticleEmiter__

#include "Component.h"

class ComPhysicsEntity;
class ComParticleEmiter : public ComponentBace {
    
    ComParticleEmiter() : _emiter(nullptr) {}
    
public:
    
    virtual ~ComParticleEmiter() override {}
    
    static ComParticleEmiter*  create(cc::ParticleSystem *emiter, cc::ParticleSystem::PositionType pt = cc::ParticleSystem::PositionType::RELATIVE) {
        ComParticleEmiter *com = new ComParticleEmiter;
        com->autorelease();
        com->_emiter = emiter;
        com->_emiter->setPositionType(pt);
        return com;
    }
    
protected:
    
    virtual void start() override;
    virtual void update(float dt) override;
    
    virtual void onLoad() override;
    virtual void onUnload() override;
    
    cc::RefPtr<cc::ParticleSystem>  _emiter;
    ComPhysicsEntity*       _entity = nullptr;
};

#endif