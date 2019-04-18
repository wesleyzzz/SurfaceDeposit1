//doing the RHS of du/dt=v-u

#include "Udeposit.h"

registerMooseObject("SurfaceDeposit1App", Udeposit);

template <>
InputParameters
validParams<Udeposit>()
{
  InputParameters params = validParams<NodalKernel>();
  params.addCoupledVar("coupled_var", "	Choose the variable you want to couple");
  return params;
}

Udeposit::Udeposit(const InputParameters & parameters)
  : NodalKernel(parameters), 
    _couple_var(coupledValue("coupled_var")),
    _couple_var_offjac(coupled("coupled_var"))
{
}


Real
Udeposit::computeQpResidual()
{
    return  -(_couple_var[_qp] - _u[_qp]);
}


Real
Udeposit::computeQpJacobian()
{
  return 1.;
}

Real
Udeposit::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _couple_var_offjac)
    return -1.;
  else
    return 0;
}
