#include "generator.hpp"
#include <inttypes.h>

class MRGenerator : public simpleGenerator<uint64_t> {
public:
    size_t numParameters = 6;
    int64_t k,p1,p2;
    double state;
    const int64_t m1 = INT64_C(4294967087);
    const int64_t m2 = INT64_C(4294944443);
    const int32_t a12 = INT32_C(1403580);
    const int32_t a13 = INT32_C(810728);
    const int32_t a21 = INT32_C(527612);
    const int32_t a23 = INT32_C(1370589);
    const int64_t corr1 = (m1 * a13);
    const int64_t corr2 = (m2 * a23);

    const double norm = 0x1.000000d00000bp-32;
    int64_t s10 = 1, s11 = 1, s12 = 1, s20 = 1, s21 = 1, s22 = 1;
  MRGenerator(std::vector<uint64_t> &params) : simpleGenerator<uint64_t>::simpleGenerator(params) {
    if (params.size() != numParameters) {
      std::cerr << "Generator initialized with incorrect number of parameters! Expecting "
		<< numParameters << std::endl;
      std::exit(0);
    }
    if (params[0] == 0 && params[1] == 0 && params[2] == 0){
      std::cerr << "s10, s11 and s12 cannot be all zero";
      std::exit(0);
    }
	if (params[3] == 0 && params[4] == 0 && params[5] == 0){
      std::cerr <<"s20, s21 and s22 cannot be all zero";
      std::exit(0);
    }
	if (params[0] < 0 || params[1] < 0 || params[2] < 0) {
      std::cerr <<"s10 (" << params[0] << "), s11 (" << params[1] << "), and s12 (" << params[2]<< ") cannot be negative";
      std::exit(0);
    }
	if (params[3] < 0 || params[4] < 0 || params[5] < 0) {
      std::cerr <<"s20 (" << params[3] << "), s21 (" << params[4] << "), and s22 (" << params[5]<< ") cannot be negative";
      std::exit(0);
    }
	if (params[0] >= m1 || params[1] >= m1 || params[2] >= m1) {
      std::cerr <<"s10 (" <<params[0] << "), s11 (" << params[1] << "), and s12 (" << params[2] << ") must be smaller than " << m1;
      std::exit(0);
    }
	if (params[3] >= m2 || params[4] >= m2 || params[5] >= m2){
	  std::cerr <<"s20 (" << params[3] << "), s21 (" << params[4] << "), and s22 (" << params[5] << ") must be smaller than " << m2;
      std::exit(0);
	}
	s10 = params[0];
	s11 = params[1];
	s12 = params[2];
	s20 = params[3];
	s21 = params[4];
	s22 = params[5];
  }
  
  uint64_t generateNumber()
  {
        int64_t r = s12 - s22;
	r -= m1 * ((r - 1) >> 63);

	// Component 1
	int64_t p = (a12 * s11 - a13 * s10 + corr1) % m1;
	s10 = s11;
	s11 = s12;
	s12 = p;
	
	// Component 2
	p = (a21 * s22 - a23 * s20 + corr2) % m2;
	s20 = s21;
	s21 = s22;
	s22 = p;
	state =  (double) r * norm;
	return (uint64_t) r;
  }
  
  double generateNormalized()
  {
    this->generateNumber();
    return state;
  }

  simpleGenerator* createNewGenerator(std::vector<uint64_t> &params) {
    return new MRGenerator(params);
  }
  
  size_t getNumParameters()
  {
    return numParameters;
  }
};
