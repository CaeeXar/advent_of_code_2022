#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>


#ifndef Day02

#define Day02

namespace day02
{
	constexpr int RESULT1{15};	   // part 1 example result
	constexpr int RESULT2{12};     // part 2 example result

	enum class ChoiseOpponent;
	enum class Choise;
	enum class Prediction;

	ChoiseOpponent getChoiseOpponent(const std::string choise);
	Choise getChoise(const std::string choise);
	Prediction getPrediction(const std::string choise);
	int getScore(const ChoiseOpponent& opp, const Choise& you);
	int getScore(const ChoiseOpponent& opp, const Prediction& you);
	void log(const ChoiseOpponent& opp, const Choise& you);
	void log(const ChoiseOpponent& opp, const Prediction& p);
	void split(const std::string str, std::vector<std::string>& out, char delim);

	auto logic1(std::string file, bool debug); // for part 1
	auto logic2(std::string file, bool debug); // for part 1
	void runTest();                // for testing (example input)
	void run();                    // for calculating (real input)
}

#endif
