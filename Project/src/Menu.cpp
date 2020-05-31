using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <algorithm>
#include <iomanip>
#include "Menu.h"

#ifndef TOURMATEAPP_HELPERFUNCTIONS_H
#include "helperfunctions.h"
#endif

#include "graphviewer.h"

struct MYEXCEPT_FileNotFound : public exception {
    const char * what () const throw () {
        return "FILENOTFOUND";
    }
};

/** Strings a serem mostradas no menu com os tipos de POI
 *  O NOT_INTERESTING deve ser ignorado.
 * */
std::string POIINSTRING[] = {"NOT_INTERESTING",
                             "Estatua",
                             "Museu",
                             "Estadio",
                             "Livraria",
                             "Palacio",
                             "Parque"};

void Menu::run() {
    bool exit = false;
    std::string inp;
    while(!exit){
        switch (currentState) {
            case START:
                drawTitle();
                nameReceiver();
                getMapInfo();
                currentState = MAINMENU;
                break;
            case MAINMENU:
                drawMainMenu();
                mainMenuHandle();
                break;
            case CHOOSINGLOCATION:
                pickInitLocation();
                location_selected = true;
                break;
            case CHOOSINGTIME:
                pickTime();
                break;
            case CHOOSINGTYPESPOI:
                pickTypesPOI();
                currentState = MAINMENU;
                poi = true;
                break;
            case CALCULATING:
                calculate();
                currentState = MAINMENU;
                poi = true;
                break;
            case DONE:
                exit = true;
                break;
            default:
                break;
            }

    }
}

/**
 * Função que guia o flow do programa
 */
void Menu::mainMenuHandle() {
    string input;
    cin >> input;
    if (input.compare("0") == 0)
        currentState = DONE;
    else if (input.compare(("1")) == 0)
        currentState = CHOOSINGLOCATION;
    else if (input.compare(("2")) == 0)
        currentState = CHOOSINGTIME;
    else if (input.compare(("3"))== 0)
        toggleVehicle();
    else if (input.compare(("4"))== 0)
        currentState = CHOOSINGTYPESPOI;
    else if (input.compare("5") == 0)
        currentState = CALCULATING;

}

/**
 * Decide se user está num veiculo ou a caminhar
 */
void Menu::toggleVehicle(){
    this->usingCar = !this->usingCar;
}

/**
 * Recebe nome do user
 */
void Menu::nameReceiver() {
    cout << "Por favor, introduza o seu nome: ";
    cin >> this->user;
}

/**
 * Desenha Menu principal
 */
void Menu::drawMainMenu()
{
    drawTitle();
    cout << "Utilizador: " << this->user << endl << endl;
    if(location_selected) { // initialLocationID != 0
        cout << "[1] - Localização Inicial [ ";
        cout << "Lat: " << initNode.getLat() << "; Lon: " << initNode.getLon();
        cout << " ]"<< endl;
    } else {
        cout << "[1] - Definir Localização Inicial" << endl;
    }

    if(timeAvailable != 0) {
        cout << "[2] - Tempo Disponível: [ ";
        cout <<  timeAvailable << " min";
        cout << " ]"<< endl;
    } else {
        cout << "[2] - Definir Tempo Disponível" << endl;
    }

    if(!usingCar){
        cout << "[3] - Deslocação: Pedestre" << endl;
    } else {
        cout << "[3] - Deslocação: Automóvel" << endl;
    }

    if (!poi) {
        cout << "[4] - Escolher tipo de POI Favoritos" << endl << endl;
    } else {
        cout << "[4] - Alterar tipo de POI Favoritos" << endl << endl;
    }
    cout << "[5] - Calcular percurso"<< endl << endl;
    cout << "Pressione um número de 1 a 5 para selecionar uma opção ou 0 para sair da API" << endl << endl;
}

/*----------------------------------------------------------------------------------------------------------------------
                                                    LOCATION
----------------------------------------------------------------------------------------------------------------------*/
/**
 * Função para remover parêntises e colocar os dados, separados por vírgula, num vector de strings
 */
vector<string> parseLine(string line) {
    line = line.substr(1);
    line = line.substr(0, line.size() - 1);
    vector<string> data;
    size_t pos;

    while ((pos = line.find(",")) != string::npos) {
        data.push_back(line.substr(0, pos));
        line = line.substr(pos+1);
    }
    data.push_back(line);

    return data;
}

/**
 * Aleatoriamente cria tags para um node
 * @param node Node a aplicar a tal
 */
