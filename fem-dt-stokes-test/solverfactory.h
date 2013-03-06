#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H

#include "settings.h"
#include "basesolver.h"

class SolverFactory
{
public:
    SolverFactory(Settings& settings);
    BaseSolver* createEx();
    BaseSolver* createTest();
private:
    Settings& _settings;
    BaseSolver* create();
};

#endif // SOLVERFACTORY_H
