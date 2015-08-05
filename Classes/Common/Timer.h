//
//  Timer.h
//  StarCowboy
//
//  Created by match5 on 15/3/25.
//
//

#ifndef __Timer_h__
#define __Timer_h__

class Timer {
    
public:
    
    Timer() = default;
    
    Timer(float time)
    :_time(time){
    }
    
    void reset(float time) {
        _time = time;
        _current = 0;
    }
    
    void reset() {
        _current = 0;
    }
    
    bool increase(float dt) {
        _current += dt;
        if (_current >= _time) {
            return true;
        }
        return false;
    }
    
    float getCurrent() {
        return _current;
    }
    
    bool isFire() {
        return _current >= _time;
    }
    
protected:
    
    float _current = 0;
    float _time = 0;
};

#endif
