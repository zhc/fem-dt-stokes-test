#ifndef DOMAINS_H_
#define DOMAINS_H_

#include <dolfin.h>

using namespace dolfin;

class DomainFloorAndWalls : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
	  return on_boundary && x[1] < 1 - DOLFIN_EPS;
  }
};

class DomainAllWalls : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
	  return on_boundary;
  }
};

class DomainTop : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
	  return on_boundary && x[1] > 1 - DOLFIN_EPS;
  }
};

class DomainBottomPoint : public SubDomain
{
  bool inside(const Array<double>& x, bool on_boundary) const
  {
	  return on_boundary && x[1] < DOLFIN_EPS && x[0] < 0.1;
  }
};

#endif /* DOMAINS_H_ */
