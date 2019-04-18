//revised from ConstantRate

#ifndef UDEPOSIT_H
#define UDEPOSIT_H

#include "NodalKernel.h"

// Forward Declarations
class Udeposit;

template <>
InputParameters validParams<Udeposit>();

class Udeposit : public NodalKernel
{
public:
  /**
   * Constructor initializes the rate
   */
  Udeposit(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const VariableValue & _couple_var;
  const unsigned _couple_var_offjac;

};

#endif
