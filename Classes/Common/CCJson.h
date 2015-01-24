
#ifndef __CCJson_h__
#define __CCJson_h__

#include "cocos2d.h"
#include "cocos2d_namespace_alias.h"
#include "cJSON.h"

namespace json {
    
    class CCJson;
    
    enum class CCJsonType {
        NullObject,
        Dictionary,
        Array,
        String,
        Number,
        Bool,
    };
    
    class CCJsonObject : public cc::Ref {
        
    public:
        bool isNull() { return type() == CCJsonType::NullObject; }
        
        bool isDictionary() { return type() == CCJsonType::Dictionary; };
        bool isArray() { return type() == CCJsonType::Array; };
        bool isString() { return type() == CCJsonType::String; };
        bool isNumber() { return type() == CCJsonType::Number; };
        bool isBool() { return type() == CCJsonType::Bool; };
        
        bool isContainer() { return isDictionary() || isArray(); }
        bool isValue() { return !isContainer() || !isNull(); }
        
        virtual CCJsonType type() = 0;
    };
    
    class CCJsonString : public CCJsonObject {
        
    public:
        static CCJsonString *create(const std::string& value = "") {
            CCJsonString* ret = new CCJsonString(value);
            if (ret != NULL) {
                ret->autorelease();
            }
            return ret;
        }
        
        CCJsonString(const std::string& value) : value_(value) {}
        
        const std::string& value() {
            return value_;
        }
        
        void setValue(const std::string& value) {
            value_ = value;
        }
        
        virtual CCJsonType type() { return CCJsonType::String; }
        
    private:
        std::string value_;
    };
    
    class CCJsonNumber : public CCJsonObject {
        
    public:
        static CCJsonNumber *create(const double value = 0.0) {
            CCJsonNumber* ret = new CCJsonNumber(value);
            if (ret != NULL) {
                ret->autorelease();
            }
            return ret;
        }
        
        CCJsonNumber(const double value) : value_(value) {}
        
        void setValue(const double value) {
            value_ = value;
        }
        
        const int intValue() {
            return value_;
        }
        
        const double doubleValue() {
            return value_;
        }
        
        virtual CCJsonType type() { return CCJsonType::Number; }
        
    private:
        double value_;
    };
    
    class CCJsonBool : public CCJsonObject {
        
    public:
        
        static CCJsonBool *create(const bool value = false) {
            CCJsonBool* ret = new CCJsonBool(value);
            if (ret != NULL) {
                ret->autorelease();
            }
            return ret;
        }
        
        CCJsonBool(const bool value) : value_(value) {}
        
        const bool value() {
            return value_;
        }
        
        void setValue(const bool value) {
            value_ = value;
        }
        
        virtual CCJsonType type() { return CCJsonType::Bool; }
        
    private:
        bool value_;
    };
    
    
    class CCJsonDictionary : public CCJsonObject {
        
    public:
        
        typedef cc::Map<std::string, CCJsonObject*> MapType;
        
        static CCJsonDictionary *create(unsigned int capacity = 1) {
            CCJsonDictionary* ret = new CCJsonDictionary(capacity);
            if (ret != NULL) {
                ret->autorelease();
            }
            return ret;
        }
        
        static CCJsonDictionary *create(const std::string& filePath);
        
        CCJsonDictionary(unsigned int capacity) : map_(capacity) {}
        
        virtual CCJsonType type() { return CCJsonType::Dictionary; }
        
        unsigned int count() { return map_.size(); }
        
        CCJsonObject *objectForKey(const std::string& key) {
            MapType::iterator it = map_.find(key);
            if (it != map_.end()) {
                return map_.find(key)->second;
            }
            return nullptr;
        }
        
        const int intValueForKey(const std::string& key) {
            return static_cast<CCJsonNumber*>(objectForKey(key))->intValue();
        }
        
        const double doubleValueForKey(const std::string& key) {
            return static_cast<CCJsonNumber*>(objectForKey(key))->doubleValue();
        }
        
        const int boolValueForKey(const std::string& key) {
            return static_cast<CCJsonBool*>(objectForKey(key))->value();
        }
        
        const std::string& stringValueForKey(const std::string& key) {
            return static_cast<CCJsonString*>(objectForKey(key))->value();
        }
        
        const char* cstringValueForKey(const std::string& key) {
            return static_cast<CCJsonString*>(objectForKey(key))->value().c_str();
        }
        
        void setObject(CCJsonObject* jObject, const std::string& key) {
            map_.insert(key, jObject);
        }
        
        void removeObjectForKey(const std::string& key) {
            map_.erase(key);
        }
        
        void removeAllObject() {
            map_.clear();
        }
        
        MapType &getCCMap() {
            return map_;
        }
        
    private:
        MapType map_;
    };
    
    class CCJsonArray : public CCJsonObject {
        
    public:
        
        typedef cc::Vector<CCJsonObject*> VectorType;
        
        static CCJsonArray *create(unsigned int capacity = 1) {
            CCJsonArray* ret = new CCJsonArray(capacity);
            if (ret != NULL) {
                ret->autorelease();
            }
            return ret;
        }
        
        static CCJsonArray *create(const std::string& filePath);
        
        CCJsonArray(unsigned int capacity) : vec_(capacity) {
        }
        
        virtual CCJsonType type() { return CCJsonType::Array; }
        
        unsigned int count() const {
            return vec_.size();
        }
        
        CCJsonObject* objectAtIndex(unsigned int index) {
            return vec_.at(index);
        }
        
        CCJsonObject* lastObject() {
            return vec_.back();
        }
        
        void addObject(CCJsonObject* object) {
            vec_.pushBack(object);
        }
        
        void removeObjectAtIndex(unsigned int index) {
            vec_.erase(index);
        }
        
        void removeAllObject() {
            vec_.clear();
        }
        
        VectorType &getCCVector() {
            return vec_;
        }
        
    private:
        VectorType vec_;
    };
    
    class CCJsonNull : public CCJsonObject {
        
    public:
        static CCJsonNull *create() {
            CCJsonNull* ret = new CCJsonNull;
            if (ret != NULL) {
                ret->autorelease();
            }
            return ret;
        }
        
        virtual CCJsonType type() { return CCJsonType::NullObject; }
    };
    
    class CCJson {
        
    public:
        static CCJsonObject *parse(const char *data);
        
        static CCJsonObject *parse(const std::string &data) {
            return parse(data.c_str());
        }
        
        static const char* print(std::string& data_out, CCJsonObject* json);
        
        static CCJsonObject *readFormFile(const std::string& path);
        
        static size_t writeToFile(const std::string& path, CCJsonObject* json);
    };
}

#endif
