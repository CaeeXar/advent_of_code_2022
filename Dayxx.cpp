#include "Dayxx.h"

namespace dayxx
{
	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		while (std::getline(stream, line))
		{

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
		std::string file{""};
		std::cout << "*** Testing day xx ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == dayxx::RESULT1);

		std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == dayxx::RESULT2);
	}

	void run()
	{
		std::string file{""};
		std::cout << "*** Running day xx ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}