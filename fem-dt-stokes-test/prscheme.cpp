#include "prscheme.h"
#include "ufl/PR1.h"
#include "ufl/PR2.h"
#include "ufl/PR3.h"
#include "ufl/PR4.h"
#include "domains.h"

using namespace dolfin;

PRScheme::PRScheme(const Settings &settings) : BaseSolver(settings)
{
    PR1::FunctionSpace* velocitySpace = new PR1::FunctionSpace(_mesh);
    PR2::FunctionSpace* pressureSpace = new PR2::FunctionSpace(_mesh);
    spaces.push_back(velocitySpace);
    spaces.push_back(pressureSpace);

    bcs.push_back(createMoveableBC(*velocitySpace));
    bcs.push_back(createNoslipBC(*velocitySpace));
    bcs.push_back(createPinpointBC(*pressureSpace));

    PR1::BilinearForm* bf1 = new PR1::BilinearForm(*velocitySpace, *velocitySpace);
    PR1::LinearForm* lf1 = new PR1::LinearForm(*velocitySpace);
    PR2::BilinearForm* bf2 = new PR2::BilinearForm(*pressureSpace, *pressureSpace);
    PR2::LinearForm* lf2 = new PR2::LinearForm(*pressureSpace);
    PR3::BilinearForm* bf3 = new PR3::BilinearForm(*velocitySpace, *velocitySpace);
    PR3::LinearForm* lf3 = new PR3::LinearForm(*velocitySpace);
    PR4::BilinearForm* bf4 = new PR4::BilinearForm(*pressureSpace, *pressureSpace);
    PR4::LinearForm* lf4 = new PR4::LinearForm(*pressureSpace);
    bfs.push_back(bf1);
    bfs.push_back(bf2);
    bfs.push_back(bf3);
    bfs.push_back(bf4);
    lfs.push_back(lf1);
    lfs.push_back(lf2);
    lfs.push_back(lf3);
    lfs.push_back(lf4);

    Function* u0 = new Function(*velocitySpace);
    Function* u12 = new Function(*velocitySpace);
    Function* u1 = new Function(*velocitySpace);
    Function* p0 = new Function(*pressureSpace);
    Function* gamma = new Function(*pressureSpace);
    Function* p1 = new Function(*pressureSpace);
    vars.push_back(u0);
    vars.push_back(u12);
    vars.push_back(u1);
    vars.push_back(p0);
    vars.push_back(gamma);
    vars.push_back(p1);

    bf1->tau = *tau;
    lf1->tau = *tau;
    lf1->p0 = *p0;
    lf1->u0 = *u0;
    lf2->tau = *tau;
    lf2->u12 = *u12;
    lf3->tau = *tau;
    lf3->u0 = *u0;
    lf3->gamma = *gamma;
    lf3->u12 = *u12;
    lf4->gamma = *gamma;
    lf4->p0 = *p0;
}

PRScheme::~PRScheme()
{
    printf("destruct pr\n");
}


void PRScheme::solve()
{
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
        dolfin::solve(*bfs[3] == *lfs[3], *vars[3], _params);
        save(t, *vars[2], *vars[5]);
        t += _settings.delta_time;
        *vars[0] = *vars[2];
        *vars[3] = *vars[5];
    }
    timer.stop();
    list_timings();
}

std::string PRScheme::name()
{
    return "pr";
}
