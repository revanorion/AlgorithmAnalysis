#include <iostream>
#include <vector>
using namespace std;
#define m 10
#define n_f 20000 
#define n_s 1000
#define delta 1000 

void Alg1(vector< int > &B) //Insertion sort
{
	for (int j = 1; j < B.size(); j++)
	{
		int key = B[j];
		if (key == 28)
			cout << "";

		int i = j - 1;
		while (i >= 0 && B[i] > key)
		{
			B[i + 1] = B[i];
			i = i - 1;

		}
		B[i + 1] = key;
	}
}

void merge(vector<int> &B, int p, int q, int r)
{
	int n_1 = q - p + 1;
	int n_2 = r - q;

	vector<int> L;
	vector<int> R;
	try {
		for (int i = 1; i <= n_1; i++)
			L.push_back(B[p + i - 1]);

		for (int j = 1; j <= n_1; j++)
			R.push_back(B[q + j]);
	}
	catch (exception& e)
	{
		cout << e.what();
	}

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




void Alg2()
{



}
void Alg3()
{



}

ostream & operator<<(ostream &out, vector<int> org)
{
	
	for (int j = 0; j < org.size(); j++)
	{
		cout<<j << ":\t" << org[j] << endl;
	}
	return out;
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
	//vector <int> t_avg1;
	//for (int n = n_s; n <= n_f; n += delta)
	//{
	//	vector <int > t_alg1;
	//	for (int i = 0; i <= m-1; i++)
	//	{
	//		vector<int > B(A[i].begin(),A[i].begin()+n);
	//		//int t_1 = time_t();
	//		//system("cls");
	//		//cout << B<< endl;
	//		cout << i << "," << n << endl;
	//		Alg1(B);
	//		//cout << B;
	//		//int t_2 = time_t();
	//		//t_alg1.push_back(t_2 - t_1);
	//	}
	//	//t_avg1.push_back(t_alg1[n]);
	//}


	vector <int> t_avg2;
	for (int n = n_s; n <= n_f; n += delta)
	{
		vector <int > t_alg1;
		for (int i = 0; i <= m - 1; i++)
		{
			vector<int > B(A[i].begin(), A[i].begin() + n);
			//int t_1 = time_t();
			system("cls");
			cout << i << "," << n << endl;
			cout << B<< endl;			
			merge_sort(B,0,n);
			cout << B;
			//int t_2 = time_t();
			//t_alg1.push_back(t_2 - t_1);
		}
		//t_avg1.push_back(t_alg1[n]);
	}






	return 0;
}