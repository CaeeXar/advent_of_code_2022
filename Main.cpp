#include "Dayxx.h"
#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"
#include "Day05.h"
#include "Day06.h"
#include "Day07.h"
#include "Day08.h"
#include "Day09.h"
#include "Day10.h"

int main()
{
	int day{10}, test{1};

	if (test)
	{
		if (day < 1)   dayxx::runTest();
		if (day == 1)  day01::runTest();
		if (day == 2)  day02::runTest();
		if (day == 3)  day03::runTest();
		if (day == 4)  day04::runTest();
		if (day == 5)  day05::runTest();
		if (day == 6)  day06::runTest();
		if (day == 7)  day07::runTest();
		if (day == 8)  day08::runTest();
		if (day == 9)  day09::runTest();
		if (day == 10) day10::runTest();
	}
	else
	{
		if (day < 1)   dayxx::run();
		if (day == 1)  day01::run();
		if (day == 2)  day02::run();
		if (day == 3)  day03::run();
		if (day == 4)  day04::run();
		if (day == 5)  day05::run();
		if (day == 6)  day06::run();
		if (day == 7)  day07::run();
		if (day == 8)  day08::run();
		if (day == 9)  day09::run();
		if (day == 10) day10::run();
	}

	return 0;
}