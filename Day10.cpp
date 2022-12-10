#include "Day10.h"

namespace day10
{
	bool isImportant(int cycleCount)
	{
		return cycleCount == 20 || ((cycleCount - 20) % 40 == 0);
	}

	int cycle(int& cycleCount, int& registerValue, const int cycles, const int add = 0)
	{
		int signalStrength{0};
		for (int i{1}; i <= cycles; ++i)
		{
			++cycleCount;
			if (isImportant(cycleCount)) signalStrength = cycleCount * registerValue;
		}

		registerValue += add;
		return signalStrength;
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		int sum{0}, cycleCount{0}, registerValue{1};
		while (std::getline(stream, line))
		{
			if (line == "noop") sum += cycle(cycleCount, registerValue, 1);
			else sum += cycle(cycleCount, registerValue, 2, std::stoi(line.substr(5)));
		}

		return sum;
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

		std::string file{"Day10_Test.txt"};
		std::cout << "*** Testing day 10 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day10::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day10::RESULT2);
	}

	void run()
	{
		std::string file{"Day10_Input.txt"};
		std::cout << "*** Running day 10 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}