//
//  Counter.h
//  StarCowboy
//
//  Created by match5 on 15/3/25.
//
//

#ifndef __Counter_h__
#define __Counter_h__

template <typename T>
class Counter {
    
public:
    
    Counter() = default;
    
    Counter(T count)
    :_count(count){
    }
    
    void reset(T count) {
        _count = count;
        _current = 0;
    }
    
    void reset() {
        _current = 0;
    }
    
    bool increase(T d) {
        _current += d;
        if (_current >= _count) {
            return true;
        }
        return false;
    }
    
    T getCurrent() const {
        return _current;
    }
    
    T getTotal() const {
        return _count;
    }
    
    float getPercent() const {
        return _current / (float)_count;
    }
    
    bool isFinish() {
        return _current >= _count;
    }
    
protected:
    
    T _current = 0;
    T _count = 0;
};

#endif
