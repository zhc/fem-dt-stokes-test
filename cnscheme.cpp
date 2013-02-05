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
    UnitSquare mesh(_settings.nx, _settings.nx);
    CN1::FunctionSpace superSpace(mesh);
    SubSpace velocitySpace(superSpace, 0);
    SubSpace pressureSpace(superSpace, 1);

    CN2::FunctionSpace pressureSpace2(mesh);

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

    CN1::BilinearForm bf1(superSpace, superSpace);
    CN1::LinearForm lf1(superSpace);

    CN2::BilinearForm bf2(pressureSpace2, pressureSpace2);
    CN2::LinearForm lf2(pressureSpace2);

    Constant tau(_settings.dt);
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
    while(t <= _settings.t){
        dolfin::solve(bf1 == lf1, w1, bcs, _params);
        gamma = w1[1];
        dolfin::solve(bf2 == lf2, p1, _params);

//        _velocityFile << w1[0];
//        _pressureFile << p1;
        save(t, w1[0], p1);

        t += _settings.dt;
        w0 = w1;
        p0 = p1;
        cout << "t = " << t << endl;


    }
    timer.stop();
    list_timings();
}

std::string CNScheme::name()
{
    return "cn";
}