void Menu::generateTag(Node * node) {
    int randNum = rand()%(100-0 + 1);
    if (randNum > 70) {
        if (randNum > 95) node->addTag("Estatua");
        else if (randNum > 95) node->addTag("Museu");
        else if (randNum > 95) node->addTag("Estadio");
        else if (randNum > 95) node->addTag("Livraria");
        else if (randNum > 95) node->addTag("Palacio");
        else node->addTag("Parque");

        int randRating = rand()%(5-1 + 1) + 1;
        node->setRating(randRating);

        int randVisitTime = rand()%(833-83 + 1) + 83;
        node->setVisitTime(randVisitTime);
    }
}


/**
 * Apos leitura do ficheiro cria os objetos correspondentes
 * @param data Strings lidas do ficheiro de text
 * @param option Edge ou node
 */
void Menu::parseNodeData(vector<string> data, int option) {
    double id = 0, lat = 0, lon = 0;
    double x = 0, y = 0;
    switch(option) {
        case 0: // Geographical Coordinates
            id = stod(data[0]);
            lat = stod(data[2]);
            lon = stod(data[1]);
            this->map.addNode(id, lat, lon, 0, 0);
            generateTag(this->map.findNode(id));

            // Buscar a Latitude e Longitude Máximas e Mínimas
            if(lat < latMin)
                latMin = lat;
            else if ( lat > latMax)
                latMax = lat;
            if(lon < lonMin)
                lonMin = lon;
            else if ( lon > lonMax)
                lonMax = lon;

            break;

        case 2: //XY
            id = stod(data[0]);
            x = stod(data[1]);
            y = stod(data[2]);
            this->map.findNode(id)->setXY(x, y);

            if(x < xMin)
                xMin = x;
            else if ( x > xMax)
                xMax = x;
            if(y < yMin)
                yMin = y;
            else if ( y > yMax)
                yMax = y;
            break;

        case 1: // Edges
            double id1 = stod(data[0]);
            double id2 = stod(data[1]);
            Node *n1 = this->map.findNode(id1);
            Node *n2 = this->map.findNode(id2);
            Edge * adj = this->map.addEdge(n1, n2);
            n1->addAdjEdge(adj);
            n2->addAdjEdge(adj);
            break;


    }
}

/**
 * Função auxiliar para ler de ficheiros de texto
 * @param file_name_prefix  path
 * @param option ficheiro das Nodes ou Edges
 */
void Menu::retrieveFileData(string file_name_prefix, int option) {

    string line;
    bool first_line = true;
    int line_nr = 0;

    string lc_location = "../maps/Porto/" + file_name_prefix;

    // Check if file exists
    try{
        if(!fileExists( lc_location ))
            throw MYEXCEPT_FileNotFound();
    }    catch( MYEXCEPT_FileNotFound& e)
    {
        cerr << "Unable to open the file: " << lc_location << endl;
        exit(1);
    }

    ifstream file;
    file.open(lc_location);
    getline(file,line);
    int number = stoi(line);
    for (int i = 1; i <= number; i++ ) {
        getline(file,line);
        parseNodeData(parseLine(line), option);
    }
    file.close();
}

/**
 * Pergunta ao user qual a sua posição para escolher o Ponto mais próximo
 */
