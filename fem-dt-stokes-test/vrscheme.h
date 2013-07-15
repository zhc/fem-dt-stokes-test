#ifndef VRSCHEME_H
#define VRSCHEME_H

#include <dolfin.h>
#include "basesolver.h"

class VRScheme : public BaseSolver
{
public:
    VRScheme(const Settings& settings);
    ~VRScheme();
    void solveStep(double t);
    std::string name();
private:
};

#endif // VRSCHEME_H
