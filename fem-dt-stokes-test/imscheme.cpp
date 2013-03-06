#include "imscheme.h"
#include <dolfin.h>
#include "ufl/IM.h"
#include "domains.h"

using namespace dolfin;

IMScheme::IMScheme(const Settings &settings)
    : BaseSolver(settings)
{
    IM::FunctionSpace* superSpace = new IM::FunctionSpace(_mesh);
    SubSpace* velocitySpace = new SubSpace(*superSpace, 0);
    SubSpace* pressureSpace = new SubSpace(*superSpace, 1);
    spaces.push_back(superSpace);
    spaces.push_back(velocitySpace);
    spaces.push_back(pressureSpace);

    bcs.push_back(createMoveableBC(*velocitySpace));
    bcs.push_back(createNoslipBC(*velocitySpace));
    bcs.push_back(createPinpointBC(*pressureSpace));

    IM::BilinearForm* bf1 = new IM::BilinearForm(*superSpace, *superSpace);
    IM::LinearForm* lf1 = new IM::LinearForm(*superSpace);
    bfs.push_back(bf1);
    lfs.push_back(lf1);

    Function* w1 = new Function(*superSpace);
    Function* w0 = new Function(*superSpace);
    vars.push_back(w1);
    vars.push_back(w0);

    lf1->w0 = *w0;
    lf1->tau = *tau;
    bf1->tau = *tau;
}

IMScheme::~IMScheme()
{
    printf("destruct im\n");
}

void IMScheme::solveStep(double t)
{
    dolfin::solve(*bfs[0] == *lfs[0], *vars[0], bcs, _params);
    save(t, (*vars[0])[0], (*vars[0])[1]);
    (*vars[1]) = (*vars[0]);
}

std::string IMScheme::name()
{
    return "im";
}
