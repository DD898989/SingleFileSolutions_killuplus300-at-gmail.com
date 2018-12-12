#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;

int main()
{
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------selection_sort.cpp
int main1()
{
   int array[100], n, c, d, position, swap;

   cout<<"Enter number of elements";
   cin>>n;

   cout<<"Enter integers";

   for ( c = 0 ; c < n ; c++ )
   cin>>array[c];

   for ( c = 0 ; c < ( n - 1 ) ; c++ )
   {
      position = c;

      for ( d = c + 1 ; d < n ; d++ )
      {
         if ( array[position] > array[d] )
            position = d;
      }
      if ( position != c )
      {
         swap = array[c];
         array[c] = array[position];
         array[position] = swap;
      }
   }

   cout<<"Sorted list in ascending order:";

   for ( c = 0 ; c < n ; c++ )
      cout<<array[c];

   return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------binarysearch.cpp

class IterativeBnySear
{
public:
	static vector<int> Search(int* array, int length, int num)
	{
		int left = 0, right = length - 1;
		int middle = (right + left) / 2;
		vector<int> v(2);
		while (left <= right)
		{
			v[0] = middle; v[1] = middle;
			if (array[middle] == num)
				return v; // found

			if (array[middle] > num)
				right = middle - 1;
			else
				left = middle + 1;

			middle = (right + left) / 2;
		}
		v[0] = right; v[1] = left;
		return v;//not found
	}
};

class DivideAndConquer
{
    public:
        static vector<int> Search(int* array, int length, int num)
		{
			return Search(array, num, 0, length - 1);
		}

		static vector<int> Search(int* array, int num, int left, int right)
		{
			vector<int> v(2);

			int middle = (right + left) / 2;

			v[0] = right; v[1] = left;
			if (left > right)
				return v; //not found

			v[0] = middle; v[1] = middle;
			if (array[middle] == num)
				return v; // found

			if (array[middle] > num)
				return Search(array, num, left, middle - 1);

			return Search(array, num, middle + 1, right);
		}
};


int main2()
{   //            0   1   2 3 4 5 6 7  8    //index
	int arr[] = { 1,  3,  5,6,7,8,9,10,11 };//must be sorted array

	vector<int> v;

	v  = IterativeBnySear::Search(arr,9,0);
	cout<<v[0]<<" "<<v[1]<<endl;
	v  = DivideAndConquer::Search(arr,9,0);
	cout<<v[0]<<" "<<v[1]<<endl;

	v  = IterativeBnySear::Search(arr,9,1);
	cout<<v[0]<<" "<<v[1]<<endl;
	v  = DivideAndConquer::Search(arr,9,1);
	cout<<v[0]<<" "<<v[1]<<endl;
	
	v  = IterativeBnySear::Search(arr,9,2);
	cout<<v[0]<<" "<<v[1]<<endl;
	v  = DivideAndConquer::Search(arr,9,2);
	cout<<v[0]<<" "<<v[1]<<endl;
	
	v  = IterativeBnySear::Search(arr,9,3);
	cout<<v[0]<<" "<<v[1]<<endl;
	v  = DivideAndConquer::Search(arr,9,3);
	cout<<v[0]<<" "<<v[1]<<endl;

	v  = IterativeBnySear::Search(arr,9,4);
	cout<<v[0]<<" "<<v[1]<<endl;
	v  = DivideAndConquer::Search(arr,9,4);
	cout<<v[0]<<" "<<v[1]<<endl;
	
	v  = IterativeBnySear::Search(arr,9,11);
	cout<<v[0]<<" "<<v[1]<<endl;
	v  = DivideAndConquer::Search(arr,9,11);
	cout<<v[0]<<" "<<v[1]<<endl;

	v  = IterativeBnySear::Search(arr,9,12);
	cout<<v[0]<<" "<<v[1]<<endl;
	v  = DivideAndConquer::Search(arr,9,12);
	cout<<v[0]<<" "<<v[1]<<endl;


	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------Radix Sort.cpp
// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
	int *output = new int[n];
    int i, count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using 
// Radix Sort
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
 
// A utility function to print an array
void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}
 
// Driver program to test above functions
int main3()
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr)/sizeof(arr[0]);
    radixsort(arr, n);
    print(arr, n);
    return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------quick_sort.cpp
void quickSort(int arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

int main4()
{
    int n,i,left=0;
    cin>>n;
    int right=n;
    int *a = new int[n];

    for(i=0;i<n;i++)
        cin>>a[i];

    quickSort(a,left,right);

    for(i=0;i<n;i++)
        cout<<a[i]<<" ";
	
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------n Queen.cpp
#define N 8
using namespace std;
 
/* print solution */
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout<<board[i][j]<<"  ";
        cout<<endl;
    }
}
 
/* check if a queen can be placed on board[row][col]*/
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
    for (i = 0; i < col; i++)
    {
        if (board[row][i])
            return false;
    }
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
            return false;
    }
 
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j])
            return false;
    }
 
    return true;
}
 
