
#include "Route.hpp"
#include "Solution.hpp"
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){
    fstream file_in;    // arquivo de entrada de dados
    string line;    // recebe cada linha do arquivo
    int index, DIMENSION, CAPACITY, vertice, coord_x, coord_y, aux;
    Node tmp;   // variavel temporaria
    vector<Node> node_list; // estrura que armazena os Nos

    // se o Nome do Arquivo nao for passado como parametro na execucao
    if(argv[1] == NULL) return 0;

    file_in.open(argv[1], fstream::in);

    // leitura do arquivo de entrada
    if(file_in.is_open()){

        // recebendo Dimensao e Capacidade do Veiculo
        getline(file_in, line);
        while(line != "NODE_COORD_SECTION"){
            index = line.find(" : ");

            if(line.substr(0, index) == "DIMENSION"){
                DIMENSION = atoi(line.substr(index + 3).c_str());
            }
            else if(line.substr(0, index) == "CAPACITY"){
                CAPACITY = atoi(line.substr(index + 3).c_str());
            }
            getline(file_in, line);
        }

        // recebendo as Coordenadas de cada Nó
        getline(file_in, line);
        while(line != "DEMAND_SECTION"){
            stringstream stream(line);

            stream >> aux;
            tmp.setIndex(aux - 1);
            stream >> aux;
            tmp.setX(aux);
            stream >> aux;
            tmp.setY(aux);
            node_list.push_back(tmp);
            getline(file_in, line);
        }

        // recebendo a Demanda de cada Nó
        getline(file_in, line);
        while(line != "DEPOT_SECTION"){
            stringstream stream(line);

            stream >> index;
            stream >> aux;
            tmp.setDemand(aux);

            node_list[index - 1].setDemand(tmp.getDemand());
            node_list[index - 1].setVisited(false);

            getline(file_in, line);
        }
    }

    // fechando o arquivo de entrada
    file_in.close();

    // for(int i = 0; i < node_list.size(); i++)
    //     cout << node_list[i].getIndex() << ":\t" << node_list[i].getDemand() << "\t" << node_list[i].getX() << "\t" << node_list[i].getY() << endl;

    /****************************/
    /* Matriz que armazena as distancias entre os Nós */
    vector< vector<double> > node_dist(node_list.size());

    for(int i = 0; i < node_dist.size(); i++)
    node_dist[i].resize(node_list.size());

    // calcula a distancia entre cada cidade
    for(int i = 0; i < node_list.size(); i++){
        for(int j = i; j < node_list.size(); j++){
            node_dist[i][j] = sqrt(pow(node_list[i].getX() - node_list[j].getX(), 2) + pow(node_list[i].getY() - node_list[j].getY(), 2));
            node_dist[j][i] = node_dist[i][j];
        }
    }

    /****************************/
    /* Metodo Construtivo */

    // Aleatorio
    vector<Node> node_list_cpy = node_list;  // copia da lista de Nós
    int index_aux, capacity_aux = 0;   // variaveis auxiliares

    // cout << node_list_cpy.size() << endl;

    Solution solution = Solution();
    Route route_aux = Route();
    route_aux.addNode(node_list[0]);

    srand(time(NULL));
    for(int i = 0; i < node_list.size(); i++){
        do{
            if(node_list_cpy.size() == 1)   // caso a lista tenha tamanho 1, teremos apenas o Nó Deposito nela, logo devemos sair do laco
                break;
            index_aux = rand() % node_list_cpy.size();
            usleep(100);
        }while(index_aux == 0); // adiciona Nó aleatorio, desde que o Nó não seja o Depósito

        if(node_list_cpy.size() == 1){  //  caso a lista tenha apenas o Nó Deposito, devemos finalizar a Construcao Aleatoria
            route_aux.addNode(node_list[0]);
            route_aux.setCost(route_aux.calculateCost(&node_dist));
            solution.addRoute(route_aux);
            break;  // sai do laco FOR
        }

        if(CAPACITY >= (capacity_aux + node_list_cpy[index_aux].getDemand())){
            route_aux.addNode(node_list_cpy[index_aux]); // adiciona o Nó na rota
            node_list_cpy.erase(node_list_cpy.begin() + index_aux);  // remove o Nó, adicionado a lista, da lista de Nós disponiveis
            capacity_aux += node_list_cpy[index_aux].getDemand();
        } else {
            route_aux.addNode(node_list[0]); // adiciona o Deposito no final da Rota
            route_aux.setCost(route_aux.calculateCost(&node_dist));   // calcula o Custo da Rota a ser adicionada a Solucao

            solution.addRoute(route_aux);    // adiciona a Rota na Solucao

            route_aux = Route();    // reinicia a Rota auxiliar
            route_aux.addNode(node_list[0]); // adiciona o Deposito no inicio da Rota
            route_aux.addNode(node_list_cpy[index_aux]); // adiciona o Nó na rota
            node_list_cpy.erase(node_list_cpy.begin() + index_aux);  // remove o Nó, adicionado a lista, da lista de Nós disponiveis

            capacity_aux = node_list_cpy[index_aux].getDemand();
        }
    }

    solution.setValue(solution.calculateObjectiveFunction());

    cout << endl << "\tsolution.value = " << solution.getValue() << endl;

    return 0;
}
