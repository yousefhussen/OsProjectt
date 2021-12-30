#include <iostream>
#include <queue>
#include <list>
#include <set>
using namespace std;

//FIRST IN FIRST OUT//
int FIFO(int*, int, int);
int LRU(int*, int, int);
int optimal(int*, int, int);



//MAIN//
int main()
{
	int size;
	cout << "Enter the size of the array" << endl;
	cin >> size;
	int* pages = new int[size];
	cout << "Enter the page string" << endl;
	for (int i = 0; i < size; i++) {
		cin >> pages[i];
	}
	int frames = 5;
	cout << "Enter the number of frames" << endl;
	cin >> frames;
	cout << "page faults=" << optimal(pages, frames,size);
}

//FUNCTIONS//
int FIFO(int* pageString, int frames, int sizeOfString)
{
		//-VARS-//
	set<int> PhysicalMemory;
	queue<int> myQueue;
	int pageFaults = 0; 
		//FUNCTIONALITY//
	for (int counter = 0; counter < 5; counter++) {
		if (PhysicalMemory.size() < frames) {  //CHECK NUMBER OF FRAMES TO ADD WITHOUT SWAPPING//
			if (PhysicalMemory.find(pageString[counter]) == PhysicalMemory.end()) {

				//cout << *c1;
				PhysicalMemory.insert(pageString[counter]);
				pageFaults++;
				myQueue.push(pageString[counter]);
			}
		}
		else {  //IF NOT, SWAP USING FIFO//
			if (PhysicalMemory.find(pageString[counter]) == PhysicalMemory.end()) {
				int temp = myQueue.front();
				myQueue.pop();
				PhysicalMemory.erase(temp);
				PhysicalMemory.insert(pageString[counter]);
				myQueue.push(pageString[counter]);
				pageFaults++;
			}
		}
	}
	return pageFaults;
}

int LRU(int* pageString, int frames, int sizeOfString)
{
	//VARIABLES//
	set<int> PhysicalMemory;
	list<int> mylist;
	int pageFaults = 0;
		//FUNCTIONALITY//
	for (int counter = 0; counter < sizeOfString; counter++) {
		//cout << " abilivle size { " << PhysicalMemory.size()<< "}";
		if (PhysicalMemory.size() < frames) {  //CHECK NUMBER OF FRAMES TO ADD WITHOUT SWAPPING//

			if (PhysicalMemory.find(pageString[counter]) == PhysicalMemory.end()) {

				//cout << " case 1}";
				PhysicalMemory.insert(pageString[counter]);
				pageFaults++;
				mylist.push_back(pageString[counter]);
			}
			else
			{
				//cout << " case 2}";
				mylist.remove(pageString[counter]);
				mylist.push_back(pageString[counter]);
			}
		}
		else {  //IF NOT, SWAP USING LRU//



			if (PhysicalMemory.find(pageString[counter]) == PhysicalMemory.end()) {

				//myVector.pop_back();
				//cout << " case 3}";
				PhysicalMemory.erase(mylist.front());
				mylist.pop_front();

				mylist.push_back(pageString[counter]);
				PhysicalMemory.insert(pageString[counter]);
				//PhysicalMemory.insert(pageString[counter]);
				pageFaults++;
			}
			else
			{

				//cout << " case 4}";
				mylist.remove(pageString[counter]);
				mylist.push_back(pageString[counter]);

			}
		}

		for (list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			cout << "  " << *it;
		cout << "\n";
	}




	return pageFaults;
}


int optimal(int* pageString, int frames, int sizeOfString)
{
		//VARIABLES//
	set<int> PhysicalMemory;
	vector<int> myvector;
	int pageFaults = 0;
		//FUNCTIONALITY//

	for (int counter = 0; counter < sizeOfString; counter++) {
		//cout << " abilivle size { " << PhysicalMemory.size()<< "}";
		int found = -1, far = counter;
		if (PhysicalMemory.size() < frames) {  //CHECK NUMBER OF FRAMES TO ADD WITHOUT SWAPPING//

			if (PhysicalMemory.find(pageString[counter]) == PhysicalMemory.end()) {

				//cout << " case 1}";
				PhysicalMemory.insert(pageString[counter]);
				pageFaults++;
				myvector.push_back(pageString[counter]);
			}

		}
		else {  //IF NOT, SWAP USING optimal//
			int notinstring = 0;
			if (PhysicalMemory.find(pageString[counter]) == PhysicalMemory.end()) {
				for (int i = 0; i < frames; i++) {
					int j;
					for (j = counter; j < sizeOfString; j++)
						if (myvector[i] == pageString[j]) {
							if (j > far) {
								far = j;
								found = i;
							}
							break;
						}
					if (j == sizeOfString) {
						//PhysicalMemory.erase(myvector[i]);
						myvector[i] = pageString[counter];

						PhysicalMemory.insert(pageString[counter]);

						pageFaults++;
						notinstring = 1;
						break;
					}
				}
				if (!notinstring)
					if (found == -1)
					{
						//PhysicalMemory.erase(myvector[0]);
						myvector[0] = pageString[counter];

						PhysicalMemory.insert(pageString[counter]);

						pageFaults++;
					}
					else
					{
						//PhysicalMemory.erase(myvector[res]);
						myvector[found] = pageString[counter];

						PhysicalMemory.insert(pageString[counter]);

						pageFaults++;
					}
			}
		}
	}
	for (int i = 0; i < frames; i++)
		cout << myvector[i] << " ";
	return pageFaults;
}