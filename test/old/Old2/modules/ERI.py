#!/usr/bin/env python3


import os
import sys
import traceback
import array

# Add the pulsar path
thispath = os.path.dirname(os.path.realpath(__file__))
psrpath = os.path.join(os.path.dirname(thispath), "../", "modules")
parent = os.path.join(os.path.dirname(thispath))
sys.path.insert(0, psrpath)
sys.path.insert(0, parent)

from pulsar.testing import *
from pulsar.system import *
from pulsar.datastore import *
from pulsar.output import *

from helper.TestAtoms import water

def CompareList(lst1, lst2, tol):
  if len(lst1) != len(lst2):
    return False

  else:
    for i in range(0, len(lst1)):
        if abs(lst1[i]-lst2[i]) > tol:
            return False

  return True

def Run(mm):
    try:

        out = get_global_output()

        # Load the python modules
        #             supermodule      module name      key
        mm.load_module("LibERD",        "LibERD_ERI",   "ERI")
        mm.print(out)
        mm.sanity_check()
  
        atoms = list(water)
        u = AtomSetUniverse()
        for a in atoms:
            u.insert(a)
        s = System(u, True)

        s = apply_single_basis("Primary","sto-3g",s)

         
        eri = mm.get_module("ERI", 0)
        eri.enable_debug(True)
        iwfn = Wavefunction()
        iwfn.system = s
        eri.SetInitialWfn(iwfn)
        eri.SetBases("Primary", "Primary", "Primary", "Primary")


        tester = Tester("Testing basic ERI")
        tester.print_header()

        ref_0000 = [ 4.78506540470550323e+00 ] 
 
        ref_1000 = [ 7.41380351973407792e-01,   # ( s  s  | s  s  )
                     0.00000000000000000e+00,   # ( px s  | s  s  )
                     0.00000000000000000e+00,   # ( py s  | s  s  )
                     8.20213813474668284e-18 ]  # ( pz s  | s  s  )

        ref_1010 = [ 1.36873385354388311e-01,   # ( s  s  | s  s  )
                     0.00000000000000000e+00,   # ( s  s  | px s  )
                     0.00000000000000000e+00,   # ( s  s  | py s  )
                     5.83811792070188069e-19,   # ( s  s  | pz s  )
                     0.00000000000000000e+00,   # ( px s  | s  s  )
                     0.00000000000000000e+00,   # ( py s  | s  s  )
                     5.83811792070188069e-19,   # ( pz s  | s  s  )
                     2.44774122580992542e-02,   # ( px s  | px s  )
                     0.00000000000000000e+00,   # ( px s  | py s  )
                     0.00000000000000000e+00,   # ( px s  | pz s  )
                     0.00000000000000000e+00,   # ( py s  | px s  )
                     2.44774122580992542e-02,   # ( py s  | py s  )
                     0.00000000000000000e+00,   # ( py s  | pz s  )
                     0.00000000000000000e+00,   # ( pz s  | px s  )
                     0.00000000000000000e+00,   # ( pz s  | py s  )
                     2.44774122580992542e-02 ]  # ( pz s  | pz s  )

        # Multi will calculate 0000, 0010, 1000, 1010
        # we take advantage of some permutational symmetry: ref_1000 = ref_0010
        ref_multi = list(ref_0000) + list(ref_1000) + list(ref_1000) + list(ref_1010)


        outbuf = array.array('d', [0]*1024)

        n = eri.calculate(0, 0, 0, 0, 0, outbuf)
        tester.test_value("Number of integrals for 0000", 1, n)
        tester.test_value("Values for 0000 integrals", True, CompareList(list(outbuf[:n]), ref_0000, 1e-15))

        n = eri.calculate(0, 1, 0, 0, 0, outbuf)
        tester.test_value("Number of integrals for 1000", 4, n)
        tester.test_value("Values for 1000 integrals", True, CompareList(list(outbuf[:n]), ref_1000, 1e-15))

        n = eri.calculate(0, 1, 0, 1, 0, outbuf)
        tester.test_value("Number of integrals for 1010", 16, n)
        tester.test_value("Values for 1010 integrals", True, CompareList(list(outbuf[:n]), ref_1010, 1e-15))

        n = eri.calculateMulti(0, [0, 1], [ 0 ], [0, 1], [ 0 ], outbuf)
        tester.test_value("Number of integrals for calculate multi", 25, n)
        tester.test_value("Values from calculateMulti", True, CompareList(list(outbuf[:n]), ref_multi, 1e-15))

        tester.print_results() 


    except Exception as e:
      print_global_output("Caught exception in main handler\n")
      traceback.print_exc()



psr.initialize(sys.argv, color = True, debug = True)

with psr.ModuleAdministrator() as mm:
    Run(mm)

psr.finalize()
