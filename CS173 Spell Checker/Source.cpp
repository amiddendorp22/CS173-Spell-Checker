#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <tuple>
#include <vector>
#include <cmath>
using namespace std;

bool tupleSort(tuple<string, int> a, tuple<string, int> b)
{
	return get<1>(a) < get<1>(b);
}

bool compStr(string a, string b)
{
	return a < b;
}

int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

int levenshteinDist(string word1, string word2)
{
	vector<vector<int>> table(word2.length() + 5, vector<int>(word1.length() + 5, 0));

	for (int i = 0; i < word2.size() + 1; i++)
	{
		for (int j = 0; j < word1.size() + 1; j++)
		{
			table[i][j] = j;
		}
		table[i][0] = i;
	}

	for (int i = 1; i < word2.length() + 1; i++)
	{
		for (int j = 1; j < word1.length() + 1; j++)
		{
			if (word1[j - 1] == word2[i - 1])
			{
				table[i][j] = table[i - 1][j - 1];
			}
			else
			{
				table[i][j] = 1 + min(table[i][j - 1], table[i - 1][j], table[i - 1][j - 1]);
			}
		}
	}
	return table[word2.length()][word1.length()];
}

bool findWord(string word, vector<string>dict)
{
	int lower = 0;
	int upper = word.length() - 1;
	while (lower <= upper)
	{
		int middle = lower + (upper - 1) / 2;
		int res = -1000;

		if (word == dict.at(middle))
		{
			res = 0;

			if (res == 0)
			{
				return true;
			}
			if (word > dict.at(middle))
			{
				lower = middle + 1;
			}
			else
			{
				upper = middle - 1;
			}
		}
	}
	return false;
}

