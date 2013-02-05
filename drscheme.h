#ifndef DRSCHEME_H_
#define DRSCHEME_H_

#include <dolfin.h>
#include "basesolver.h"

class DRScheme : public BaseSolver {
public:
    DRScheme(const Settings& settings);
    ~DRScheme();
	void solve();
    std::string name();
private:
};

#endif /* DRSOLVER_H_ */
