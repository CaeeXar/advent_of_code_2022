#include "Day14.h"

namespace day14
{
	struct Position
	{
		int x, y;
		bool isSand{false};

		bool operator<(const Position& r) const noexcept
		{
			return (x == r.x) ? (y < r.y) : (x < r.x);
		}

		bool operator==(const Position& other) const
		{
			return x == other.x && y == other.y;
		}

		std::string toString()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}
	};

	using Positions = std::vector<Position>;
	using Boundaries = std::pair<Position, Position>;

	int sign(int x)
	{
		return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
	}

	Positions getRockPositions(std::string_view line)
	{
		std::vector<std::string> input;
		boost::split(input, line, boost::is_any_of(" -> "), boost::token_compress_on);

		Positions positions{};
		for (auto coord : input)
		{
			std::vector<std::string> pos;
			boost::split(pos, coord, boost::is_any_of(","), boost::token_compress_on);
			positions.push_back(Position(std::stoi(pos[0]), std::stoi(pos[1])));
		}

		size_t size{positions.size()};
		for (size_t i{0}; i < size - 1; ++i)
		{
			Position from{positions[i]}, to{positions[i + 1]};
			int dx{to.x - from.x}, dy{to.y - from.y};
			for (int x{1}; x < std::abs(dx); ++x)
			{
				positions.push_back(Position(from.x + (sign(dx) * x), from.y));
			}
			for (int y{1}; y < std::abs(dy); ++y)
			{
				positions.push_back(Position(from.x, from.y + (sign(dy) * y)));
			}
		}

		std::sort(positions.begin(), positions.end());

		return positions;
	}

	Boundaries getBoundaries(const Positions& cave)
	{
		Position min{INT_MAX, INT_MAX}, max{0, 0};

		for (auto rockPosition : cave)
		{
			// get min & max x/y-values from rock
			min.x = std::min(min.x, rockPosition.x);
			min.y = std::min(min.y, rockPosition.y);
			max.x = std::max(max.x, rockPosition.x);
			max.y = std::max(max.y, rockPosition.y);
		}

		// min-boundary must be (500, 0) since thats where the source of the sand is
		min.x = std::min(min.x, 500);
		min.y = std::min(min.y, 0);
		return Boundaries{min, max};
	}

	bool contains(const Positions& cave, const Position& position)
	{
		return (std::find(cave.begin(), cave.end(), position) != cave.end());
	}

	Position const& getPosition(const Positions& cave, const Position& p)
	{
		for (auto& position : cave)
		{
			if (position == p) return position;
		}

	}

	void printCave(const Positions& cave, const Boundaries& boundaries)
	{
		for (int y{boundaries.first.y}; y <= boundaries.second.y; ++y)
		{
			for (int x{boundaries.first.x}; x <= boundaries.second.x; ++x)
			{
				Position p = Position(x, y);
				if (contains(cave, p))
				{
					if (getPosition(cave, p).isSand) std::cout << "o";
					else std::cout << "#";
				}
				else if (x == 500 && y == 0) std::cout << "+";
				else std::cout << ".";
			}

			std::cout << "\n";
		}
	}

	void addSand(Positions& cave, const Boundaries& boundaries)
	{
		while (true) {
			bool isMoving{true};
			Position sand{500, 0, true};

			while (isMoving)
			{
				if (sand.x < boundaries.first.x || sand.x > boundaries.second.x ||
					sand.y < boundaries.first.y || sand.y > boundaries.second.y) return;

				if (!contains(cave, Position(sand.x, sand.y + 1)))
				{
					++sand.y;
				}
				else if (!contains(cave, Position(sand.x - 1, sand.y + 1)))
				{
					++sand.y; --sand.x;
				}
				else if (!contains(cave, Position(sand.x + 1, sand.y + 1)))
				{
					++sand.y; ++sand.x;
				}
				else
				{
					isMoving = {false};
				}
			}

			cave.push_back(sand);
		}
	}

	void addSand2(Positions& cave, const int floor)
	{
		while (true) {
			Position sand{500, 0, true};

			while (true)
			{
				// stop when we're at the sand-source
				if (cave.back() == Position(500, 0))
				{
					std::cout << "source reached\n";
					return;
				}

				if (sand.y == floor) break;

				if (!contains(cave, Position(sand.x, sand.y + 1)))
				{
					++sand.y;
				}
				else if (!contains(cave, Position(sand.x - 1, sand.y + 1)))
				{
					++sand.y; --sand.x;
				}
				else if (!contains(cave, Position(sand.x + 1, sand.y + 1)))
				{
					++sand.y; ++sand.x;
				}
				else
				{
					break;
				}
			}

			cave.push_back(sand);
		}
	}

	int countSand(const Positions& cave)
	{
		int sum{0};
		for (auto position : cave)
		{
			if (position.isSand) ++sum;
		}

		return sum;
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		Positions cave{};
		std::string line;
		while (std::getline(stream, line))
		{
			Positions rock{getRockPositions(line)};
			cave.insert(cave.end(), rock.begin(), rock.end());
		}

		Boundaries boundaries{getBoundaries(cave)};
		addSand(cave, boundaries);

		if (debug) printCave(cave, boundaries);

		return countSand(cave);
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		Positions cave{};
		std::string line;
		while (std::getline(stream, line))
		{
			Positions rock{getRockPositions(line)};
			cave.insert(cave.end(), rock.begin(), rock.end());
		}

		Boundaries boundaries{getBoundaries(cave)};
		addSand2(cave, boundaries.second.y + 1);

		if (debug)
		{
			boundaries = {getBoundaries(cave)};
			printCave(cave, boundaries);
		}

		return countSand(cave);
	}

	void runTest()
	{
		std::string file{"Day14_Test.txt"};
		std::cout << "*** Testing day 14 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day14::RESULT1);

		std::cout << "------------------" << "\n";

		auto y = logic2(file, true);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day14::RESULT2);
	}

	void run()
	{
		std::string file{"Day14_Input.txt"};
		std::cout << "*** Running day 14 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}