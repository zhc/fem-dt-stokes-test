#include "imscheme.h"
#include <dolfin.h>
#include "ufl/IM.h"
#include "domains.h"

using namespace dolfin;

IMScheme::IMScheme(const Settings &settings) : BaseSolver(settings)
{
}


void IMScheme::solve()
{
    UnitSquare mesh(_settings.nx, _settings.nx);

    IM::FunctionSpace superSpace(mesh);
    SubSpace velocitySpace(superSpace, 0);
    SubSpace pressureSpace(superSpace, 1);

    Constant noSlip(0, 0);
    Constant moveRight(1, 0);
    Constant zero(0);
    DomainTop top;
    DomainFloorAndWalls walls;
    DomainBottomPoint bottomPoint;
    DirichletBC bc0(velocitySpace, noSlip, walls);
    DirichletBC bc1(velocitySpace, moveRight, top);
    DirichletBC bc2(pressureSpace, zero, bottomPoint);
    std::vector<const BoundaryCondition*> bcs;
    bcs.push_back(&bc0);
    bcs.push_back(&bc1);
    bcs.push_back(&bc2);

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
        cout << "t = " << t << endl;
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
