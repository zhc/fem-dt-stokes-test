#ifndef IMSCHEME_H
#define IMSCHEME_H

#include "basesolver.h"

class IMScheme : public BaseSolver
{
public:
    IMScheme(const Settings& settings);
    ~IMScheme();
    void solve();
    std::string name();
};

#endif // MIXEDSCHEMEGRAD_H
