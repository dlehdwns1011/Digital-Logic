#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>

using namespace std;
vector<char*> *v; //all of m and d
vector<char*> minterm; //all of minterm
vector<char*> Pls;  //all of prime implicant
int len; //lenght of input bits
int **for_pls;

int calculate_cost(char* l)
{//calculate cost of n-bits num function
	int result = 0;	int inv = 0; int count = 0;
	for (int j = 0; j < len; j++)
	{//counting 0 and -
		if (l[j] == '0')
			inv++;
		if (l[j] != '-')
			count++;
	}
	//calculation
	result += 2 * count + 2; //n-input AND gate
	result += 2 * inv; //Inverter
	return result;
}

int calculate_cost(vector<char*> l)
{//calculate cost of Boolean Expression function
	int result = 0;
	bool *check = new bool[len]();
	for (int i = 0; i < (int)l.size(); i++)
	{
		int count = 0;
		for (int j = 0; j < sizeof(l[i]) ; j++)
		{//counting 0 and -
			if (l[i][j] != '-')
				count++;
			if (l[i][j] == '0')
				check[j] = true;
		}
		result += 2 * count + 2; //n-input AND gate
	}
	result += 2 * l.size() + 2; //n-input OR gate
	for (int i = 0; i < len; i++)
		if (check[i] == true)
			result += 2; //Inverter
	return result;
}

vector<char*> find_set()
{//Find Minimal Set function
	vector<char*> result;
	bool *check_minterm = new bool[minterm.size()]();
	int **table;	//Declare Each Value
	table = new int*[minterm.size()];
	for (int i = 0; i < (int)minterm.size(); i++)
		table[i] = new int[Pls.size()]();
	
	for (int i = 0; i < (int)minterm.size(); i++)
	{//setting table X : True Minterms / Y : Pls
		for (int j = 0; j < (int)Pls.size(); j++)
		{
			int count = 0;
			for (int h = 0; h < len; h++)
			{
				if (minterm[i][h] != Pls[j][h] && Pls[j][h] != '-')
				{
					count = 1;
					break;
				}
			}
			if (count == 0)
				table[i][j] = 1;
		}
	}
	for (int i = 0; i < (int)minterm.size(); i++)
	{//Identify Essential Pls
		int count = 0; int h = 0;
		for (int j = 0; j < (int)Pls.size(); j++)
		{
			if (table[i][j] == 1)
			{
				h = j;
				count++;
			}
		}
		if (count == 1)
		{//Delete all columns covered by the Essential Pls
			if(check_minterm[i] == false)
				result.push_back(Pls[h]);
			for (int n = 0; n < (int)minterm.size(); n++)
			{
				if (table[n][h] == 1)
					check_minterm[n] = true;
			}
		}
	}
	bool *temp = new bool[Pls.size()]();
	for (int i = 0; i < (int)minterm.size(); i++)
	{//Find the minimum set of Pls that covers the remaining columns
	// and Cover case of No essential Pl
		if (check_minterm[i] == false)
		{
			int min = -1;
			int min_cost = INT_MAX;
			//Regional Optimization is Global Optimization
			for (int j = 0; j < (int)Pls.size(); j++)
			{
				if (table[i][j] == 1)
				{
					if (min_cost >= calculate_cost(Pls[j]))
						min = j;
				}
			}
			if (min != -1 && temp[min] == false)
			{
				result.push_back(Pls[min]);
				temp[min] = true;
			}
		}
	}
	return result;
}

vector<char*> combine(int i,int j)
{//Making Implicant Table and Combining variables function
	vector<char*> result;
	char *com,*com2; //Declare Each value
	for (int a = 0; a < (int)v[i].size(); a++)
	{
		com = v[i][a];
		for (int b = 0; b < (int)v[j].size(); b++)
		{//comparing
			com2 = v[j][b];
			int count = 0;
			for (int c = 0; c < len; c++)
			{
				if (com[c] != com2[c])
					count++;
			}
			if (count == 1)
			{//if Find two elements in adjacent groups with Hamming distance 1
				for_pls[i][a] = 1;
				for_pls[j][b] = 1;
				char* insert = new char[len];
				for (int c = 0; c < len; c++)
				{
					if (com[c] != com2[c]) insert[c] = '-';
					else insert[c] = com[c];
				}
				insert[len] = '\0';
				result.push_back(insert);
			}
		}
	}
	if (result.size() >= 2)
	{//Remove duplicate values
		for (int i = 0; i < (int)result.size()-1; i++)
		{
			if (!strcmp(result[i],result[i + 1]))
			{
				char* temp = result[i + 1];
				result[i + 1] = result[result.size() - 1];
				result[result.size() - 1] = temp;
				result.pop_back();
			}
		}
	}

	return result;
}

int main()
{
	ifstream fin; //file read
	ofstream fout;//file write

	fin.open("input_minterm.txt");//file open to reading
	if (fin.fail())
	{//if not exist text file -> error
		cout << "Can not read text file" << endl;
		return 1;
	}
	char num[10];
	fin.getline(num, 10); //get input bit length
	len = atoi(num);
	
	v = new vector<char*>[len+1];
	
	char line[100];
	while (fin.getline(line, 100))
	{//get line by line
		char *t = new char[2];	char *t2 = new char[len];
		strcpy(t,strtok(line, " "));
		strcpy(t2,strtok(NULL, "\n"));
		if (!strcmp(t, "m")) minterm.push_back(t2); //if minterm
		int count = 0;
		for (int i = 0; i < len; i++)
		{//deviding values using count of 1
			if (t2[i] == '1')
				count++;
		}
		v[count].push_back(t2);
	}
	int count = len;
	int count2 = 0;
	for_pls = new int*[count + 1];
	
	while(count > 0)
	{//Loop until all columns have been completed
		count2 = 0;
		for (int i = 0; i < count + 1; i++)
			for_pls[i] = new int[v[i].size()];		
		for (int i = 0; i < count; i++)
		{//call combine function and make new vector will be used next column
			vector<char*> check = combine(i, i + 1);
			for (int j = 0; j < (int)v[i].size(); j++)
			{
				if (for_pls[i][j] != 1)
					Pls.push_back(v[i][j]);
			}
			if (check.size() != 0)
			{
				v[count2] = check;
				count2++;
			}
		}
		for (int j = 0; j < (int)v[count].size(); j++)
		{
			if (for_pls[count - 1][j] != 1)
				Pls.push_back(v[count][j]);
		}
		
		for (int i = 0; i < count + 1; i++)
			delete[] for_pls[i];
		count = count2-1;
	}
	delete[] for_pls;
	//print result
	cout << "Pls" << endl;
	for (int i = 0; i < (int)Pls.size(); i++)
		cout << Pls[i]<<endl;
	cout << "minterms" << endl;
	for (int i = 0; i < (int)minterm.size(); i++)
		cout << minterm[i] << endl;
	//file open to writing
	fout.open("result.txt", ios::trunc);

	vector<char*> result = find_set();
	cout << endl << "--Result--" << endl;
	for (int i = 0; i < (int)result.size(); i++)
	{
		cout << result[i] << endl;
		fout << result[i] << endl;
	}
	//calculation cost of result
	cout << endl << "Cost(# of transistors): "<< calculate_cost(result);
	fout << endl << "Cost(# of transistors): " << calculate_cost(result);
	
	delete[] v;
	fin.close();
	fout.close(); //delete
	return 0;
}