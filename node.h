#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node();
    Node(int x, int y, int parent);

    void setX(const int& x);
    int getX();
    void setY(const int& y);
    int getY();
    void setParent(const int& parent);
    int getParent();

private:

    int x;
    int y;
    int parent;

};

#endif // NODE_H
