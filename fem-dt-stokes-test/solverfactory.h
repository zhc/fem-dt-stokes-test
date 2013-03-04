#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H

#include "settings.h"
#include "basesolver.h"

class SolverFactory
{
public:
    SolverFactory(const Settings& settings);
    BaseSolver* create();
private:
    const Settings& _settings;
};

#endif // SOLVERFACTORY_H
