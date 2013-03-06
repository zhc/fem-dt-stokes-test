#ifndef LBSCHEME_H
#define LBSCHEME_H

#include "basesolver.h"

class LBScheme : public BaseSolver
{
public:
    LBScheme(const Settings& _settings);
    ~LBScheme();
    void solveStep(double t);
    std::string name();
};

#endif // LBSCHEME_H
