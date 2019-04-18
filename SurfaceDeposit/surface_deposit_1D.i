[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmax = 1
  ny = 10
[]

[Variables]
  [C_O]
    order = FIRST
    family = LAGRANGE
    [InitialCondition]
      type = ConstantIC
      value = 1
      variable = C_O
    []
  []
  [C_R]
    family = LAGRANGE
    order = FIRST
    [InitialCondition]
      type = ConstantIC
      value = 0
      variable = C_R
    []
  []
[]

[Kernels]
  [C_O_diff]
    type = MatDiffusion
    variable = C_O
    D_name = D_O
  []
  [C_O_dot]
    type = TimeDerivative
    variable = C_O
  []
  [C_R]
    type = NullKernel
    variable = C_R
  []
[]

[BCs]
  [C_O_right]
    type = DirichletBC
    variable = C_O
    boundary = 'right'
    value = 1
  []
  [C_O_left_coupled_Flux]
    # C_O (primary var) will couple the value of C_R (coupled var)
    type = FluxBCudot
    variable = C_O
    boundary = 'left'
    coupled_var = 'C_R'
  []
[]

[Materials]
  [Diffusivity_of_C_O]
    type = GenericConstantMaterial
    prop_names = 'D_O'
    prop_values = '0.01'
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  # solve_type = NEWTON
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
  type = Transient
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  petsc_options = '-ksp_converged_reason -snes_converged_reason -snes_test_display'
  solve_type = PJFNK
  num_steps = 1000
  end_time = 1.8
  dtmax = 0.5e-2
  line_search = basic
  [TimeStepper]
    type = IterationAdaptiveDT
    dt = 0.5e-2
  []
[]

[Outputs]
  # execute_on = 'TIMESTEP_END'
  # csv = true
  exodus = true
[]

[Debug]
  show_var_residual_norms = true
[]

[Postprocessors]
  [C_O]
    type = NodalVariableValue
    nodeid = 0
    variable = C_O
  []
  [Flux_C_O]
    type = SideFluxIntegral
    diffusivity = D_O
    variable = 'C_O'
    boundary = 'left'
  []
  [C_R]
    type = NodalVariableValue
    nodeid = 0
    variable = C_R
  []
[]

[NodalKernels]
  [Udeposit_dot]
    type = TimeDerivativeNodalKernel
    variable = C_R
    boundary = 'left'
  []
  [Udeposit_other]
    type = Udeposit
    variable = C_R
    coupled_var = 'C_O'
    boundary = 'left'
  []
[]
