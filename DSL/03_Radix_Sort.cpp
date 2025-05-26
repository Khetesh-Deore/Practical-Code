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
void count_sort(vector<int> &arr, int expo,int n)
{
	
	int cnt[10] = {0};
	vector<int>result(n);
	for (int i = 0; i < n; i++)
	{
		cnt[(arr[i] / expo) % 10]++;
	}
	for(int i=1;i<10;i++){
		cnt[i]+=cnt[i-1];
	}
	for (int i = n-1; i>=0; i--)
	{   int index=(arr[i]/expo)%10;
		result[cnt[index]-1]=arr[i];
		cnt[index]--;
	}
	arr=result;

}
void Radix_sort(vector<int> &arr,int n)
{
	int maxval = *max_element(arr.begin(), arr.end());
	for (int expo = 1; maxval / expo > 0; expo *= 10)
	{
		count_sort(arr, expo,n);
	}
}

int main()
{
	int n;
	cout << "Enter the No. of Element:";
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	Radix_sort(arr,n);
	printArray(arr,arr.size());
}