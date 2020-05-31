#ifndef TOURMATEAPP_HELPERFUNCTIONS_H
#define TOURMATEAPP_HELPERFUNCTIONS_H

#include "Graph.h"

bool fileExists(const std::string& filename);

double distanceBetweenNodes(Node* origin, Node* dest);

template <class T>
T grauToRad(T deg);

#endif //TOURMATEAPP_HELPERFUNCTIONS_H
