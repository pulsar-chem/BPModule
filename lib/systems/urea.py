import pulsar as psr
def load_ref_system():
    """ Returns urea as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        N      1.3308     -0.3250     -0.0930
        C     -0.0155      0.0630      0.0071
        N     -1.0241     -0.9132     -0.0464
        O     -0.3102      1.2521      0.1409
        H      1.5932     -1.2730     -0.2006
        H      2.0400      0.3650     -0.0547
        H     -1.9724     -0.6371      0.0242
        H     -0.8142     -1.8744     -0.1532
        """)
