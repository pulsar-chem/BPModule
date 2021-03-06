import pulsar as psr
def load_ref_system():
    """ Returns pentacene as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
      C          0.00000        0.70751       -1.21703
      C         -0.00000       -0.70751       -1.21703
      C         -0.00000       -1.40554        0.00000
      C         -0.00000       -0.70751        1.21703
      C          0.00000        0.70751        1.21703
      C          0.00000        1.40554       -0.00000
      C          0.00000        1.40620       -2.43405
      C         -0.00000       -1.40620       -2.43405
      H         -0.00000       -2.49043        0.00000
      C         -0.00000       -1.40620        2.43405
      C          0.00000        1.40620        2.43405
      H          0.00000        2.49043       -0.00000
      C          0.00000       -0.70775       -3.65027
      C          0.00000        0.70775       -3.65027
      H          0.00000        2.49106       -2.43468
      H         -0.00000       -2.49106       -2.43468
      C          0.00000       -1.40234       -4.87042
      C          0.00000        1.40234       -4.87042
      C         -0.00000       -0.70775        3.65027
      C         -0.00000        0.70775        3.65027
      H         -0.00000       -2.49106        2.43468
      H          0.00000        2.49106        2.43468
      C         -0.00000       -1.40234        4.87042
      C         -0.00000        1.40234        4.87042
      C         -0.00000        0.69872        6.07826
      C         -0.00000       -0.69872        6.07826
      H         -0.00000       -2.48577        4.88725
      H          0.00000        2.48577        4.88725
      H         -0.00000        1.23799        7.01671
      H         -0.00000       -1.23799        7.01671
      C          0.00000        0.69872       -6.07826
      C          0.00000       -0.69872       -6.07826
      H         -0.00000       -2.48577       -4.88725
      H          0.00000        2.48577       -4.88725
      H          0.00000        1.23799       -7.01671
      H          0.00000       -1.23799       -7.01671
        """)
