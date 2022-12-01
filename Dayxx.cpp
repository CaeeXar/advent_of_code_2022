#include "Dayxx.h"

namespace dayxx
{
	auto logic1(std::string file)
	{
		return -1;
	}

	auto logic2(std::string file)
	{
		return -1;
	}

	void runTest()
	{
		std::string file{""};

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == dayxx::RESULT1);

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == dayxx::RESULT2);
	}

	void run()
	{
		std::string file{""};

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}