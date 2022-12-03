#include "Day03.h"

namespace day03
{

	char findCommon(const std::string_view& s1,
		const std::string_view& s2)
	{
		for (int i{0}; i < s1.size(); ++i)
		{
			bool found{s2.find(s1[i]) != std::string::npos};
			if (found) return s1[i];
		}

		return -1;
	}

	char findCommon(const std::vector<std::string>& lines)
	{
		for (int i{0}; i < lines[0].size(); ++i)
		{
			char c{lines[0][i]};
			std::string_view s1{lines[1]}, s2{lines[2]};
			bool found{
				s1.find(c) != std::string::npos &&
				s2.find(c) != std::string::npos
			};
			if (found) return lines[0][i];
		}

		return -1;
	}

	int getPriority(const char c)
	{
		// calculate from one range into another
		// OldRange = (OldMax - OldMin)
		// NewRange = (NewMax - NewMin)
		// NewValue = ((( OldValue - OldMin ) * NewRange) / OldRange) + NewMin

		int p;
		if (c > 'Z')
		{
			// lower
			int oldRange{'z' - 'a'}, newRange{26 - 1}, value{(((c - 'a') * newRange) / oldRange) + 1};
			p = {value};
		}
		else
		{
			// upper
			int oldRange{'Z' - 'A'}, newRange{26 - 1}, value{(((c - 'A') * newRange) / oldRange) + 27};
			p = {value};
		}

		return p;
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		int sum{0};
		std::string line;
		while (std::getline(stream, line))
		{
			size_t half{line.size() / 2};
			std::string s1{line.substr(0, half)}, s2{line.substr(half)};
			sum += getPriority(findCommon(s1, s2));
		}

		return sum;
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		int sum{0}, index{1};
		std::string line;
		std::vector<std::string> groups;
		while (std::getline(stream, line))
		{
			groups.push_back(line);

			// only check group of three lines
			if (index % 3 == 0)
			{
				sum += getPriority(findCommon(groups));
				groups.clear();
			}

			++index;
		}

		return sum;
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day03_Test.txt"};
		std::cout << "*** Testing day 03 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == RESULT2);
	}

	void run()
	{
		std::string file{"Day03_Input.txt"};
		std::cout << "*** Running day 03 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}