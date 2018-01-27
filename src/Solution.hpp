
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

    double calculateObjectiveFunction();

   std::vector<Route> routes; // rotas a serem feitas
   double value;  // soma dos valores das rotas
};

#endif
