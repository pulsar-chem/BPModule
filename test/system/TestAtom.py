from TestFxns import *

tester=Tester("Testing the Atom class")

H, H2=psr.create_atom([0.0,0.0,0.0],1), psr.create_atom([0.0,0.0,0.0],1,1)
tester.test("create_atom works",True,True,H.__eq__,H2)
tester.test_value("correct Z",1,H.Z)
tester.test_value("correct isotope",1,H.isotope)
tester.test_value("correct mass",1.007975,H.mass)
tester.test_value("correct isotope mass",1.0078250322,H.isotope_mass)
tester.test_value("correct charge",0,H.charge)
tester.test_value("correct multiplicity",2,H.multiplicity)
tester.test_value("correct nelectrons",1,H.nelectrons)
tester.test_value("correct covalent radius",0.5858150988919267,H.cov_radius)
tester.test_value("correct vDW radius",2.267671350549394,H.vdw_radius)

H3=psr.Atom(H2)
tester.test("copy constructor works",True,True,H.__eq__,H3)
D=psr.create_atom([0.0,0.0,0.0],1,2)
tester.test_value("Isotopes work",2,D.isotope)
tester.test("Isotopes are different",True,True,D.__ne__,H)

tester.test("hash works",True,H.my_hash(),H2.my_hash)
tester.test("hash works 1",True,H.my_hash(),H3.my_hash)
    
GH=psr.make_ghost_atom(H2)
tester.test("ghost works",True,True,psr.is_ghost_atom,GH)
q=psr.make_point_charge(H2,3.3)
q2=psr.make_point_charge(H2.get_coords(),3.3)
tester.test("point charges work",True,True,psr.is_point_charge,q)
tester.test("point charges work 2",True,True,psr.is_point_charge,q2)
tester.test("is same point charge",True,True,q.__eq__,q2)
Dm=psr.make_dummy_atom(H)
Dm2=psr.make_dummy_atom(H.get_coords())
tester.test("is dummy atom",True,True,psr.is_dummy_atom,Dm)
tester.test("is dummy atom 2",True,True,psr.is_dummy_atom,Dm2)
tester.test("is same dummy atom",True,True,Dm.__eq__,Dm2)

tester.print_results()
