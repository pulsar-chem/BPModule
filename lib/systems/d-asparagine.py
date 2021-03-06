import pulsar as psr
def load_ref_system():
    """ Returns d-asparagine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      0.7537      0.0379     -1.2915
        C      0.1045     -0.4153     -0.4977
        C     -1.1985     -0.8661     -1.1511
        O     -1.5280     -0.7582     -2.3158
        O     -2.1114     -1.4321     -0.3254
        H     -2.8863     -1.6767     -0.8215
        C     -0.2185      0.6514      0.5598
        C      1.0401      1.3677      1.0060
        H     -0.9122      1.3989      0.1237
        N      0.8199     -1.6069      0.0122
        H      0.3759     -1.9614      0.8330
        H      1.7649     -1.3644      0.2198
        O      1.6788      2.1496      0.3115
        N      1.5312      1.1109      2.2873
        H     -0.7677      0.2065      1.4168
        H      1.0270      0.5305      2.9108
        H      2.3373      1.5784      2.6251
        """)
