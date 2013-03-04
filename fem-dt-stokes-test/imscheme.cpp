#include "imscheme.h"
#include <dolfin.h>
#include "ufl/IM.h"
#include "domains.h"

using namespace dolfin;

IMScheme::IMScheme(const Settings &settings)
    : BaseSolver(settings)
{
}


void IMScheme::solve()
{
    IM::FunctionSpace superSpace(_mesh);
    SubSpace velocitySpace(superSpace, 0);
    SubSpace pressureSpace(superSpace, 1);

    std::auto_ptr<BoundaryCondition> bc1(createMoveableBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc0(createNoslipBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc2(createPinpointBC(pressureSpace));
    std::vector<const BoundaryCondition*> bcs;
    bcs.push_back(bc0.get());
    bcs.push_back(bc1.get());
    bcs.push_back(bc2.get());

    IM::BilinearForm bf1(superSpace, superSpace);
    IM::LinearForm lf1(superSpace);

    Constant tau(_settings.dt);
    Function w1(superSpace);
    Function w0(superSpace);
    lf1.w0 = w0;
    lf1.tau = tau;
    bf1.tau = tau;

    double t = 0;
    Timer timer("Calculation timer");
    timer.start();

    while(t <= _settings.t + _settings.dt){
        info("t=%lf", t);
        dolfin::solve(bf1 == lf1, w1, bcs, _params);
        save(t, w1[0], w1[1]);
        t += _settings.dt;
        w0 = w1;
    }

    timer.stop();
    list_timings();
}

std::string IMScheme::name()
{
    return "im";
}
