
#ifndef NODE_HPP
#define NODE_HPP

class Node{
private:
    int index;
    int demand;
    int x;
    int y;
    bool visited;

public:
    Node();
    ~Node();
    Node(const int &index, const int &x, const int &y, const int &demand);
    Node& operator=(const Node &node);

    void setIndex(const int &index);
    int getIndex();
    void setDemand(const int &demand);
    int getDemand();
    void setX(const int x);
    int getX();
    void setY(const int &y);
    int getY();
    void setVisited(const bool &visited);
    bool getVisited();
};

#endif
