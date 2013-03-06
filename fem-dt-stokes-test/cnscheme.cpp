#include "cnscheme.h"
#include "ufl/CN1.h"
#include "ufl/CN2.h"
#include <dolfin.h>
#include "domains.h"

using namespace dolfin;

CNScheme::CNScheme(const Settings &settings) : BaseSolver(settings)
{
    CN1::FunctionSpace* superSpace = new CN1::FunctionSpace(_mesh);
    SubSpace* velocitySpace = new SubSpace(*superSpace, 0);
    SubSpace* pressureSpace = new SubSpace(*superSpace, 1);
    CN2::FunctionSpace* pressureSpace2 = new CN2::FunctionSpace(_mesh);

    spaces.push_back(superSpace);
    spaces.push_back(velocitySpace);
    spaces.push_back(pressureSpace);
    spaces.push_back(pressureSpace2);

    bcs.push_back(createMoveableBC(*velocitySpace));
    bcs.push_back(createNoslipBC(*velocitySpace));
    bcs.push_back(createPinpointBC(*pressureSpace));

    CN1::BilinearForm* bf1 = new CN1::BilinearForm(*superSpace, *superSpace);
    CN1::LinearForm* lf1 = new CN1::LinearForm(*superSpace);
    CN2::BilinearForm* bf2 = new CN2::BilinearForm(*pressureSpace2, *pressureSpace2);
    CN2::LinearForm* lf2 = new CN2::LinearForm(*pressureSpace2);

    bfs.push_back(bf1);
    bfs.push_back(bf2);
    lfs.push_back(lf1);
    lfs.push_back(lf2);

    Function* w1 = new Function(*superSpace);
    Function* w0 = new Function(*superSpace);
    Function* gamma = new Function(*pressureSpace2);
    Function* p0 = new Function(*pressureSpace2);
    Function* p1 = new Function(*pressureSpace2);

    vars.push_back(w1);
    vars.push_back(w0);
    vars.push_back(gamma);
    vars.push_back(p0);
    vars.push_back(p1);

    lf1->w0 = *w0;
    lf1->tau = *tau;
    bf1->tau = *tau;
    lf2->gamma = *gamma;
    lf2->p0 = *p0;
}

CNScheme::~CNScheme()
{
    printf("destruct cn\n");
}

void CNScheme::solveStep(double t)
{
    dolfin::solve(*bfs[0] == *lfs[0], *vars[0], bcs, _params);
    *vars[2] = (*vars[0])[1];
    dolfin::solve(*bfs[1] == *lfs[1], *vars[4], _params);
    save(t, (*vars[0])[0], *vars[4]);
    *vars[1] = *vars[0];
    *vars[3] = *vars[4];
}

std::string CNScheme::name()
{
    return "cn";
}
