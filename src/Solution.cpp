
#include "Solution.hpp"

Solution::Solution(){
    this->value = 0.0;
}

Solution::~Solution() { }

void Solution::setValue(const double &value){
    this->value = value;
}
double Solution::getValue(){
    return this->value;
}
void Solution::sumValue(const double &sumValue){
    this->value += sumValue;
}

void Solution::addRoute(const Route &route){
    this->routes.push_back(route);
}

double Solution::calculateObjectiveFunction(){
    this->setValue(0.0);
    for(int i = 0; i < this->routes.size(); i++){
            this->sumValue(routes[i].getCost());
    }

    return this->getValue();
}
