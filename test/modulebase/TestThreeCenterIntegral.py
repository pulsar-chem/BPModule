import pulsar as psr
import numpy as np

Mat1 = [1.1,2.2,3.3]

class Test3CInt(psr.ThreeCenterIntegral):
    def __init__(self,id):
        super(Test3CInt,self).__init__(id)

    def initialize_(self,deriv,wf,bs1,bs2,bs3):
        return

    def calculate_(self,shell1,shell2,shell3):
        return Mat1

    def my_hash_(self,deriv,wf,bs1,bs2,bs3):
        return ""

def run_test():
    tester=psr.PyTester("Testing ThreeCenterIntegral Python Bindings")
    mm=psr.ModuleManager()
    mm.load_lambda_module(Test3CInt,"IntBuilder","test_builder")
    builder=mm.get_module("test_builder",0)
    deriv=1
    wf=psr.Wavefunction()
    bs=psr.BasisSet(1,1,1,3)
    bs.add_shell(psr.BasisShellInfo(psr.ShellType.SphericalGaussian,0,1,1,[0.0],[0.0]),
                 [0.0,0.0,0.0])
    tester.test_call("Can call initialize",True,builder.initialize,deriv,wf,bs,bs,bs)
    temp = builder.calculate(0,0,0)
    tester.test_double_vector("Can call calculate",Mat1,temp)

    tester.print_results()
    return tester.nfailed()
