#include "lbscheme.h"
#include "ufl/LB1.h"
#include "ufl/LB2.h"
#include "ufl/LB3.h"
#include "domains.h"

using namespace dolfin;

LBScheme::LBScheme(const Settings &_settings) : BaseSolver(_settings)
{
    LB1::FunctionSpace *velocitySpace = new LB1::FunctionSpace(_mesh);
    LB2::FunctionSpace *pressureSpace = new LB2::FunctionSpace(_mesh);
    spaces.push_back(velocitySpace);
    spaces.push_back(pressureSpace);

    bcs.push_back(createMoveableBC(*velocitySpace));
    bcs.push_back(createNoslipBC(*velocitySpace));
    bcs.push_back(createPinpointBC(*pressureSpace));

    LB1::BilinearForm *bf1 = new LB1::BilinearForm(*velocitySpace, *velocitySpace);
    LB1::LinearForm *lf1 = new LB1::LinearForm(*velocitySpace);
    LB2::BilinearForm *bf2 = new LB2::BilinearForm(*pressureSpace, *pressureSpace);
    LB2::LinearForm *lf2 = new LB2::LinearForm(*pressureSpace);
    LB3::BilinearForm *bf3 = new LB3::BilinearForm (*velocitySpace, *velocitySpace);
    LB3::LinearForm *lf3 = new LB3::LinearForm(*velocitySpace);
    bfs.push_back(bf1);
    bfs.push_back(bf2);
    bfs.push_back(bf3);
    lfs.push_back(lf1);
    lfs.push_back(lf2);
    lfs.push_back(lf3);

    Function* u0 = new Function(*velocitySpace);
    Function* u12 = new Function(*velocitySpace);
    Function* u1 = new Function(*velocitySpace);
    Function* p1 = new Function(*pressureSpace);
    vars.push_back(u0);
    vars.push_back(u12);
    vars.push_back(u1);
    vars.push_back(p1);

    bf1->tau = *tau;
    lf1->tau = *tau;
    lf1->u0 = *u0;
    lf2->tau = *tau;
    lf2->u12 = *u12;
    lf3->tau = *tau;
    lf3->p1 = *p1;
    lf3->u12 = *u12;
}

LBScheme::~LBScheme()
{
    printf("destruct lb\n");
}

void LBScheme::solve()
{
    std::vector<const BoundaryCondition*> bcs;
    bcs.push_back(this->bcs[0]);
    bcs.push_back(this->bcs[1]);
    std::vector<const BoundaryCondition*> bcs2;
    bcs2.push_back(this->bcs[2]);

    double t = 0;
    Timer timer("Calculation timer");
    timer.start();
    while(t <= _settings.max_time + _settings.delta_time){
        info("t=%lf", t);
        dolfin::solve(*bfs[0] == *lfs[0], *vars[1], bcs, _params);
        dolfin::solve(*bfs[1] == *lfs[1], *vars[3], bcs2, _params);
        dolfin::solve(*bfs[2] == *lfs[2], *vars[2], bcs, _params);
        save(t, *vars[2], *vars[3]);
        t += _settings.delta_time;
        *vars[0] = *vars[2];
    }
    timer.stop();
    list_timings();
}

std::string LBScheme::name()
{
    return "lb";
}
