from .modinfo import *

# SO file
from .bpmodule_output import SetOut_Stdout, SetOut_Stderr, SetOut_File, SetColor, SetDebug, Valid, Flush 

from .bpmodule_output import Output as Output_
from .bpmodule_output import Success as Success_
from .bpmodule_output import Warning as Warning_
from .bpmodule_output import Error as Error_
from .bpmodule_output import Changed as Changed_
from .bpmodule_output import Debug as Debug_

# for output:
# package args into a list then pass to SO file
def Output(s, *args):
    if(len(args)) > 0:
      Output_(s, list(args))
    else:
      Output_(s, [])


def Success(s, *args):
    if(len(args)) > 0:
      Success_(s, list(args))
    else:
      Success_(s, [])


def Warning(s, *args):
    if(len(args)) > 0:
      Warning_(s, list(args))
    else:
      Warning_(s, [])


def Error(s, *args):
    if(len(args)) > 0:
      Error_(s, list(args))
    else:
      Error_(s, [])


def Debug(s, *args):
    if(len(args)) > 0:
      Debug_(s, list(args))
    else:
      Debug_(s, [])


def Changed(s, *args):
    if(len(args)) > 0:
      Changed_(s, list(args))
    else:
      Changed_(s, [])


def Line(char, n = 80):
    return char * n + "\n" 

