#include "Day05.h"

namespace day05
{

	void reverseStack(std::stack<char>& stack)
	{
		char item;
		std::stack<char> tmpStack;

		while (stack.empty() == false)
		{
			item = stack.top();
			stack.pop();
			tmpStack.push(item);
		}

		stack = tmpStack;
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::string result{""};
		std::ifstream stream{file};
		if (!stream.is_open()) return result;

		// splite input into 2 different strings
		std::string line, stack, moves;
		bool isStack{true};
		while (std::getline(stream, line))
		{
			if (line.size() == 0)
			{
				isStack = {false};
				continue; // continue removes the empty line
			}

			if (isStack) stack += line + "\n";
			else  moves += line + "\n";
		}

		// generate initial stacks
		std::vector<std::string> out;
		boost::split(out, stack, boost::is_any_of("\n"), boost::token_compress_on);
		boost::trim(out[out.size() - 2]);
		boost::split(out, out[out.size() - 2], boost::is_any_of(" "), boost::token_compress_on);
		const uint64_t size{static_cast<uint64_t>(out.size())};
		std::vector<std::stack<char>> stacks{size};
		std::stringstream sstream{stack};

		while (std::getline(sstream, line))
		{
			for (int i{0}; i < line.size(); ++i)
			{
				// /4 since the spacing between chars is 
				if (line[i] >= 'A' && line[i] <= 'Z') stacks[i / 4].push(line[i]);
			}
		}

		for (int i{0}; i < stacks.size(); ++i)
		{
			reverseStack(stacks[i]);
		}

		// rearrange
		sstream.clear();
		sstream.str(moves);
		while (std::getline(sstream, line))
		{
			// prepare line
			line.replace(0, 5, "");
			line.replace(line.find("from"), 5, "");
			line.replace(line.find("to"), 3, "");
			boost::split(out, line, boost::is_any_of(" "), boost::token_compress_on);
			int amount{std::stoi(out[0])}, from{std::stoi(out[1]) - 1}, to{std::stoi(out[2]) - 1};

			// move
			for (int i{0}; i < amount; ++i)
			{
				if (stacks[from].empty()) break;
				char c{stacks[from].top()};
				stacks[to].push(c);
				stacks[from].pop();
			}
		}

		// get top crates
		for (int i{0}; i < size; ++i)
		{
			result += stacks[i].top();
		}

		return result;
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::string result{""};
		std::ifstream stream{file};
		if (!stream.is_open()) return result;

		// splite input into 2 different strings
		std::string line, stack, moves;
		bool isStack{true};
		while (std::getline(stream, line))
		{
			if (line.size() == 0)
			{
				isStack = {false};
				continue; // continue removes the empty line
			}

			if (isStack) stack += line + "\n";
			else  moves += line + "\n";
		}

		// generate initial stacks
		std::vector<std::string> out;
		boost::split(out, stack, boost::is_any_of("\n"), boost::token_compress_on);
		boost::trim(out[out.size() - 2]);
		boost::split(out, out[out.size() - 2], boost::is_any_of(" "), boost::token_compress_on);
		const uint64_t size{static_cast<uint64_t>(out.size())};
		std::vector<std::stack<char>> stacks{size};
		std::stringstream sstream{stack};

		while (std::getline(sstream, line))
		{
			for (int i{0}; i < line.size(); ++i)
			{
				// /4 since the spacing between chars is 
				if (line[i] >= 'A' && line[i] <= 'Z') stacks[i / 4].push(line[i]);
			}
		}

		for (int i{0}; i < stacks.size(); ++i)
		{
			reverseStack(stacks[i]);
		}

		// rearrange
		sstream.clear();
		sstream.str(moves);
		while (std::getline(sstream, line))
		{
			// prepare line
			line.replace(0, 5, "");
			line.replace(line.find("from"), 5, "");
			line.replace(line.find("to"), 3, "");
			boost::split(out, line, boost::is_any_of(" "), boost::token_compress_on);
			int amount{std::stoi(out[0])}, from{std::stoi(out[1]) - 1}, to{std::stoi(out[2]) - 1};
			std::stack<char> q{};

			// move
			for (int i{0}; i < amount; ++i)
			{
				if (stacks[from].empty()) break;

				char c{stacks[from].top()};
				q.push(c);
				stacks[from].pop();
			}

			while (!q.empty())
			{
				char c{q.top()};
				stacks[to].push(c);
				q.pop();
			}
		}

		// get top crates
		for (int i{0}; i < size; ++i)
		{
			result += stacks[i].top();
		}

		return result;
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day05_Test.txt"};
		std::cout << "*** Testing day 05 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day05::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day05::RESULT2);
	}

	void run()
	{
		std::string file{"Day05_Input.txt"};
		std::cout << "*** Running day 05 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}