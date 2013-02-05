#include "solverfactory.h"
#include "cnscheme.h"
#include "drscheme.h"
#include "prscheme.h"
#include "lbscheme.h"
#include "implicitscheme.h"
#include <map>

SolverFactory::SolverFactory(const Settings &settings) : _settings(settings)
{
}

BaseSolver *SolverFactory::create()
{
    std::map<std::string, BaseSolver*> solvers;
    std::string solverNames;
    BaseSolver *solver;
    solver = new CNScheme(_settings);
    solvers[solver->name()] = solver;
    solver = new DRScheme(_settings);
    solvers[solver->name()] = solver;
    solver = new PRScheme(_settings);
    solvers[solver->name()] = solver;
    solver = new LBScheme(_settings);
    solvers[solver->name()] = solver;
    solver = new ImplicitScheme(_settings);
    solvers[solver->name()] = solver;

    solver = 0;

    for(std::map<std::string, BaseSolver*>::iterator it = solvers.begin(); it != solvers.end(); it++){
        solverNames += it->first + " ";
        if (it->first == _settings.scheme){
            solver = it->second;
        } else {
            delete it->second;
        }
    }

    if (!solver){
        std::cerr << "Unknown scheme: " << _settings.scheme << ". Available schemes: "<< solverNames << std::endl;
        exit(-1);
    }

    return solver;
}
