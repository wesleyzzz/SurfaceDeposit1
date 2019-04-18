// operate on C_R or C_O, in coupling term they have the same form.
#include "FluxBCudot.h"

registerMooseObject("SurfaceDeposit1App", FluxBCudot);

template <>
InputParameters
validParams<FluxBCudot>()
{
  InputParameters params = validParams<IntegratedBC>();

  params.addCoupledVar("coupled_var", "	Choose the variable you want to couple");

  return params;
}

FluxBCudot::FluxBCudot(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _couple_var(coupledValue("coupled_var")),
    _couple_var_offjac(coupled("coupled_var")),
    _u_dot(dot()),
    _du_dot_du(dotDu())
{
}

Real
FluxBCudot::computeQpResidual()
{
    return  _test[_i][_qp] * (_u_dot[_qp]+(_u[_qp]-_couple_var[_qp]));
}

Real
FluxBCudot::computeQpJacobian()
{
  return _test[_i][_qp] * (_du_dot_du[_qp] + 1) * _phi[_j][_qp];
}

Real
FluxBCudot::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _couple_var_offjac)
    return _test[_i][_qp] * - _phi[_j][_qp];
  else
    return 0;
}



