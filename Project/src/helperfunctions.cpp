#include "helperfunctions.h"
#include "Graph.h"

/**
 * Function to help checking file existance: Using FILE is faster than ifstream for this.
 * @param[in] <string> name for the file to check it's existance (including file extension)
 * @param[out] <bool> true if file exists, false if it doesn't
 * */
bool fileExists(const std::string& filename) {
    if (FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

/**
 * Converte de Graus para radianos
 * @tparam T double, int, float , etc
 * @param deg Graus a converter
 * @return deg em Radianos
 */
template <class T>
T grauToRad(T deg) {
    return (deg * 0.017453292519943295);
}

/**
 * Calcula a distancia entre 2 Nodes. Usando a Fórmula de Haversine
 * @param origin Node de origem
 * @param dest   Node de destino
 * @return   Distancia em metros.
 */
double distanceBetweenNodes(Node* origin, Node* dest){
    double earthRadius = 6371000;

    double curv1 = origin->getLat() * ( M_PI/180);
    double curv2 = dest->getLat() * ( M_PI/180);

    double deltaLats =  grauToRad(dest->getLat() - origin->getLat());
    double deltaLongs =  grauToRad(dest->getLon() - origin->getLon());

    double a = sin(deltaLats/2) * sin(deltaLats/2) +
                    cos(curv1) * cos(curv2) *
                    sin(deltaLongs/2) * sin(deltaLongs/2);

    double c = (double) 2 * atan2(sqrt(a), sqrt( (double)1 - a ));

    return (earthRadius * c);
}
