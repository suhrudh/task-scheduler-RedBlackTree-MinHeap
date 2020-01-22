//
// Created by Suhrudh Reddy on 11/16/19.
//

#ifndef ADS_NODES_H
#define ADS_NODES_H

#include "Building.h"

class MinHeapElement;
class Structure;

enum Color{Red=0,Black=1};

//Red Black node structure
class RedBlackElement {
public:
    int building_num;
    RedBlackElement *parent;
    RedBlackElement *leftChild;
    RedBlackElement *rightChild;
    Color color;
    MinHeapElement *detail;

    RedBlackElement(int building_num,  RedBlackElement *parent, RedBlackElement *leftChild, RedBlackElement *rightChild, Color color, MinHeapElement *detail)
    {
        this->building_num = building_num;
        this->parent = parent;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->color = color;
        this->detail = detail;
    }
};

//Min heap Node
class MinHeapElement : public Building
{
public:
    RedBlackElement *Node;

    MinHeapElement( int x, int y, int z, RedBlackElement *node) : Building(x, y, z) {

        Node = node;
    }
};

#endif //ADS_NODES_H
