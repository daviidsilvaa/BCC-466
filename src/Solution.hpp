
#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Route.hpp"

class Solution{
private:
    std::vector<Route> routes; // rotas a serem feitas
    std::vector<Node> node_list; // lista de nodes existentes
    std::vector< std::vector<double> > node_distance;
    double value;  // soma dos valores das rotas
    double capacity;
public:

    Solution();
    Solution(std::vector<Node> *node_list, std::vector< std::vector<double> > *node_dist);

    ~Solution();

    Solution& operator=(const Solution& solution);
    void setCapacity(const double capacity);
    double getCapacity();
    double getValue();

    double calculateObjectiveFunction();    // calcula o Valor da Funcao Objetivo
    void addRoute(const Route &route);

    void buildRandomSolution();   // constroi Solucao Aleatoria

    // metodos de troca
    void tradeIntraRoute();    // troca intra-rota
    void tradeInterRoute();    // troca inter-rota
    void tradeBetweenRoute();    // troca inter-rota

    void moveIntraRoute();
    void moveInterRoute();
    void moveBetweenRoute();
};

#endif
