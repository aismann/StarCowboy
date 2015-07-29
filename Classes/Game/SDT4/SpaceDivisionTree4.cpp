//
//  SpaceDivisionTree4.cpp
//  StarCowboy
//
//  Created by match5 on 15/6/1.
//
//

#include "SpaceDivisionTree4.h"
#include "Allocator.h"


template <class T>
void SpaceDivisionTree4<T>::init(float x, float y, float w, float minSize)
{
    if (_root) {
        clear();
    }
    _root = New(NodeType, x, y, w);
    _minSize = minSize;
}

template <class T>
void SpaceDivisionTree4<T>::insert(float x, float y, DataType* data)
{
    if (_root == nullptr) {
        return;
    }
    insert(mkEntity(x, y, data));
}

template <class T>
void SpaceDivisionTree4<T>::insert(SDT4Entity<T>* e) {
    SDT4Node<T> *node = nullptr;
    if (contain(_root, e->x, e->y) && (node = getNode(_root, e->x, e->y))) { //在root空间内
        divInsert(node, e);
    } else {    //在root空间外 增加高度
        if (e->x < _root->x) {
            if (e->y < _root->y) {
                _root = rise(_root, NodeType::TOP_RIGHT);
            } else {
                _root = rise(_root, NodeType::BOTTOM_RIGHT);
            }
        } else {
            if (e->y < _root->y) {
                _root = rise(_root, NodeType::TOP_LEFT);
            } else {
                _root = rise(_root, NodeType::BOTTOM_LEFT);
            }
        }
        insert(e);
    }
}

template <class T>
void SpaceDivisionTree4<T>::divInsert(SDT4Node<T>* n, SDT4Entity<T>* e)
{
    assert(e->next == nullptr);
    if (n->entity) {
        if (n->w > _minSize + _minSize) {
            div(n);
            for (EntityType *p = n->entity; p; p = n->entity) {
                n->entity = p->next;
                p->next = nullptr;
                for (int i = 0; i < 4; ++i) {
                    if (n->childs[i] && contain(n->childs[i], p->x, p->y)) {
                        divInsert(n->childs[i], p);
                        break;
                    }
                }
            }
            assert(n->entity == nullptr);
        } else {    //无法细分 加入已有接点
            e->next = n->entity;
            n->entity = e;
        }
    } else {    //空接点
        n->entity = e;
    }
}

template <class T>
void SpaceDivisionTree4<T>::update(float formX, float formY, float toX, float toY , DataType* data)
{
    if (_root) {
        NodeType *node = getNode(_root, formX, formY);
        if (node) {
            EntityType *e = getEntity(node, formX, formY, data);
            if (e) {
                if (contain(node, toX, toY)) {
                    e->x = toX;
                    e->y = toY;
                } else {
                    e = removeEntity(node, formX, formY, data);
                    assert(e != nullptr && "error");
                    e->x = toX;
                    e->y = toY;
                    insert(e);
                }
            }
        }
    }
}

template <class T>
void SpaceDivisionTree4<T>::remove(float x, float y, DataType* data)
{
    EntityType *e = removeEntity(_root, x, y, data);
    Delete(e);
}

template <class T>
void SpaceDivisionTree4<T>::clear()
{
    if (_root) {
        del(_root);
    }
}

template <class T>
void SpaceDivisionTree4<T>::div(NodeType* node)
{
//    if (node->childs) {
//        return;
//    }
    float hfw = node->w * 0.5;
    float midx = node->x + hfw;
    float midy = node->y + hfw;
    
    //node->childs = New(NodeType*[4]);
    
    node->childs[NodeType::BOTTOM_LEFT] = New(NodeType, node->x, node->y, hfw);
    node->childs[NodeType::BOTTOM_LEFT]->direct = NodeType::BOTTOM_LEFT;
    node->childs[NodeType::BOTTOM_LEFT]->parant = node;
    
    node->childs[NodeType::BOTTOM_RIGHT] = New(NodeType, midx, node->y, hfw);
    node->childs[NodeType::BOTTOM_RIGHT]->direct = NodeType::BOTTOM_RIGHT;
    node->childs[NodeType::BOTTOM_RIGHT]->parant = node;
    
    node->childs[NodeType::TOP_LEFT] = New(NodeType, node->x, midy, hfw);
    node->childs[NodeType::TOP_LEFT]->direct = NodeType::TOP_LEFT;
    node->childs[NodeType::TOP_LEFT]->parant = node;
    
    node->childs[NodeType::TOP_RIGHT] = New(NodeType, midx, midy, hfw);
    node->childs[NodeType::TOP_RIGHT]->direct = NodeType::TOP_RIGHT;
    node->childs[NodeType::TOP_RIGHT]->parant = node;
}

