import pulsar as psr
def load_ref_system():
    """ Returns 18-crown-6 as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
      C          0.52133        2.98003       -0.69606
      C          2.02024        2.69966       -0.72281
      O          2.27141        1.31380       -0.56707
      C          2.84145        1.03853        0.69606
      C          3.34810       -0.39974        0.72281
      O          2.27348       -1.31020        0.56707
      C          2.32012       -1.94150       -0.69606
      C          1.32786       -3.09941       -0.72281
      O          0.00208       -2.62400       -0.56707
      C         -0.52133       -2.98003        0.69606
      C         -2.02024       -2.69967        0.72281
      O         -2.27141       -1.31379        0.56707
      C         -2.84145       -1.03853       -0.69606
      C         -3.34810        0.39974       -0.72281
      O         -2.27349        1.31020       -0.56707
      C         -2.32011        1.94150        0.69606
      C         -1.32786        3.09941        0.72281
      O         -0.00207        2.62399        0.56707
      H          0.40333        4.07155       -0.89000
      H          0.02825        2.38963       -1.49976
      H          2.52185        3.34807        0.03529
      H          2.42796        3.01062       -1.70808
      H          2.08360        1.17035        1.49976
      H          3.72773        1.68648        0.89000
      H          3.82125       -0.59737        1.70808
      H          4.16044       -0.50995       -0.03529
      H          3.32440       -2.38506       -0.89000
      H          2.05535       -1.21928       -1.49976
      H          1.63859       -3.85802        0.03529
      H          1.39329       -3.60798       -1.70808
      H         -0.02825       -2.38963        1.49976
      H         -0.40333       -4.07155        0.89000
      H         -2.42796       -3.01062        1.70808
      H         -2.52185       -3.34807       -0.03529
      H         -3.72773       -1.68648       -0.89000
      H         -2.08360       -1.17035       -1.49976
      H         -4.16044        0.50995        0.03529
      H         -3.82125        0.59737       -1.70808
      H         -2.05535        1.21928        1.49976
      H         -3.32440        2.38506        0.89000
      H         -1.39329        3.60798        1.70808
      H         -1.63859        3.85802       -0.03529
        """)