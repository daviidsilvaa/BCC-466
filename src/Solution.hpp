
#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Route.hpp"

class Solution{
private:
    std::vector<Route> routes; // rotas a serem feitas
    double value;  // soma dos valores das rotas
    double capacity;
public:

    Solution();

    ~Solution();

    Solution& operator=(const Solution& solution);
    void setCapacity(const double capacity);
    double getCapacity();
    double getValue();

    double calculateObjectiveFunction();    // calcula o Valor da Funcao Objetivo
    void addRoute(const Route &route);

    void buildRandomSolution(std::vector<Node> *node_list, std::vector< std::vector<double> > *node_dist);   // constroi Solucao Aleatoria

    // metodos de troca
    void tradeIntraRoute(std::vector< std::vector<double> > *node_dist);    // troca intra-rota
    void tradeInterRoute(std::vector< std::vector<double> > *node_dist);    // troca inter-rota
    void tradeBetweenRoute(std::vector< std::vector<double> > *node_dist);    // troca inter-rota
};

#endif
