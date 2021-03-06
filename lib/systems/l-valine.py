import pulsar as psr
def load_ref_system():
    """ Returns l-valine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      0.2036     -0.4958      0.3403
        N      1.4832     -1.2440      0.2997
        C      0.3147      0.9660      0.8346
        C     -1.0593      1.6179      0.8658
        C      0.9346      1.0303      2.2224
        C     -0.3596     -0.5230     -1.0775
        O      0.1045     -0.0437     -2.0961
        O     -1.5354     -1.1775     -1.2134
        H     -0.4768     -1.0587      1.0299
        H      1.8309     -1.3539      1.2292
        H      2.1548     -0.7502     -0.2505
        H      0.9641      1.5372      0.1249
        H     -1.5332      1.6117     -0.1249
        H     -0.9924      2.6651      1.1892
        H     -1.7373      1.1021      1.5594
        H      0.9116      2.0570      2.6127
        H      1.9862      0.7132      2.2244
        H      0.3950      0.3965      2.9394
        H     -1.8067     -1.1757     -2.1262
        """)
