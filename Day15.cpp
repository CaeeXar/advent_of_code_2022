#include "Day15.h"

namespace day15
{
	enum class Tile
	{
		empty = '.',
		beacon = 'B',
		sensor = 'S',
		scan = '#',
	};

	struct Point
	{
		int64_t x, y;
		Tile tile{Tile::empty};

		bool operator<(const Point& r) const noexcept
		{
			return (x == r.x) ? (y < r.y) : (x < r.x);
		}

		bool operator==(const Point& other) const
		{
			return x == other.x && y == other.y;
		}

		std::string toString()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}
	};

	using Tunnel = std::map<Point, Point>;
	using Scans = std::set<Point>;

	void parsePoint(Tunnel& tunnel, const std::string& line)
	{
		Point sensor, beacon;
		size_t x{line.find("x")}, y{line.find("y")}, xs{line.find(",")}, ys{line.find(":")};
		int64_t xv{std::stoi(line.substr(x + 2, xs - x - 2))},
			yv{std::stoi(line.substr(y + 2, ys - y - 2))};
		sensor = {xv, yv, Tile::sensor};

		x = {line.find("x", ++x)}; y = {line.find("y", ++y)}; xs = {line.find(",", ++xs)};
		xv = {std::stoi(line.substr(x + 2, xs - x - 2))};
		yv = {std::stoi(line.substr(y + 2))};
		beacon = {xv, yv, Tile::beacon};

		tunnel.emplace(sensor, beacon);
	}

	int64_t manhattan(const Point& p1, const Point& p2)
	{
		return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
	}

	bool containsValue(const Tunnel& tunnel, const Point& p)
	{
		return (std::find_if(
			tunnel.begin(),
			tunnel.end(),
			[p](const auto& mo) {return mo.second == p; }
		) != tunnel.end());
	}

	void generateScans(Tunnel& tunnel, Scans& scans)
	{
		for (auto& pair : tunnel)
		{
			if (pair.first.tile != Tile::sensor) continue;

			Point sensor{pair.first}, beacon{pair.second};
			int64_t dist{manhattan(sensor, beacon)};

			for (int64_t row{dist * -1}; row <= dist; ++row)
			{
				Point centerScan{sensor.x, sensor.y + row};
				if (std::abs(row) - dist == 0) scans.insert(centerScan);
				else
				{
					for (int64_t col{std::abs(row) - dist};
						col <= std::abs(std::abs(row) - dist);
						++col)
					{
						Point scan{sensor.x + col, sensor.y + row};
						scans.insert(scan);
					}
				}
			}
		}
	}

	void printTunnel(Tunnel& tunnel, Scans& scans)
	{
		Point min{INT64_MAX, INT64_MAX}, max{INT64_MIN, INT64_MIN};
		for (auto& pair : tunnel)
		{
			min.x = std::min(min.x, std::min(pair.first.x, pair.second.x));
			min.y = std::min(min.y, std::min(pair.first.y, pair.second.y));
			max.x = std::max(max.x, std::max(pair.first.x, pair.second.x));
			max.y = std::max(max.y, std::max(pair.first.y, pair.second.y));
		}

		for (auto& point : scans)
		{
			min.x = std::min(min.x, point.x);
			min.y = std::min(min.y, point.y);
			max.x = std::max(max.x, point.x);
			max.y = std::max(max.y, point.y);
		}

		for (int64_t y{min.y}; y <= max.y; ++y)
		{
			for (int64_t x{min.x}; x <= max.x; ++x)
			{
				Point p{x, y};
				if (tunnel.contains(p)) std::cout << (char)Tile::sensor;
				else if (containsValue(tunnel, p)) std::cout << (char)Tile::beacon;
				else if (scans.contains(p)) std::cout << (char)Tile::scan;
				else std::cout << (char)Tile::empty;
			}

			std::cout << "\n";
		}
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return (int64_t)-1;

		Tunnel tunnel{};
		std::string line;
		while (std::getline(stream, line))
		{
			parsePoint(tunnel, line);
		}

		if (debug)
		{
			Scans scans{};
			generateScans(tunnel, scans);
			printTunnel(tunnel, scans);
		}

		int64_t Y{debug ? 10 : 2000000}, sum{0};
		Scans scans{};
		for (auto& pair : tunnel)
		{
			Point sensor{pair.first}, beacon{pair.second};
			int64_t dist{manhattan(sensor, beacon)};
			if (Y <= sensor.y + dist || Y >= sensor.y - dist)
			{
				int64_t len{dist - std::abs(sensor.y - Y)};
				if (len == 0) len = 1; // center, only one #
				for (int64_t x{len * -1}; x <= len; ++x)
				{
					scans.insert(Point(sensor.x + x, Y));
				}
			}
		}

		return (int64_t)scans.size() - 1;
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
		std::string file{"Day15_Test.txt"};
		std::cout << "*** Testing day 15 ***\n\n";

		auto x = logic1(file, true);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day15::RESULT1);

		std::cout << "------------------" << "\n";

		auto y = logic2(file, true);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day15::RESULT2);
	}

	void run()
	{
		std::string file{"Day15_Input.txt"};
		std::cout << "*** Running day 15 ***\n\n";

		auto x = logic1(file, false);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file, false);
		std::cout << "Part 2: " << y << "\n";
	}
}