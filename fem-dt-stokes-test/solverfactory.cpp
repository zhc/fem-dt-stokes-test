#include "solverfactory.h"
#include "cnscheme.h"
#include "drscheme.h"
#include "prscheme.h"
#include "lbscheme.h"
#include "imscheme.h"
#include "vrscheme.h"
#include <map>

SolverFactory::SolverFactory(Settings &settings) : _settings(settings)
{
}

BaseSolver *SolverFactory::createEx()
{
    _settings.prepareEx();
    return create();
}

BaseSolver *SolverFactory::createTest()
{
    _settings.prepareTest();
    return create();
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
    solver = new IMScheme(_settings);
    solvers[solver->name()] = solver;
    solver = new VRScheme(_settings);
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
