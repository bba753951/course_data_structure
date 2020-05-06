#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int findMed(int *arr, int front, int end){
    int pivot;
    int med = (front+end)/2;
    if(arr[front] > arr[end]){
        if(arr[med] > arr[end])
            pivot = med;
        else
            pivot = end;

    }else{
        if(arr[med] > arr[front])
            pivot = med;
        else
            pivot = front;

    }
    // std::cout << arr[front] << " "<<arr[med]<< " "<<arr[end] << std::endl;
    return pivot;
}
void PrintArray(int *arr, int size){
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
void quickSort(int *arr, int left, int right)
{ 
	int pivot, i, j,med,aa;
	if (left < right) {

        //------median--------
        // med=findMed(arr, left, right);
        // swap(&arr[left], &arr[med]);

        //------leftmost-----
		i = left;  j = right+1;
		pivot = arr[left];

        //------rightmost-----
		// i = left-1;  j = right;
		// pivot = a[right];
        // PrintArray(arr, right);




		do { 
            

			do  i++; while(arr[i] && arr[i] < pivot);
			do  j--; while(arr[j] && arr[j] > pivot);
			if (i< j)  swap(&arr[i], &arr[j]);
		} while (i < j);

        // ------leftmost-----
		swap( &arr[left], &arr[j]);
        // original
		// quickSort(arr, left, j-1);
		// quickSort(arr, j+1, right);

        // longer first.shorter first
        if(j-1-left < right -j -1){
            quickSort(arr, left, j-1);
		    quickSort(arr, j+1, right);

        }else{
            quickSort(arr, j+1, right);
            quickSort(arr, left, j-1);
        }


        //------rightmost-----
		// swap( &a[right], &a[i]);
		// quickSort(a, left, i-1);
		// quickSort(a, i+1, right);
	}
}

int main(){
    // int n = 9;
    // int arr[] = {9, 4, 1, 6, 7, 3, 8, 2, 5};

    // PrintArray(arr, n);

    // quickSort(arr, 0, n-1);

    // std::cout << "sorted:\n";
    // PrintArray(arr, n);



    std::vector<int> v;
     
    std::ifstream infile;
    clock_t start, end;
    double cpu_time_used;
     
    infile.open("test data.txt");
     
    int tmp;
    while(!infile.eof())
    {
        infile>>tmp;
        v.push_back(tmp);
    }

     
    infile.close();
    int n = v.size();
    int *arr=NULL;

    arr = (int *) malloc ( sizeof(int) * v.size()); 
    for(int i=0;i<v.size();i++ ){
        arr[i]=v[i];
    }


    // std::cout << "original:\n";
    // PrintArray(arr, n);
    start = clock();
    quickSort(arr, 0, n-1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // std::cout<<"use leftmost and longer fist execution time = "<< cpu_time_used << std::endl;
    // std::cout<<"use leftmost and original execution time = "<< cpu_time_used << std::endl;
    std::cout<<"use leftmost and shorter fist execution time = "<< cpu_time_used << std::endl;
    // std::cout<<"use median of three and longer fist execution time = "<< cpu_time_used << std::endl;
    // std::cout<<"use median of three and original execution time = "<< cpu_time_used << std::endl;
    // std::cout<<"use median of three and shorter fist execution time = "<< cpu_time_used << std::endl;

    // // std::cout << "sorted:\n";
    // PrintArray(arr, n);
    free(arr);
    return 0;
}