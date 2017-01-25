import pulsar as psr
def load_ref_system():
    """ Returns d-allo-threonine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.0130     -0.0443     -0.7539
        C     -0.1045     -0.6741      0.0730
        C     -1.0594      0.4341      0.6114
        H     -1.6192      0.9103     -0.2276
        O     -0.3438      1.5305      1.1275
        H      0.1437      1.2272      1.8840
        C     -2.0213     -0.1462      1.6458
        H     -2.6523     -0.9282      1.2048
        H     -2.6873      0.6309      2.0437
        H     -1.4899     -0.5918      2.4982
        N     -0.8773     -1.6703     -0.7042
        O      1.0146      0.2274     -1.9409
        O      2.1554      0.2124     -0.0792
        H      0.3437     -1.2252      0.9390
        H     -0.2618     -2.3719     -1.0559
        H     -1.3498     -1.2269     -1.4640
        H      2.7850      0.6411     -0.6509
        """)