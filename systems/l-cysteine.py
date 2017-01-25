import pulsar as psr
def load_ref_system():
    """ Returns l-cysteine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H     -0.1792     -1.2020      0.7234
        C      0.1917     -0.4923     -0.0613
        N      1.5911     -0.8802     -0.3526
        H      1.9612     -0.3164     -1.0895
        H      1.6242     -1.8410     -0.6181
        C      0.1436      0.9377      0.4864
        H      0.7537      1.6170     -0.1396
        C     -0.7265     -0.5932     -1.2854
        O     -0.3921     -0.6678     -2.4487
        O     -2.0709     -0.6229     -1.1644
        H     -2.3287     -0.5569     -0.2531
        S      0.5933      1.0933      2.2391
        H     -0.8909      1.3333      0.4343
        H      1.8309      0.6651      2.2150
        """)