void Menu::pickInitLocation() {
    double input_lat, input_lon;
    do {
        if (cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
        drawTitle();

        cout << endl << "Escolha da localização inicial" << endl;
        cout << "Escolha uma Latitude entre "<< latMin << " e " << latMax<<":" << endl << endl;
        cin >> input_lat;
        cout << "Escolha uma Longitude entre "<<lonMin<<" e " << lonMax <<":" << endl << endl;
        cin >> input_lon;

        if (input_lat <= latMax && input_lat >= latMin && input_lon <= lonMax && input_lon >= lonMin) {
            initNode = map.getInitLoc(input_lat, input_lon);
            cout << "Node mais perto:" << endl;
            initNode.printInfo();
            initialLocationID = initNode.getId();

            //todo check if InitNode has Edges connected.
            bool exit = false;
            for(auto it = map.getEdges()->begin(); it != map.getEdges()->end(); ++it){
                if(  (*it).getOrig()->getId() == initNode.getId() ) {
                    exit = true;
                    break;
                }
                continue;
            }
            cin.clear();
            if(exit)
                break;
            //else
            std::cout << "That node has no output Edges" << std::endl;
        }

    } while (!cin.fail());
    currentState = MAINMENU;
}

/**
 * Vai buscar informação dos Nodes e Arestas ao ficheiros de texto correspondentes
 */
void Menu::getMapInfo() {
    map.getNodes().clear();

    cout << "A carregar o mapa. Por favor, aguarde." << endl;

    retrieveFileData("porto_full_nodes_latlng.txt", 0);
    retrieveFileData("porto_full_edges.txt", 1);
    retrieveFileData("porto_full_nodes_xy.txt", 2);
      
    cout << "Mapa carregado com sucesso!" << endl;

    std::cout << "\nCalculando distancias entre pontos" << endl;

    int se = calculateNodeWeight();

    std::cout << "Distâncias calculadas\n" << endl;
    std::cout << "Encontrados " << se << " Edges inúteis." << endl;
}

/**
 * Calcula os pesos das Edges, tendo em conta as coordenadas dos Nodes
 * Remove também Qualquer edge de um nó para si próprio.
 * @return Numero de nós "inuteis"
 */
int Menu::calculateNodeWeight() {
    int stupidEdges = 0;
    for(auto it = map.getEdges()->begin(); it != map.getEdges()->end(); ){
        if((*it).getOrig()->getId() == (*it).getDest()->getId()){
            stupidEdges++;
            map.getEdges()->erase(it);
        }else{
        (*it).setWeight( distanceBetweenNodes( (*it).getOrig(), (*it).getDest()) / getWalkingSpeed());
            ++it;
        }
    }
    return stupidEdges;
}




/*--------------------------------------------------------------------------------------------------------------------
                                                        TYPES
----------------------------------------------------------------------------------------------------------------------*/

/**
 * Pergunta ao user os tipos de POI
 */
void Menu::pickTypesPOI() {
    int input = 0;
    do {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
        }
        drawTitle();
        for (int i = 1; i != (sizeof(picks) / sizeof(bool)) - 1; i++) {
            cout << "    [" << i << "] - ";
            if (picks[i])
                cout << " [S] ";
            else
                cout << " [N] ";
            cout << POIINSTRING[i];
            cout << endl;
        }

        cout << endl << "Escolha os seus POI favoritos.\nS - Selecionado ; N - Não Selecionado" << endl;
        cout << "Pressione 0 para voltar ao menu principal e 7 para selecionar/desselecionar todos" << endl << endl;
        cout << "POI a alterar: " << std::endl;
        cin >> input;

        if (input == 0)
            break;
        else if (input == 7) {
            for (int p = 1; p != (sizeof(picks) / sizeof(bool)); ++p) {
                picks[p] = !picks[p];
            }
        }
        if (input < 7 && input > 0)
            picks[input] = !picks[input];

        switch (input) {
            case 1:
                this->types.estatua = this->types.estatua == 1 ? 0 : 1;
                break;
            case 2:
                this->types.museu = this->types.museu == 1 ? 0 : 1;
                break;
            case 3:
                this->types.estadio = this->types.estadio == 1 ? 0 : 1;
                break;
            case 4:
                this->types.livraria = this->types.livraria == 1 ? 0 : 1;
                break;
            case 5:
                this->types.palacio = this->types.palacio == 1 ? 0 : 1;
                break;
            case 6:
                this->types.parque = this->types.parque == 1 ? 0 : 1;
                break;
            case 7:
                this->types.estatua = this->types.estatua == 1 ? 0 : 1;
                this->types.museu = this->types.museu == 1 ? 0 : 1;
                this->types.estadio = this->types.estadio == 1 ? 0 : 1;
                this->types.livraria = this->types.livraria == 1 ? 0 : 1;
                this->types.palacio = this->types.palacio == 1 ? 0 : 1;
                this->types.parque = this->types.parque == 1 ? 0 : 1;
                break;
            default:
                break;
        }
    } while (!cin.fail());

}

/**
 * Pergunta ao user o tempo disponivel
 */
