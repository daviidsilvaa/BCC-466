
#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "Node.hpp"
#include <vector>
#include <iostream>

class Route{
private:
    double cost;
    int capacity;

public:
    std::vector<Node> nodes;
    Route();
    ~Route();

    double getCost();
    int getCapacity();
    std::vector<Node> getNodes();

    void addNode(const Node &node); // adiciona um Nó na Rota
    double calculateCost(std::vector<std::vector<double> > node_dist); // calcula o Custo da Rota
    void calculateCapacity();
};

#endif