template <class T>
typename SpaceDivisionTree4<T>::NodeType* SpaceDivisionTree4<T>::rise(NodeType* node, typename NodeType::Direction as)
{
    float x = 0;
    float y = 0;
    switch (as) {
        case NodeType::BOTTOM_LEFT:
            x = node->x;
            y = node->y;
            break;
        case NodeType::BOTTOM_RIGHT:
            x = node->x - node->w;
            y = node->y;
            break;
        case NodeType::TOP_LEFT:
            x = node->x;
            y = node->y - node->w;
            break;
        case NodeType::TOP_RIGHT:
            x = node->x - node->w;
            y = node->y - node->w;
            break;
        default:
            assert(0 && "error");
            break;
    }
    
    NodeType *newRoot = New(NodeType, x, y, node->w + node->w);
    div(newRoot);
    node->direct = as;
    node->parant = newRoot;
    *(newRoot->childs[as]) = *node;
    Delete(node);
    return newRoot;
}

template <class T>
void SpaceDivisionTree4<T>::del(NodeType* node)
{
    if (node->childs[0]) {
        for (int i = 0; i < 4; ++i) {
            if (node->childs[i]) {
                del(node->childs[i]);
                node->childs[i] = nullptr;
            }
        }
        //Delete(node->childs);
    }

    EntityType* p = nullptr;
    for (; node->entity; node->entity = node->entity->next) {
        p = node->entity;
        Delete(p);
    }
    Delete(node);
}

template <class T>
bool SpaceDivisionTree4<T>::isEmpty(NodeType* node)
{
    if (node->entity) {
        return false;
    }
    for (int i = 0; i < 4; ++i) {
        if (node->childs[i]) {
            if (!isEmpty(node)) {
                return false;
            }
        }
    }
    return true;
}

template <class T>
bool SpaceDivisionTree4<T>::contain(NodeType* node, float x, float y)
{
    if (node->x <= x && x < node->x + node->w
        && node->y <= y && y < node->y + node->w) {
        return true;
    }
    return false;
}

template <class T>
typename SpaceDivisionTree4<T>::NodeType *SpaceDivisionTree4<T>::getNode(NodeType* node, float x, float y)
{
    NodeType *ret = nullptr;
    if (contain(node, x, y)) {
        ret = node;
    }
    if (node->childs[0]) {
        if (node->childs[0] && contain(node->childs[0], x, y)) {
            ret = getNode(node->childs[0], x, y);
        } else if (node->childs[1] && contain(node->childs[1], x, y)) {
            ret = getNode(node->childs[1], x, y);
        } else if (node->childs[2] && contain(node->childs[2], x, y)) {
            ret = getNode(node->childs[2], x, y);
        } else if (node->childs[3] && contain(node->childs[3], x, y)) {
            ret = getNode(node->childs[3], x, y);
        }
    }
    return ret;
}
template <class T>
typename SpaceDivisionTree4<T>::NodeType *SpaceDivisionTree4<T>::getNode(NodeType* node, float x, float y, float minW)
{
    NodeType *ret = nullptr;
    if (contain(node, x, y)) {
        ret = node;
    }
    if (node->childs[0]) {
        if (node->childs[0] && contain(node->childs[0], x, y)) {
            ret = getNode(node->childs[0], x, y, minW);
        } else if (node->childs[1] && contain(node->childs[1], x, y)) {
            ret = getNode(node->childs[1], x, y, minW);
        } else if (node->childs[2] && contain(node->childs[2], x, y)) {
            ret = getNode(node->childs[2], x, y, minW);
        } else if (node->childs[3] && contain(node->childs[3], x, y)) {
            ret = getNode(node->childs[3], x, y, minW);
        }
    }
    if (ret && ret->w < minW) {
        return ret->parant;
    }
    return ret;
}

