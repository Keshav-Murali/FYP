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