/*solve N Queen problem */
bool solveNQUtil(int board[N][N], int col)
{
    if (col >= N)
        return true;
    for (int i = 0; i < N; i++)
    {
        if ( isSafe(board, i, col) )
        {
            board[i][col] = 1;
            if (solveNQUtil(board, col + 1) == true)
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}
 
/* solves the N Queen problem using Backtracking.*/
bool solveNQ()
{
    int board[N][N] = {0};
    if (solveNQUtil(board, 0) == false)
    {
        cout<<"Solution does not exist"<<endl;
        return false;
    }
    printSolution(board);
    return true;
}
 
// Main
int main5()
{
    solveNQ();
    return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------merge_sort.cpp
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int *L = new int[n1];
    int *R = new int[n1];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        cout<<A[i]<<",";
    cout<<"\n";
}

/* Driver program to test above functions */
int main6()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    cout<<"Given array is "<<"\n";
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    cout<<"\n"<<"Sorted array is" <<"\n";
    printArray(arr, arr_size);
    return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------Insertion Sort.cpp
int main7()
{
    int arr[100],num,temp,j;
    cout << "Enter the number of elements" << endl;
    cin >> num;
    cout << "Enter the elements" << endl;
    for(int i=0;i<num;i++){ // Entering the number
        cin >> arr[i];
    }
    for(int i=1; i<num-1;i++){
        temp = arr[i];
        j = i-1;
        while((temp<arr[j]) && (j>=0)){ // Number of comparison.
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = temp; //Insert at its proper position.
        cout << "Pass " << i << " : "; // Print the number of passes.
            for(int i=0;i<num;i++){
                cout << arr[i] << " "; // Print the array element
            }
        cout << endl;
    }

	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------heapsort.cpp
// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

/* A utility function to print array of size n */
void printArray1(int arr[], int n)
{
    for (int i=0; i<n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Driver program
int main8()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);

    heapSort(arr, n);

    cout << "Sorted array is \n";
    printArray1(arr, n);

	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------Kruskal’s Minimum Spanning Tree Algorithm.cpp
// a structure to represent a weighted edge in graph
struct Edge
{
	int src, dest, weight;
};

// a structure to represent a connected, undirected
// and weighted graph
struct Graph
{
	// V-> Number of vertices, E-> Number of edges
	int V, E;

	// graph is represented as an array of edges.
	// Since the graph is undirected, the edge
	// from src to dest is also edge from dest
	// to src. Both are counted as 1 edge here.
	struct Edge* edge;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;

	graph->edge = new Edge[E];

	return graph;
}

// A structure to represent a subset for union-find
struct subset
{
	int parent;
	int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
	// find root and make root as parent of i
	// (path compression)
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	// Attach smaller rank tree under root of high
	// rank tree (Union by Rank)
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	// If ranks are same, then make one as root and
	// increment its rank by one
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight > b1->weight;
}


void printResult(Edge* result,int E)
{
	ofstream  myfile;
	myfile.open("D:\\MyLog.txt", fstream::app);
	//myfile<<"ID"<<"\t"<<"E"<<"\t"<<"edge"<<"\t"<<"V"<<endl;
	
	myfile<<"----------------------------\n";
	for(int i=0;i<E;i++)
	{
		myfile<<i<<"\t";
		myfile<<result[i].src<<"\t";
		myfile<<result[i].dest<<"\t";
		myfile<<result[i].weight<<"\t";
		

		myfile<<endl;
	}
	myfile.close();
}

void printGraph(struct Graph* graph)                                           //for debug
{
	ofstream  myfile;
	myfile.open("D:\\MyLog.txt", fstream::app);
	//myfile<<"ID"<<"\t"<<"E"<<"\t"<<"edge"<<"\t"<<"V"<<endl;


	//myfile<<graph->E<<"\t";
	//myfile<<graph->V<<"\t";
	//myfile<<endl;
	
	myfile<<"----------------------------\n";
	for(int i=0;i<graph->E;i++)
	{
		myfile<<i<<"\t";
		myfile<<graph->edge->src<<"\t";
		myfile<<graph->edge->dest<<"\t";
		myfile<<graph->edge->weight<<"\t";
		
		graph->edge++;

		myfile<<endl;
	}
	graph->edge-=graph->E;
	myfile.close();
}


// The main function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph)
{
	printGraph(graph);

	int V = graph->V;
	
	Edge* result = new Edge[V];


	int e = 0; // An index variable, used for result[]
	int i = 0; // An index variable, used for sorted edges

	// Step 1: Sort all the edges in non-decreasing
	// order of their weight. If we are not allowed to
	// change the given graph, we can create a copy of
	// array of edges
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
	printGraph(graph);

	// Allocate memory for creating V ssubsets
	struct subset *subsets = (struct subset*) malloc( V * sizeof(struct subset) );

	// Create V subsets with single elements
	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	// Number of edges to be taken is equal to V-1
	while (e < V - 1)
	{
		// Step 2: Pick the smallest edge. And increment
		// the index for next iteration
		struct Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		// If including this edge does't cause cycle,
		// include it in result and increment the index
		// of result for next edge
		if (x != y)
		{
			result[e++] = next_edge;
			printResult(result,e);
			Union(subsets, x, y);
		}
		// Else discard the next_edge
	}

	// print the contents of result[] to display the
	// built MST
	printf("保留以下%d條線,weight sum是...自己加,在==後面\n",e);
	for (i = 0; i < e; ++i)
		printf("%d -- %d == %d\n", result[i].src, result[i].dest,result[i].weight);

	return;
}

// Driver program to test above functions
int main9()
{
	/* Let us create following weighted graph
			10
		0--------1     這橫條是edge[0]
		|  \	 |
	   6|   5\   |15	最左直條是edge[1]   斜條是edge[2]   最右直條是edge[3]
		|	   \ |
		2--------3     這橫條是edge[4]
			4												*/

	int V = 4; // Number of vertices in graph
	int E = 5; // Number of edges in graph
	struct Graph* graph = createGraph(V, E);

	// add edge 0-1
	graph->edge[0].src = 0;		//src是V起點
	graph->edge[0].dest = 1;	//dest是V終點
	graph->edge[0].weight = 10;

	// add edge 0-2
	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 6;

	// add edge 0-3
	graph->edge[2].src = 0;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 5;

	// add edge 1-3
	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 15;

	// add edge 2-3
	graph->edge[4].src = 2;
	graph->edge[4].dest = 3;
	graph->edge[4].weight = 4;

	KruskalMST(graph);

	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------Dijkstra’s shortest path algorithm.cpp
// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
// Initialize min value
int min = INT_MAX, min_index;

for (int v = 0; v < V; v++)
	if (sptSet[v] == false && dist[v] <= min)
		min = dist[v], min_index = v;

return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n)
{
printf("Vertex Distance from Sourcen");
for (int i = 0; i < V; i++)
	printf("%d tt %dn", i, dist[i]);
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
	int dist[V];	 // The output array. dist[i] will hold the shortest
					// distance from src to i

	bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
					// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V-1; count++)
	{
	// Pick the minimum distance vertex from the set of vertices not
	// yet processed. u is always equal to src in first iteration.
	int u = minDistance(dist, sptSet);

	// Mark the picked vertex as processed
	sptSet[u] = true;

	// Update dist value of the adjacent vertices of the picked vertex.
	for (int v = 0; v < V; v++)

		// Update dist[v] only if is not in sptSet, there is an edge from
		// u to v, and total weight of path from src to v through u is
		// smaller than current value of dist[v]
		if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
									&& dist[u]+graph[u][v] < dist[v])
			dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printSolution(dist, V);
}

// driver program to test above function
int main10()
{
/* Let us create the example graph discussed above */
int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
					{4, 0, 8, 0, 0, 0, 0, 11, 0},
					{0, 8, 0, 7, 0, 4, 0, 0, 2},
					{0, 0, 7, 0, 9, 14, 0, 0, 0},
					{0, 0, 0, 9, 0, 10, 0, 0, 0},
					{0, 0, 4, 14, 10, 0, 2, 0, 0},
					{0, 0, 0, 0, 0, 2, 0, 1, 6},
					{8, 11, 0, 0, 0, 0, 1, 0, 7},
					{0, 0, 2, 0, 0, 0, 6, 7, 0}
					};

	dijkstra(graph, 0);

	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------Bucket Sort.cpp
// Function to sort arr[] of size n using bucket sort
void bucketSort(float arr[], int n)
{
    // 1) Create n empty buckets
	vector< vector<float>> b;
	b.resize(n);


    // 2) Put array elements in different buckets
    for (int i=0; i<n; i++)
    {
       int bi = n*arr[i]; // Index in bucket
       b[bi].push_back(arr[i]);
    }
 
    // 3) Sort individual buckets
    for (int i=0; i<n; i++)
       sort(b[i].begin(), b[i].end());
 
    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
          arr[index++] = b[i][j];
}
 
/* Driver program to test above funtion */
int main11()
{
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr)/sizeof(arr[0]);
    bucketSort(arr, n);
 
    cout << "Sorted array is \n";
    for (int i=0; i<n; i++)
       cout << arr[i] << " ";
    return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------bubble_sort.cpp
int main12()
{
    int n,a[100],temp,i,j;
    cout<<"enter the number of elements";
    cin>>n;
    cout<<"enter elements";

    for(i=0;i<n;i++)
        cin>>a[i];

    for(i=0;i<n;i++)
        for(j=0;j<n-1-i;j++)
            if(a[j+1]<a[j])
            {
                temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
            }

    cout<<"the sorted numbers are:";

    for(i=0;i<n;i++)
        cout<<a[i];

	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