template <class T>
typename SpaceDivisionTree4<T>::EntityType *SpaceDivisionTree4<T>::getEntity(NodeType* node, float x, float y, DataType* data)
{
    node = getNode(node, x, y);
    if (node) {
        EntityType *e = node->entity;
        for (; e; e = e->next) {
            if (e->data == data) {
                return e;
            }
        }
    }
    return nullptr;
}

template <class T>
typename SpaceDivisionTree4<T>::EntityType* SpaceDivisionTree4<T>::removeEntity(NodeType* node, float x, float y, DataType *data)
{
    node = getNode(node, x, y);
    if (node && node->entity) {
        EntityType *e1 = nullptr;
        EntityType *e2 = node->entity;
        for (;e2->data != data && e2->next; e1 = e2, e2 = e2->next);
        if (e2->data == data) { //found
            if (e2->next) {
                if (e1) {
                    e1->next = e2->next;
                } else {
                    node->entity = e2->next;
                }
                e2->next= nullptr;
            } else {
                if (e1) {
                    e1->next = nullptr;
                } else{
                    node->entity = nullptr;
                }
            }
            e2->next= nullptr;
            return e2;
        }
    }
    return nullptr;
}

template <class T>
typename SpaceDivisionTree4<T>::EntityType *SpaceDivisionTree4<T>::mkEntity(float x, float y, DataType* data) {
    EntityType *entity = New(EntityType);
    entity->x = x;
    entity->y = y;
    entity->data = data;
    return entity;
}

template <class T>
void SpaceDivisionTree4<T>::getNearbyData(float x, float y, std::set<DataType*>& output)
{
    NodeType *node = getNode(_root, x, y);
    if (node) {
        if (node->parant) {
            getData(node->parant, output);
            float w = node->w;
            float hafW = node->w * 0.5;
            switch (node->direct) {
                case NodeType::BOTTOM_LEFT:
                {
                    getData(getNode(node, x - hafW, y + hafW, node->w), output);
                    getData(getNode(node, x - hafW, y - hafW, node->w), output);
                    getData(getNode(node, x + hafW, y - hafW, node->w), output);
                }
                    break;
                case NodeType::BOTTOM_RIGHT:
                {
                    getData(getNode(node, x + w + hafW, y + hafW, node->w), output);
                    getData(getNode(node, x + w + hafW, y - hafW, node->w), output);
                    getData(getNode(node, x + hafW, y - hafW, node->w), output);
                }
                    break;
                case NodeType::TOP_LEFT:
                {
                    getData(getNode(node, x - hafW, y + hafW, node->w), output);
                    getData(getNode(node, x - hafW, y + w + hafW, node->w), output);
                    getData(getNode(node, x + hafW, y + w + hafW, node->w), output);
                }
                    break;
                case NodeType::TOP_RIGHT:
                {
                    getData(getNode(node, x + w + hafW, y + hafW, node->w), output);
                    getData(getNode(node, x + w + hafW, y + w + hafW, node->w), output);
                    getData(getNode(node, x + hafW, y + w + hafW, node->w), output);
                }
                    break;
                default:
                    assert(0 && "error");
                    break;
            }
        } else {
            getData(node, output);
        }
    }
}

template <class T>
void SpaceDivisionTree4<T>::getData(NodeType* node, std::set<DataType*>& output)
{
    if (node) {
        if (node->childs[0]) {
            for (int i = 0; i < 4; ++i) {
                if (node->childs[i]) {
                    getData(node->childs[i], output);
                }
            }
        }
        for (EntityType* e = node->entity; e; e = e->next) {
            output.insert(e->data);
        }
    }
}

