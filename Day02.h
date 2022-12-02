#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#ifndef Day02

#define Day02

namespace day02
{
	constexpr int RESULT1{15};	   // part 1 example result
	constexpr int RESULT2{-1};     // part 2 example result

	auto logic1(std::string file); // for part 1
	auto logic2(std::string file); // for part 1
	void runTest();                // for testing (example input)
	void run();                    // for calculating (real input)
}

#endif
