#include "solverfactory.h"

using namespace dolfin;

int main(int argc, char *argv[]){
    Settings settings(argc, argv);
    cout << "Using parameters: " << settings.toString() << endl;
    SolverFactory factory(settings);
    BaseSolver *solver = factory.create();
    solver->solve();
    delete solver;

}
