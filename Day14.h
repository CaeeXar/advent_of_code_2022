#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <set>

#ifndef Day14

#define Day14

namespace day14
{
	constexpr int RESULT1{24};				   // part 1 example result
	constexpr int RESULT2{93};                 // part 2 example result
	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();                            // for testing (example input)
	void run();                                // for calculating (real input)
}

#endif
