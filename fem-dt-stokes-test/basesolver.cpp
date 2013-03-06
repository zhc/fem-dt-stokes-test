#include "basesolver.h"
#include <dolfin.h>
#include <fstream>
#include <cstdio>
#include <domains.h>
#include "ufl/IM.h"
#include "ufl/L2V.h"

using namespace dolfin;

BaseSolver::BaseSolver(const Settings &settings)
    : _settings(settings),
      _velocityFile(_settings.output_dir+"/u."+_settings.mode+".pvd"),
      _pressureFile(_settings.output_dir+"/p."+_settings.mode+".pvd"),
      _moveRight(1, 0),
      _noSlip(0, 0),
      _zero(0),
      _mesh(_settings.mesh_size, _settings.mesh_size)
{
    set_log_level(_settings.log_level);
    _params.add("linear_solver", _settings.solver);
    _params.add("preconditioner", _settings.preconditioner);    
    tau = NULL;
}

BaseSolver::~BaseSolver()
{
    printf("destruct basesolver\n");
    for(std::vector<Function*>::iterator it=calculatedVelocity.begin(); it != calculatedVelocity.end(); it++){
        delete (*it);
    }
    for(std::vector<Function*>::iterator it=calculatedPressure.begin(); it != calculatedPressure.end(); it++){
        delete (*it);
    }
    for(std::vector<dolfin::BoundaryCondition*>::iterator it=bcs.begin(); it!=bcs.end(); it++){
        delete (*it);
    }
    for(std::vector<dolfin::Form*>::iterator it=bfs.begin(); it!=bfs.end(); it++){
        delete (*it);
    }
    for(std::vector<dolfin::Form*>::iterator it=lfs.begin(); it!=lfs.end(); it++){
        delete (*it);
    }
    for(std::vector<dolfin::FunctionSpace*>::iterator it=spaces.begin(); it!=spaces.end(); it++){
        delete (*it);
    }
    for(std::vector<dolfin::Function*>::iterator it=vars.begin(); it!=vars.end(); it++){
        delete (*it);
    }
    if (tau)
        delete tau;
}

void BaseSolver::save(double t, Function &u, Function &p)
{
    if (isInteresting(t)){
        savePvd(t, u, p);
        saveTxt(t, u, p);
        saveFunctions(t, u, p);
    }
}

void BaseSolver::compare(BaseSolver *exact)
{
    assert(this->calculatedPressure.size() == this->calculatedVelocity.size());
    assert(exact->calculatedPressure.size() == exact->calculatedVelocity.size());
    assert(this->calculatedPressure.size() == exact->calculatedVelocity.size());
    int i;
    for(i=0;i<this->calculatedPressure.size();i++){
        Function *test_u = calculatedVelocity[i];
        Function *ex_u = exact->calculatedVelocity[i];
        L2V::Functional unorm_func(exact->_mesh, *test_u, *ex_u);
        double unorm = sqrt(assemble(unorm_func));
        printf("unorm=%lf at i=%d\n", unorm, i);
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
    //save each 0.01 time step
    double eps = 0.0001;
    double k = 0;
    for(k=0.01; k<_settings.max_time + _settings.delta_time; k+=0.01) {
        if (fabs(k-t) < eps){
            return true;
        }
    }
    return false;
}

void BaseSolver::savePvd(double t, Function &u, Function &p)
{
    _velocityFile 	<< u;
    _pressureFile 	<< p;
}

void BaseSolver::saveTxt(double t, Function &u, Function &p)
{
    std::stringstream ss;
    ss << t;
    std::ofstream outPressure((_settings.output_dir + "/p." +  ss.str() + ".txt").c_str());
    std::ofstream outVelo((_settings.output_dir + "/u." + ss.str() + ".txt").c_str());
}

void BaseSolver::saveFunctions(double t, Function &u, Function &p)
{
    calculatedVelocity.push_back(new Function(u));
    calculatedPressure.push_back(new Function(p));
}
