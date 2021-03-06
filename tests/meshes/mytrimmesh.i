[Mesh]
 type = MyTRIMMesh
  dim = 2
  nx = 60
  ny = 60
  xmin = 0
  xmax = 200
  ymin = -60
  ymax = 140
  elem_type = QUAD4
[]
[Variables]
  [./c]
    [./InitialCondition]
      type = FunctionIC
      function = 0.3*((x/1000)+(y/1000)^2+(z/1000)^3)+0.1
    [../]
  [../]
[]
[Problem]
  solve = false
  kernel_coverage_check = false
[]

[Executioner]
  type = Transient
  num_steps = 1
[]
[./num_elems_total]
   type = NumElems
   elem_filter = 'TOTAL'
   execute_on = 'initial timestep_end'
 [../]
[Outputs]
  exodus = true
[]
