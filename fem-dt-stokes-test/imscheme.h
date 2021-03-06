#ifndef IMSCHEME_H
#define IMSCHEME_H

#include "basesolver.h"

class IMScheme : public BaseSolver
{
public:
    IMScheme(const Settings& settings);
    ~IMScheme();
    void solveStep(double t);
    std::string name();
};

#endif // MIXEDSCHEMEGRAD_H
