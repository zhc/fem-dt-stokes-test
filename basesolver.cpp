#include "basesolver.h"
#include <dolfin.h>
#include <fstream>
#include <cstdio>

using namespace dolfin;

BaseSolver::BaseSolver(const Settings &settings)
    : _settings(settings),
      _velocityFile(_settings.output_dir+"/u.pvd"),
      _pressureFile(_settings.output_dir+"/p.pvd")
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
        _velocityFile 	<< u;
        _pressureFile 	<< p;

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
}

bool BaseSolver::isInteresting(double t)
{
    return true;

    double eps = _settings.dt/10;
    if (fabs(t-0.2)<eps){
        return true;
    }
    return false;
//    cout << "ttttttt=" << t << endl;
//    if (fabs(t-0.05)<eps || fabs(t-0.1)<eps || fabs(t-0.15)<eps || fabs(t-0.2)<eps){
//        return true;
//    }
//    return false;
}
