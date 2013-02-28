#include "basesolver.h"
#include <dolfin.h>
#include <fstream>
#include <cstdio>
#include <domains.h>

using namespace dolfin;

BaseSolver::BaseSolver(const Settings &settings)
    : _settings(settings),
      _velocityFile(_settings.output_dir+"/u.pvd"),
      _pressureFile(_settings.output_dir+"/p.pvd"),
      _moveRight(1, 0),
      _noSlip(0, 0),
      _zero(0),
      _mesh(_settings.nx, _settings.nx)
{
    set_log_level(_settings.log_level);
    _params.add("linear_solver", _settings.solver_name);
    _params.add("preconditioner", _settings.precond_name);    
}

BaseSolver::~BaseSolver()
{
}

void BaseSolver::save(double t, Function &u, Function &p)
{
    if (isInteresting(t)){
        savePvd(t, u, p);
        saveTxt(t, u, p);
    }
}

BoundaryCondition *BaseSolver::createMoveableBC(FunctionSpace &space)
{
    DirichletBC *bc1 = new DirichletBC(space, _moveRight, _top);
    return bc1;
}

BoundaryCondition *BaseSolver::createNoslipBC(FunctionSpace &space)
{
    DirichletBC* bc0 = new DirichletBC(space, _noSlip, _walls);
    return bc0;
}

BoundaryCondition *BaseSolver::createPinpointBC(FunctionSpace &space)
{
    DirichletBC* bc2 = new DirichletBC(space, _zero, _bottomPoint);
    return bc2;
}

bool BaseSolver::isInteresting(double t)
{
    return true;

    double eps = _settings.dt/10;
    if (fabs(t-0.2)<eps){
        return true;
    }
    return false;
}

void BaseSolver::saveTxt(double t, Function &u, Function &p)
{
    _velocityFile 	<< u;
    _pressureFile 	<< p;
}

void BaseSolver::savePvd(double t, Function &u, Function &p)
{
    std::stringstream ss;
    ss << t;
    std::ofstream outPressure((_settings.output_dir + "/p." +  ss.str() + ".txt").c_str());
    std::ofstream outVelo((_settings.output_dir + "/u." + ss.str() + ".txt").c_str());

    outPressure << std::fixed << std::setprecision(10);
    outVelo << std::fixed << std::setprecision(10);

    Array<double> values(2);
    double step = 1.0/200.0;
    for(double x=0; x<=1; x += step){
        for(double y=0; y<=1; y += step){
            double pressure = p(x, y);
            u(values, x, y);
            outPressure     << x << " " << y  << " " << pressure  << std::endl;
            outVelo         << x << " " << y  << " " << values[0] << " " << values[1] << std::endl;
        }
    }
}
