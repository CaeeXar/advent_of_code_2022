#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <stack>

#ifndef Day05

#define Day05

namespace day05
{
	constexpr std::string_view RESULT1{"CMZ"};	   // part 1 example result
	constexpr std::string_view RESULT2{"MCD"};	   // part 2 example result

	auto logic1(std::string file, bool debug);	   // for part 1
	auto logic2(std::string file, bool debug);	   // for part 1
	void runTest();								   // for testing (example input)
	void run();									   // for calculating (real input)
}

#endif
