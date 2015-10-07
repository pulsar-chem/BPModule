#!/usr/bin/env python3


import os
import sys
import argparse
import copy
import traceback 

sys.path.insert(0, "/home/ben/programming/BPModule/install/modules")

import bpmodule as bp


# can d be converted to t
def IsValid(t, d):
    if t == d:
        return True

    if t == "float" and d == "int":  # cast int to float
        return False

    if t == "listfloat" and d == "listint":  # cast int to float
        return False

    if d == "listempty":  # Empty list passed to a list type
      return t in [ "listint", "listfloat", "listbool", "liststr" ]

    return False



def Run():
    try:

        tester = bp.testing.Tester("Testing construction of OptionMap objects")
        tester.PrintHeader()

        # python types that are valid for option
        validtypes = ["int", "float", "bool", "str", "listint", "listfloat", "listbool", "liststr" ]

        # valid data for some types
        validvals = { "int" :       5,
                      "float" :     5.0,
                      "bool" :      True,
                      "str":        "Hello",
                      "listint" :   [-1, 0, 1],
                      "listfloat" : [-1.0, 0.0, 1.0],
                      "listbool" :  [False, False, True],
                      "liststr" :   ["My", "Test", "Strings"]
                    }


        # All test data (including above)
        testelements = [ (k,v) for k,v in validvals.items() ]

        # more test data
        #                  type                default,              
        testelements = [ ( "int",              int(500)                ),
                         ( "int",              int(0)                  ),
                         ( "float",            float(5.0)              ),
                         ( "bool",             True                    ),
                         ( "bool",             False                   ),
                         ( "str",              "Hi"                    ),
                         ( "str",              ""                      ),
                         ( "dict",             {"key" : int(5)}        ),
                         ( "tuple",            ("key", int(5))         ),
                         ( "set",              {"key", int(5)}         ),
                         ( "listint",          [ 5, 10, 15 ]           ),
                         ( "listfloat",        [ 5.0, 10.0, 15.0 ]     ),
                         ( "listbool",         [ False, False, True ]  ),
                         ( "liststr",          [ "5", "10", "Hi" ]     ),
                         ( "listlist",         [ [ 5, 10, 15 ] ]       ),
                         ( "listdict",         [ {"key" : 5 } ]        ),
                         ( "listtuple",        [ ("key" , 5 ) ]        ),
                         ( "listset",          [ {"key" , 5 } ]        ),
                         ( "listempty",        [  ]                    ),
                         ( "listhetero",       [ 5, 10.1, [ 4 ]]       ),
                         ( "listhetero",       [ 5, "Hi" ]             ),
                         ( "listhetero",       [ "Hi", 5 ]             ),
                       ]

        # all tested types
        alltypes = sorted(set( x[0] for x in testelements ))


        # Test single element, no validator
        for d1 in testelements:

            # with default, not required
            s = "Test construction with {} - with default".format(d1[0])
            expected = (d1[0] in validtypes)
            opt = { d1[0] : ( d1[0], d1[1], False, None, "(no help)" ) }
            tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

            # wihout default, not required
            s = "Test construction with {} - no default".format(d1[0])
            expected = (d1[0] in validtypes)
            opt = { d1[0] : ( d1[0], None, False, None, "(no help)" ) }
            tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

            # default, but required (should always be false)
            s = "Test construction with {}".format(d1[0])
            expected = False
            opt = { d1[0] : ( d1[0], d1[1], True, None, "(no help)" ) }
            tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

            # without default, but required
            s = "Test construction with {}".format(d1[0])
            expected = (d1[0] in validtypes)
            opt = { d1[0] : ( d1[0], None, True, None, "(no help)" ) }
            tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)


        # Test two elements, no validator
        for d1 in testelements:
            for d2 in testelements:
                # with default, not required
                s = "Test construction with {} + {} - with default".format(d1[0], d2[0])
                expected = (d1[0] in validtypes) and (d2[0] in validtypes)
                opt = { d1[0] : ( d1[0], d1[1], False, None, "(no help)" ),  
                        d2[0] : ( d2[0], d2[1], False, None, "(no help)" ) }
                tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} + {} - no default".format(d1[0], d2[0])
                expected = (d1[0] in validtypes) and (d2[0] in validtypes)
                opt = { d1[0] : ( d1[0], None, False, None, "(no help)" ),  
                        d2[0] : ( d2[0], None, False, None, "(no help)" ) }
                tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                # default, but required (should always be false)
                s = "Test construction with {} + {}".format(d1[0], d2[0])
                expected = False
                opt = { d1[0] : ( d1[0], d1[1], True, None, "(no help)" ),  
                        d2[0] : ( d2[0], d2[1], True, None, "(no help)" ) }
                tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                # without default, but required
                s = "Test construction with {} + {}".format(d1[0], d2[0])
                expected = (d1[0] in validtypes) and (d2[0] in validtypes)
                opt = { d1[0] : ( d1[0], None, True, None, "(no help)" ),  
                        d2[0] : ( d2[0], None, True, None, "(no help)" ) }
                tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)



        # Test single element, with varying types, not required, and with some other valid or invalid stuff
        for t1 in alltypes:
            for d1 in testelements:
                s = "Test construction with {} -> {}".format(t1, d1[0])
                expected = (t1 in validtypes) and (IsValid(t1, d1[0]))
                opt = { d1[0] : ( t1, d1[1], False, None, "(no help)" ) }  
                tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} -> {}, help = None".format(t1, d1[0])
                expected = (t1 in validtypes) and (IsValid(t1, d1[0]))
                opt = { d1[0] : ( t1, d1[1], False, None, None ) }  
                tester.Test(s, expected, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} -> {}, bad help".format(t1, d1[0])
                opt = { d1[0] : ( t1, d1[1], False, None, 4 ) }  
                tester.Test(s, False, bp.testing.PyTestFunc, bp.options.OptionMap, opt)
                
                s = "Test construction with {} -> {}, bad required".format(t1, d1[0])
                opt = { d1[0] : ( t1, d1[1], 19, None, "(no help)" ) }  
                tester.Test(s, False, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} -> {}, required = None".format(t1, d1[0])
                opt = { d1[0] : ( t1, d1[1], None, None, "(no help)" ) }  
                tester.Test(s, False, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} -> {}, bad type".format(t1, d1[0])
                opt = { d1[0] : ( 4, d1[1], False, None, "(no help)" ) }  
                tester.Test(s, False, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} -> {}, bad type str".format(t1, d1[0])
                opt = { d1[0] : ( "notype", d1[1], False, None, "(no help)" ) }  
                tester.Test(s, False, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} -> {}, too many elements in tuple".format(t1, d1[0])
                opt = { d1[0] : ( t1, d1[1], False, None, "(no help)", "extra" ) }  
                tester.Test(s, False, bp.testing.PyTestFunc, bp.options.OptionMap, opt)

                s = "Test construction with {} -> {}, too few elements in tuple".format(t1, d1[0])
                opt = { d1[0] : ( t1, d1[1], False, None ) }  
                tester.Test(s, False, bp.testing.PyTestFunc, bp.options.OptionMap, opt)


        for t1 in validtypes:
            # create a list of dicts to test
            allopt = [ { "test_opt" : ( t1,   None,          True, None, "(no help)" ) },
                       { "test_opt" : ( t1,   None,          False, None, "(no help)" ) },
                       { "test_opt" : ( t1,   validvals[t1], False, None, "(no help)" ) },
                     ]


            for opt in allopt:
                # Construct with some valid data
                opm = bp.options.OptionMap(opt)

                v = opt["test_opt"]

                # should be invalid if required
                isvalid = not v[2]

                # have (default) value?
                hasdefault = v[1] != None

                s = "OptionMap {} : Testing validity".format(t1)
                tester.Test(s, isvalid, bp.testing.PyTestBoolFunc, opm.IsValid)

                s = "OptionMap {} : Has option?".format(t1)
                tester.Test(s, True, bp.testing.PyTestBoolFunc, opm.HasKey, "test_opt")

                s = "OptionMap {} : Has option value?".format(t1)
                tester.Test(s, hasdefault, bp.testing.PyTestBoolFunc, opm.Has, "test_opt")

                # set the value
                for d1 in testelements:
                    s = "OptionMap {} : Resetting option".format(t1)
                    tester.Test(s, True, bp.testing.PyTestFunc, opm.ResetToDefault, "test_opt")

                    s = "OptionMap {} : Testing validity after resetting".format(t1)
                    tester.Test(s, isvalid, bp.testing.PyTestBoolFunc, opm.IsValid)

                    s = "OptionMap {} : Setting option with {}".format(t1, d1[0])
                    expected = IsValid(t1, d1[0])
                    tester.Test(s, expected, bp.testing.PyTestFunc, opm.Change, "test_opt", d1[1])

                    # should be valid if expected == True, since that means the value is now set
                    # (or if it was previously valid)
                    s = "OptionMap {} : Is valid now?".format(t1)
                    tester.Test(s, expected or isvalid, bp.testing.PyTestBoolFunc, opm.IsValid)

                    # should still have the option
                    s = "OptionMap {} : Has option?".format(t1)
                    tester.Test(s, True, bp.testing.PyTestBoolFunc, opm.HasKey, "test_opt")

                    # value is set if expected == True
                    s = "OptionMap {} : Has option value?".format(t1)
                    tester.Test(s, expected or hasdefault, bp.testing.PyTestBoolFunc, opm.Has, "test_opt")



                    # Reset again
                    s = "OptionMap {} : Resetting option".format(t1)
                    tester.Test(s, True, bp.testing.PyTestFunc, opm.ResetToDefault, "test_opt")

                    s = "OptionMap {} : Testing validity after resetting".format(t1)
                    tester.Test(s, isvalid, bp.testing.PyTestBoolFunc, opm.IsValid)

                    s = "OptionMap {} : Setting option as dict with {}".format(t1, d1[0])
                    expected = IsValid(t1, d1[0])
                    tester.Test(s, expected, bp.testing.PyTestFunc, opm.ChangeDict, { "test_opt" :  d1[1] })

                    # should be valid if expected == True, since that means the value is now set
                    # (or if it was previously valid)
                    s = "OptionMap {} : Is valid now?".format(t1)
                    tester.Test(s, expected or isvalid, bp.testing.PyTestBoolFunc, opm.IsValid)

                    # should still have the option
                    s = "OptionMap {} : Has option?".format(t1)
                    tester.Test(s, True, bp.testing.PyTestBoolFunc, opm.HasKey, "test_opt")

                    # value is set if expected == True
                    s = "OptionMap {} : Has option value?".format(t1)
                    tester.Test(s, expected or hasdefault, bp.testing.PyTestBoolFunc, opm.Has, "test_opt")



        tester.PrintResults() 


    except Exception as e:
      bp.output.Output("Caught exception in main handler. Contact the developers\n")
      traceback.print_exc()
      bp.output.Error("\n")
      bp.output.Error(str(e))
      bp.output.Error("\n")




bp.Init(sys.argv, out = "stdout", color = True, debug = True)
Run()
bp.Finalize()
