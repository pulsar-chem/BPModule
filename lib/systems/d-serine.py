import pulsar as psr
def load_ref_system():
    """ Returns d-serine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      1.4204      0.3851     -0.4057
        C      0.4948      0.0286      0.1146
        N      0.8789     -1.1659      0.9081
        H      1.6617     -0.9393      1.4843
        H      0.1140     -1.4447      1.4871
        C     -0.0890      1.1783      0.9660
        O      0.8437      1.6610      1.8932
        C     -0.4885     -0.3918     -0.9788
        O     -1.4637      0.2167     -1.3674
        O     -0.3207     -1.5296     -1.6837
        H      0.4140     -2.0318     -1.3511
        H     -0.9266      0.8369      1.6016
        H     -0.4684      1.9894      0.3151
        H      1.4882      2.1678      1.4151
        """)
