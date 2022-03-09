default:
	print "Instructions to be created"
test: test_simple_generator

test_simple_generator:
	g++ -o tests/simpleGenerator tests/simpleGenerator.cpp
	tests/simpleGenerator

