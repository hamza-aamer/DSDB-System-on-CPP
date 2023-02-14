#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include "Node.h"
using namespace std;



int size_of_file(fstream& file)
{
	int count = 0;
	string text;
	while (getline(file, text))
	{
		count++;
	}
	return count;
}

node* insert(fstream& file, int count)
{
	node* a;
	a = new node[count - 1];
	int index = 0;
	bool flag = 0;
	string text;
	string str;
	int part = 0;
	bool flah = 0;
	while (getline(file, text))
	{
		if (flag == 0)
		{
			flag = 1;
			continue;
		}
		else
		{
			for (int i = 0; i < text.length(); i++)
			{

				if (text[i] != ',' && text[i + 1] != '\0')
				{
					if (text[i] == '"')
					{
						for (int j = i + 1; text[j] != '"'; j++)
						{
							str += text[j];
							if (text[j + 1] == '"')
							{
								i = j + 1;
								break;
							}
						}
					}
					else
					{
						str += text[i];
					}
				}
				else
				{
					part++;
					switch (part)
					{
					case 1:
						a[index].id = stoi(str);
						str = "";
						break;
					case 2:
						a[index].year = stoi(str);
						str = "";
						break;
					case 3:
						str = "";
						break;
					case 4:
						a[index].cause = (str);
						str = "";
						
						break;
					case 5:
						a[index].state = (str);
						str = "";
						break;
					case 6:
						a[index].deaths = stoi(str);
						str = "";
						break;
					case 7:
						str += text[i];
						a[index].DR = stof(str);
						str = "";
						break;
					}
				}
			}
		}
		index++;
		str = "";
		part = 0;
		flah = 0;
	}
	return a;
}

