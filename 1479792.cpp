#include <cstdio>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

string addBits(string x, string y)
{
	string result = "";
	int carry = 0;
	int xSize = x.size() - 1;
	int ySize = y.size() - 1;
	while (xSize >= 0 || ySize >= 0 || carry == 1)
	{
		carry += xSize >= 0 ? x[xSize--] - '0' : 0;
		carry += ySize >= 0 ? y[ySize--] - '0' : 0;
		result = char(carry % 2 + '0') + result;
		carry /= 2;
	}
	return result;
}

int multiplySingleBit(string x, string y)
{
	return (x[0] - '0')*(y[0] - '0');
}

unsigned volatile long long int  multiplyByClssc(string x, string y)
{
	if (x.length() != y.length())
	{
		if (x.length() > y.length())
		{
			int temp = x.length() - y.length();
			for (int i = 0; i < temp; i++)
			{
				y = '0' + y;
			}
		}
		else
		{
			int temp = y.length() - x.length();
			for (int i = 0; i < temp; i++)
			{
				x = '0' + x;
			}
		}
	}
	//cout << "x:" << x << endl;
	//cout << "y: " << y << endl;
	int lengthOfNumber = x.length();
	if (lengthOfNumber == 0) return 0;
	if (lengthOfNumber == 1) return multiplySingleBit(x, y);
	string xLow, xHigh, yLow, yHigh;
	int n = floor(lengthOfNumber / 2);
	int formula = lengthOfNumber - n;
	for (int i = 0; i <lengthOfNumber; i++) {
		if (i < n)
		{
			xHigh += x[i];
			yHigh += y[i];
		}
		else
		{
			xLow += x[i];
			yLow += y[i];
		}
	}

	unsigned volatile long long int P1 = multiplyByClssc(xHigh, yHigh);
	unsigned volatile long long int P2 = multiplyByClssc(xHigh, yLow);
	unsigned volatile long long int P3 = multiplyByClssc(xLow, yHigh);
	unsigned volatile long long int P4= multiplyByClssc(xLow, yLow);
	unsigned volatile long long int c1 = 2;
	unsigned volatile long long int c2 = 2;

	for (int i = 1; i < formula*2; i++)
	{
		if (i < formula)
		{
			c2 *= 2;
		}

		c1 *= 2;
	}
	volatile long long int result = P1*(c1) + (P2+P3)*(c2)+ P4;
	return result;
}

unsigned volatile long long int  algorithm0(string x, string y)
{
	if (x.length() != y.length())
	{
		if (x.length() > y.length())
		{
			int temp = x.length() - y.length();
			for (int i = 0; i < temp; i++)
			{
				y = '0' + y;
			}
		}
		else
		{
			int temp = y.length() - x.length();
			for (int i = 0; i < temp; i++)
			{
				x = '0' + x;
			}
		}
	}
	int lengthOfNumber = max(x.length(),y.length());
	if (lengthOfNumber == 1) return multiplySingleBit(x, y);
	string xLow, xHigh, yLow, yHigh = "";
	int n = floor(lengthOfNumber / 2);
	int formula = lengthOfNumber - n;
	for (int i = 0; i < lengthOfNumber; i++) {
		if (i < n)
		{
			xHigh += x[i];
			yHigh += y[i];
		}
		else
		{
			xLow += x[i];
			yLow += y[i];
		}
	}

	unsigned volatile long long int  P1 = algorithm0(xHigh, yHigh);
	unsigned volatile long long int  P2 = algorithm0(xLow, yLow);
	unsigned volatile long long int  P3 = algorithm0(addBits(xHigh,xLow), addBits(yHigh,yLow));

	unsigned volatile long long int  c1 = 2;
	unsigned volatile long long int  c2 = 2;

	for (int i = 1; i < 2 * formula; i++)
	{
		if (i < formula)
		{
			c2 *= 2;
		}

		c1 *= 2;
	}

	return ((P1*c1) + ((P3 - P1 - P2)*c2) + P2);
}

int main() {
	ofstream myfile;
	myfile.open("result.txt");
	srand(time(NULL));
	string xBit;
	string yBit;
	int bit = 32;
	while (bit != 2048)
	{
		xBit += '1';
		yBit += '1';
		for (int i = 1; i < bit; i++)
		{
			int temp = rand() % 2;
			stringstream  ss;
			ss << temp;
			xBit += ss.str();

		}
		for (int i = 1; i < bit; i++)
		{
			int temp = rand() % 2;
			stringstream  ss;
			ss << temp;
			yBit += ss.str();
		}

		myfile << "Bit: "  << bit << "\n";
		myfile << "X: " << xBit << "\n";
		myfile << "Y: " << yBit << "\n";

		clock_t timeClassic;
		clock_t timeAlgorithm0;
		//cout << xBit << endl;
		//cout << yBit << endl;
		timeClassic = clock();
		unsigned volatile long long int resultClsc = multiplyByClssc(xBit, yBit);
		timeClassic = clock() - timeClassic;
		timeAlgorithm0 = clock();
		//cout << "Time for classic algorithm: " << (float)timeClassic / CLOCKS_PER_SEC << " seconds" << endl;
		myfile << "Result ( Classical Method ): " << resultClsc << "\n";
		myfile << "Time: " << (float)timeClassic / CLOCKS_PER_SEC <<" seconds"<< "\n";

		unsigned volatile long long int resultAlg = algorithm0(xBit, yBit);
		timeAlgorithm0 = clock() - timeAlgorithm0;
		//cout << "Time for algorithm0 algorithm: " << (float)timeAlgorithm0 / CLOCKS_PER_SEC << " seconds" << endl;
		myfile << "Result ( Algorithm0 Method ): " << resultAlg << "\n";
		myfile << "Time: " << (float)timeAlgorithm0 / CLOCKS_PER_SEC << " seconds" << "\n\n\n\n";

		//cout << endl;
		//cout << endl;
		//cout << endl;

		bit *= 2;
	}
	myfile.close();

	
}