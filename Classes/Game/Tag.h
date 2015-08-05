
#ifndef __GameObjectType_h__
#define __GameObjectType_h__

#include <string>
#include <bitset>
#include <map>
#include <assert.h>

class Tag {
    
    enum {
        BIT_SIZE = sizeof(int) * 8
    };
    
public:
    
    typedef std::bitset<BIT_SIZE> Bit;
    
    const std::bitset<BIT_SIZE> bit() const {
        return _bit;
    }
    
    const std::string& name() const {
        return _name;
    }
    
    static Tag& get(const std::string& tagName) {
        auto it = _sTagMap->find(tagName);
        if (it != _sTagMap->end()) {
            return *it->second;
        }
        Tag *t = new Tag(tagName);
        _sTagMap->insert(std::make_pair(tagName, t));
        return *t;
    }
    
    static const Bit getBit(const std::string& tagName) {
        return get(tagName).bit();
    }
    
protected:
    
    Tag(const std::string& name)
    :_bit(_sNextBit)
    ,_name(name) {
        _sNextBit = _sNextBit << 1;
        assert(_bit != 0 && "BIT_SIZE is not enough");
    }
    
    //init the static null and all
    Tag() :_bit(0) ,_name("null"){
        if (_sTagMap == nullptr) {
            _sTagMap = new std::map<std::string, Tag*>;
        }
        if (_sTagMap->find("null") == _sTagMap->end()) {
            _sTagMap->insert(std::make_pair(_name, this));
        } else {
            assert(!"error");
        }
    }
    
    Bit                 _bit;
    std::string         _name;
    
    static Bit          _sNextBit;
    static std::map<std::string, Tag*>*  _sTagMap;
    
public:
    
    const static Tag null;
};

#endif
