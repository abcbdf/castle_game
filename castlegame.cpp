// castlegame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>
#include<algorithm>
#include <sys/timeb.h>

using namespace std;

#define acme 1e9

struct Strategy
{
	int index;
	double score;
	int times;
};

vector<vector<int>> allStrategy;
vector<Strategy> sampleStrategy;
int countS;


void attack(const vector<int> &a, const vector<int> &b, int &scoreA, int &scoreB)
{
	scoreA = 0;
	scoreB = 0;
	for (int i = 0; i < 10; i++)
	{
		if (a[i] > 2 * b[i])
		{
			scoreA += i + 1;
		}
		else if (b[i] > 2 * a[i])
		{
			scoreB += i + 1;
		}
	}
}

void gen(vector<int> &a) // uneven, deprecated
{
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			a[i] = rand() % (100 / 10 + 1);
		}
		else if (i == 9)
		{
			a[i] = 100 - sum;
			//assert(a[i] >= a[i - 1]);
		}
		else
		{
			a[i] = rand() % ((100 - sum) / (10 - i) - a[i - 1] + 1) + a[i - 1];
			//assert(a[i] >= a[i - 1]);
		}
		sum += a[i];
	}
}

void genAll(vector<int> base, int sum, int num, int min)
{
	if (num == 1)
	{
		base.push_back(sum);
		allStrategy.push_back(base);
		countS += 1;
		if (countS % 100000 == 0)
		{
			/*cout << base.size() << endl;
			for (int i = 0; i < 10; i++)
			{
				cout << base[i] << " ";
			}
			cout << endl;*/
			cout << countS << endl;
		}
		return;
	}
	for (int i = min; i <= sum / num; i++)
	{
		vector<int> tempBase(base);
		tempBase.push_back(i);
		genAll(tempBase, sum - i, num - 1, i);
	}
}

void gen2(int num)
{
	for (int i = 0; i < num; i++)
	{
		Strategy st = { rand() % allStrategy.size() , 0 };
		sampleStrategy.push_back(st);
	}
}

void gen3()
{
	for (int i = 0; i < allStrategy.size(); i++)
	{
		Strategy st = { i, 0, 0 };
		sampleStrategy.push_back(st);
	}
}

bool cmp(Strategy a, Strategy b)
{
	return a.score > b.score;
}

int BigRand()
{
	return RAND_MAX * rand() + rand();
}


void melee()
{
	for (int i = 0; i < sampleStrategy.size(); i++)
	{
		sampleStrategy[i].score = 0;
		sampleStrategy[i].times = 0;
	}
	for (int i = 0; i < sampleStrategy.size(); i++)
	{
		if (i % 10000 == 0)
		{
			cout << i << endl;
		}
		if ((long long)(sampleStrategy.size()) * (long long)(sampleStrategy.size()) > acme)
		{
			struct timeb timeSeed;
			ftime(&timeSeed);
			srand(timeSeed.time * 1000 + timeSeed.millitm);
			int times = acme / (long long)(sampleStrategy.size());
			for (int _i = 0; _i < times; _i++)
			{
				int j = BigRand() % sampleStrategy.size();
				int addA, addB;
				attack(allStrategy[sampleStrategy[i].index], allStrategy[sampleStrategy[j].index], addA, addB);
				sampleStrategy[i].score += addA;
				sampleStrategy[j].score += addB;
				sampleStrategy[i].times++;
				sampleStrategy[j].times++;
			}
		}
		else
		{
			for (int j = i + 1; j < sampleStrategy.size(); j++)
			{
				int addA, addB;
				attack(allStrategy[sampleStrategy[i].index], allStrategy[sampleStrategy[j].index], addA, addB);
				sampleStrategy[i].score += addA;
				sampleStrategy[j].score += addB;
				sampleStrategy[i].times++;
				sampleStrategy[j].times++;
			}
		}
	}
	for (int i = 0; i < sampleStrategy.size(); i++)
	{
		sampleStrategy[i].score = sampleStrategy[i].score / sampleStrategy[i].times;
	}
	cout << "start sort" << endl;
	sort(sampleStrategy.begin(), sampleStrategy.end(), cmp);
	for (int i = 0; i < min(int(sampleStrategy.size()), 10); i++)
	{
		for (int j = 0; j < allStrategy[sampleStrategy[i].index].size(); j++)
		{
			cout << allStrategy[sampleStrategy[i].index][j] << " ";
		}
		cout << endl;
		cout << "score:" << sampleStrategy[i].score << endl;
	}
}


int main()
{
	//srand((unsigned)time(NULL));
	countS = 0;
	genAll(vector<int>(), 100, 10, 0);
	cout << "total size: " << allStrategy.size() << endl;
	//gen2(40000);
	gen3();
	while (sampleStrategy.size() > 2)
	{
		int originSize = sampleStrategy.size();
		cout << "size:" << originSize << endl;
		melee();
		while (sampleStrategy.size() > originSize / 2)
		{
			sampleStrategy.pop_back();
		}
		cout << "******************" << endl;
	}
	
	/*vector<vector<int>> allStrategy(N, vector<int>(10, 0));
	for (auto &s : allStrategy)
	{
		gen(s);
		for (auto &num : s)
		{
			cout << num << " ";
		}
		cout << endl;
	}*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
