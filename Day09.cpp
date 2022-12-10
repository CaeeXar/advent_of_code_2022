#include "Day09.h"

namespace day09
{
	struct Position
	{
		int x{0};
		int y{0};

		bool operator<(const Position& r) const noexcept
		{
			return (x == r.x) ? (y < r.y) : (x < r.x);
		}

		std::string to_string()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}
	};

	using Visited = std::set<Position>;

	int distance(Position& head, Position& tail)
	{
		return std::sqrt(std::pow(head.x - tail.x, 2) + std::pow(head.y - tail.y, 2));
	}

	void setPosition(Position& position, Position& newPos)
	{
		position.x = newPos.x; position.y = newPos.y;
	}

	void moveHead(Position& head, const char direction)
	{
		switch (direction)
		{
			case 'L': --head.x; break;
			case 'R': ++head.x; break;
			case 'D': --head.y; break;
			case 'U': ++head.y; break;
		}
	}

	void moveTail(Position& head, Position& tail, Position& last, Visited& visited, const char direction)
	{
		if (distance(head, tail) <= 1) return;
		setPosition(tail, last);
		visited.insert(tail);
	}

	void move(
		Position& head,
		Position& tail,
		Position& last,
		Visited& visited,
		const char direction,
		const int steps
	)
	{
		for (int i{0}; i < steps; ++i)
		{
			setPosition(last, head);                        // needed for correct tail-movement
			moveHead(head, direction);                      // move head 1-step into direction
			moveTail(head, tail, last, visited, direction); // move tail to last position if needed
		}
	}

	void moveTail2(Position& head, Position& tail) {
		int dx{head.x - tail.x}, dy{head.y - tail.y};
		if (std::abs(dx) > 1)
		{
			tail.x += dx / 2;
			if (std::abs(dy) > 1) tail.y += dy / 2;
			else tail.y += dy;
		}
		else if (std::abs(dy) > 1)
		{
			tail.y += dy / 2;
			tail.x += dx;
		}
	}

	void move2(
		std::vector<Position>& rope,
		Visited& visited,
		const char direction,
		const int steps
	)
	{
		for (int i{0}; i < steps; ++i)
		{
			moveHead(rope[0], direction);
			for (int idx{1}; idx < rope.size(); ++idx) moveTail2(rope[idx - 1], rope[idx]);
			visited.insert(rope[9]);
		}
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		Position head, tail, last;
		Visited visited{{0, 0}}; // inital tail position needs to be added, otherwise wont count
		while (std::getline(stream, line))
		{
			char direction{line.substr(0,1)[0]};
			int steps{std::stoi(line.substr(2))};
			move(head, tail, last, visited, direction, steps);
		}

		return (int)visited.size();
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		std::vector<Position> rope{10, {0, 0}};
		Visited visited{{0, 0}}; // inital tail position needs to be added, otherwise wont count
		while (std::getline(stream, line))
		{
			char direction{line.substr(0,1)[0]};
			int steps{std::stoi(line.substr(2))};
			move2(rope, visited, direction, steps);
		}

		return (int)visited.size();
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day09_Test.txt"};
		std::cout << "*** Testing day 09 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		//assert(x == day09::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file);
		std::cout << "Part 2 (Test): " << y << "\n";
		//assert(y == day09::RESULT2);
	}

	void run()
	{
		std::string file{"Day09_Input.txt"};
		std::cout << "*** Running day 09 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}