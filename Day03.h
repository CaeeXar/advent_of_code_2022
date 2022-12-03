#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

#ifndef Day03

#define Day03

namespace day03
{
	constexpr int RESULT1{157};	   // part 1 example result
	constexpr int RESULT2{70};     // part 2 example result

	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();                // for testing (example input)
	void run();                    // for calculating (real input)

	int getPriority(const char c);
	char findCommon(const std::string_view& s1, const std::string_view& s2);
	char findCommon(const std::vector<std::string>& lines);
}

#endif
