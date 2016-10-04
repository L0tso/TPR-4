#include <iostream>
#include <fstream>
#include <deque>
#include <map>

#define COLUMNS_COUNT 3
#define ROWS_COUNT 4
using namespace std;
void readFile(char* str, deque<int>& coef, deque<deque<char>>& matrix, deque<char>& alphabet)
{
	ifstream readFile(str);
	for (int i = 0; i < COLUMNS_COUNT; i++)
		{
			readFile >> coef[i];
		}

	for (int i = 0; i < ROWS_COUNT; i++)
		readFile >> alphabet[i];
	for (int i = 0; i < ROWS_COUNT; i++)
	{
		matrix[i].resize(COLUMNS_COUNT);
		for (int j = 0; j < COLUMNS_COUNT; j++)
		{
			readFile >> matrix[i][j];
		}
	}
	readFile.close();
	
}
void pluralityVoting(deque<int>& coef, deque<deque<char>>& matrix)
{
	map<char, int> voting;
	for (int i = 0; i < COLUMNS_COUNT;i++)
		voting[matrix[0][i]] += coef[i];
	int max = INT_MIN;
	auto maxIterator = voting.begin();
	for (auto it = voting.begin(); it != voting.end(); ++it)
	{
		if (it->second > max)
		{
			max = it->second;
			maxIterator = it;
		}
	}
	cout << "PluralityVoting  : " << maxIterator->first << endl;
	
}

void Condorcet(deque<int>& coef, deque<deque<char>>& matrix, deque<char>& alphabet)
{
	map<char, int> matrixIndexes;

	// a = 0 b = 1  c = 2 d = 3 
	for (size_t i = 0; i < alphabet.size(); i++)
			matrixIndexes[alphabet[i]] = i;

	int leaderBoard[3][4] = { 0 };
	// nomer table
	for (int i = 0; i < ROWS_COUNT; i++)
		for (size_t j = 0; j < COLUMNS_COUNT; j++)
			leaderBoard[j][matrixIndexes[matrix[i][j]]] = i + 1;

	
	int resultBoard[ROWS_COUNT][ROWS_COUNT] = { 0 };
	//Result table
	for (int i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < ROWS_COUNT; j++)
			for (size_t k = 0; k < ROWS_COUNT; k++)
			{
				if (leaderBoard[i][j] < leaderBoard[i][k]) {
					//cout << leaderBoard[i][j] << "  " << leaderBoard[i][k];
					resultBoard[j][k] += coef[i];
				}
			}
	}
		
	bool res[ROWS_COUNT] = { 0 };
	//find best
	for (size_t i = 0; i < ROWS_COUNT; i++)
	{
		for (size_t j = 0; j < ROWS_COUNT; j++)
		{
			if (resultBoard[i][j] >= resultBoard[j][i])
				res[i] = true;
			else
			{
				res[i] = false;
				break;
			}
		}
	}
	for (size_t i = 0; i < ROWS_COUNT; i++)
		if (res[i] == 1)
			cout<< "Condorcet: "  << alphabet[i]<<endl;
}
void printMatrix(deque<deque<char>>& matrix)
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
			cout << matrix[i][j] << "  ";

		cout << endl;
	}
	cout << endl;
}
void findMinumum(map<char, int> & indexes, deque<deque<char>>& matrix)
{
	char key;
	int max = INT_MIN;
	for (auto i : indexes)
	{
		if (i.second > max)
		{
			max = i.second;
			key = i.first;
		}
		i.second = 0;
	}
	//cout << "key:  " << key << endl;
	for (size_t i = 0; i < matrix.size()-1; i++)
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == key)
			{
				swap(matrix[i][j], matrix[i+1][j]);
				//printMatrix(matrix);
			}
				
		}

	matrix.resize(matrix.size() - 1);
    indexes.erase(key);
}
void alternative(deque<int>& coef, deque<deque<char>>& matrix, deque<char>& alphabet)
{
	deque <char> results(coef.size());

	map<char, int> indexes;

	// a = 0 b = 1  c = 2 d = 3 
	for (size_t i = 0; i < alphabet.size(); i++)
		indexes[alphabet[i]] = 0;

	while (matrix.size() != 1)
	{
		for (size_t i = 0; i < coef.size(); i++)
		{
			indexes[matrix.back()[i]] += coef[i];
		}
		findMinumum(indexes, matrix);
		for (size_t i = 0; i < coef.size(); i++)
		{
			indexes[matrix.front()[i]] = 0;
		}
	}
	
	for (auto i : indexes)
		cout <<"Alternative:  "<< i.first << endl;
}
int main() {
	
	deque<int> coefficient(COLUMNS_COUNT);
	deque<deque<char>> matrix(ROWS_COUNT);
	deque<char> alphabet(ROWS_COUNT);
	readFile("inputs.txt", coefficient, matrix, alphabet);
	//for (int i = 0; i < matrix.size();i++)
	//	for (int j = 0; j < matrix[i].size(); j++)
	//		cout << matrix[i][j];


	pluralityVoting(coefficient, matrix);
	Condorcet(coefficient, matrix, alphabet);
	alternative(coefficient, matrix, alphabet);
	system("pause");
}