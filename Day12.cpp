#include "Day12.h"

namespace day12
{
	using Graph = std::vector<std::vector<int64_t>>;

	struct Position
	{
		int64_t x{-1};
		int64_t y{-1};
		std::string name{"Position"};

		bool operator==(const Position& other) const
		{
			return x == other.x && y == other.y;
		}

		std::string toString()
		{
			return name + " (" + std::to_string(x) + "," + std::to_string(y) + ")";
		}
	};

	void printGraph(const Graph& graph)
	{
		std::cout << "Graph:\n";
		for (std::vector<int64_t> row : graph)
		{
			for (int64_t height : row) std::cout << height << (height > 9 ? " " : "  ");
			std::cout << "\n";
		}
	}

	int64_t fewestSteps(const Graph& graph, const Position& start, const Position& end)
	{
		// setup
		size_t height{graph.size()}, width{graph[0].size()};
		Graph dist{height, std::vector<int64_t>(width, INT64_MAX - 10)};
		dist[start.y][start.x] = 0;
		std::vector<std::vector<bool>> visited{height, std::vector<bool>(width, false)};
		std::queue<Position> queue{};
		queue.push(start);

		// BFS
		while (!queue.empty())
		{
			Position p{queue.front()};
			queue.pop();

			if (p == end) return dist[p.y][p.x];
			if (visited[p.y][p.x]) continue;

			visited[p.y][p.x] = {true};

			std::vector<int64_t>::iterator it;
			std::vector<int64_t> adj{1, -1};
			for (it = adj.begin(); it != adj.end(); ++it)
			{
				int64_t x{p.x + *it}, y{p.y + *it}, currentValue{graph[p.y][p.x]};
				if (x <= width - 1 && x >= 0 && !visited[p.y][x] &&
					graph[p.y][x] - currentValue <= (int64_t)1)
				{
					queue.push(Position{x, p.y});
					dist[p.y][x] = {std::min(dist[p.y][x], dist[p.y][p.x] + 1)};
				}

				if (y <= height - 1 && y >= 0 && !visited[y][p.x] &&
					graph[y][p.x] - currentValue <= (int64_t)1)
				{
					queue.push(Position{p.x, y});
					dist[y][p.x] = {std::min(dist[y][p.x], dist[p.y][p.x] + 1)};
				}
			}
		}

		return (int64_t)-1;
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return (int64_t)-1;

		Graph graph;
		Position start, end;
		int64_t iRow{0}, iCol{0};
		std::string line;
		while (std::getline(stream, line))
		{
			std::vector<int64_t> row{};
			for (char c : line)
			{
				if (c == 'S')
				{
					start = {iCol, iRow, "Start"};
					c = {'a'};
				}
				else if (c == 'E')
				{
					end = {iCol, iRow, "End"};
					c = {'z'};
				}

				row.push_back((int64_t)(c - 'a'));
				++iCol;
			}

			graph.push_back(row);
			++iRow;
			iCol = {0};
		}

		if (debug)
		{
			std::cout << start.toString() << "\n";
			std::cout << end.toString() << "\n";
			printGraph(graph);
		}

		return fewestSteps(graph, start, end);
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return (int64_t)-1;

		Graph graph;
		Position end;
		std::vector<Position> startPositions{};
		int64_t iRow{0}, iCol{0};
		std::string line;
		while (std::getline(stream, line))
		{
			std::vector<int64_t> row{};
			for (char c : line)
			{
				if (c == 'S' || c == 'a')
				{
					startPositions.push_back(Position{iCol, iRow, "Start"});
					c = {'a'};
				}
				else if (c == 'E')
				{
					end = {iCol, iRow, "End"};
					c = {'z'};
				}

				row.push_back((int64_t)(c - 'a'));
				++iCol;
			}

			graph.push_back(row);
			++iRow;
			iCol = {0};
		}

		int64_t minSteps = {INT64_MAX};

		for (Position start : startPositions)
		{
			int64_t steps{fewestSteps(graph, start, end)};
			minSteps = {std::min(minSteps, steps > -1 ? steps : minSteps)};
		}

		return minSteps;
	}

	void runTest()
	{
		std::string file{"Day12_Test.txt"};
		std::cout << "*** Testing day 12 ***\n\n";

		auto x = logic1(file, true);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day12::RESULT1);

		std::cout << "------------------" << "\n";

		auto y = logic2(file, true);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day12::RESULT2);
	}

	void run()
	{
		std::string file{"Day12_Input.txt"};
		std::cout << "*** Running day 12 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}