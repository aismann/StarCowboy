//
//  SpaceDivisionTree4.cpp
//  StarCowboy
//
//  Created by match5 on 15/6/1.
//
//

#include "SDTree4.h"
#include "Allocator.h"

#define MIN_NODE_SIZE 32

//SDT4Node
SDT4Node* SDT4Node::getNode(float x, float y)
{
    if (contain(x, y)) {
        if (_childs) {
            SDT4Node* node = nullptr;
            for (int i = 0; i < 4; ++i) {
                node = _childs[i]->getNode(x, y);
                if (node) {
                    return node;
                }
            }
        } else {
            return this;
        }
    }
    return nullptr;
}

bool SDT4Node::insert(const SDT4Pos& pos)
{
    if (!contain(pos.x, pos.y)) {
        return false;
    }
    
    return false;
}

bool SDT4Node::updateOrRemove(const SDT4Pos& pos, float newX, float newY)
{
    if (!contain(pos.x, pos.y)) {
        remove(pos);
        return false;
    }
    if (_points) {
//        auto it = std::find_if(_points->begin(), _points->end(), [&pos](const SDT4Pos& p){
//            return p.obj == pos.obj;
//        });
//        if (it != _points->end()) {
//            it->x = newX;
//            it->y = newY;
//            return true;
//        }
    }
    return false;
}

bool SDT4Node::remove(const SDT4Pos& pos)
{
    if (!contain(pos.x, pos.y)) {
        return false;
    }
    return false;
}

void SDT4Node::divide()
{
}

void SDT4Node::del()
{
    if (_points) {
//        _points.clear();
        Delete(_points);
    }
    if (_childs) {
        for (int i = 0; i < 4; ++i) {
                _childs[i]->del();
        }
        Delete(_childs);
    }
}

bool SDT4Node::contain(float x, float y)
{
    if (_x <= x && x < _x + _w
        && _y <= y && y < _y + _w) {
        return true;
    }
    return false;
}


//SDTree4
void SDTree4::insert(float x, float y, GameObjectHandle obj)
{
    if (!_root) {
        _root = New(SDT4Node, x - 512, y - 512, 1024);
    }
    SDT4Node *node = _root->getNode(x, y);
    if (node) {
        SDT4Pos pos;
        pos.x = x;
        pos.y = y;
        pos.obj = obj;
        node->insert(pos);
    }
}

void SDTree4::update(float x, float y, GameObjectHandle obj, float newX, float newY)
{
    if (!_root) {
        return;
    }
    SDT4Node *node = _root->getNode(x, y);
    if (node) {
        SDT4Pos pos;
        pos.x = x;
        pos.y = y;
        pos.obj = obj;
        if(node->updateOrRemove(pos, newX, newY)) {
            //success;
        } else {
            //failed to update, insert agin
            pos.x = newX;
            pos.y = newY;
            _root->insert(pos);
        }
    }
}

void SDTree4::remove(float x, float y, GameObjectHandle obj)
{
    if (!_root) {
        return;
    }
    SDT4Node *node = _root->getNode(x, y);
    if (node) {
        SDT4Pos pos;
        pos.x = x;
        pos.y = y;
        pos.obj = obj;
        node->remove(pos);
    }
}

void SDTree4::rise(SDT4Node::Direction direct)
{
    if (!_root) {
        return;
    }
}

void SDTree4::clear()
{
    if (_root) {
        _root->del();
    }
}

