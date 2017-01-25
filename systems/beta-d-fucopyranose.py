import pulsar as psr
def load_ref_system():
    """ Returns beta-d-fucopyranose as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      0.3042      1.1432     -0.8933
        O     -0.9306      0.5529     -1.2693
        C     -1.6599     -0.2252     -0.2931
        C     -0.7098     -0.9652      0.6785
        C      0.6538     -1.2328      0.0055
        C      1.3373      0.0889     -0.3931
        O      2.2170     -0.2776     -1.4641
        O      1.4095     -1.8833      1.0389
        O     -0.5173     -0.1042      1.8178
        C     -2.6525      0.6707      0.4269
        O      0.1140      2.1201      0.1002
        H     -2.1761     -0.9592     -0.9604
        H     -1.1607     -1.9129      1.0506
        H      0.5690     -1.9086     -0.8766
        H      1.9324      0.5051      0.4519
        H      0.6143      1.6864     -1.8125
        H     -0.2844      1.7251      0.9295
        H      2.8265      0.4612     -1.6754
        H      2.2968     -2.1351      0.6972
        H      0.2051     -0.4799      2.3844
        H     -2.1417      1.3848      1.0934
        H     -3.2298      1.2665     -0.2935
        H     -3.3510      0.0946      1.0432
        """)