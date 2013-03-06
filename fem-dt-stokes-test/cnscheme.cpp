#include "cnscheme.h"
#include "ufl/CN1.h"
#include "ufl/CN2.h"
#include <dolfin.h>
#include "domains.h"

using namespace dolfin;

CNScheme::CNScheme(const Settings &settings) : BaseSolver(settings)
{
}

CNScheme::~CNScheme()
{
}

void CNScheme::solve()
{
    CN1::FunctionSpace superSpace(_mesh);
    SubSpace velocitySpace(superSpace, 0);
    SubSpace pressureSpace(superSpace, 1);
    CN2::FunctionSpace pressureSpace2(_mesh);

    std::auto_ptr<BoundaryCondition> bc1(createMoveableBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc0(createNoslipBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc2(createPinpointBC(pressureSpace));
    std::vector<const BoundaryCondition*> bcs;
    bcs.push_back(bc0.get());
    bcs.push_back(bc1.get());
    bcs.push_back(bc2.get());

    CN1::BilinearForm bf1(superSpace, superSpace);
    CN1::LinearForm lf1(superSpace);
    CN2::BilinearForm bf2(pressureSpace2, pressureSpace2);
    CN2::LinearForm lf2(pressureSpace2);

    Constant tau(_settings.delta_time);
    Function w1(superSpace);
    Function w0(superSpace);
    Function gamma(pressureSpace2);
    Function p0(pressureSpace2);
    Function p1(pressureSpace2);
    lf1.w0 = w0;
    lf1.tau = tau;
    bf1.tau = tau;
    lf2.gamma = gamma;
    lf2.p0 = p0;

    double t = 0;
    Timer timer("Calculation timer");
    timer.start();
    while(t <= _settings.max_time + _settings.delta_time){
        info("t=%lf", t);
        dolfin::solve(bf1 == lf1, w1, bcs, _params);
        gamma = w1[1];
        dolfin::solve(bf2 == lf2, p1, _params);
        save(t, w1[0], p1);
        t += _settings.delta_time;
        w0 = w1;
        p0 = p1;
    }
    timer.stop();
    list_timings();
}

std::string CNScheme::name()
{
    return "cn";
}
