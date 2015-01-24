
#ifndef __TypeInfoCmp_h__
#define __TypeInfoCmp_h__

struct TypeInfoCmp {
    bool operator()(const std::type_info* lhs, const std::type_info* rhs) const {
        return lhs->before(*rhs);
    }
};

#endif
