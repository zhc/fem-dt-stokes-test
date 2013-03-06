#ifndef BASESOLVER_H
#define BASESOLVER_H

#include "settings.h"
#include <dolfin.h>
#include <domains.h>

class BaseSolver
{
public:
    BaseSolver(const Settings& settings);
    virtual ~BaseSolver();
    virtual void solve() = 0;
    virtual std::string name() = 0;
    void save(double t, dolfin::Function& u, dolfin::Function& p);
    void compare(BaseSolver* exact);
protected:
//    BaseSolver(const Settings& settings);
    const Settings& _settings;
    dolfin::Parameters _params;
    dolfin::File _velocityFile;
    dolfin::File _pressureFile;
    dolfin::BoundaryCondition* createMoveableBC(dolfin::FunctionSpace& space);
    dolfin::BoundaryCondition* createNoslipBC(dolfin::FunctionSpace& space);
    dolfin::BoundaryCondition* createPinpointBC(dolfin::FunctionSpace& space);

    dolfin::UnitSquare _mesh;
    std::vector<const dolfin::BoundaryCondition*> bcs;
    std::vector<dolfin::Form*> bfs;
    std::vector<dolfin::Form*> lfs;
    std::vector<dolfin::FunctionSpace*> spaces;
    std::vector<dolfin::Function*> vars;
    dolfin::Constant *tau;

private:
    bool isInteresting(double t);
    void saveTxt(double t, dolfin::Function& u, dolfin::Function& p);
    void savePvd(double t, dolfin::Function& u, dolfin::Function& p);
    void saveFunctions(double t, dolfin::Function& u, dolfin::Function& p);

    dolfin::Constant _moveRight;
    dolfin::Constant _noSlip;
    dolfin::Constant _zero;
    DomainTop _top;
    DomainFloorAndWalls _walls;
    DomainBottomPoint _bottomPoint;

    std::vector<Function*> calculatedVelocity;
    std::vector<Function*> calculatedPressure;


};

#endif // BASESOLVER_H
