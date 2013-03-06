#include "prscheme.h"
#include "ufl/PR1.h"
#include "ufl/PR2.h"
#include "ufl/PR3.h"
#include "ufl/PR4.h"
#include "domains.h"

using namespace dolfin;

PRScheme::PRScheme(const Settings &settings) : BaseSolver(settings)
{

}

PRScheme::~PRScheme()
{
    printf("destruct pr\n");
}


void PRScheme::solve()
{
    PR1::FunctionSpace velocitySpace(_mesh);
    PR2::FunctionSpace pressureSpace(_mesh);

    std::auto_ptr<BoundaryCondition> bc1(createMoveableBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc0(createNoslipBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc2(createPinpointBC(pressureSpace));
    std::vector<const BoundaryCondition*> bcs;
    bcs.push_back(bc0.get());
    bcs.push_back(bc1.get());
    std::vector<const BoundaryCondition*> bcs2;
    bcs2.push_back(bc2.get());

    PR1::BilinearForm bf1(velocitySpace, velocitySpace);
    PR1::LinearForm lf1(velocitySpace);
    PR2::BilinearForm bf2(pressureSpace, pressureSpace);
    PR2::LinearForm lf2(pressureSpace);
    PR3::BilinearForm bf3(velocitySpace, velocitySpace);
    PR3::LinearForm lf3(velocitySpace);
    PR4::BilinearForm bf4(pressureSpace, pressureSpace);
    PR4::LinearForm lf4(pressureSpace);

    Constant tau(_settings.delta_time);
    Function u0(velocitySpace);
    Function u12(velocitySpace);
    Function u1(velocitySpace);
    Function p0(pressureSpace);
    Function gamma(pressureSpace);
    Function p1(pressureSpace);
    bf1.tau = tau;
    lf1.tau = tau;
    lf1.p0 = p0;
    lf1.u0 = u0;
    lf2.tau = tau;
    lf2.u12 = u12;
    lf3.tau = tau;
    lf3.u0 = u0;
    lf3.gamma = gamma;
    lf3.u12 = u12;
    lf4.gamma = gamma;
    lf4.p0 = p0;

    double t = 0;
    Timer timer("Calculation timer");
    timer.start();
    while(t <= _settings.max_time + _settings.delta_time){
        info("t=%lf", t);
        dolfin::solve(bf1 == lf1, u12, bcs, _params);
        dolfin::solve(bf2 == lf2, gamma, bcs2, _params);
        dolfin::solve(bf3 == lf3, u1, bcs, _params);
        dolfin::solve(bf4 == lf4, p1, _params);
        save(t, u1, p1);
        t += _settings.delta_time;
        u0 = u1;
        p0 = p1;
    }
    timer.stop();
    list_timings();
}

std::string PRScheme::name()
{
    return "pr";
}
