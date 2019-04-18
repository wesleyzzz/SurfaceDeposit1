//revised from ConstantRate

#ifndef UDEPOSITFUNC_H
#define UDEPOSITFUNC_H

#include "NodalKernel.h"

// Forward Declarations
class UdepositFunc;
class Function;
//class NodalKernel;
template <>
InputParameters validParams<UdepositFunc>();

class UdepositFunc : public NodalKernel
{
public:
  /**
   * Constructor initializes the rate
   */
  UdepositFunc(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableValue & _couple_var;
  const unsigned _couple_var_offjac;
  Real _K_O;
  Function & _func_1;
 
  Function & _func_2;

};

#endif
