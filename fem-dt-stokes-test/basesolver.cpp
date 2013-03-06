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
}

BaseSolver::~BaseSolver()
{
    for(std::vector<Function*>::iterator it=calculatedVelocity.begin(); it != calculatedVelocity.end(); it++){
        delete (*it);
    }
    for(std::vector<Function*>::iterator it=calculatedPressure.begin(); it != calculatedPressure.end(); it++){
        delete (*it);
    }
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
//    assert(this->calculatedPressure.size() == this->calculatedVelocity.size());
//    assert(exact->calculatedPressure.size() == exact->calculatedVelocity.size());
//    assert(this->calculatedPressure.size() == exact->calculatedVelocity.size());
    int i;
    for(i=0;i<this->calculatedPressure.size();i++){
        Function *test_u = calculatedVelocity[i];
        Function *ex_u = exact->calculatedVelocity[i];
        L2V::Functional unorm_func(exact->_mesh, *test_u, *ex_u);
//        L2V::Functional unorm_func(this->_mesh, *test_u);
        double unorm = sqrt(assemble(unorm_func));
        printf("1111unorm=%lf at i=%d\n", unorm, i);

//        Function in_test_u(*ex_u);
//        in_test_u.interpolate(*test_u);

//        L2V::Functional M_u1(exact->_mesh, in_test_u, *ex_u);
//        double unorm = assemble(M_u1);
//        printf("%lf\n", unorm);

//        L2V::Functional M_u2(exact->_mesh, *test_u, *ex_u);
//        unorm = assemble(M_u2);
//        printf("%lf\n", unorm);

//        L2V::Functional M_u3(exact->_mesh, *test_u, *test_u);
//        unorm = assemble(M_u3);
//        printf("%lf\n", unorm);

//        L2V::Functional M_u4(exact->_mesh, *ex_u, *ex_u);
//        unorm = assemble(M_u4);
//        printf("%lf\n", unorm);

//        L2V::Functional M_u5(exact->_mesh, in_test_u, *test_u);
//        unorm = assemble(M_u5);
//        printf("%lf\n", unorm);

//        break;
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
//    outPressure << std::fixed << std::setprecision(10);
//    outVelo << std::fixed << std::setprecision(10);

//    Array<double> values(2);
//    double step = 1.0/80.0;
//    for(double x=0; x<=1; x += step){
//        for(double y=0; y<=1; y += step){
//            double pressure = p(x, y);
//            u(values, x, y);
//            outPressure     << x << " " << y  << " " << pressure  << std::endl;
//            outVelo         << x << " " << y  << " " << values[0] << " " << values[1] << std::endl;
//        }
    //    }
}

void BaseSolver::saveFunctions(double t, Function &u, Function &p)
{
//    L2V::Functional unorm_func(this->_mesh, u);
//    double unorm = sqrt(assemble(unorm_func));
//    printf("asbndabdjunorm=%lf at i=%lf\n", unorm, t);
    calculatedVelocity.push_back(new Function(u));
    calculatedPressure.push_back(new Function(p));


//    static int nnn = 0;
//    if (nnn<5){
//        nnn++;
//    } else {
//        exit(1);
//    }

//    L2V::Functional unorm_func1(this->_mesh, *calculatedVelocity[0]);
//    double unorm = sqrt(assemble(unorm_func1));
//    printf("aaaaaaaaaaaaaaanorm=%lf at i=%lf\n", unorm, t);
}
