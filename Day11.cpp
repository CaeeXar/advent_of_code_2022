#include "Day11.h"

namespace day11
{
#pragma region PART1
	using WorryLevels = std::vector<boost::multiprecision::uint1024_t>;

	struct Monkey
	{
		const int ID{0};
		WorryLevels worryLevels{};
		const std::string operand{""};
		const char operation{'+'};
		const int test{0};
		const int trueMonkey{0};
		const int falseMonkey{0};
		boost::multiprecision::uint1024_t inspected{0};

		boost::multiprecision::uint1024_t newWorryLevel(const boost::multiprecision::uint1024_t old)
		{
			boost::multiprecision::uint1024_t newValue{0};
			switch (operation)
			{
				case '+': newValue = old +
					(boost::multiprecision::uint1024_t)(operand == "old" ? old : std::stoi(operand));
					break;
				case '*': newValue = old *
					(boost::multiprecision::uint1024_t)(operand == "old" ? old : std::stoi(operand));
					break;
			}

			return newValue;
		}

		std::string to_string()
		{
			std::string s = "Monkey " + std::to_string(ID) + ":\n" + std::string(" - Items: ");

			for (const boost::multiprecision::uint1024_t& worryLevel : worryLevels)
			{
				s += worryLevel.str() + ", ";
			}

			s += std::string("\n") + std::string(" - Operation: new = old ") +
				(char)operation + std::string(" ") + operand + std::string("\n") +
				std::string(" - Test: divisible by ") + std::to_string(test) + std::string("\n") +
				std::string("    - If true: throw to monkey ") + std::to_string(trueMonkey) +
				std::string("\n") + std::string("    - If false: throw to monkey ") +
				std::to_string(falseMonkey) + std::string("\n");
			return s;

		}

	};

	using Monkeys = std::vector<Monkey>;

	Monkey& getMonkeyByID(Monkeys& monkeys, const int ID)
	{
		Monkey nll;
		for (Monkey& m : monkeys)
		{
			if (m.ID == ID) return m;
		}

		return nll;
	}

	Monkeys initializeMonkeys(std::string file)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return {};

		Monkeys monkeys{};
		WorryLevels worryLevels;
		std::string line, operand{""};
		char operation{'+'};
		int ID{0}, test{0}, trueMonkey{0}, falseMonkey{0};
		std::vector<std::string> temp;
		while (std::getline(stream, line))
		{
			if (line == "")
			{
				monkeys.push_back({ID++, worryLevels, operand, operation, test, trueMonkey, falseMonkey});
				worryLevels = {};
				continue;
			}

			if (boost::starts_with(line, "  Starting items:"))
			{
				boost::split(temp, line.substr(18), boost::is_any_of(","), boost::token_compress_on);
				for (std::string item : temp)
				{
					worryLevels.push_back((boost::multiprecision::uint1024_t)std::stoi(item));
				}
			}

			if (boost::starts_with(line, "  Operation:"))
			{
				boost::split(temp, line.substr(23), boost::is_any_of(" "), boost::token_compress_on);
				operation = {temp[0][0]};
				operand = {temp[1]};
			}

			if (boost::starts_with(line, "  Test:")) test = {std::stoi(line.substr(21))};
			if (boost::starts_with(line, "    If true:")) trueMonkey = {std::stoi(line.substr(29))};
			if (boost::starts_with(line, "    If false:")) falseMonkey = {std::stoi(line.substr(30))};
		}

		monkeys.push_back({ID++, worryLevels, operand, operation, test, trueMonkey, falseMonkey});

		return monkeys;
	}

	void playRound(Monkeys& monkeys, const boost::multiprecision::uint1024_t divider)
	{
		WorryLevels newWorryLevels{};
		for (Monkey& monkey : monkeys)
		{
			while (monkey.worryLevels.size() > 0)
			{
				boost::multiprecision::uint1024_t newWorryLevel{
					(boost::multiprecision::uint1024_t)(monkey.newWorryLevel(monkey.worryLevels[0]) / divider)
				};

				if (newWorryLevel <= 0)
				{
					std::cout << "current WL: " << monkey.worryLevels[0] << "\n";
					std::cout << "new WL    : " << newWorryLevel << "\n";
				}

				monkey.worryLevels.erase(monkey.worryLevels.begin());
				Monkey& m{getMonkeyByID(monkeys,
					(newWorryLevel % monkey.test == 0) ? monkey.trueMonkey : monkey.falseMonkey)};
				m.worryLevels.push_back(newWorryLevel);
				monkey.inspected++;
			}

		}
	}

	void printMonkeys(const Monkeys& monkeys)
	{
		for (Monkey monkey : monkeys)
		{
			std::cout << monkey.to_string() << "\n";
		}
	}

	void printInspected(const Monkeys& monkeys)
	{
		for (Monkey monkey : monkeys)
		{
			std::cout << "Monkey " << monkey.ID << " inspected items "
				<< monkey.inspected << " times!\n";
		}
	}
#pragma endregion PART1

	auto logic1(std::string file, bool debug = false)
	{
		// play 20 rounds
		boost::multiprecision::uint1024_t divider{3};
		Monkeys monkeys{initializeMonkeys(file)};
		for (int i{0}; i < 20; ++i)
		{
			playRound(monkeys, divider);
		}

		if (debug) printMonkeys(monkeys);

		// get 2 most active monkeys 
		std::set<boost::multiprecision::uint1024_t> max{};
		for (Monkey m : monkeys)
		{
			max.insert(m.inspected);
		}

		auto end = max.end();
		boost::multiprecision::uint1024_t x = {*--end}, y = {*--end};
		return x * y;
	}

	auto logic2(std::string file, bool debug = false)
	{
		// FUCK IT FOR KNOW
		return -1;
		//// play 10000 rounds
		//boost::multiprecision::uint1024_t divider{1};
		//Monkeys monkeys{initializeMonkeys(file)};
		//for (int i{0}; i < 10000; ++i)
		//{
		//	playRound(monkeys, divider);
		//	if (debug && (i + 1) % 1000 == 0)
		//	{
		//		std::cout << "== After round " << (i + 1) << " ==\n";
		//		printInspected(monkeys);
		//		std::cout << "\n";
		//	}
		//}
		//if (debug) printMonkeys(monkeys);
		//// get 2 most active monkeys 
		//std::set<boost::multiprecision::uint1024_t> max{};
		//for (Monkey m : monkeys)
		//{
		//	max.insert(m.inspected);
		//}
		//auto end = max.end();
		//boost::multiprecision::uint1024_t x = {*--end}, y = {*--end};
		//return x * y;
	}

	void runTest()
	{
		std::string file{"Day11_Test.txt"};
		std::cout << "*** Testing day 11 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day11::RESULT1);

		std::cout << "------------------" << "\n";

		auto y = logic2(file, true);
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