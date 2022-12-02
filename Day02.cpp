#include "Day02.h"

namespace day02
{
	enum class ChoiseOpponent
	{
		A = 1, // Rock
		B = 2, // Paper
		C = 3, // Scissor
	};

	enum class Choise
	{
		X = 1, // Rock
		Y = 2, // Paper
		Z = 3, // Scissor
	};

	enum class Prediction
	{
		X = 0, // Lose
		Y = 3, // Draw
		Z = 6, // Win
	};

	std::ostream& operator<<(std::ostream& out, ChoiseOpponent choise)
	{
		if (choise == ChoiseOpponent::A) std::cout << "Rock";
		if (choise == ChoiseOpponent::B) std::cout << "Paper";
		if (choise == ChoiseOpponent::C) std::cout << "Sciccor";

		return out;
	}

	std::ostream& operator<<(std::ostream& out, Choise choise)
	{
		if (choise == Choise::X) std::cout << "Rock";
		if (choise == Choise::Y) std::cout << "Paper";
		if (choise == Choise::Z) std::cout << "Sciccor";

		return out;
	}

	std::ostream& operator<<(std::ostream& out, Prediction p)
	{
		if (p == Prediction::X) std::cout << "Lose";
		if (p == Prediction::Y) std::cout << "Draw";
		if (p == Prediction::Z) std::cout << "Win";

		return out;
	}

	ChoiseOpponent getChoiseOpponent(const std::string choise)
	{
		if (choise == "A") return ChoiseOpponent::A;
		if (choise == "B") return ChoiseOpponent::B;
		return ChoiseOpponent::C;
	}

	Choise getChoise(const std::string choise)
	{
		if (choise == "X") return Choise::X;
		if (choise == "Y") return Choise::Y;
		return Choise::Z;
	}

	Prediction getPrediction(const std::string choise)
	{
		if (choise == "X") return Prediction::X;
		if (choise == "Y") return Prediction::Y;
		return Prediction::Z;
	}

	int getScore(const ChoiseOpponent& opp, const Choise& you)
	{
		int score{static_cast<int>(you)};

		if (opp == ChoiseOpponent::A)
		{
			if (you == Choise::Y) return score + 6; // win
			if (you == Choise::Z) return score + 0; // lose
			if (you == Choise::X) return score + 3; // draw
		}

		if (opp == ChoiseOpponent::B)
		{
			if (you == Choise::Z) return score + 6; // win
			if (you == Choise::X) return score + 0; // lose
			if (you == Choise::Y) return score + 3; // draw
		}

		if (opp == ChoiseOpponent::C)
		{
			if (you == Choise::X) return score + 6; // win
			if (you == Choise::Y) return score + 0; // lose
			if (you == Choise::Z) return score + 3; // draw
		}

		return 0;
	}

	int getScore(const ChoiseOpponent& opp, const Prediction& p)
	{
		int score{static_cast<int>(p)};
		Choise you{Choise::X};

		if (opp == ChoiseOpponent::A)
		{
			if (p == Prediction::X) you = {Choise::Z}; // lose
			if (p == Prediction::Y) you = {Choise::X}; // draw
			if (p == Prediction::Z) you = {Choise::Y}; // win
		}

		if (opp == ChoiseOpponent::B)
		{
			if (p == Prediction::X) you = {Choise::X}; // lose
			if (p == Prediction::Y) you = {Choise::Y}; // draw
			if (p == Prediction::Z) you = {Choise::Z}; // win
		}

		if (opp == ChoiseOpponent::C)
		{
			if (p == Prediction::X) you = {Choise::Y}; // lose
			if (p == Prediction::Y) you = {Choise::Z}; // draw
			if (p == Prediction::Z) you = {Choise::X}; // win
		}

		return score + static_cast<int>(you);
	}

	void log(const ChoiseOpponent& opp, const Choise& you)
	{
		std::cout << "Opponent choosed " << opp << ".\n";
		std::cout << "You choosed " << you << ".\n";
		std::cout << "Scored " << getScore(opp, you) << ".\n";
		std::cout << "\n";
	}

	void log(const ChoiseOpponent& opp, const Prediction& p)
	{
		std::cout << "Opponent choosed " << opp << ".\n";
		std::cout << "You " << p << "!\n";
		std::cout << "Scored " << getScore(opp, p) << ".\n";
		std::cout << "\n";
	}

	void split(const std::string str, std::vector<std::string>& out, char delim)
	{
		std::stringstream sstream(str);
		std::string choise;

		while (std::getline(sstream, choise, delim)) {
			out.push_back(choise);
		}
	}

	auto logic1(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		int total{0};

		while (std::getline(stream, line))
		{
			// Split line between ' '
			std::vector<std::string> out;
			split(line, out, ' ');

			// first entry is opponent, second entry is you
			ChoiseOpponent opp{getChoiseOpponent(out[0])};
			Choise you{getChoise(out[1])};

			if (debug) log(opp, you);

			// calculate score
			total += getScore(opp, you);
		}

		return total;
	}

	auto logic2(std::string file, bool debug = false)
	{
		std::ifstream stream{file};
		if (!stream.is_open()) return -1;

		std::string line;
		int total{0};

		while (std::getline(stream, line))
		{
			// Split line between ' '
			std::vector<std::string> out;
			split(line, out, ' ');

			// first entry is opponent, second entry is you
			ChoiseOpponent opp{getChoiseOpponent(out[0])};
			Prediction p{getPrediction(out[1])};

			if (debug) log(opp, p);

			// calculate score
			total += getScore(opp, p);
		}

		return total;
	}

	void runTest()
	{
		bool debug{true};

		std::string file{"Day02_Test.txt"};
		std::cout << "*** Testing day 2 ***\n\n";

		auto x = logic1(file, debug);
		std::cout << "Part 1 (Test): " << x << "\n";
		assert(x == day02::RESULT1);

		if (debug) std::cout << "------------------" << "\n";

		auto y = logic2(file, debug);
		std::cout << "Part 2 (Test): " << y << "\n";
		assert(y == day02::RESULT2);
	}

	void run()
	{
		std::string file{"Day02_Input.txt"};
		std::cout << "*** Running day 2 ***\n\n";

		auto x = logic1(file);
		std::cout << "Part 1: " << x << "\n";

		auto y = logic2(file);
		std::cout << "Part 2: " << y << "\n";
	}
}