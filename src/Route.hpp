
#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "Node.hpp"
#include <vector>
#include <iostream>

class Route{
public:
    std::vector<Node> nodes;
    double cost;
    int demand;

    Route();

    ~Route();

    void setCost(const double &cost);
    double getCost();
    void setDemand(const int &demand);
    int getDemand();

    void addNode(const Node &node); // adiciona um Nó na Rota
    double calculateCost(std::vector<std::vector<double> > *node_dist); // calcula o Custo da Rota
};

#endif
