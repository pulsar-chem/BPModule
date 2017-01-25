import pulsar as psr
def load_ref_system():
    """ Returns glycerol as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
      C          0.24329       -0.69184       -1.26932
      C         -0.24083        0.02394        0.00000
      C          0.24329       -0.69184        1.26932
      O          0.17264        1.36804        0.00000
      H          1.16593        1.37890        0.00000
      O         -0.25529       -0.03049        2.39890
      H          0.08452       -0.53307        3.18431
      O         -0.25529       -0.03049       -2.39890
      H          0.08452       -0.53307       -3.18431
      H         -0.12954       -1.74076       -1.25906
      H          1.35643       -0.69119       -1.29432
      H         -1.35299        0.00688        0.00000
      H          1.35643       -0.69119        1.29432
      H         -0.12954       -1.74076        1.25906
        """)