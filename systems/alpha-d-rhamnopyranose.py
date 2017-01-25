import pulsar as psr
def load_ref_system():
    """ Returns alpha-d-rhamnopyranose as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C     -0.8728      1.4263     -0.3270
        O     -1.5909      0.3677      0.2833
        C     -1.1433     -0.9887      0.0086
        C      0.3390     -1.0821      0.4414
        O      0.8751     -2.3755      0.1209
        C      1.1868     -0.1193     -0.4147
        C      0.6705      1.3308     -0.3098
        O      1.0480      1.9270      0.9344
        O      2.5224     -0.0436      0.1069
        C     -2.0793     -1.8494      0.8365
        O     -1.2047      1.4329     -1.7148
        H     -1.2520     -1.1765     -1.0826
        H      0.4676     -0.8772      1.5266
        H      1.2377     -0.4682     -1.4721
        H      1.1005      1.9572     -1.1305
        H     -1.2644      2.3269      0.1977
        H     -2.1732      1.3552     -1.8431
        H      1.9510      1.6015      1.1977
        H      2.8904     -0.9551      0.1994
        H      0.5074     -3.0553      0.7225
        H     -2.0383     -1.5878      1.9031
        H     -3.1236     -1.6900      0.5276
        H     -1.8591     -2.9160      0.7258
        """)