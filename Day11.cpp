#include "Day11.h"

namespace day11
{
	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		while (std::getline(stream, line))
		{
			std::cout << line << "\n";
		}

		return -1;
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		while (std::getline(stream, line))
		{

		}

		return -1;
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day11_Test.txt"};
		std::cout << "*** Testing day 11 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day11::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day11::RESULT2);
	}

	void run()
	{
		std::string file{"Day11_Input.txt"};
		std::cout << "*** Running day 11 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}