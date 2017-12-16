#include "stdafx.h"
#include "December01.h"

int December01::ComputeSumForCaptchaNumber(int captchaNumber)
{
	if (captchaNumber < 10)
	{
		return 0;
	}

	int tempNum = captchaNumber;
	int sum = 0;
	int prevRest = 0;

	while (tempNum > 0)
	{
		int rest = tempNum % 10;
		tempNum /= 10;

		if (rest == prevRest)
		{
			sum += rest;
		}

		prevRest = rest;
	}

	if (prevRest == captchaNumber % 10)
	{
		sum += prevRest;
	}

	return sum;
}

int December01::ComputeSumForCaptchaString(const std::string& captchaString)
{
	if (captchaString.length() < 2)
	{
		return 0;
	}

	int prevDigit = 0;
	int sum = 0;
	for (auto& c : captchaString)
	{
		int digit = CharToInt(c);
		if (digit == prevDigit)
		{
			sum += digit;
		}

		prevDigit = digit;
	}

	if (prevDigit == CharToInt(captchaString[0]))
	{
		sum += prevDigit;
	}

	return sum;
}

int December01::CharToInt(char c)
{
	return c - '0';
}