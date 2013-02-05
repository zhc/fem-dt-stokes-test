#ifndef IMPLICITSCHEME_H
#define IMPLICITSCHEME_H

#include "basesolver.h"

class ImplicitScheme : public BaseSolver
{
public:
    ImplicitScheme(const Settings& settings);
    void solve();
    std::string name();
};

#endif // MIXEDSCHEMEGRAD_H
