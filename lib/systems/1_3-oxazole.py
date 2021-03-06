import pulsar as psr
def load_ref_system():
    """ Returns 1_3-oxazole as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      0.9555      0.5543     -0.3567
        C      0.7830     -0.7986     -0.4669
        H      1.7389      1.2601     -0.6145
        H      1.4252     -1.5800     -0.8679
        O     -0.1712      1.0951      0.2304
        C     -1.0325      0.0563      0.4768
        N     -0.4940     -1.0860      0.0730
        H     -1.9946      0.2681      0.9433
        """)
