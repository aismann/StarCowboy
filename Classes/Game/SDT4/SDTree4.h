//
//  SpaceDivisionTree4.h
//  StarCowboy
//
//  Created by match5 on 15/6/1.
//
//

#ifndef __SDTree4_h__
#define __SDTree4_h__

#include "GameObjectHandle.h"

struct SDT4Pos {
    float               x = 0;
    float               y = 0;
    GameObjectHandle    obj;
    SDT4Pos*            next = nullptr;
};

class SDT4Node {
    
public:
    
    friend class SDTree4;
    
    SDT4Node(float x, float y, float w)
    :_x(x), _y(y), _w(w) {
    }
    
    enum Direction {
        BL  = 0, //bottom left
        BR  = 1, //bottom right
        TL  = 2, //top left
        TR  = 3, //top right
    };
    
protected:
    
    float getX() { return _x; }
    float getY() { return _y; }
    float getW() { return _w; }
    
    SDT4Node* getNode(float X, float y);
    
    bool insert(const SDT4Pos& pos);
    bool updateOrRemove(const SDT4Pos& pos, float newX, float newY);
    bool remove(const SDT4Pos& pos);
    
    void divide();
    
    void del();
    
    bool contain(float x, float y);
    
    Direction _direct = BL;
    
    float _x = 0;
    float _y = 0;
    float _w = 1;
    
    SDT4Node*               _parant = nullptr;
    SDT4Node**              _childs = nullptr;
    SDT4Pos*                _points;
};

class SDTree4 {
    
public:
    
    void insert(float x, float y, GameObjectHandle obj);
    
    void update(float x, float y, GameObjectHandle obj, float newX, float newY);
    
    void remove(float x, float y, GameObjectHandle obj);
    
    void rise(SDT4Node::Direction direct);
    
    void clear();
    
protected:
    
    SDT4Node *_root;
};

#endif
