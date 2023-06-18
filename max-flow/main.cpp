#include <iostream>
#include <chrono>
#include "Hypercube.h"

int main(int argc, char** argv) {
    int k;
    int meta;
    if (argc < 3) {
        std::cerr << "wrong number of arguments";
        return 1;
    }
    if (std::string(argv[1]) == "-size") {
        k = atoi(argv[2]);
        meta = int(pow(2,k) - 1);
    } else return 1;

    int numOfPaths = -1;
    auto begin = std::chrono::high_resolution_clock::now();

    Hypercube hypercube = Hypercube(k);
    std::cout << "max flow: " << hypercube.maxFlow(0, meta, numOfPaths) << '\n';
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now() - begin);
    if (argc == 4 && std::string(argv[3]) == "-printFlow")
        hypercube.printFlow();

    std::cerr << "t = " << t.count() << " ms\n";
    std::cerr << "number of paths found: " << numOfPaths;
    return 0;
}
