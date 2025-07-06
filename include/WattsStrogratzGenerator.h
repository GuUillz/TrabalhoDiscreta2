#pragma once
#include "Graph.h"
#include <random>
class WattsStrogatzGenerator {
public:
    WattsStrogatzGenerator(const unsigned int&);

    Graph generate(const int&, const int&, const double&);
private:
    std::mt19937 rng;
    Graph createRing(const int&, const int&);
    void rewireGraph(Graph&,const int& ,const double&);

};