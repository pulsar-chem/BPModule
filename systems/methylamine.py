import pulsar as psr
def load_ref_system():
    """ Returns methylamine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        N      0.6863     -0.2421      0.0179
        C     -0.7159      0.1921     -0.0246
        H      1.0976      0.0296      0.8864
        H      1.1953      0.1876     -0.7260
        H     -1.2710     -0.2978      0.7863
        H     -1.1633     -0.1230     -0.9766
        H     -0.8656      1.2787      0.0739
        """)