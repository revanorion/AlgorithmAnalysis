#include <iostream>
#include <vector>
#include <ctime>
#include <thread>

using namespace std;
#define m 10
#define n_f 20000 
#define n_s 1000
#define delta 1000 
//Part of insertion sort
void inline insertion_sort(vector< int > &B) //Insertion sort
{
	for ( int j = 1; j < B.size(); j++)
	{
		int key = B[j];
		int i = j - 1;
		while (i >= 0 && B[i] > key)
		{
			B[i + 1] = B[i];
			i = i - 1;

		}
		B[i + 1] = key;
	}
}
//part of merge sort
void merge(vector<int> &B, int p, int q, int r)
{
	int n_1 = q - p + 1;
	int n_2 = r - q;
	vector<int> L;
	vector<int> R;

		for (int i = 1; i <= n_1; i++)
			L.push_back(B[p + i - 1]);

		for (int j = 1; j <= n_2; j++)
			R.push_back(B[q + j]);
	
	L.push_back( std::numeric_limits<int>::max());
	R.push_back( std::numeric_limits<int>::max());

	int i = 0;
	int j = 0;

	for (int k = p; k <= r; k++)
		if (L[i] <= R[j])
		{
			B[k] = L[i];
			i++;
		}
		else
		{
			B[k] = R[j];
			j++;
		}
}

//part of merge sort
void merge_sort(vector<int> &B, int p, int r)
{
	if (p<r)
	{
		int q = floor((p + r) / 2);
		merge_sort(B, p, q);
		merge_sort(B, q + 1, r);
		merge(B, p, q, r);
	}
}

//part of quicksort
int partition(vector<int> &B, int p, int r)
{
	int x = B[r];
	int i = p - 1;

	for (int j = p; j <= r-1 ; j++)
	{
		if (B[j] <= x)
		{
			i++;
			int temp = B[j];
			B[j] = B[i];
			B[i] = temp;
		}
		
	}
	int temp = B[r];
	B[r] = B[i + 1];
	B[i + 1] = temp;
	return i + 1;
}
//part of quicksort
void quicksort(vector<int> &B, int p, int r)
{
	if (p<r)
	{
		int q = partition(B, p, r);
		quicksort(B, p, q - 1);
		quicksort(B, q + 1, r);
	}
}


template <typename T>
ostream & operator<<(ostream &out, vector<T> org)
{
	for (int j = 0; j < org.size(); j++)
		out << j << ":\t" << org[j] << endl;
	return out;
}


//Part of insertion sort & merge sort
double average(vector<double> time, int elements)
{
	double avg = 0;
	for (int i = 0; i < time.size(); i++)
		avg += time[i];
	return avg /= elements;
}
//Part of insertion sort
void insertCalc(vector<vector<int>>&A)
{
	vector <double> t_avg1;
	for (int n = n_s; n <= n_f; n += delta)
	{
		vector <double> t_alg1;
		for (int i = 0; i <= m - 1; i++)
		{
			vector<int > B(A[i].begin(), A[i].begin() + n);
			clock_t begin = clock();
			//cout <<"Insert: " << i<<"\t"<<n << endl;
			insertion_sort(B);
			clock_t end = clock();
			t_alg1.push_back(end - begin);

		}
		t_avg1.push_back(average(t_alg1, m));
	}
	cout << "insertion sort time:\n" << t_avg1 << endl;

}
//Part of merge sort
void mergeCalc(vector<vector<int>>&A)
{
	vector <double> t_avg2;
	for (int n = n_s; n <= n_f; n += delta)
	{
		vector <double> t_alg2;
		for (int i = 0; i <= m - 1; i++)
		{
			vector<int > B(A[i].begin(), A[i].begin() + n);
			clock_t begin = clock();
			//cout << "Merge: " << i << "\t" << n << endl;
			merge_sort(B, 0, n - 1);
			clock_t end = clock();
			t_alg2.push_back(end - begin);
		}
		t_avg2.push_back(average(t_alg2, m));
	}
	cout << "merge sort time:\n" << t_avg2 << endl;
}
//part of quick sort
void quickCalc(vector<vector<int>>&A)
{
	vector <double> t_avg3;
	for (int n = n_s; n <= n_f; n += delta)
	{
		vector <double> t_alg3;
		for (int i = 0; i <= m - 1; i++)
		{
			vector<int > B(A[i].begin(), A[i].begin() + n);
			clock_t begin = clock();
			//cout << "Quick: " << i << "\t" << n << endl;
			quicksort(B, 0, n - 1);
			clock_t end = clock();
			t_alg3.push_back(end - begin);
		}
		t_avg3.push_back(average(t_alg3, m));
	}
	cout << "Quicksort time:\n" << t_avg3 << endl;
}

int main()
{

	vector< vector<int> > A;
	for (int i = 0; i < m; i++)
	{
		vector<int> row;
		for (int j = 0; j < n_f; j++)
			row.push_back(rand());
		A.push_back(row);
	}

	thread t1(insertCalc, A);

	thread t2(mergeCalc, A);

	thread t3(quickCalc, A);


	t3.join();

	t2.join();

	t1.join();

	


	

	system("pause");
	return 0;
}