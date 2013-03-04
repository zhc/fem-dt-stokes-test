#include "solverfactory.h"
#include <fstream>

using namespace dolfin;

int main(int argc, char *argv[]){
    Settings settings(argc, argv);
    info("Using parameters: " + settings.toString());
    SolverFactory factory(settings);
    BaseSolver *solver = factory.create();
    solver->solve();
    delete solver;
}