bool stringIsNumber(string word)
{
	for (int i = 0; i < word.length(); i++)
	{
		if (std::isdigit(word.at(i)))
		{
			//do nothing
		}
		else
		{
			return false;
		}
	}
	return true;
}
int main()
{
	ifstream inputFile;
	inputFile.open("C:\\School\\Winter 2022\\CS 173\\Assignment 1\\mobydick.txt");
	vector<tuple<string, int>> words;
	string line;
	string word = "";
	tuple<string, int> wordItem;

	if (!inputFile.is_open())
	{
		cout << "Error opening corpus..." << endl;
		return -1;
	}
	while (inputFile >> word)
	{
		if (word.at(word.length() - 1) == '?' || word.at(word.length() - 1) == '.' || word.at(word.length() - 1) == '!' || word.at(word.length() - 1) == ',' || word.at(word.length() - 1) == ';' || word.at(word.length() - 1) == '\\' || word.at(word.length() - 1) == '/')
		{
			string originalWord = (word.substr(0, word.length() - 1));
			string punct = (word.substr(word.length() - 1, word.length()));
			transform(originalWord.begin(), originalWord.end(), originalWord.begin(), ::tolower);
			bool found1 = false;
			bool found2 = false;
			for (int j = 0; j < words.size(); j++) //searches the token list for the current word
			{
				if (get<0>(words.at(j)) == originalWord)
				{
					get<1>(words.at(j)) = get<1>(words.at(j)) + 1;
					found1 = true;
				}
				if (get<0>(words.at(j)) == punct)
				{
					get<1>(words.at(j)) = get<1>(words.at(j)) + 1;
					found2 = true;
				}
				if (found1 && found2)
				{
					break;
				}
			}
			if (found1 == false)
			{
				words.push_back(make_tuple(originalWord, 1));
			}
			if (found2 == false)
			{
				words.push_back(make_tuple(punct, 1));
			}
			found1 = false;
			found2 = false;
		}
		else
		{
			bool found = false;
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			for (int k = 0; k < words.size(); k++)
			{
				if (get<0>(words.at(k)) == word)
				{
					get<1>(words.at(k)) = get<1>(words.at(k)) + 1;
					found = true;
					break;
				}
			}
			if (found == false)
			{
				words.push_back(make_tuple(word, 1));
			}
		}
	}

	sort(words.begin(), words.end(), tupleSort);
	inputFile.close();

	for (int i = 0; i < words.size(); i++)
	{
		string word = get<0>(words.at(i));
		for (int j = 0; j < word.length(); j++)
		{
			if ((word.at(j) == '-' || word.at(j) == '.' )&& j == 0)//removes dash and period at beginning of token
			{
				get<0>(words.at(i)) = word.substr(1, word.length());
			}
			else if ((word.at(j) == '-' || word.at(j) == '.') && j == word.length() - 1) //removes dash and period at end of token
			{
				get<0>(words.at(i)) = word.substr(0, word.length() - 1);
			}
			else //removes all other punctuation and special characters
			{
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '!'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '@'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '#'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '$'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '%'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '^'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '&'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '*'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '('), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), ')'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '{'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '}'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '['), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), ']'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '\''), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), ';'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), ':'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), ','), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '.'), get<0>(words.at(i)).end());
				get<0>(words.at(i)).erase(std::remove(get<0>(words.at(i)).begin(), get<0>(words.at(i)).end(), '/'), get<0>(words.at(i)).end());
			}
		}
	}

	ifstream dict;
	dict.open("C:\\School\\Winter 2022\\CS 173\\Assignment 1\\en_US.txt");
	vector<string> dictionary;
	string tempWord;
	string newWord = "";
	while (dict >> tempWord) //initializes the english dictionary
	{
		transform(tempWord.begin(), tempWord.end(), tempWord.begin(), ::tolower);
		for (int i = 0; i < tempWord.length(); i++)
		{
			if (tempWord.at(i) == '/')
			{
				//dictionary.push_back(newWord);
				break;
			}
			else
			{
				newWord += tempWord.at(i);
			}
		}
		dictionary.push_back(newWord);
		newWord = "";
	}
	dict.close();
	vector<vector<string>> possibleMisspell;
	for (int i = 0; i < words.size(); i++) //iterate through the list of word objects
	{
		if (get<1>(words.at(i)) < 11) //if the word we are looking at occurs in the text less than 11 times... (probably not misspelled more than 10 times with <15000 tokens)
		{
 			vector<string> misspelledWord;
			string wrongWord = get<0>(words.at(i));
			if (binary_search(dictionary.begin(), dictionary.end(), wrongWord))
			{

			}
			else if(!stringIsNumber(wrongWord) && wrongWord.length() != 0) //dont correct spelling if it is only a number in the string
			{
				misspelledWord.push_back(wrongWord);

				for (int j = 0; j < dictionary.size(); j++)
				{
					if (abs(int(wrongWord.length() - dictionary.at(j).length())) < 2) //if the words are similar in length...
					{
						if (levenshteinDist(wrongWord, dictionary.at(j)) < 3) //if the words are spelled similarly...
						{
							misspelledWord.push_back(dictionary.at(j)); //offer the dictionary word as a possible correction...
							if (misspelledWord.size() >= 4)
							{
								break; //stops finding new options after finding 3 alternatives
							}
						}
					}
				}
				possibleMisspell.push_back(misspelledWord);
			}
		}
		else
		{
			break;
		}
	}

	ofstream outFile;
	outFile.open("C:\\School\\Winter 2022\\CS 173\\Assignment 1\\outFile.txt");

	if (!outFile.is_open())
	{
		cout << "Error opening output file, only printing to console." << endl << endl;

		for (int i = 0; i < possibleMisspell.size(); i++)
		{
			for (int j = 0; j < possibleMisspell.at(i).size(); j++)
			{
				if (j == 0)
				{
					cout << possibleMisspell.at(i).at(j) << ": ";
				}
				else if (j != possibleMisspell.at(i).at(j).length() - 1)
				{
					cout << possibleMisspell.at(i).at(j) << ", ";
				}
				else
				{
					cout << possibleMisspell.at(i).at(j);
				}
			}
			cout << endl;
		}

	}
	else
	{
		for (int i = 0; i < possibleMisspell.size(); i++)
		{
			for (int j = 0; j < possibleMisspell.at(i).size(); j++)
			{
				if (j == 0)
				{
					cout << possibleMisspell.at(i).at(j) << ": ";
					outFile << possibleMisspell.at(i).at(j) << ": ";
				}
				else if (j != possibleMisspell.at(i).at(j).length() - 1)
				{
					cout << possibleMisspell.at(i).at(j) << ", ";
					outFile << possibleMisspell.at(i).at(j) << ", ";
				}
				else
				{
					cout << possibleMisspell.at(i).at(j);
					outFile << possibleMisspell.at(i).at(j);
				}
			}
			cout << endl;
			outFile << endl;
		}
	}
	outFile.close();
	return 0;
}

// remove brackets and dashes at the beginning of a word, dont include only numbers in words that may be mispelled...