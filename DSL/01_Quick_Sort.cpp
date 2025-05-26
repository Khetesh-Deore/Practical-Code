#include <bits/stdc++.h>
using namespace std;
void printArray(vector<int> &arr, int n)
{
	cout << "[" << " ";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "]" << endl;
}
int sort(vector<int> &arr, int low, int high)
{
	int i = low;
	int j = high;
	int pivot = arr[low];
	while (i < j)
	{
		while (arr[i] <= pivot && i <= high)
			i++;
		while (arr[j] > pivot && j >= low)
			j--;
		if (i < j)
		{
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[low], arr[j]);
	printArray(arr, arr.size());
	return j;
};
void Quick_Sort(vector<int> &arr, int low, int high)
{
	if (low < high)
	{
		int partition = sort(arr, low, high);
		Quick_Sort(arr, low, partition - 1);
		Quick_Sort(arr, partition + 1, high);
	}
}

int main()
{
	int n;
	cout << "Enter the No. of Element of array" << endl;
	cin >> n;
	vector<int> arr(n);
	cout << "Enter The element:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	printArray(arr, n);
	Quick_Sort(arr, 0, n - 1);
	printArray(arr, n);
}