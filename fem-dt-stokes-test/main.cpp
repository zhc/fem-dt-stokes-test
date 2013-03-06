#include "solverfactory.h"
#include <fstream>
//#define NDEBUG
#include <assert.h>


using namespace dolfin;

int main(int argc, char *argv[]){
    Settings settings(argc, argv);
    info("Using parameters: " + settings.toString());
    SolverFactory factory(settings);

    BaseSolver *solverTest = factory.createTest();
    solverTest->solve();

    BaseSolver *solverEx = factory.createEx();
    solverEx->solve();

    solverTest->compare(solverEx);

    delete solverTest;
    delete solverEx;
}
