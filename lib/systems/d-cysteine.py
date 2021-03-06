import pulsar as psr
def load_ref_system():
    """ Returns d-cysteine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C     -0.2529     -0.1635     -0.4344
        C      0.1089     -1.5934     -0.0355
        O      0.9646     -2.3176     -0.5120
        O     -0.6270     -2.1189      0.9673
        C      0.3653      0.8052      0.5791
        S     -0.3580      2.4713      0.5904
        N      0.1922      0.1748     -1.8067
        H     -1.3683     -0.0544     -0.4148
        H     -0.3367     -3.0058      1.1586
        H      1.4633      0.8563      0.4496
        H      0.1967      0.4284      1.6080
        H     -0.1184      2.8528     -0.6389
        H     -0.2910     -0.3946     -2.4679
        H      1.1768      0.0345     -1.8996
        """)
