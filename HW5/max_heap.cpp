#include <iostream>
#include <vector>

void swap(int &p1, int &p2){
    int temp = p1;
    p1 = p2;
    p2 = temp;
}

void MaxHeapify(std::vector<int> &array, int root, int length){

    int left = 2*root,      // 取得left child
    right = 2*root + 1,     // 取得right child
    largest;                // largest用來記錄包含root與child, 三者之中Key最大的node

    if (left <= length && array[left] > array[root])
        largest = left;
    else
        largest = root;

    if (right <= length && array[right] > array[largest])
        largest = right;

    if (largest != root) {                         // 如果目前root的Key不是三者中的最大
        swap(array[largest], array[root]);         // 就調換root與三者中Key最大的node之位置
        MaxHeapify(array, largest, length);        // 調整新的subtree成Max Heap
    }
}

void BuildMaxHeap(std::vector<int> &array){

    for (int i = (int)array.size()/2; i >= 1 ; i--) {
        MaxHeapify(array, i, (int)array.size() - 1);   
    }
}

int HeapSort(std::vector<int> &array,int people){

    int sum=0;

    array.insert(array.begin(), 0);                     // 將index(0)閒置

    BuildMaxHeap(array);                                // 將array調整成Max Heap

    int size = (int)array.size() -1;                    // size用來記錄「目前要處理的矩陣」之長度
    for (int i = 0; i < people; i++) {
        sum+=array[1]--;
        MaxHeapify(array, 1, size);
    }

    array.erase(array.begin());                         // 將index(0)刪除
    return sum;

}


int main() {

    int case_num=0,rows=0,people=0,seats=0;
    std::vector<int> array;
    std::cout << "Input:" << std::endl;
    std::cin >> case_num;
    int *answer = new int[case_num];
    for(int j = 0; j < case_num;j++){
        std::cin >> rows;
        std::cin >> people;

        array.resize(rows);
        for(int i = 0 ;i < rows; i++){
            std::cin >> seats;
            array[i]=seats;
        };
        answer[j]=HeapSort(array,people);
    }
    std::cout << std::endl;
    std::cout << "output:" << std::endl;
    for(int j = 0; j < case_num;j++){
        std::cout << answer[j] << std::endl;
    }
    delete [] answer;
    


    return 0;
}
