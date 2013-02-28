#include "solverfactory.h"
#include <fstream>

using namespace dolfin;

int main(int argc, char *argv[]){
    Settings settings(argc, argv);
    set_log_active();
    std::string logname = settings.output_dir + "/log.txt";
    std::ofstream out(logname.c_str());
    set_output_stream(out);
    info("Using parameters: " + settings.toString());
    SolverFactory factory(settings);
    BaseSolver *solver = factory.create();
    solver->solve();
    delete solver;

}
