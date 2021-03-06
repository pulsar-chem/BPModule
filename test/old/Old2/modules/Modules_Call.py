#!/usr/bin/env python3


import os
import sys
import argparse
import traceback 

# Add the pulsar path
thispath = os.path.dirname(os.path.realpath(__file__))
psrpath = os.path.join(os.path.dirname(thispath), "../", "modules")
sys.path.insert(0, psrpath)

import pulsar as psr


def Run(mm):
    try:
      out = psr.output.get_global_output()

      # Load the python modules
      #             supermodule      module name      key
      mm.load_module("TestModules",   "TestModule1",   "TESTMOD1")
      mm.load_module("TestModules",   "TestPyModule1", "TESTPYMOD1")

      mm.change_option("TESTMOD1", "double_opt_def", 1.111)
      mm.change_option("TESTMOD1", "int_opt_def", 55 )
      mm.print(out)
      mm.sanity_check()


      b1 = mm.get_module("TESTMOD1", 0)
      b2 = mm.get_module("TESTPYMOD1", 0)

      b1.run_test()
      psr.output.print_global_output("\n")
      b2.run_test()
      psr.output.print_global_output("\n")
    
      b3 = mm.get_module("TESTMOD1", 0)
      b4 = mm.get_module("TESTPYMOD1", 0)

      b3.run_test()
      psr.output.print_global_output("\n")
      b4.run_test()
      psr.output.print_global_output("\n")
    
      psr.output.print_global_output("\nDone testing\n")


    except Exception as e:
      psr.output.print_global_output("Caught exception in main handler\n")
      traceback.print_exc()
      psr.output.print_global_error("\n")
      psr.output.print_global_error(str(e))
      psr.output.print_global_error("\n")



psr.initialize(sys.argv, color = True, debug = True)

with psr.ModuleAdministrator() as mm:
    Run(mm)

psr.finalize()
