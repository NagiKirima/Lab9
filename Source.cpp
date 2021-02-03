#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
string Delete_Spaces(string current_row)
{
	//”даление двойных пробелов в строке
	while (current_row.find("  ") != -1)
	{
		current_row.replace(current_row.find("  "), 2, " ");
	}
	//удаление пробела в начала строки
	if (current_row[0] == ' ')
	{
		current_row.erase(0, 1);
	}
	//удаление пробела в конце строки
	else if (current_row[current_row.length() - 1] == ' ')
	{
		current_row.erase(current_row.length() - 1, 1);
	}
	return current_row;//возвращение строки с одинарными пробелами
}
vector<string> Split_Row_To_Words(string row)
{
	row = Delete_Spaces(row);
	vector<int> pos;
	int words = 0;
	//считаем кол-во слов, их на 1 больше, чем пробелов
	for (int i = 0; i < row.length(); i++)
	{
		if (row[i] == ' ')
		{
			words++;
			pos.push_back(i);
		}
	}
	words++;
	pos.push_back(row.length());//добавление нуль-терминатора за пробел
	vector<string> result;
	int StartPos = 0;
	int SpacePos = 0;
	for (int i = 0; i < words; i++)
	{
		int SpacePos = pos[i];
		string tmp;
		for (int j = StartPos; j < SpacePos; j++)
		{
			tmp.push_back(row[j]);
		}
		result.push_back(tmp);
		tmp = "";
		StartPos = SpacePos + 1;
	}
	return result;
}

bool Check_Doubles(vector<string> arr)
{
	for (int i = 0; i < arr.size() - 1; i++)
	{
		for (int j = i + 1; j < arr.size(); j++)
		{
			if (arr[i] == arr[j])
			{
				return true;
			}
		}
	}
	return false;
}

int GetCount(string& row) 
{
	int count = 0;
	for (int i = 0; i < row.length(); i++) 
	{
		switch (row[i]) 
		{
			case 'a': case 'A': case 'e': case 'E': 
			case 'i': case 'I': case 'o': case 'O':
			case 'u': case 'U': case 'y': case 'Y': 
				count++;
		}
	}
	return count;
}
int main()
{
	setlocale(LC_ALL, "ru");
	ifstream inputF1("F1.txt");
	string Last_Row;
	if (inputF1.is_open()) //проверка на открытие файла
	{
		ofstream outputF2("F2.txt");
		while (!inputF1.eof())
		{
			string CurrentRow;
			vector <string> WordsArray; //указатель на массив слов в текущей строке
			getline(inputF1, CurrentRow); //считывание текущей строки
			WordsArray = Split_Row_To_Words(CurrentRow);
			if (Check_Doubles(WordsArray))
			{
				outputF2 << CurrentRow << endl;
				Last_Row = CurrentRow;
			}
			//cout << "---" << endl; //проверка цикла
		}
		outputF2.close();
	}
	else
	{
		cout << "‘айл F1 не открылс€! ќшибка!\n";
		inputF1.close();
	}
	inputF1.close();
	//¬ывод количества гласных букв в последней строке файла F2!
	cout << "¬ последней строке файла F2 " << GetCount(Last_Row) << " гласных букв!\n";

}