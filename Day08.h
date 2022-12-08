#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <numeric>

#ifndef Day08

#define Day08

namespace day08
{
	constexpr int RESULT1{21};	   // part 1 example result
	constexpr int RESULT2{8};     // part 2 example result

	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();                // for testing (example input)
	void run();                    // for calculating (real input)
}

#endif
