#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <map>

#ifndef Day07

#define Day07

namespace day07
{
	constexpr long long RESULT1{95437};	       // part 1 example result
	constexpr long long RESULT2{24933642};	   // part 2 example result

	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();							   // for testing (example input)
	void run();                                // for calculating (real input)
}

#endif
#pragma once
