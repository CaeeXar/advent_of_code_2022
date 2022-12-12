#include <boost/algorithm/string.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <set>

#ifndef Day11

#define Day11

namespace day11
{
	constexpr long long RESULT1{10605};		   // part 1 example result
	constexpr long long RESULT2{2713310158};   // part 2 example result

	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();                            // for testing (example input)
	void run();								   // for calculating (real input)
}

#endif
