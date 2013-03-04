#ifndef PRSCHEME_H
#define PRSCHEME_H

#include "basesolver.h"

class PRScheme : public BaseSolver
{
public:
    PRScheme(const Settings& settings);
    ~PRScheme();
    void solve();
    std::string name();
private:

};

#endif // PRSCHEME_H
