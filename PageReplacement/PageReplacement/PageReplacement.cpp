// Final_Os.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;
void fifo(int number_of_pages, int page_number[], int frame_number[], int number_frames)
{
	int page_falt = 0;
	int hit = 0;
	int j = 0;
	for (int i = 0; i < number_frames; i++)
	{
		frame_number[i] = -1;
	}
	for (int i = 0; i < number_of_pages; i++)
	{
		cout << "page number [" << i << "]";
		int flag = 0;
		for (int k = 0; k < number_frames; k++)
			if (frame_number[k] == page_number[i])
			{
				flag = 1;
				hit++;
				for (int k = 0; k < number_frames; k++)

					cout << frame_number[k] << " ";
			}
		if (flag == 0)
		{
			frame_number[j] = page_number[i];
			j = (j + 1) % number_frames;
			page_falt++;
			for (int k = 0; k < number_frames; k++)
			{
				cout << " ";
				cout << frame_number[k];
			}
		}
		cout << endl;
	}
	cout << "*******************************************" << endl;
	cout << " Page Fault Is " << page_falt << endl;
	cout << " the hit number " << hit << endl;

}
//////////////////////////////////////////////////////////////////////////////////////////////////
bool check(vector<int> &frame_array, int key)
{
	for (int i = 0; i < frame_array.size(); i++)
		if (frame_array[i] == key)
			return true;
	return false;

}
int future(int page_array[], vector<int> &frame_array, int page_number, int ind)
{

	int furthest_index = ind, reverse = -1;
	for (int i = 0; i < frame_array.size(); i++)
	{
		int j;
		for (j = ind; j < page_number; j++)
		{
			if (frame_array[i] == page_array[j])
			{
				if (j > furthest_index)
				{
					furthest_index = j;
					reverse = i;
				}
				break;
			}
		}
		if (j == page_number)
			reverse = i;
	}
	return (reverse == -1) ? 0 : reverse;
}
void optimal(int page_array[], int page_number, int frame_number)
{
	vector<int>frame_array;
	int hits = 0;
	for (int i = 0; i < page_number; i++)
	{
		cout << "page number [" << i << "]";

		if (check(frame_array, page_array[i]))
		{
			hits++;
			for (int i = 0; i < frame_array.size(); i++)
			{
				cout << frame_array[i] << " ";
			}
			cout << endl;
			continue;
		}
		if (frame_array.size() < frame_number)
		{
			frame_array.push_back(page_array[i]);
			for (int i = 0; i < frame_array.size(); i++)
			{
				cout << frame_array[i] << " ";
			}
			cout << endl;
		}

		else
		{
			int victim = future(page_array, frame_array, page_number, i + 1);
			frame_array[victim] = page_array[i];
			for (int i = 0; i < frame_array.size(); i++)
			{
				cout << frame_array[i] << " ";
			}
			cout << endl;
		}
	}
	int page_fault = page_number - hits;
	cout << "number of hits equal : " << hits << endl;
	cout << "number of page fault equal :" << page_fault << endl;
}
////////////////////////////////////////////////////////////////////////////////// 
int victim(int virtual_frame[], int n)
{
	int i, minimum = virtual_frame[0], pos = 0;

	for (i = 1; i < n; ++i) {
		if (virtual_frame[i] < minimum) {
			minimum = virtual_frame[i];
			pos = i;
		}
	}
	return pos;
}
void lru(int number_frames, int number_pages, int frame_array[], int page_array[])
{
	int counter = 0;
	int page_fault = 0;
	int hits = 0;
	int *virtual_frame;
	virtual_frame = new int[number_frames];
	for (int i = 0; i < number_frames; ++i)
	{
		frame_array[i] = -1;
	}

	for (int i = 0; i < number_pages; ++i)
	{

		int condtion1, condtion2;
		condtion1 = condtion2 = 0;
		for (int j = 0; j < number_frames; ++j)
		{

			if (frame_array[j] == page_array[i])
			{
				hits++;
				counter++;
				virtual_frame[j] = counter;
				condtion1 = condtion2 = 1;
				break;
			}
		}

		if (condtion1 == 0) {
			for (int j = 0; j < number_frames; ++j)
			{
				if (frame_array[j] == -1)
				{
					counter++;
					page_fault++;
					frame_array[j] = page_array[i];
					virtual_frame[j] = counter;
					condtion2 = 1;
					break;
				}
			}
		}

		if (condtion2 == 0)
		{
			int	postion = victim(virtual_frame, number_frames);
			counter++;
			page_fault++;
			frame_array[postion] = page_array[i];
			virtual_frame[postion] = counter;
		}

		cout << endl;
		cout << "page number [" << i << "]";
		for (int j = 0; j < number_frames; ++j)
		{
			cout << frame_array[j] << " ";
		}
	}
	cout << endl;
	cout << "number of hits equal : " << hits << endl;
	cout << "number of page fault equal :" << page_fault << endl;
}
int main()
{
	int stoping_condtion;
	do
	{
		char choice;
		cout << "choose one of the algorithms" << endl;
		cout << " f --> for FIFO" << endl;
		cout << " o --> for opitmal" << endl;
		cout << " l --> for lru" << endl;
		cin >> choice;
		cout << "*******************************************" << endl;
		int  number_of_pages, *frame_number, number_frames;
		int * page_number;
		cout << " ENTER THE NUMBER OF PAGES:" << endl;
		cin >> number_of_pages;
		cout << " ENTER THE PAGE NUMBER :" << endl;
		page_number = new int[number_of_pages];
		for (int i = 0; i < number_of_pages; i++)
		{
			cin >> page_number[i];

		}
		cout << " ENTER THE NUMBER OF FRAMES :" << endl;
		cin >> number_frames;
		frame_number = new int[number_frames];
		if (choice == 'f' || choice == 'F')
		{
			fifo(number_of_pages, page_number, frame_number, number_frames);
		}
		else if (choice == 'o' || choice == 'O')
		{
			optimal(page_number, number_of_pages, number_frames);
		}
		else if (choice == 'l' || choice == 'L')
		{
			lru(number_frames, number_of_pages, frame_number, page_number);
		}
		cout << "***************************************************" << endl;
		cout << "if yo want to choose another algorithm press 1" << endl;
		cout << "if yo want to stop press -1" << endl;
		cin >> stoping_condtion;
	} while (stoping_condtion != -1);
}


