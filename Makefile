default:
	print "Instructions to be created"
test: test_simple_generator

test_simple_generator:
	g++ -o tests/simpleGenerator tests/simpleGenerator.cpp
	tests/simpleGenerator
test_LCG:
	g++ -o tests/LCGenerator tests/LCGenerator.cpp
	tests/LCGenerator
	g++ -o tests/LCG_PractRand tests/LCG_PractRand.cpp
	timeout 20s tests/LCG_PractRand | PractRand/RNG_test stdin64
test_MRG:
	g++ -o tests/MRGenerator tests/MRGenerator.cpp
	tests/MRGenerator
	g++ -o tests/MRG_PractRand tests/MRG_PractRand.cpp
#	timeout 45s tests/MRG_PractRand | PractRand/RNG_test stdin64
	tests/MRG_PractRand | PractRand/RNG_test stdin32
test_MWCG:
	g++ -o tests/MWCGenerator tests/MWCGenerator.cpp
	tests/MWCGenerator
	g++ -o tests/MWCG_PractRand tests/MWCG_PractRand.cpp
	tests/MWCG_PractRand | PractRand/RNG_test stdin32
test_WMSG:
	g++ -o tests/WMSGenerator tests/WMSGenerator.cpp
	tests/WMSGenerator
	g++ -o tests/WMSG_PractRand tests/WMSG_PractRand.cpp
	tests/WMSG_PractRand | PractRand/RNG_test stdin32
test_xoro:
	g++ -o tests/xoroshiro tests/xoroshiro.cpp
	tests/xoroshiro
	g++ -o tests/xoroshiro_PractRand tests/xoroshiro_PractRand.cpp
	timeout 20s tests/xoroshiro_PractRand | PractRand/RNG_test stdin32
test_comb:
	g++ -o tests/combinationGenerator tests/combinationGenerator.cpp
	tests/combinationGenerator
test_lxm_u01:
	cd TestU01; g++ -o ../tests/test_lxm ../tests/test_lxm.cpp -Iinclude -Llib -ltestu01 -lprobdist -lmylib -lm -Ofast
	cd lxm_res; ../tests/test_lxm
test_LXM: test_lxm_u01
	g++ -o tests/LXM tests/LXM.cpp
	tests/LXM
	g++ -o tests/LXM_PractRand tests/LXMPractRand.cpp
	timeout 5000s tests/LXM_PractRand | PractRand/RNG_test stdin64
test_LXM2:
	g++ -o tests/LXM2_PractRand tests/LXM2PractRand.cpp
	timeout 5000s tests/LXM2_PractRand | PractRand/RNG_test stdin64
test_perf:
	g++ -o tests/ctest tests/ctest.cpp -Ofast -std=c++2a
	tests/ctest
	cd tests ; javac timing.java ; java timing
test_mt:
	cd TestU01; g++ -o ../tests/test_mt ../tests/test_mt.cpp -Iinclude -Llib -ltestu01 -lprobdist -lmylib -lm
	tests/test_mt



