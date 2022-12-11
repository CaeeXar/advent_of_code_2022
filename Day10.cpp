#include "Day10.h"

namespace day10
{
#pragma region PART1
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
#pragma endregion PART1

#pragma region PART2
	using Sprite = std::string;
	using CRT = std::vector<Sprite>;

	enum class Operation
	{
		noop = 1,
		addx = 2,
	};

	std::ostream& operator<<(std::ostream& out, Operation operation)
	{
		if (operation == Operation::noop) std::cout << "noop";
		if (operation == Operation::addx) std::cout << "addx";
		return out;
	}

	void printCRT(const CRT& crt)
	{
		for (std::string row : crt)
		{
			for (char pixel : row) std::cout << pixel;
			std::cout << "\n";
		}
	}

	void printCRTRow(const CRT& crt, int row)
	{
		for (int i{0}; i < crt[row].size(); ++i) std::cout << crt[row][i];
		std::cout << "\n";
	}

	void printSprite(const Sprite& sprite)
	{
		for (char pixel : sprite) std::cout << pixel;
		std::cout << "\n";
	}

	Sprite initializeSprite()
	{
		Sprite sprite(40, '.');
		for (int i{0}; i < 3; ++i) sprite[i] = '#';
		return sprite;
	}

	void updateSpritePosition(Sprite& sprite, const int registerValue)
	{
		sprite = {""};
		for (int i{0}; i < 40; ++i)
		{
			if (i >= registerValue - 1 && i <= registerValue + 1) sprite += '#';
			else sprite += '.';
		}
	}

	void calculateCRT(
		CRT& crt,
		Sprite& sprite,
		Operation& operation,
		int& currentCycle,
		int& registerValue,
		const int add = 0,
		const bool debug = false
	)
	{
		int cycles{static_cast<int>(operation)}, position, row;
		std::string addS{(add != 0 ? std::to_string(add) : "")};

		// start of a cycle
		if (debug)
		{
			std::cout << "Sprite position: ";
			printSprite(sprite);

			std::cout << "Start cycle " << (currentCycle + 1) << ": begin executing "
				<< operation << " " << addS << "\n";
		}

		// during cycles
		for (int i{0}; i < cycles; ++i)
		{
			++currentCycle;
			position = {(currentCycle - 1) % 40};
			row = {(currentCycle - 1) / 40};

			crt[row][position] = sprite[position];

			if (debug)
			{
				std::cout << "During cycle " << currentCycle << ": CRT draws pixel in position "
					<< position << "\n";

				std::cout << "Current CRT row: ";
				printCRTRow(crt, row);
			}
		}

		// end of cycle
		position = {(currentCycle - 1) % 40};
		row = {(currentCycle - 1) / 40};

		registerValue += add;
		updateSpritePosition(sprite, registerValue);

		if (debug)
		{
			std::cout << "End of cycle " << currentCycle << ": finish executing "
				<< operation << " " << addS << " (Register X is now " << registerValue << ")\n";

			std::cout << "Sprite position: ";
			printSprite(sprite);

			std::cout << "\n";
		}
	}
#pragma endregion PART2

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
		int sum{0}, currentCycle{0}, registerValue{1};
		CRT crt{6, Sprite(40, '?')};
		Sprite sprite{initializeSprite()};
		while (std::getline(stream, line))
		{
			Operation operation;
			int add{0};
			if (line == "noop") operation = {Operation::noop};
			else
			{
				operation = {Operation::addx};
				add = {std::stoi(line.substr(5))};
			}

			calculateCRT(crt, sprite, operation, currentCycle, registerValue, add, debug);
		}

		std::cout << "Sprite position: \n";
		printSprite(sprite);

		std::cout << "\nCRT:\n";
		printCRT(crt);
		std::cout << "\n";

		return -1;
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day10_Test.txt"};
		std::cout << "*** Testing day 10 ***\n\n";

		auto x = logic1(file, debug);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day10::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file, debug);
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