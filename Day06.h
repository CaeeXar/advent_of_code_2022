#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

#ifndef Day06

#define Day06

namespace day06
{
	constexpr int RESULT1{7};	   // part 1 example result
	constexpr int RESULT2{19};     // part 2 example result

	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();                // for testing (example input)
	void run();                    // for calculating (real input)

	constexpr int MARKER_RANGE_1{4};
	constexpr int MARKER_RANGE_2{14};
}

#endif
