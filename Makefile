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
test_xoro:
	g++ -o tests/xoroshiro tests/xoroshiro.cpp
	tests/xoroshiro
	g++ -o tests/xoroshiro_PractRand tests/xoroshiro_PractRand.cpp
	timeout 20s tests/xoroshiro_PractRand | PractRand/RNG_test stdin64
test_comb:
	g++ -o tests/combinationGenerator tests/combinationGenerator.cpp
	tests/combinationGenerator
test_LXM:
	g++ -o tests/LXM tests/LXM.cpp
	tests/LXM
	g++ -o tests/LXM_PractRand tests/LXMPractRand.cpp
	timeout 120s tests/LXM_PractRand | PractRand/RNG_test stdin64
test_perf:
	g++ -o tests/ctest tests/ctest.cpp -Ofast -std=c++2a
	tests/ctest
	cd tests ; javac timing.java ; java timing




