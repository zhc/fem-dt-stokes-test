#include "drscheme.h"
#include <dolfin.h>
#include "ufl/DR1.h"
#include "ufl/DR2.h"
#include "ufl/DR3.h"
#include "ufl/DR4.h"
#include "domains.h"
#include "ufl/L2V.h"

using namespace dolfin;

DRScheme::DRScheme(const Settings& settings) : BaseSolver(settings)
{
    spaces.push_back(new DR1::FunctionSpace(_mesh));
    spaces.push_back(new DR2::FunctionSpace(_mesh));

    FunctionSpace& velocitySpace = *spaces[0];
    FunctionSpace& pressureSpace = *spaces[1];

    bcs.push_back(createMoveableBC(velocitySpace));
    bcs.push_back(createNoslipBC(velocitySpace));
    bcs.push_back(createPinpointBC(pressureSpace));

    DR1::BilinearForm   *bf1 = new DR1::BilinearForm(velocitySpace, velocitySpace);
    DR1::LinearForm     *lf1 = new DR1::LinearForm(velocitySpace);
    DR2::BilinearForm   *bf2 = new DR2::BilinearForm(pressureSpace, pressureSpace);
    DR2::LinearForm     *lf2 = new DR2::LinearForm(pressureSpace);
    DR3::BilinearForm   *bf3 = new DR3::BilinearForm(velocitySpace, velocitySpace);
    DR3::LinearForm     *lf3 = new DR3::LinearForm(velocitySpace);
    DR4::BilinearForm   *bf4 = new DR4::BilinearForm(pressureSpace, pressureSpace);
    DR4::LinearForm     *lf4 = new DR4::LinearForm(pressureSpace);

    lfs.push_back(lf1);
    lfs.push_back(lf2);
    lfs.push_back(lf3);
    lfs.push_back(lf4);
    bfs.push_back(bf1);
    bfs.push_back(bf2);
    bfs.push_back(bf3);
    bfs.push_back(bf4);

    Function* u0 = new Function(velocitySpace);
    Function* u12 = new Function(velocitySpace);
    Function* u1 = new Function(velocitySpace);
    Function* p0 = new Function(pressureSpace);
    Function* p01 = new Function(pressureSpace);
    Function* p1 = new Function(pressureSpace);

    vars.push_back(u0);
    vars.push_back(u12);
    vars.push_back(u1);
    vars.push_back(p0);
    vars.push_back(p01);
    vars.push_back(p1);


    bf1->tau = *tau;
    lf1->tau = *tau;
    lf1->p0 = *p0;
    lf1->u0 = *u0;
    lf2->tau = *tau;
    lf2->u12 = *u12;
    lf3->tau = *tau;
    lf3->p01 = *p01;
    lf3->u12 = *u12;
    lf4->p01 = *p01;
    lf4->p0 = *p0;
}

DRScheme::~DRScheme()
{
    printf("destruct drscheme\n");
}

void DRScheme::solve() {
    std::vector<const BoundaryCondition*> bcs;
    std::vector<const BoundaryCondition*> bcs2;

    bcs.push_back(this->bcs[0]);
    bcs.push_back(this->bcs[1]);
    bcs2.push_back(this->bcs[2]);

    double t = 0;
    Timer timer("Calculation timer");
    timer.start();
    while(t <= _settings.max_time + _settings.delta_time){
        info("t=%lf", t);
        dolfin::solve(*bfs[0] == *lfs[0], *vars[1], bcs, _params);
        dolfin::solve(*bfs[1] == *lfs[1], *vars[4], bcs2, _params);
        dolfin::solve(*bfs[2] == *lfs[2], *vars[2], bcs, _params);
        dolfin::solve(*bfs[3] == *lfs[3], *vars[5], _params);
        save(t, *vars[2], *vars[5]);
        t += _settings.delta_time;
        *vars[0] = *vars[2];
        *vars[3] = *vars[5];
    }
    timer.stop();
    list_timings();
}

std::string DRScheme::name()
{
    return "dr";
}
