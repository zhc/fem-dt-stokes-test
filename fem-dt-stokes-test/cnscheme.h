#ifndef CNSCHEME_H
#define CNSCHEME_H

#include <dolfin.h>
#include "basesolver.h"

class CNScheme : public BaseSolver {
public:
    CNScheme(const Settings& settings);
    ~CNScheme();
    void solve();
    std::string name();
private:
};


#endif // CNSCHEME_H
