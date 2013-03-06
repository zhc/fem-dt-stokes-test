#include "lbscheme.h"
#include "ufl/LB1.h"
#include "ufl/LB2.h"
#include "ufl/LB3.h"
#include "domains.h"

using namespace dolfin;

LBScheme::LBScheme(const Settings &_settings) : BaseSolver(_settings)
{
}

LBScheme::~LBScheme()
{
    printf("destruct lb\n");
}

void LBScheme::solve()
{
    LB1::FunctionSpace velocitySpace(_mesh);
    LB2::FunctionSpace pressureSpace(_mesh);

    std::auto_ptr<BoundaryCondition> bc1(createMoveableBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc0(createNoslipBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc2(createPinpointBC(pressureSpace));
    std::vector<const BoundaryCondition*> bcs;
    bcs.push_back(bc0.get());
    bcs.push_back(bc1.get());
    std::vector<const BoundaryCondition*> bcs2;
    bcs2.push_back(bc2.get());

    LB1::BilinearForm bf1(velocitySpace, velocitySpace);
    LB1::LinearForm lf1(velocitySpace);
    LB2::BilinearForm bf2(pressureSpace, pressureSpace);
    LB2::LinearForm lf2(pressureSpace);
    LB3::BilinearForm bf3(velocitySpace, velocitySpace);
    LB3::LinearForm lf3(velocitySpace);

    Constant tau(_settings.delta_time);
    Function u0(velocitySpace);
    Function u12(velocitySpace);
    Function u1(velocitySpace);
    Function p1(pressureSpace);
    bf1.tau = tau;
    lf1.tau = tau;
    lf1.u0 = u0;
    lf2.tau = tau;
    lf2.u12 = u12;
    lf3.tau = tau;
    lf3.p1 = p1;
    lf3.u12 = u12;

    double t = 0;
    Timer timer("Calculation timer");
    timer.start();
    while(t <= _settings.max_time + _settings.delta_time){
        info("t=%lf", t);
        dolfin::solve(bf1 == lf1, u12, bcs, _params);
        dolfin::solve(bf2 == lf2, p1, bcs2, _params);
        dolfin::solve(bf3 == lf3, u1, bcs, _params);
        save(t, u1, p1);
        t += _settings.delta_time;
        u0 = u1;
    }
    timer.stop();
    list_timings();
}

std::string LBScheme::name()
{
    return "lb";
}
