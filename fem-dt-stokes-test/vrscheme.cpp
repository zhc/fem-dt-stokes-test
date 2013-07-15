#include "vrscheme.h"
#include <dolfin.h>
#include "ufl/VR1.h"
#include "ufl/VR2.h"
#include "ufl/VR3.h"
#include "domains.h"
#include "ufl/L2V.h"

using namespace dolfin;

VRScheme::VRScheme(const Settings &settings) : BaseSolver(settings)
{
    spaces.push_back(new VR1::FunctionSpace(_mesh));
    spaces.push_back(new VR2::FunctionSpace(_mesh));

    FunctionSpace& velocitySpace = *spaces[0];
    FunctionSpace& pressureSpace = *spaces[1];

    bcs.push_back(createMoveableBC(velocitySpace));
    bcs.push_back(createNoslipBC(velocitySpace));
    bcs.push_back(createPinpointBC(pressureSpace));

    VR1::BilinearForm   *bf1 = new VR1::BilinearForm(velocitySpace, velocitySpace);
    VR1::LinearForm     *lf1 = new VR1::LinearForm(velocitySpace);
    VR2::BilinearForm   *bf2 = new VR2::BilinearForm(pressureSpace, pressureSpace);
    VR2::LinearForm     *lf2 = new VR2::LinearForm(pressureSpace);
    VR3::BilinearForm   *bf3 = new VR3::BilinearForm(velocitySpace, velocitySpace);
    VR3::LinearForm     *lf3 = new VR3::LinearForm(velocitySpace);

    lfs.push_back(lf1);
    lfs.push_back(lf2);
    lfs.push_back(lf3);
    bfs.push_back(bf1);
    bfs.push_back(bf2);
    bfs.push_back(bf3);

    Function* u1 = new Function(velocitySpace);
    Function* u2 = new Function(velocitySpace);
    Function* u10 = new Function(velocitySpace);
    Function* u20 = new Function(velocitySpace);
    Function* p2 = new Function(pressureSpace);
    Function* p20 = new Function(pressureSpace);

    vars.push_back(u1);
    vars.push_back(u2);
    vars.push_back(u10);
    vars.push_back(u20);
    vars.push_back(p2);
    vars.push_back(p20);

    bf1->tau = *tau;
    lf1->tau = *tau;
    lf1->u10 = *u10;
    lf1->p20 = *p20;
    lf2->p20 = *p20;
    lf2->tau = *tau;
    lf2->u1 = *u1;
    lf2->u10 = *u10;
    bf3->tau = *tau;
    lf3->tau = *tau;
    lf3->u1 = *u1;
    lf3->u20 = *u20;
    lf3->p2 = *p2;
}

VRScheme::~VRScheme()
{
    printf("destruct vrscheme\n");
}

void VRScheme::solveStep(double t)
{
    dolfin::solve(*bfs[0] == *lfs[0], *vars[0], bcs1, _params);
    dolfin::solve(*bfs[1] == *lfs[1], *vars[4], bcs2, _params);
    dolfin::solve(*bfs[2] == *lfs[2], *vars[1], bcs1, _params);
    save(t, *vars[1], *vars[4]);
    *vars[2] = *vars[0];
    *vars[3] = *vars[1];
    *vars[5] = *vars[4];
}

std::string VRScheme::name()
{
    return "vr";
}
