#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct DATA
{
	int index;
	int year;
	string Cause_name;
	string cause;
	string state;
	int deaths;
	float death_rate;


	DATA(int i = 0, int y = 0, string cn = "", string c = "", string s = "", int d = 0, float dr = 0.00)
	{
		index = i;
		year = y;
		Cause_name = cn;
		cause = c;
		state = s;
		deaths = d;
		death_rate = dr;
	}

	void display()
	{
		cout << "*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		cout << "Index : " << index << endl;
		cout << "Year : " << year << endl;
		cout << "113 Cause Name : " << Cause_name << endl;
		cout << "Cause : " << cause << endl;
		cout << "State : " << state << endl;
		cout << "Deaths : " << deaths << endl;
		cout << "Death Rate : " << death_rate << endl;
		cout << "*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	}
};

void write_to_file(fstream& file, DATA* arr, int len)
{

	for (int i = 0; i < len; i++)
	{
		file << arr[i].index << "," << arr[i].year << "," << arr[i].cause << "," << arr[i].cause << "," << arr[i].state << "," << arr[i].deaths << "," << arr[i].death_rate << "\n";
	}
}

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

DATA* insert(fstream& file, int count)
{
	DATA* a;
	a = new DATA[count - 1];
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
						a[index].index = stoi(str);
						str = "";
						break;
					case 2:
						a[index].year = stoi(str);
						str = "";
						break;
					case 3:
						a[index].Cause_name = (str);
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
						a[index].death_rate = stof(str);
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

int main()
{

	vector<DATA*> arr;

	fstream file1("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
	int count1 = size_of_file(file1);
	file1.close();

	fstream file2("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
	DATA* F1 = insert(file2, count1);
	count1--;
	file2.close();

	fstream file3("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_2.csv");
	int count2 = size_of_file(file3);
	file3.close();

	fstream file4("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_2.csv");
	DATA* F2 = insert(file4, count2);
	count2--;
	file4.close();

	fstream file5("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_3.csv");
	int count3 = size_of_file(file5);
	file5.close();

	fstream file6("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_3.csv");
	DATA* F3 = insert(file6, count3);
	count3--;
	file6.close();

	fstream file7("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_4.csv");
	int count4 = size_of_file(file7);
	file7.close();

	fstream file8("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_4.csv");
	DATA* F4 = insert(file8, count4);
	count4--;
	file8.close();

	fstream file9("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_5.csv");
	int count5 = size_of_file(file9);
	file9.close();

	fstream file10("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_5.csv");
	DATA* F5 = insert(file10, count5);
	count5--;
	file10.close();

	fstream file11("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_6.csv");
	int count6 = size_of_file(file11);
	file11.close();

	fstream file12("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_6.csv");
	DATA* F6 = insert(file12, count6);
	count6--;
	file12.close();


	fstream file13("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_7.csv");
	int count7 = size_of_file(file13);
	file13.close();

	fstream file14("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_7.csv");
	DATA* F7 = insert(file14, count7);
	count7--;
	file14.close();

	fstream file15("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_8.csv");
	int count8 = size_of_file(file15);
	file15.close();

	fstream file16("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_8.csv");
	DATA* F8 = insert(file16, count8);
	count8--;
	file16.close();

	fstream file17("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_9.csv");
	int count9 = size_of_file(file17);
	file17.close();

	fstream file18("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_9.csv");
	DATA* F9 = insert(file18, count9);
	count9--;
	file18.close();

	fstream file19("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_10.csv");
	int count10 = size_of_file(file19);
	file19.close();

	fstream file20("C:\\Users\\maraf\\source\\repos\\Project\\Project\\Files\\NCHS_-_Leading_Causes_of_Death__United_States_10.csv");
	DATA* F10 = insert(file20, count10);
	count10--;
	file20.close();

	fstream file33("C:\\Users\\maraf\\source\\repos\\Project\\Project\\FilesANS.csv", 'w');


	file33 << "ID" << ',' << "Year" << "," << "\n";

	write_to_file(file33, F1, count1);
	write_to_file(file33, F2, count2);
	write_to_file(file33, F3, count3);
	write_to_file(file33, F4, count4);
	write_to_file(file33, F5, count5);
	write_to_file(file33, F6, count6);
	write_to_file(file33, F7, count7);
	write_to_file(file33, F8, count8);
	write_to_file(file33, F9, count9);
	write_to_file(file33, F10, count10);

}
