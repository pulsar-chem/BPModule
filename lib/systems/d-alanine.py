import pulsar as psr
def load_ref_system():
    """ Returns d-alanine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      0.4907      1.6416      0.2248
        C      0.4294      0.5575      0.4954
        N      1.8262      0.0879      0.6410
        H      2.2964      0.1457     -0.2369
        H      1.8434     -0.8553      0.9680
        C     -0.3237      0.4046      1.8122
        H     -1.3379      0.8179      1.7351
        H      0.1882      0.9387      2.6239
        H     -0.4173     -0.6466      2.1183
        C     -0.3337     -0.1771     -0.6032
        O     -0.1056     -1.2719     -1.0870
        O     -1.4000      0.4802     -1.1099
        H     -1.8242     -0.0509     -1.7771
        """)
