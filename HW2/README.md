Data Structure Assignment 2
===
###### tags:`Data Structure`
[TOC]

## Solitaire

### 先產生random array
使用時間當亂數種子
將產生的亂數以array大小(n)取餘數，可以得到0-(n-1)範圍的數字
使用for迴圈 和隨機得到的數字當index做交換位置
```cpp=
void swap (string *a, string *b)  
{  
    string temp = *a;  
    *a = *b;  
    *b = temp;  
}  
  
void randomize (string arr[], int n)  
{  
    srand (time(NULL));  

    for (int i = n - 1; i > 0; i--)  
    {  
        // Pick a random index from 0 to i  
        int j = rand() % (i + 1);  

        swap(&arr[i], &arr[j]);  
    }  
}  

```
### 創建一個circular queue
減少內存使用，並可以按照題目要的做pop和push
```cpp=
class QueueArrayCircular{
private:
    int capacity, front, back,end;
    string *queue;
    void DoubleCapacity();
public:
    QueueArrayCircular():capacity(14),front(0),back(0){ 
        queue = new string[capacity];
    }
    void Push(string x);
    void Pop();
    bool IsEmpty();
    void printq();
    void deleteq();
    string getFront();
};
```

### 將random array 結果儲存到 queue
```cpp=
    randomize (arr, n);  

    for (int i=0;i<n;i++){
        q.Push(arr[i]);
    }
```
### 開始和題目要求的K到A的順序做比較
當有相同時，開始筆下一位
當有不同時，重新push回去
```cpp=
    while(count != n){
        ch = q.getFront();
        q.Pop();
        if (ch == arr_og[count]){
            count++;
        }else{
            q.Push(ch);
        }

        q.printq();
    }

```