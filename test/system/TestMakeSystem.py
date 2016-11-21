import pulsar as psr

def run_test():

    tester=psr.PyTester("Testing Make System Python Function")
    carts=[
    -2.0449536949999998,    -1.6898322539999999,     0.0354707364500000,
    -2.3427132454308994,    -2.1474611062791298,     0.8216939386571565,
    -1.1344686596866658,    -1.9649570182333860,    -0.0720244010028244,
     2.4859145229999999,    -0.9260656876000000,     0.0354704040100000,
     2.2689370278862486,    -0.0000001286725659,    -0.0720246525395077,
     3.0311125996609807,    -0.9551186438629339,     0.8216935421441762
    ]
    ToAu=1/0.52917721067
    all_atoms=[
        psr.create_atom([carts[i]*ToAu for i in range(0,3)],8),
        psr.create_atom([carts[i]*ToAu for i in range(3,6)],1),
        psr.create_atom([carts[i]*ToAu for i in range(6,9)],1),
        psr.create_atom([carts[i]*ToAu for i in range(9,12)],8),
        psr.create_atom([carts[i]*ToAu for i in range(12,15)],1),
        psr.create_atom([carts[i]*ToAu for i in range(15,18)],1)
    ]

    unv=psr.AtomSetUniverse(all_atoms)
    for i in all_atoms:
        unv.insert(psr.make_ghost_atom(i))

    corr_mol1=psr.System(unv,False)
    corr_mol2=psr.System(corr_mol1)
    for i in all_atoms:
        corr_mol2.insert(i)

    corr_mol3=psr.System(corr_mol1)
    for i in all_atoms[0:3]:
        corr_mol3.insert(psr.make_ghost_atom(i))
    for i in all_atoms[3:6]:
        corr_mol3.insert(i)

    mol1="""
    #0 1
    #O    -2.0449536949999998    -1.6898322539999999     0.0354707364500000
    #H    -2.3427132454308994    -2.1474611062791298     0.8216939386571565
    #H    -1.1344686596866658    -1.9649570182333860    -0.0720244010028244
    #O     2.4859145229999999    -0.9260656876000000     0.0354704040100000
    #H     2.2689370278862486    -0.0000001286725659    -0.0720246525395077
    #H     3.0311125996609807    -0.9551186438629339     0.8216935421441762
    """

    tester.test_function("Comments work",True,corr_mol1,psr.make_system,mol1)

    mol2="""
    0 1
    O    -2.0449536949999998    -1.6898322539999999     0.0354707364500000
    H    -2.3427132454308994    -2.1474611062791298     0.8216939386571565
    H    -1.1344686596866658    -1.9649570182333860    -0.0720244010028244
    O     2.4859145229999999    -0.9260656876000000     0.0354704040100000
    H     2.2689370278862486    -0.0000001286725659    -0.0720246525395077
    H     3.0311125996609807    -0.9551186438629339     0.8216935421441762
    """

    tester.test_function("Normal molecule works",True,corr_mol2,psr.make_system,mol2)

    mol3="""
    0 1
    @O    -2.0449536949999998    -1.6898322539999999     0.0354707364500000
    @H    -2.3427132454308994    -2.1474611062791298     0.8216939386571565
    @H    -1.1344686596866658    -1.9649570182333860    -0.0720244010028244
    O     2.4859145229999999    -0.9260656876000000     0.0354704040100000
    H     2.2689370278862486    -0.0000001286725659    -0.0720246525395077
    H     3.0311125996609807    -0.9551186438629339     0.8216935421441762
    """

    #tester.test_function("@ for ghost works",True,corr_mol3,psr.make_system,mol3)

    mol4="""
    0 1
    Gh(O)    -2.0449536949999998    -1.6898322539999999     0.0354707364500000
    Gh(H)    -2.3427132454308994    -2.1474611062791298     0.8216939386571565
    Gh(H)    -1.1344686596866658    -1.9649570182333860    -0.0720244010028244
    O     2.4859145229999999    -0.9260656876000000     0.0354704040100000
    H     2.2689370278862486    -0.0000001286725659    -0.0720246525395077
    H     3.0311125996609807    -0.9551186438629339     0.8216935421441762
    """

    #tester.test_function("Gh(X) for ghosts works",True,corr_mol3,psr.make_system,mol4)

    tester.print_results()
    return tester.nfailed()