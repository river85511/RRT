#include "node.h"

Node::Node()
{

}

Node::Node(int x, int y, int parent): x(x), y(y), parent(parent)
{

}

void Node::setX(const int& x)
{
    this->x = x;
}

int Node::getX()
{
    return this->x;
}

void Node::setY(const int& y)
{
    this->y = y;
}

int Node::getY()
{
    return this->y;
}

void Node::setParent(const int& parent)
{
    this->parent = parent;
}

int Node::getParent()
{
    return parent;
}
