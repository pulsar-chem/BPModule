import pulsar as psr
def load_ref_system():
    """ Returns acetone as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      2.0471      0.1029      0.7251
        C      1.4376      0.0818     -0.1875
        H      1.6643      0.9894     -0.7620
        H      1.7616     -0.7796     -0.7860
        C     -0.0377     -0.0035      0.0968
        O     -0.4797     -0.0446      1.2294
        C     -0.9294     -0.0345     -1.1150
        H     -0.7844      0.8703     -1.7195
        H     -0.6856     -0.8986     -1.7467
        H     -1.9948     -0.0979     -0.8587
        """)
