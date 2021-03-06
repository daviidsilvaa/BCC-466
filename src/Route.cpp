
#include "Route.hpp"

using namespace std;

Route::Route(){
    this->cost = 0;
    this->nodes = std::vector<Node>();
    this->capacity = 0;
}

Route::~Route(){ }

double Route::getCost(){
    return this->cost;
}

void Route::addNode(const Node &node){
    this->nodes.push_back(node);
}

int Route::getCapacity(){
    return this->capacity;
}

std::vector<Node> Route::getNodes(){
    return this->nodes;
}

double Route::calculateCost(std::vector<std::vector<double> > node_dist){
    this->cost = 0;

    for(int i = 0; i < nodes.size()-1; i++){
        this->cost += node_dist[this->nodes[i].getIndex()][this->nodes[i+1].getIndex()];
    }
    this->calculateCapacity();

    return this->cost;
}

void Route::calculateCapacity(){
    this->capacity = 0;

    for(int i = 0; i < this->nodes.size(); i++)
        this->capacity += this->nodes[i].getDemand();
}
