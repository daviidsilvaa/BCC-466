
#include "Solution.hpp"
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
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

    /******************************/

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

    /******************************/

    Solution solution = Solution(&node_list, &node_dist);
    Solution solution_aux;
    vector<Solution> possible_solutions;
    solution.setCapacity(CAPACITY);

    solution.buildRandomSolution();
    cout << "\tsolution.value = " << solution.getValue() << endl;

    solution_aux = solution;
    solution.VariableNeighborhoodSearch(100, 1000);
    cout << "\tsolution.value = " << solution.getValue() << endl;

    //solution.moveIntraRoute();
    //cout << "\tsolution.value = " << solution.getValue() << endl;

    /*
    solution.tradeIntraRoute();
    cout << "\tintra route" << endl;
    cout << "\tsolution.value = " << solution.getValue() << endl;

    solution.tradeInterRoute();
    cout << "\tinter route" << endl;
    cout << "\tsolution.value = " << solution.getValue() << endl;

    solution.tradeBetweenRoute();
    cout << "\tbetween route" << endl;
    cout << "\tsolution.value = " << solution.getValue() << endl;
    */

    //solution.improve("type"); First, Best, Random
    //solution.improve();
    //cout << "\tsolution.value = " << solution.getValue() << endl;

    return 0;
}
