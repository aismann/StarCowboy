//
//  SpaceDivisionTree4.h
//  StarCowboy
//
//  Created by match5 on 15/6/1.
//
//

#ifndef __SpaceDivisionTree4_h__
#define __SpaceDivisionTree4_h__

#include <set>
#include <array>

template <class T>
struct SDT4Entity {
    float x = 0;
    float y = 0;
    T *data = nullptr;
    SDT4Entity *next = nullptr;
};


template <class T>
struct SDT4Node {
    
    SDT4Node(float posX, float posY, float sizeW)
    :x(posX), y(posY), w(sizeW) {
        memset(childs, 0, sizeof(childs));
        
    }
    
    enum Direction {
        BOTTOM_LEFT     = 0,
        BOTTOM_RIGHT    = 1,
        TOP_LEFT        = 2,
        TOP_RIGHT       = 3,
    };
    Direction direct = BOTTOM_LEFT;
    
    float x = 0;
    float y = 0;
    float w = 1;
  
//    std::array<SDT4Node*, 4> childs = {0, 0, 0, 0};
//    SDT4Node **childs = nullptr;
    SDT4Node *childs[4];
    SDT4Node *parant = nullptr;
    SDT4Entity<T> *entity = nullptr;
};

template <class T>
class SpaceDivisionTree4 {
    
public:
    typedef T DataType;
    typedef SDT4Node<T> NodeType;
    typedef SDT4Entity<T> EntityType;
    
    SpaceDivisionTree4() {}
    
    void init(float x, float y, float w, float minSize);
    
    void insert(float x, float y, DataType* data);
    
    void update(float formX, float formY, float toX, float toY, DataType* data);
    
    void remove(float x, float y, DataType* data);
    
    void clear();
    
    void getNearbyData(float x, float y, std::set<DataType*>& output);
    
protected:
    
    
    void insert(EntityType* entity);
    
    void divInsert(NodeType* node, EntityType* entity);
    
    void div(NodeType* node);
    
    NodeType* rise(NodeType* node, typename NodeType::Direction as);
    
    void del(NodeType* node);
    
    bool isEmpty(NodeType* node);
    
    bool contain(NodeType* node, float x, float y);
    
    void getData(NodeType* node, std::set<DataType*>& output);
    
    NodeType *getNode(NodeType* node, float x, float y);
    
    NodeType *getNode(NodeType* node, float x, float y, float minW);
    
    EntityType *getEntity(NodeType* node, float x, float y, DataType *data);
    
    EntityType *removeEntity(NodeType* node, float x, float y, DataType *data);
    
    EntityType *mkEntity(float x, float y, DataType* data);
    
    NodeType *_root = nullptr;
    
    float _minSize;
};

#include "SpaceDivisionTree4.cpp"

#endif
