Data Structure Assignment 5
===
###### tags:`Data Structure`
[TOC]

# Monk And Champions League
use max heap

## MaxHeapify
- Max Heap規則:
所有父node都比子node大


- 使用array表達heap
只要讓array中==index(0)的位置閒置==，從index(1)開始存放資料

方法：
1. 找到這三者(root ,leftchild,rightchild)的最大值，並以int largest==記錄該最大值的index==
2. ==將index(root)與index(largest)這兩個node互換==位置，如此一來，當前的subtree必定能滿足Max Heap規則
3. ==繼續以index(largest)當作新的subtree的root==，檢查新的subtree是否符合Max Heap規則(因為調整後，可能影響下面，所以繼續往下檢查)

變數說明：
- array：記錄heap的矩陣。
- root：當前的subtree之root的index。
- ==length==：這是「==目前要處理的矩陣==」的長度，同時也用來判斷- child是否超過矩陣長度。

```cpp=
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
```
## BuildMaxHeap
只要對所有「==具有child的node==」(index(1) 到index(N/2)的node)檢查一次MaxHeapify()，便能夠把一個任意矩陣調整成Max Heap
```cpp=
void BuildMaxHeap(std::vector<int> &array){

    for (int i = (int)array.size()/2; i >= 1 ; i--) {
        MaxHeapify(array, i, (int)array.size() - 1);     // length要減一, 因為heap從1開始存放資料
    }
}
```


## HeapSort
利用heap sort改良

1. 因為第一個node肯定是最大值，因此可以先取出加入sum
2. 接下來把第一個node減1代表票被買走，空位變少，所以價錢變低
3. 對改變後的第一個node做MaxHeapify調整，確保第一個heap肯定最大值
4. 不停重複，直到所有people都買完票為止
```cpp=
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
```
# Height Union

## collapsingFind/Find
1. 第一個for回圈用來得到root
2. 第二個while做collasping
```cpp=
int collapsingFind(std::vector<int> &subset, int i){      

    int root,count=0;  
    for (root = i; subset[root] >= 0; root = subset[root]);  // 找到root

    while (i != root) {             // 進行collapsing
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    };

    return root;
}
```
Find程式基本上和collapsingFind差不多，只是為了計算次數，回傳值不同

## heightUnion 
1. 先對x,y分別做collapsingFind,找出他們的root
2. 判斷他們root對應的值，負越多代表level越高，以level高的為parent(只要把level低的root的parent改成level高的root就好)



```cpp=
void heightUnion(std::vector<int> &subset, int x, int y){

    int xroot = collapsingFind(subset, x),
        yroot = collapsingFind(subset, y);

    // 用rank比較, 負越多表示set level 越高
    // xroot, yroot的subset[]一定都是負值

    // x比較level較高或是一樣多的時候, 以x作為root
    if (subset[xroot] <= subset[yroot]) {     
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot;
    }
    else {    //  subset[xroot] > subset[yroot], 表示y比較多element
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}
```
### weightedUnion and heightUnion 比較
weightedUniong是用nodes數目多的當parent,但是有時候node數目多不代表level高，因此比heightUnion容易使height增加,而height增加會影響collapsingFind()的效率

- 例如
Ａ tree(10 個 node,height=2)
B tree(5 個 node,height=4)
會造成把B合併到A下面

