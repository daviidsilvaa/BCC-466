#include "Node.hpp"

Node::Node(){
    this->setIndex(0);
    this->setX(0);
    this->setY(0);
    this->setDemand(0);
    this->setVisited(0);
}

Node::~Node(){}

Node::Node(const int &index, const int &x, const int &y, const int &demand){
    this->index = index;
    this->x = x;
    this->y = y;
    this->demand = demand;
    this->visited = false;
}

Node& Node::operator=(const Node &node){
    if(this != &node){
        this->setIndex(node.index);
        this->setDemand(node.demand);
        this->setX(node.x);
        this->setY(node.y);
        this->setVisited(node.visited);
    }
    return *this;
}

void Node::setIndex(const int &index){
    this->index = index;
}
int Node::getIndex(){
    return this->index;
}

void Node::setDemand(const int &demand){
    this->demand = demand;
}
int Node::getDemand(){
    return this->demand;
}

void Node::setX(const int x){
    this->x = x;
}
int Node::getX(){
    return this->x;
}

void Node::setY(const int &y){
    this->y = y;
}
int Node::getY(){
    return this->y;
}

void Node::setVisited(const bool &visited){
    this->visited = visited;
}
bool Node::getVisited(){
    return this->visited;
}
