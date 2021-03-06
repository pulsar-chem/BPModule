import pulsar as psr
def load_ref_system():
    """ Returns thiophene as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.2268      0.1466      0.0000
        C      0.9199     -1.1842      0.0000
        C     -0.4978     -1.4144      0.0000
        C     -1.2102     -0.2491      0.0000
        S     -0.1848      1.1378      0.0000
        H      2.2310      0.5665      0.0000
        H      1.6489     -1.9946      0.0000
        H     -0.9332     -2.4137      0.0000
        H     -2.2956     -0.1685      0.0000
        """)
