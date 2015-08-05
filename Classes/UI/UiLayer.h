
#ifndef __UiLayer_h__
#define __UiLayer_h__

#include "cocos.h"

#include "Radar.h"

class UiLayer : public cc::Layer {
    
public:
    
    virtual bool init();
    
    void onRadarButtonClicked(cc::Ref*);
    
    CREATE_FUNC(UiLayer);
    
protected:
    cc::RefPtr<Radar> _radar = nullptr;
};

#endif
