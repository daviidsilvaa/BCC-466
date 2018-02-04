
#include "Solution.hpp"
#include <algorithm>
#include <unistd.h>

Solution::Solution(){
    this->value = 0.0;
    this->capacity = 0.0;
}

Solution::Solution(std::vector<Node> *node_list, std::vector< std::vector<double> > *node_dist){
    this->value = 0.0;
    this->capacity = 0.0;
    this->node_list = (*node_list);
    this->node_distance = (*node_dist);
}

Solution::~Solution() { }

Solution& Solution::operator=(const Solution& solution)
{
    if(&solution == this)
        return *this;

    this->value = solution.value;
    this->capacity = solution.capacity;
    this->routes = solution.routes;
    this->node_list = solution.node_list;
    this->node_distance = solution.node_distance;
    return *this;
}

void Solution::setCapacity(const double capacity) {
    this->capacity = capacity;
}

double Solution::getCapacity() {
    return this->capacity;
}

double Solution::getValue(){
    return this->value;
}

void Solution::addRoute(const Route &route){
    this->routes.push_back(route);
}

double Solution::calculateObjectiveFunction(){
    this->value = 0.0;
    for(int i = 0; i < this->routes.size(); i++){
        if(routes[i].getCapacity() > this->capacity)
            this->value += routes[i].getCost() * 100;
        else
            this->value += routes[i].getCost();
    }

    return this->value;
}

void Solution::buildRandomSolution(){
    std::vector<Node> node_list_cpy = this->node_list;
    int index_aux, capacity_aux = 0;   // variaveis auxiliares

    // *this = Solution();

    Route route_aux = Route();
    route_aux.addNode(this->node_list[0]);

    for(int i = 0; i < this->node_list.size(); i++){
        if(node_list_cpy.size() > 1) // adiciona Nó aleatorio, desde que o Nó não seja o Depósito
            index_aux = rand() % (node_list_cpy.size() - 1) + 1;
        else
            index_aux = 0;

        if(node_list_cpy.size() == 1){  //  caso a lista tenha apenas o Nó Deposito, devemos finalizar a Construcao Aleatoria
            route_aux.addNode(this->node_list[0]);
            route_aux.calculateCost(this->node_distance);
            this->addRoute(route_aux);
            break;  // sai do laco FOR
        }

        if(this->capacity >= (capacity_aux + node_list_cpy[index_aux].getDemand())){
            route_aux.addNode(node_list_cpy[index_aux]); // adiciona o Nó na rota
            capacity_aux += node_list_cpy[index_aux].getDemand();
        } else {
            route_aux.addNode(this->node_list[0]); // adiciona o Deposito no final da Rota
            route_aux.calculateCost(this->node_distance);   // calcula o Custo da Rota a ser adicionada a Solucao !!!
            this->addRoute(route_aux);    // adiciona a Rota na Solucao

            route_aux = Route();    // reinicia a Rota auxiliar
            route_aux.addNode(this->node_list[0]); // adiciona o Deposito no inicio da Rota
            route_aux.addNode(node_list_cpy[index_aux]); // adiciona o Nó na rota
            capacity_aux = node_list_cpy[index_aux].getDemand();
        }
        node_list_cpy.erase(node_list_cpy.begin() + index_aux);  // remove o Nó usado da lista de Nós disponiveis
    }
    this->calculateObjectiveFunction();
}

void Solution::tradeIntraRoute(){
    Route route_aux;   // variaveis auxiliares
    Node node_aux;
    bool out = false, neigh_node = true;
    int i = 0;
    int index_node[2];

    int index_route = rand() % this->routes.size();   // elege uma rota aleatoriamente

    route_aux = this->routes[index_route];

    while(!out){   // enquanto a troca nao for valida
        while(i < 2) {
            if(i == 0){
                index_node[0] = rand() % route_aux.nodes.size();
                usleep(100);
                if((index_node[0] > 0) && (index_node[0] < route_aux.nodes.size() - 1)) // Nó eleito nao pode ser o Deposito
                i++;
            } else {
                index_node[1] = rand() % route_aux.nodes.size();
                usleep(100);

                if((index_node[0] - index_node[1] < -1) || (index_node[0] - index_node[1] > 1)) // Nó eleito nao pode ser vizinho do outro Nó ja eleito
                neigh_node = false;

                if((index_node[1] > 0) && (index_node[1] < route_aux.nodes.size() - 1) && (!neigh_node)){
                    i++;
                    out = true;
                }
            }
        }
    }

    node_aux = route_aux.nodes[index_node[0]];  // troca os Nós dentro da Rota auxiliar, ie, Rota copiada
    route_aux.nodes[index_node[0]] = route_aux.nodes[index_node[1]];
    route_aux.nodes[index_node[1]] = node_aux;

    route_aux.calculateCost(this->node_distance);

    if(route_aux.getCost() < this->routes[index_route].getCost()){
        this->routes[index_route] = route_aux;  // troca caso ocorra melhora
        this->calculateObjectiveFunction(); // atualiza valor da funcao Objetivo
    }
}

