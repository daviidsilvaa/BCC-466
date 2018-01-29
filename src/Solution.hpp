
#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Route.hpp"

class Solution{
public:
    Solution();

    ~Solution();

    void setValue(const double &value);
    double getValue();
    void sumValue(const double &sumValue);

    void addRoute(const Route &route);

    double calculateObjectiveFunction();    // calcula o Valor da Funcao Objetivo
    void buildRandomSolution(const int &CAPACITY, const std::vector<Node> *node_list, std::vector< std::vector<double> > *node_dist);   // constroi Solucao Aleatoria

    // metodos de troca
    void tradeIntraRoute(std::vector< std::vector<double> > *node_dist);    // troca intra-rota
    void tradeInterRoute(const int &CAPACITY, std::vector< std::vector<double> > *node_dist);    // troca inter-rota
    void tradeBetweenRoute(const int &CAPACITY, std::vector< std::vector<double> > *node_dist);    // troca inter-rota

    std::vector<Route> routes; // rotas a serem feitas
    double value;  // soma dos valores das rotas
};

#endif
