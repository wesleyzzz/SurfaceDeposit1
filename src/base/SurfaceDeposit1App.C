#include "SurfaceDeposit1App.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<SurfaceDeposit1App>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

SurfaceDeposit1App::SurfaceDeposit1App(InputParameters parameters) : MooseApp(parameters)
{
  SurfaceDeposit1App::registerAll(_factory, _action_factory, _syntax);
}

SurfaceDeposit1App::~SurfaceDeposit1App() {}

void
SurfaceDeposit1App::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"SurfaceDeposit1App"});
  Registry::registerActionsTo(af, {"SurfaceDeposit1App"});

  /* register custom execute flags, action syntax, etc. here */
}

void
SurfaceDeposit1App::registerApps()
{
  registerApp(SurfaceDeposit1App);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
SurfaceDeposit1App__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  SurfaceDeposit1App::registerAll(f, af, s);
}
extern "C" void
SurfaceDeposit1App__registerApps()
{
  SurfaceDeposit1App::registerApps();
}
