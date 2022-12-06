#include "Day06.h"

namespace day06
{
	bool isUnique(std::string_view s, bool isPartOne = true)
	{
		const int range{isPartOne ? MARKER_RANGE_1 : MARKER_RANGE_2};
		std::set<char> set{s.begin(), s.begin() + range};
		return set.size() == range;
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		std::getline(stream, line);

		for (int i{0}; i < line.size() - MARKER_RANGE_1; ++i)
		{
			std::string s{line.substr(i, MARKER_RANGE_1)};
			if (isUnique(s)) return i + MARKER_RANGE_1;
		}

		return -1;
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		std::getline(stream, line);

		for (int i{0}; i < line.size() - MARKER_RANGE_2; ++i)
		{
			std::string s{line.substr(i, MARKER_RANGE_2)};
			if (isUnique(s, false)) return i + MARKER_RANGE_2;
		}

		return -1;
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day06_Test.txt"};
		std::cout << "*** Testing day 06 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day06::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day06::RESULT2);
	}

	void run()
	{
		std::string file{"Day06_Input.txt"};
		std::cout << "*** Running day 06 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}