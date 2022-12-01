#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <list>
#include <algorithm>

#ifndef Day01

#define Day01

namespace day01
{
	constexpr int RESULT1{24000};  // part 1 example result
	constexpr int RESULT2{45000};  // part 2 example result

	auto logic1(std::string file); // for part 1
	auto logic2(std::string file); // for part 1
	void runTest();                // for testing (example input)
	void run();                    // for calculating (real input)
}

#endif
