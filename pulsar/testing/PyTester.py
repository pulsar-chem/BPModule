from .. import *

class PyTester(TesterBase):
    """Adds duck-typed test function and gets around no overloads."""

    def __init__(self, desc):
        super(PyTester, self).__init__(desc)

    def test_equal(self, desc, v1, v2):
        self.test(desc, v1 == v2)

    def test_inot_equal(self, desc, v1, v2):
        self.test(desc, (v1 != v2))

    def test_function(self, desc, should_pass, expected, func, *args):
        try:
            success = (expected==func(*args) and should_pass)
        except Exception as e:
            success = not should_pass
        self.test(desc,success)

    def test_double(self,desc,v1,v2,tol=0.0001):
        """Same as Tester's test with two values."""
        if type(v1)==float and type(v2)==float:
           self.test_float(desc,v1,v2,tol)
        else:
            self.test(desc,v1==v2)



##################
# For testing on the python side
##################
def py_test_function(func, *args):
    try:
       func(*args)
    except Exception as e:
        print_global_debug(str(e) + "\n")
        return 0
    except:
        return 0

    return 1



def py_test_bool_function(func, *args):
    try:
        return func(*args)

    except Exception as e:
        print_global_debug(str(e) + "\n")
        return 0

    except:
        return 0    
         