
#ifndef __Singleton_h__
#define __Singleton_h__

#include <cstdlib>

template <typename T>
class Singleton {
public:
    
    static T*   getInstance() {
        if (instance_ == nullptr) {
            instance_ = new T;
        }
        return instance_;
    }
    
    static void destroy() {
        if (instance_) {
            delete instance_;
            instance_ = nullptr;
        }
    }
    
protected:
    
    Singleton() = default;
    virtual ~Singleton() = default;
    Singleton(const Singleton&) = default;
    Singleton & operator= (const Singleton &) = default;
    
    static T    *instance_;
};

template<class T>
T* Singleton<T>::instance_ = nullptr;

#endif
