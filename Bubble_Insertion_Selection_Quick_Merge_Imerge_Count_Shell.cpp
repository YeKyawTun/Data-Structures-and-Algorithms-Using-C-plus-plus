#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>
//#include <cstdint> //INT32_MAX
using namespace std;

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


void Bubble(int A[], int n)
{
	int i, j; //i=number of passes, j=comparison
	int adaptive_flag = 0; //to verify bubble sort is adaptive or not

	for (i=0; i<n-1; i++) //number of passes
	{
		//initialize adaptive_flag = 0 before starting every pass
		adaptive_flag = 0;

		//compare the consecutive pair of elements
		//why (n-1-i) -> Every pass, one comparison should be reduced. 
		for (j=0; j<n-1-i; j++) 
		{
			if (A[j]>A[j+1])
			{
				swap(&A[j],&A[j+1]);
				adaptive_flag = 1;
			}
		}

		if (adaptive_flag==0) //adaptive_flag==0 mean no swaps done and already is already sorted and so break;
			break;

	}


}

/*Note: Insertion Sort is naturally the adaptive and so we don't need to introduce the flag.
		Insertion Sort is stable.*/
void insertion(int A[], int n)
{
	int i, j, x;

	//for is used for the number of passes.
	//i=1 because at index '0', we have the 1st element and we are assuming that is already sorted
	for (i=1; i<n; i++)
	{
		j = i - 1; //j is to use for swapping and comparison
		x = A[i];  //x is the element that we have taken out from array and compare with the remaining elements to insert at proper place
	
		while (j>-1 && A[j]>x) //j>-1 = stop when j=-1
		{
			A[j+1] = A[j];
			j--;
		}

		A[j+1] = x; //insert x into the proper place

	}
}

/*Note: Minimum number of swaps
		Good for less number of swaps
		Selection Sort is getting the smallest elements while bubble sort is getting the largest one
		Intermediate Results of selection sorts are useful.
*/
void SelectionSort(int A[], int n)
{
	int i,j,k;

	//for is used for the number of passes.
	for (i=0; i<n-1; i++)
	{
		//for is used for the each pass
		for (j=k=i; j<n; j++)
		{
			if (A[j] < A[k])
			{
				k=j;
			}
		}
		swap(&A[i],&A[k]);
	}
}

int partition(int A[], int l, int h)
{
	int pivot = A[l];
	int i=l, j=h;

	do
	{
		//i should continue and find, if it is samller than pivot.
		//i should stop and interchange, if it is greater than pivot.
		do {i++;} while(A[i] <= pivot);

		//j should continue and find, if it greater than pivot.
		//j should stop and interchange, if it is smaller than pivot.
		do {j--;} while(A[j] > pivot);

		if (i<j) swap(&A[i],&A[j]);
	}
	while (i<j);

	swap(&A[l],&A[j]); //A[l] is pivot element
	return j;
}

void QuickSort(int A[], int l, int h)
{
	int j;

	if (l<h)
	{
		j=partition(A,l,h);
		QuickSort(A,l,j);
		QuickSort(A,j+1,h);
	}
}

//Single Array with 2 lists
void Merge(int A[], int l, int mid, int h) 
{
	int i=l, j=mid+1, k=l; //k=l because low can be anywhere in the array
	int B[100];

	while (i<=mid && j<=h)
	{
		if (A[i] < A[j])
			B[k++] = A[i++];
		else 
			B[k++] = A[j++];
	}

	for (; i<=mid; i++)
		B[k++] = A[i];

	for (; j<=h; j++)
		B[k++] = A[j];

	for (i=l; i<=h; i++) //iterate values from low to high
		A[i] = B[i];
}

//Iterative Merge Sort
void IMergeSort(int A[], int n)
{
	int p, l, h, mid, i;

	//for is used for the number of passes.
	for (p=2; p<=n; p=p*2)
	{
		//for is used for the each pass
		for (i=0; i+p-1<n; i=i+p)
		{
			l=i;
			h=i+p-1;
			mid=(l+h)/2;
			cout << "i=" << i << " l=" << l << " h=" << h << " mid=" << mid << endl;
			Merge(A, l, mid, h);
		}
		/*
		if (n-i > p/2)
		{
			l=i;
			h=i+p-1;
			mid=(l+h)/2;
			Merge(A, l, mid, n-1);
		}
		*/
	}

	//for odd number of elements in the list
	//for list size is not in power of 2 (log 8 base 2 and log 9 base 2)
	//for the above, some elements will be left over and need to merge 
	if (p/2 < n) 
	{
		Merge(A,0,p/2-1,n);
		//Merge(A,0,p/2,n-1);
	}
}

//Recursive Merge Sort
void MergeSort(int A[], int l, int h)
{
	int mid;
	//int count=0;

	if (l < h)
	{
		mid=(l+h)/2;
		MergeSort(A,l,mid);
		MergeSort(A,mid+1,h);
		Merge(A,l,mid,h);
	}
}



int findMax(int A[], int n)
{
	int max=INT_MIN;
	cout << "system Max Value=" << max << endl;
	int i;

	for (i=0; i<n; i++)
	{
		if (A[i] > max)
		{
			max = A[i];
		}
	}

	return max;
}


void CountSort(int A[], int n)
{
	int i, j, max, *C;

	max = findMax(A,n);

	cout << "max=" << max << endl;

	C = (int *)malloc(sizeof(int)*(max+1)); //size of C array

	//Initiailze the count array with 0
	for (i=0; i<max+1; i++)
	{
		C[i] = 0;
	}
	//while scan through the arraym, whenever the element is found, increase the elements of count array
	for (i=0; i<n; i++)
	{
		C[A[i]]++;
	}
	//scan throgh both A and C
	i=0; j=0;
	while (j < max+1)
	{
		if (C[j] > 0)
		{
			A[i++] = j;
			C[j]--;
		}
		else 
			j++;
	}
}


void ShellSort(int A[], int n)
{
	int gap, i, j, temp;

	for (gap=n/2; i<n; gap/=2)
	{
		for (i=gap; i<n; i++)
		{
			temp=A[i];
			j=i - gap;
			while (j >= 0 && A[j] > temp)
			{
				A[j+gap] = A[j];
				j = j- gap;
			}
			A[j + gap] = temp;
		}
	}
}


int main()
{
	//int A[]={11,13,7,12,16,9,24,5,10,3};
	//int n=10;
	//int A[]={3,7,9,10}; //Test for adaptive flag
	//int n=4;
	//int A[] = {11,13,7,12,16,9,24,5,10,3,INT32_MAX};
	//int A[] = {11,13,7,12,16,9,24,5,10,3,65566};
	//int n=11;
	//int i=0;
	//int A[]={11,13,7,12,16,9,24,5,10,3},n=10,i;
	//int A[] = {8,3,7,4,9,2,6,5};
	//int n=8;
	//int i;
	int A[]={11,13,7,12,16,9,24,5,10,3},n=10,i;
	
	//Bubble(A,n);
	//insertion(A,n);
	//SelectionSort(A,n);
	//QuickSort(A,0,n-1);
	//MergeSort(A,0,9);
	//IMergeSort(A,n);
	//CountSort(A,n);
	ShellSort(A,n);

	for (i=0; i<n; i++)
		cout << A[i] << " ";
	cout << endl;

	return 0;

}