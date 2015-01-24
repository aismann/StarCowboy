
#ifndef __GameObjectType_h__
#define __GameObjectType_h__

#include <string>
#include <bitset>
#include <map>
#include <assert.h>

class TagSet {
    
    enum {
        BIT_SIZE = 64
    };
    
public:
    
    typedef std::bitset<BIT_SIZE> TagBit;
    
    const std::bitset<BIT_SIZE> bit() const {
        return _bit;
    }
    
    const std::string& name() const {
        return _name;
    }
    
    static TagSet& get(const std::string& typeName) {
        auto it = _sTagMap->find(typeName);
        if (it != _sTagMap->end()) {
            return *it->second;
        }
        TagSet *t = new TagSet(typeName);
        _sTagMap->insert(std::make_pair(typeName, t));
        return *t;
    }
    
    static const TagBit getBit(const std::string& typeName) {
        return get(typeName).bit();
    }
    
protected:
    
    TagSet(const std::string& name)
    :_bit(_sNextBit)
    ,_name(name){
        _sNextBit = _sNextBit << 1;
        assert(_bit != 0 && "BIT_SIZE is not enough");
    }
    
    //init the static null type
    TagSet() :_bit(0) ,_name("null"){
        if (_sTagMap == nullptr) {
            _sTagMap = new std::map<std::string, TagSet*>;
        }
        _sTagMap->insert(std::make_pair(_name, this));
    }
    
    TagBit                  _bit;
    std::string             _name;
    
    static TagBit                           _sNextBit;
    static std::map<std::string, TagSet*>*  _sTagMap;
    
public:
    
    const static TagSet null;
};

#endif
