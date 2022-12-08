#include "Day07.h"

namespace day07
{
	struct File
	{
		std::string name{""};
		long long size{0};
	};

	struct Directory
	{
		std::string name{""};
		std::vector<Directory> directories{};
		std::vector<File> files{};
		long long sumFileSizes()
		{
			long long sum{0};
			for (File f : files) sum += f.size;
			for (Directory dir : directories) sum += dir.sumFileSizes();
			return sum;
		};
	};

	bool operator==(const Directory& lh, const std::string& name)
	{
		return lh.name == name;
	}

	bool contains(std::vector<Directory>& dirs, const std::string& name)
	{
		return std::find(dirs.begin(), dirs.end(), name) != dirs.end();
	}

	Directory& find(std::vector<Directory>& dirs, const std::string& name)
	{
		std::vector<Directory>::iterator it{std::find(dirs.begin(), dirs.end(), name)};
		return *it;
	}

	void printDirectories(const std::vector<Directory>& dirs)
	{
		for (Directory dir : dirs)
		{
			std::cout << dir.name << ":\n";

			for (File file : dir.files)
			{
				std::cout << " - File: " << file.name << " (size: " << file.size << ")\n";
			}

			for (Directory subdir : dir.directories)
			{
				std::cout << " - Directory: " << subdir.name << " (size: " << subdir.sumFileSizes() << ")\n";
			}

			std::cout << "\n";
		}
	}

	long long findSumBelow(const std::vector<Directory>& dirs, const long long max = 100000)
	{
		long long sum{0};

		for (Directory dir : dirs)
		{
			long long dirSize{dir.sumFileSizes()};
			if (dirSize < max) sum += dirSize;
		}

		return sum;
	}

	long long findSmallestSize(const std::vector<Directory>& dirs, long long max)
	{
		std::vector<long long> candidates;

		for (Directory dir : dirs)
		{
			long long dirSize{dir.sumFileSizes()};
			if (dirSize >= max) candidates.push_back(dirSize);
		}

		return *boost::range::min_element(candidates);
	}

	void correctDirectorySizes(std::vector<Directory>& dirs)
	{
		for (auto itDir = dirs.rbegin(); itDir != dirs.rend(); ++itDir)
		{
			for (auto itSubDir = (*itDir).directories.rbegin(); itSubDir != (*itDir).directories.rend(); ++itSubDir)
			{
				(*itSubDir) = find(dirs, (*itSubDir).name);
			}
		}
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1LL;

		std::vector<std::string> path{};
		std::string line;
		std::vector<Directory> dirs{};
		while (std::getline(stream, line))
		{
			if (line == "$ cd ..")
			{
				path.pop_back();
			}
			else if (boost::starts_with(line, "$ cd"))
			{
				path.push_back(line.substr(5));
				std::string newDirectory{boost::join(path, "/")};
				dirs.push_back({newDirectory, {}, {}});
			}
			else if (!boost::starts_with(line, "$"))
			{
				std::vector<std::string> data;
				boost::split(data, line, boost::is_any_of(" "), boost::token_compress_on);
				std::string newDirectory{boost::join(path, "/")};

				Directory& currentDirectory{find(dirs, newDirectory)};
				if (data[0] == "dir") currentDirectory.directories.push_back({newDirectory + "/" + data[1]});
				else currentDirectory.files.push_back({data[1], std::stoi(data[0])});
			}
		}

		correctDirectorySizes(dirs);
		if (debug) printDirectories(dirs);

		return findSumBelow(dirs);
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1LL;

		std::vector<std::string> path{};
		std::string line;
		std::vector<Directory> dirs{};
		while (std::getline(stream, line))
		{
			if (line == "$ cd ..")
			{
				path.pop_back();
			}
			else if (boost::starts_with(line, "$ cd"))
			{
				path.push_back(line.substr(5));
				std::string newDirectory{boost::join(path, "/")};
				dirs.push_back({newDirectory, {}, {}});
			}
			else if (!boost::starts_with(line, "$"))
			{
				std::vector<std::string> data;
				boost::split(data, line, boost::is_any_of(" "), boost::token_compress_on);
				std::string newDirectory{boost::join(path, "/")};

				Directory& currentDirectory{find(dirs, newDirectory)};
				if (data[0] == "dir") currentDirectory.directories.push_back({newDirectory + "/" + data[1]});
				else currentDirectory.files.push_back({data[1], std::stoi(data[0])});
			}
		}

		correctDirectorySizes(dirs);
		if (debug) printDirectories(dirs);

		Directory root{find(dirs, "/")};
		long long diskSpace{70000000},
			updateRequired{30000000},
			usedSpace{root.sumFileSizes()},
			unusedSpace{diskSpace - usedSpace},
			requiredSpace{updateRequired - unusedSpace};

		return findSmallestSize(dirs, requiredSpace);
	}

	void runTest()
	{
		bool debug{false};

		std::string file{"Day07_Test.txt"};
		std::cout << "*** Testing day 07 ***\n\n";

		auto x = logic1(file, debug);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day07::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file, debug);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day07::RESULT2);
	}

	void run()
	{
		std::string file{"Day07_Input.txt"};
		std::cout << "*** Running day 07 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}