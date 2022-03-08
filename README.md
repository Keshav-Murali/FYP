# FYP
Final year Project

# Team Members
- Keshav M
- Vasanthakumar R

# Environment setup
TestU01 and PractRand libraries need to present within the repository's directory.
The next two subsections can be followed after cd'ing into the repository.

## Installing PractRand
```
mkdir PractRand
cd PractRand
curl -OL https://downloads.sourceforge.net/project/pracrand/PractRand_0.93.zip
unzip -q PractRand_0.93.zip
curl -sL http://www.pcg-random.org/downloads/practrand-0.93-bigbuffer.patch | patch -p0
g++ -std=c++14 -c src/*.cpp src/RNGs/*.cpp src/RNGs/other/*.cpp -Iinclude -pthread
ar rcs libPractRand.a *.o
rm *.o
g++ -std=c++14 -o RNG_test tools/RNG_test.cpp libPractRand.a -Iinclude -pthread
```

Install instructions adapted from [this link.](https://www.pcg-random.org/posts/how-to-test-with-practrand.html)

Do NOT compile with optimization (-O3) flag - will result in RNGTest crashing

## Installing TestU01
```
mkdir TestU01
cd TestU01
basedir=`pwd`
curl -OL http://simul.iro.umontreal.ca/testu01/TestU01.zip
unzip -q TestU01.zip
cd TestU01-1.2.3
./configure --prefix="$basedir"
make -j 6
make -j 6 install
cd ..
mkdir lib-so
mv lib/*.so lib-so/.
```

Install instructions adapted from [this link.](https://www.pcg-random.org/posts/how-to-test-with-testu01.html)

Pending: instructions for compiling while using TestU01 libraries


