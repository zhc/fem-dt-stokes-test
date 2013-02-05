#ifndef BASESOLVER_H
#define BASESOLVER_H

#include "settings.h"
#include <dolfin.h>

class BaseSolver
{
public:
    BaseSolver(const Settings& _settings);
    virtual ~BaseSolver();
    virtual void solve() = 0;
    virtual std::string name() = 0;
    void save(double t, dolfin::Function& u, dolfin::Function& p);
protected:
    const Settings& _settings;
    dolfin::Parameters _params;
    dolfin::File _velocityFile;
    dolfin::File _pressureFile;
private:
    bool isInteresting(double t);
};

#endif // BASESOLVER_H
