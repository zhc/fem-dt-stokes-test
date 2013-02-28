#include "drscheme.h"
#include <dolfin.h>
#include "ufl/DR1.h"
#include "ufl/DR2.h"
#include "ufl/DR3.h"
#include "ufl/DR4.h"
#include "domains.h"

using namespace dolfin;

DRScheme::DRScheme(const Settings& settings) : BaseSolver(settings)
{
}

DRScheme::~DRScheme()
{
}

void DRScheme::solve() {
    DR1::FunctionSpace velocitySpace(_mesh);
    DR2::FunctionSpace pressureSpace(_mesh);

    std::auto_ptr<BoundaryCondition> bc1(createMoveableBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc0(createNoslipBC(velocitySpace));
    std::auto_ptr<BoundaryCondition> bc2(createPinpointBC(pressureSpace));
    std::vector<const BoundaryCondition*> bcs;
    bcs.push_back(bc0.get());
    bcs.push_back(bc1.get());
    std::vector<const BoundaryCondition*> bcs2;
    bcs2.push_back(bc2.get());

    DR1::BilinearForm bf1(velocitySpace, velocitySpace);
    DR1::LinearForm lf1(velocitySpace);
    DR2::BilinearForm bf2(pressureSpace, pressureSpace);
    DR2::LinearForm lf2(pressureSpace);
    DR3::BilinearForm bf3(velocitySpace, velocitySpace);
    DR3::LinearForm lf3(velocitySpace);
    DR4::BilinearForm bf4(pressureSpace, pressureSpace);
    DR4::LinearForm lf4(pressureSpace);

    Constant tau(_settings.dt);
    Function u0(velocitySpace);
    Function u12(velocitySpace);
    Function u1(velocitySpace);
    Function p0(pressureSpace);
    Function p01(pressureSpace);
    Function p1(pressureSpace);
    bf1.tau = tau;
    lf1.tau = tau;
    lf1.p0 = p0;
    lf1.u0 = u0;
    lf2.tau = tau;
    lf2.u12 = u12;
    lf3.tau = tau;
    lf3.p01 = p01;
    lf3.u12 = u12;
    lf4.p01 = p01;
    lf4.p0 = p0;

	double t = 0;
	Timer timer("Calculation timer DR");
	timer.start();
    while(t <= _settings.t){
        dolfin::solve(bf1 == lf1, u12, bcs, _params);
        dolfin::solve(bf2 == lf2, p01, bcs2, _params);
        dolfin::solve(bf3 == lf3, u1, bcs, _params);
        dolfin::solve(bf4 == lf4, p1, _params);
        save(t, u1, p1);
        t += _settings.dt;
        u0 = u1;
        p0 = p1;
	}
	timer.stop();
    list_timings();
}

std::string DRScheme::name()
{
    return "dr";
}
