
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

void Solution::moveIntraRoute(){
    Route route_aux;
    Node node_aux;
    int index_route;
    int index_node[2];

    index_route = rand() % this->routes.size();   // elege uma Rota aleatoriamente

    route_aux = this->routes[index_route];

    index_node[0] = rand() % (route_aux.nodes.size() - 2) + 1;
    if(route_aux.nodes.size() < 4)
        return;
    do{
        index_node[1] = rand() % (route_aux.nodes.size() - 2) + 1;
    }while(index_node[1] == index_node[0]);

    node_aux = route_aux.nodes[index_node[0]];  // troca os Nós dentro da Rota auxiliar, ie, Rota copiada
    route_aux.nodes[index_node[0]] = route_aux.nodes[index_node[1]];
    route_aux.nodes[index_node[1]] = node_aux;

    route_aux.calculateCost(this->node_distance);
    route_aux.calculateCapacity();

    this->routes[index_route] = route_aux;

    this->calculateObjectiveFunction();
};

void Solution::moveInterRoute(){
    Route route_aux[2];   // variaveis auxiliares
    Node node_aux;
    int index_route[2];
    int index_node[2];

    index_route[0] = rand() % this->routes.size();   // elege uma Rota aleatoriamente
    if(this->routes.size() < 2)
        return;
    do{
        index_route[1] = rand() % this->routes.size();  // elege outra Rota aleatoriamente, diferente da primeira Rota eleita
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

    this->routes[index_route[0]] = route_aux[0];
    this->routes[index_route[1]] = route_aux[1];

    this->calculateObjectiveFunction(); // atualiza valor da funcao Objetivo
};

void Solution::moveBetweenRoute(){
    Route route_aux[2];   // variaveis auxiliares
    Node node_aux;
    int index_route[2];
    int index_node[2];

    index_route[0] = rand() % this->routes.size();   // elege uma Rota aleatoriamente
    if(this->routes.size() < 2)
        return;
    do{
        index_route[1] = rand() % this->routes.size();  // elege outra Rota aleatoriamente, diferente da primeira Rota eleita
    }while(index_route[0] == index_route[1]);

    route_aux[0] = this->routes[index_route[0]];
    route_aux[1] = this->routes[index_route[1]];

    if(route_aux[0].nodes.size() == 3){   // caso a Rota de origem tenha apenas um Nó válido
        index_node[0] = 1;
    } else {
        index_node[0] = rand() % (route_aux[0].nodes.size() - 2) + 1;
    }

    index_node[1] = rand() % (route_aux[1].nodes.size() - 2) + 1;

    route_aux[1].nodes.insert(route_aux[1].nodes.begin() + index_node[1], route_aux[0].nodes[index_node[0]]);    // insere o Nó na Rota de destino
    route_aux[0].nodes.erase(route_aux[0].nodes.begin() + index_node[0]);     // remove o Nó da Rota de origem

    route_aux[0].calculateCost(this->node_distance);
    route_aux[1].calculateCost(this->node_distance);

    route_aux[0].calculateCapacity();   // calcula a soma da Demanda de todos os Nós da Rota
    route_aux[1].calculateCapacity();

    this->routes[index_route[1]] = route_aux[1];
    if(route_aux[0].nodes.size() == 2){
        this->routes.erase(this->routes.begin() + index_route[0]);  // deleta a Rota origem caso ela não tenha mais Nó não Depósito
    } else {
        this->routes[index_route[0]] = route_aux[0];
    }

    this->calculateObjectiveFunction(); // atualiza valor da funcao Objetivo
};

std::vector<Solution> Solution::generateKNeighbors(const int K){
    int move_option = 0, num_moves = 0;
    std::vector<Solution> solutions(K);

    for(int i = 0; i < K; i++){
        solutions[i] = *this;

        num_moves = rand() % 5 + 1; // decide quantos movimentos esse vizinho vai fazer
        for(int j=0; j < num_moves; j++) {
            move_option = rand() % 3;  // elege qual movimento sera feito
            switch (move_option) {
                case 0: // troca posicao de dois nodes dentro da rota
                    solutions[i].moveIntraRoute();
                    break;
                case 1: // troca node de uma rota com node de outra
                    solutions[i].moveInterRoute();
                    break;
                case 2: // remove node de uma rota e adiciona na outra
                default:
                    solutions[i].moveBetweenRoute();
                    break;
            }
        }
    }
    return solutions;
}

void Solution::VariableNeighborhoodSearch(const int max_iterations, const int K){
    Solution solution_aux;
    std::vector<Solution> possible_solutions(K);
    int iterator = 0;

    while(iterator < max_iterations){
        iterator++;
        possible_solutions = this->generateKNeighbors(K);   // gera os k-vizinhos

        for(int i=0; i < K; i++){
            // Best improvement dentro dos k-vizinhos
            if(possible_solutions[i].getValue() < this->getValue()){
                this->routes = possible_solutions[i].routes;
                this->calculateObjectiveFunction();
                std::cout << "Melhor FO vizinho " << i << " iteracaoo " << iterator << ": " << this->value << std::endl;
            }
        }
    }
}
