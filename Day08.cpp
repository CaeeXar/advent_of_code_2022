#include "Day08.h"

namespace day08
{

	void printTreeMap(const std::vector<std::vector<int>>& treeMap)
	{
		for (std::vector<int> row : treeMap)
		{
			for (int value : row) std::cout << value;
			std::cout << "\n";
		}
	}

	bool visibleHorizontal(const std::vector<std::vector<int>>& treeMap,
		const int row,
		const int col,
		const int value)
	{
		bool isVisibleLeft{true}, isVisibleRight{true};
		for (int _col{0}; _col < treeMap[row].size(); ++_col)
		{
			if (treeMap[row][_col] >= value && _col != col)
			{
				if (_col < col) isVisibleLeft = {false}; // visible from the left  (_col < col)
				else isVisibleRight = {false};           // visible from the right (_col > col)
			}
		}

		return isVisibleLeft || isVisibleRight;
	}

	bool visibleVertical(const std::vector<std::vector<int>>& treeMap,
		const int row,
		const int col,
		const int value)
	{
		bool isVisibleTop{true}, isVisibleBottom{true};
		for (int _row{0}; _row < treeMap.size(); ++_row)
		{
			if (treeMap[_row][col] >= value && _row != row)
			{
				if (_row < row) isVisibleTop = {false}; // visible from top    (_row < row)
				else isVisibleBottom = {false};         // visible from bottom (_row > row)
			}
		}

		return isVisibleTop || isVisibleBottom;
	}

	int countVisibleTrees(const std::vector<std::vector<int>>& treeMap)
	{
		int visible{0};
		for (int row{1}; row < treeMap.size() - 1; ++row)
		{
			for (int col{1}; col < treeMap[row].size() - 1; ++col)
			{
				int value{treeMap[row][col]};
				if (visibleHorizontal(treeMap, row, col, value) ||
					visibleVertical(treeMap, row, col, value)) visible++;
			}
		}

		return visible;
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		// generate tree-map
		std::string line;
		std::vector<std::vector<int>> treeMap;
		while (std::getline(stream, line))
		{
			treeMap.push_back({});
			for (int i{0}; i < line.size(); ++i) treeMap[treeMap.size() - 1].push_back(int(line[i] - '0'));
		}

		if (debug) printTreeMap(treeMap);

		// count visible trees
		int visible{((int)treeMap.size() * 4 - 4) + countVisibleTrees(treeMap)};

		return visible;
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
		bool debug{true};

		std::string file{"Day08_Test.txt"};
		std::cout << "*** Testing day 08 ***\n\n";

		auto x = logic1(file, debug);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day08::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file, debug);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day08::RESULT2);
	}

	void run()
	{
		std::string file{"Day08_Input.txt"};
		std::cout << "*** Running day 08 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}