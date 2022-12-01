#include "Day01.h"

namespace day01
{
	bool compareDescending(const int& lsh, const int& rsh)
	{
		return (rsh < lsh);
	}

	auto logic1(std::string file)
	{
		std::ifstream myfile(file);

		if (!myfile.is_open())
		{
			std::cout << "Unable to open file!\n";
			return -1;
		}

		std::string line;
		int most{0};
		int sum{0};

		while (std::getline(myfile, line))
		{
			if (line == "")
			{
				if (most < sum) most = sum;
				sum = {0};
			}
			else
			{
				sum += std::stoi(line);
			}
		}

		// check one last time, since the last line / sum wont get checked
		if (most < sum) most = sum;

		myfile.close();

		return most;
	}

	auto logic2(std::string file)
	{
		std::ifstream myfile(file);

		if (!myfile.is_open())
		{
			std::cout << "Unable to open file!\n";
			return -1;
		}

		std::string line;
		std::list<int> sums;
		int sum{0};

		while (std::getline(myfile, line))
		{
			if (line == "")
			{
				sums.push_back(sum);
				sum = {0};
			}
			else
			{
				sum += std::stoi(line);
			}
		}

		// push last sum into list, otherwise it gets lost
		sums.push_back(sum);

		myfile.close();

		// sort descending so that the first 3 entries will be the highest
		sums.sort(compareDescending);
		sum = {0};

		// sum the first 3 entires (alternative sums[0] + sums[1] + ...)
		std::list<int>::iterator it;
		int i;
		for (it = sums.begin(), i = 0;
			it != sums.end() && i < 3;
			++it, ++i)
		{
			sum += (*it);
		}

		return sum;
	}

	void runTest()
	{
		std::string file{"Day01_Test.txt"};

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day01::RESULT1);

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day01::RESULT2);
	}

	void run()
	{
		std::string file{"Day01_Input.txt"};

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}