#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

#ifndef Day09

#define Day09

namespace day09
{
	constexpr int RESULT1{13};	   // part 1 example result
	constexpr int RESULT2{-1};     // part 2 example result

	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();                // for testing (example input)
	void run();                    // for calculating (real input)
}

#endif