void Solution::tradeInterRoute(){
    Route route_aux[2];   // variaveis auxiliares
    Node node_aux[2], node_aux2;
    bool out = false;
    int index_route[2];
    int index_node[2];

    index_route[0] = rand() % this->routes.size();   // elege uma Rota aleatoriamente
    do{
        index_route[1] = rand() % this->routes.size();  // elege outra Rota aleatoriamente, diferente da primeira Rota eleita
        usleep(100);
    }while(index_route[0] == index_route[1]);

    route_aux[0] = this->routes[index_route[0]];
    route_aux[1] = this->routes[index_route[1]];

    for(int i = 0; i < 2; i++){ // elege os Nós a serem trocados
        do{
            index_node[i] = rand() % route_aux[i].nodes.size();
            usleep(100);
        }while(!((index_node[i] > 0) && (index_node[i] < route_aux[i].nodes.size() - 1))); // garante que o Nó escolhido não é o Deposito
    }

    node_aux2 = route_aux[0].nodes[index_node[0]];  // troca os Nós dentro da Rota auxiliar, ie, Rota copiada
    route_aux[0].nodes[index_node[0]] = route_aux[1].nodes[index_node[1]];
    route_aux[1].nodes[index_node[1]] = node_aux2;

    route_aux[0].calculateCost(this->node_distance);
    route_aux[1].calculateCost(this->node_distance);

    route_aux[0].calculateCapacity();   // calcula a soma da Demanda de todos os Nós da Rota
    route_aux[1].calculateCapacity();

    if((route_aux[0].getCapacity() < this->capacity) && (route_aux[1].getCapacity() < this->capacity)){ // verifica se a "Capacidade" da nova Rota satisfaz a do veiculo
        if((route_aux[0].getCost() + route_aux[1].getCost()) < (this->routes[index_route[0]].getCost() + this->routes[index_route[1]].getCost())){
            this->routes[index_route[0]] = route_aux[0];  // troca caso ocorra melhora
            this->routes[index_route[1]] = route_aux[1];

            this->calculateObjectiveFunction(); // atualiza valor da funcao Objetivo
        }
    }
}

void Solution::tradeBetweenRoute(){
    Route route_aux[2];   // variaveis auxiliares
    Node node_aux;
    int index_route[2];
    int index_node;
    bool out = false;

    index_route[0] = rand() % this->routes.size();   // elege uma Rota aleatoriamente
    do{
        index_route[1] = rand() % this->routes.size();  // elege outra Rota aleatoriamente, diferente da primeira Rota eleita
        usleep(100);
    }while(index_route[0] == index_route[1]);

    route_aux[0] = this->routes[index_route[0]];
    route_aux[1] = this->routes[index_route[1]];

    do{ // elege o Nó a ser trocados
        index_node = rand() % route_aux[0].nodes.size();
        usleep(100);
    }while(!((index_node > 0) && (index_node < route_aux[0].nodes.size() - 1))); // garante que o Nó escolhido não é o Deposito

    node_aux = route_aux[0].nodes[index_node];
    route_aux[0].nodes.erase(route_aux[0].nodes.begin() + index_node);
    route_aux[0].calculateCost(this->node_distance);

    if((route_aux[1].getCapacity() + node_aux.getDemand()) < this->capacity){ // verifica se a "Capacidade" da nova Rota satisfaz a do veiculo
        for(int i = 1; (i < route_aux[1].nodes.size() - 1) && (!out); i++){
            route_aux[1].nodes.insert(route_aux[1].nodes.begin() + i, node_aux);  // insere o Nó em um indice(crescente) da nova Rota
            route_aux[1].calculateCost(this->node_distance);    // calcula o Custo da nova Rota

            if(this->routes[index_route[1]].getCost() > route_aux[1].getCost()){
                this->routes[index_route[0]] = route_aux[0];    // troca caso ocorra melhora
                this->routes[index_route[1]] = route_aux[1];

                out = true;
            } else {
                route_aux[1].nodes.erase(route_aux[1].nodes.begin() + i);
            }
        }
    }

    this->calculateObjectiveFunction(); // atualiza valor da funcao Objetivo
}


void Solution::moveInterRoute(){
    Route route_aux[2];   // variaveis auxiliares
    Node node_aux;
    int index_route[2];
    int index_node[2];

    index_route[0] = rand() % this->routes.size();   // elege uma Rota aleatoriamente
    do{
        index_route[1] = rand() % this->routes.size();  // elege outra Rota aleatoriamente, diferente da primeira Rota eleita
        usleep(100);
    }while(index_route[0] == index_route[1]);

    route_aux[0] = this->routes[index_route[0]];
    route_aux[1] = this->routes[index_route[1]];

    index_node[0] = rand() % (route_aux[0].nodes.size() - 2) + 1;
    index_node[1] = rand() % (route_aux[1].nodes.size() - 2) + 1;

    node_aux = route_aux[0].nodes[index_node[0]];  // troca os Nós dentro da Rota auxiliar, ie, Rota copiada
    route_aux[0].nodes[index_node[0]] = route_aux[1].nodes[index_node[1]];
    route_aux[1].nodes[index_node[1]] = node_aux;

    route_aux[0].calculateCost(this->node_distance);
    route_aux[1].calculateCost(this->node_distance);

    route_aux[0].calculateCapacity();   // calcula a soma da Demanda de todos os Nós da Rota
    route_aux[1].calculateCapacity();

    this->routes[index_route[0]] = route_aux[0];  // troca caso ocorra melhora
    this->routes[index_route[1]] = route_aux[1];

    this->calculateObjectiveFunction(); // atualiza valor da funcao Objetivo
};