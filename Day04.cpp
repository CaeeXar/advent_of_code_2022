#include "Day04.h"

namespace day04
{

	struct Section
	{
		int from{-1};
		int to{-1};
	};

	bool fullyContains(const Section& s1, const Section& s2)
	{
		return (s2.from >= s1.from && s2.to <= s1.to) ||
			(s1.from >= s2.from && s1.to <= s2.to);
	}

	bool overlaps(const Section& s1, const Section& s2)
	{
		return s1.from <= s2.to && s2.from <= s1.to;
		//return std::max(s1.from, s2.from) <= std::min(s1.to, s2.to);
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		int fullyContain{0};
		while (std::getline(stream, line))
		{
			// split into two sections
			std::vector<std::string> pairs;
			boost::split(pairs, line, boost::is_any_of(","), boost::token_compress_on);
			Section s1{std::stoi(pairs[0].substr(0, pairs[0].find("-"))),std::stoi(pairs[0].substr(pairs[0].find("-") + 1))},
				s2{std::stoi(pairs[1].substr(0, pairs[1].find("-"))),std::stoi(pairs[1].substr(pairs[1].find("-") + 1))};

			// check if one range fully contains the other
			if (fullyContains(s1, s2)) ++fullyContain;
		}

		return fullyContain;
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		int fullyContain{0};
		while (std::getline(stream, line))
		{
			// split into two sections
			std::vector<std::string> pairs;
			boost::split(pairs, line, boost::is_any_of(","), boost::token_compress_on);
			Section s1{std::stoi(pairs[0].substr(0, pairs[0].find("-"))),std::stoi(pairs[0].substr(pairs[0].find("-") + 1))},
				s2{std::stoi(pairs[1].substr(0, pairs[1].find("-"))),std::stoi(pairs[1].substr(pairs[1].find("-") + 1))};

			// check if ranges overlap
			if (fullyContains(s1, s2) || overlaps(s1, s2)) ++fullyContain;
		}

		return fullyContain;
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day04_Test.txt"};
		std::cout << "*** Testing day 04 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day04::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day04::RESULT2);
	}

	void run()
	{
		std::string file{"Day04_Input.txt"};
		std::cout << "*** Running day 04 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}