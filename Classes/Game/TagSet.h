
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
    
    static TagSet& get(const std::string& tagName) {
        auto it = _sTagMap->find(tagName);
        if (it != _sTagMap->end()) {
            return *it->second;
        }
        TagSet *t = new TagSet(tagName);
        _sTagMap->insert(std::make_pair(tagName, t));
        return *t;
    }
    
    static const TagBit getBit(const std::string& tagName) {
        return get(tagName).bit();
    }
    
protected:
    
    TagSet(const std::string& name)
    :_bit(_sNextBit)
    ,_name(name) {
        _sNextBit = _sNextBit << 1;
        assert(_bit != 0 && "BIT_SIZE is not enough");
    }
    
    //init the static null and all
    TagSet() :_bit(0) ,_name("null"){
        if (_sTagMap == nullptr) {
            _sTagMap = new std::map<std::string, TagSet*>;
        }
        if (_sTagMap->find("null") == _sTagMap->end()) {
            _sTagMap->insert(std::make_pair(_name, this));
        } else {
            assert(!"error");
        }
    }
    
    TagBit                  _bit;
    std::string             _name;
    
    static TagBit                           _sNextBit;
    static std::map<std::string, TagSet*>*  _sTagMap;
    
public:
    
    const static TagSet null;
};

#endif