void Menu::pickTime() {
    int timeAvailableTemp;
    do {
        if(cin.fail()){
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        drawTitle();
        cout << "Insira o tempo máximo disponível para o percurso ou prima 0 para cancelar.\n" << endl;
        cout << "Tempo maximo: ";
        cin >> timeAvailableTemp;
    } while (cin.fail());

    currentState = MAINMENU;

    if (timeAvailableTemp == 0) {
        cout << "Aborting..." << endl;
    } else if (timeAvailableTemp > 0) {
        timeAvailable = timeAvailableTemp;
    }
    return;
}


/**
 * Desenha o Titulo
 */
void Menu::drawTitle() {
    cout << "\n";
    cout << " --------------------------------------------------- " << endl;
    cout << "  TourMateApp - Rotas Turísticas Urbanas Adaptáveis " << endl;
    cout << " ---------------------------------------------------\n" << endl;
}


/**
 * Função que mostra o grafo. O primeiro e ultimo pontos serão desenhados de forma diferente
 * @param nodes vector de nodes a mostrar de cor diferentes
 * @Param edges a mostrar de cor diferentes
 */
void Menu::showGraph(vector<Node *> nodes, vector<Edge> * edges)
{
    GraphViewer *gv = new GraphViewer(2000, 1000, false);
    gv->setBackground("background.jpg");
    gv->createWindow(2000, 1000);

    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->defineEdgeCurved(false);

    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        gv->addNode((*it)->getId(),(((*it)->getX()-xMin)/7)+100,(((*it)->getY()-yMin)/7)+50);
        if ((*it)->getId() == initNode.getId()) {
            gv->setVertexColor((*it)->getId(), "blue");
            cout << "First Node | Lat: " << setw(10) << (*it)->getLat() << " | Lon: " << setw(10) << (*it)->getLon() << endl;
        }
        else if ((*it)->getId() == lastNodeId)  {
            gv->setVertexColor((*it)->getId(), "green");
            cout << "Last Node  | Lat: " << setw(10) << (*it)->getLat() << " | Lon: " << setw(10) << (*it)->getLon() << endl;
        }
        else gv->setVertexSize((*it)->getId(), 0.1);
    }

    cout << "\nStreets to pass by:\n" << endl;
    int i = 0;
    for (auto itr = edges->begin(); itr != edges->end(); itr++) {
        gv->addEdge(i, (*itr).getOrig()->getId(), (*itr).getDest()->getId(), EdgeType::DIRECTED);
        if ( (*itr).getOrig()->isMostEfficient() && (*itr).getDest()->isMostEfficient() )  {
            gv->setEdgeColor(i, "red");
            cout << "Street | From Lat: " << setw(10) << (*itr).getOrig()->getLat() << " | Lon: " << setw(10) << (*itr).getOrig()->getLon() <<
            " to Lat: " << setw(10) << (*itr).getOrig()->getLat() << " | Lon: " << setw(10) << (*itr).getOrig()->getLon() << endl;
        }
        i++;
    }

    cout << "\nPOI's to visit:\n" << endl;
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if ((*it)->isMostEfficient() && (*it)->getVisitTime() != 0)  {
            gv->setVertexSize((*it)->getId(), 10);
            gv->setVertexColor((*it)->getId(), "red");
            cout << "POI | Lat: " << setw(10) << (*it)->getLat() << " | Lon: " << setw(10) << (*it)->getLon() << endl;
        }
    }

    gv->rearrange();

}

/**
 * Aplica o Algoritmo de Prim e de Pesquisa e Peso
 */
void Menu::calculate(){
    string nothing;
    if(!poi){
        cout << "\n     Nenhum tipo de POI escolhidos"<< endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        currentState = MAINMENU;
        return;
    }
    if(map.getNodes().size() == 0) {
        cout << "\n     Nenhum tipo de Mapa escolhido"<< endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');// para forçar o user a carregar no Enter
        currentState = MAINMENU;
        return;
    }
    if(timeAvailable == 0) {
        cout << "\n     Tempo disponível não definido"<< endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n'); // para forçar o user a carregar no Enter
        currentState = MAINMENU;
        return;
    }


    this->map.userPreferences(this->types);

    std::vector<Node* > afterPrim;

    if(usingCar)
        afterPrim = this->map.calculatePrim(&initNode, (timeAvailable * carSpeedMultiplier));
    else
       afterPrim = this->map.calculatePrim(&initNode, timeAvailable);

    lastNodeId = BFSFindBestPath(afterPrim, &initNode);

    showGraph(afterPrim, map.getEdges());

}

/**
 * Constructor
 */
Menu::Menu() {
    currentState = START;

    this->types.estatua = 0;
    this->types.museu = 0;
    this->types.estadio = 0;
    this->types.livraria = 0;
    this->types.palacio = 0;
    this->types.parque = 0;
}

double long Menu::getWalkingSpeed() {
    return walkingSpeed;
}

/**
 * Algoritmo de Pesquisa e Peso utilizado para descobrir o maior número de pontos possivel num percurso
 * @param vector vector de nodes depois do corrido o algoritmo de Prim
 */
double Menu::BFSFindBestPath(vector<Node *> vector, Node * start) {

    std::vector<Node *> nodePath;
    std::vector<Edge *> edgePath;

    std::vector<Node *> nodesOnEdge;

    // Buscar Node com maior dist
    int lastDist = 0;
    Node* longestNode;
    for(auto it = vector.begin(); it != vector.end(); ++it){
        if( (*it)->getDist() > lastDist  ){
            longestNode = (*it);
            lastDist = (*it)->getDist();
        }
    }

    Node* lastPath = longestNode;
    while(!(lastPath->getId() == start->getId())){
        nodePath.push_back(lastPath->getPath());
        lastPath = lastPath->getPath();
    }

    for(auto it = nodePath.begin(); it != nodePath.end(); ++it){
        (*it)->setMostEfficient(true);
    }

    return longestNode->getId();
}


