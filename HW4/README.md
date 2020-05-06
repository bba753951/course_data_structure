Data Structure Assignment 4
===
###### tags:`Data Structure`
[TOC]

# Solitaire(linked list)
創一個node的struct
包含了data(one card)
pointer next
```cpp=
struct QueueNode{
    string data;
    QueueNode *next;
    QueueNode():data(0),next(0){};
    QueueNode(string x):data(x),next(0){};
};
```


創一個linked list
包含了兩個指針
- front 指向第一個node(for Pop(),getFront())
- back 指向最後一個node(for Push,getBack())

printq()輸出linked list裡每個node的data(空格分開)
```cpp=
class QueueList{
private:
    QueueNode *front;
    QueueNode *back;
    int size;
public:
    QueueList():front(0),back(0),size(0){};
    void Push(string x);
    void Pop();
    bool IsEmpty();
    string getFront();
    string getBack();
    int getSize();
	void printq();
};
```

產生一個random順序的array(和HW2相同)
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
## 和HW2(circularly array)比較
大致上的運算是一樣的，因為都是實現queue得push,pop,getfront

但是HW2使用了circularly queue，為了不浪費空間，但為了判斷是full還是empty，因此13張卡片需要14的空間

而使用linked list的好處是可以節省空間，代碼寫起來比較方便，不需要像circularly queue 使用mod(%)


# Queueing in Costco(linked list)
創造一個node struct
一個node代表一個人
type為一個人的朋友圈編號
name為人的名字
next指向下一個人
```cpp=
struct person_info{
    int type;
    string name;
    person_info *next;
    person_info():name(0),next(0),type(0){};
    person_info(int y,string x):name(x),next(0),type(y){};
};
```
創造一個linked list代表一個隊伍
```cpp=
class QueueList{
private:
    person_info *front;
    person_info *back;
    int size;
public:
    QueueList():front(0),back(0),size(0){};
    void Push(int y,string x);
    void Pop();
    bool IsEmpty();
    string getFront();
    string getBack();
    int getSize();
	void printq();
    int findGroup(string ch);
    void insert(int y,string z);
};
```

- front 指向隊首那個人
- back 指向隊尾那個人
- Push()加入排隊
- Pop()離開隊伍
- getFront()得到隊首那個人的名字
- printq()打印這個隊伍每個人的名字(換行隔開)
- findGroup(string ch)查看ch這個人有沒有認識的朋友圈
```cpp=
int QueueList::findGroup(string ch){
    person_info *temp=front;
    while(front){
        if(front->name==ch){
            int x=front->type;
            front=temp;
            return x;
        }
        front=front->next;
    };
    front=temp;
    return -1; 
}
```
- insert(int y,string z)加入隊伍
	- 如果lincked list是empty，則創造一個node在開頭
	- while(curr && curr->type != y)負責travesal查看lincked list裡面有沒有認識的朋友
	- 最後三種判斷要如何插入隊伍

```cpp=
void QueueList::insert(int y,string z){

    if (IsEmpty()) {
        front = new person_info(y,z);
        back = front;
        size++;
        return;
    }
    person_info *newNode = new person_info(y,z);

    person_info *prev=0;
    person_info *curr=front;


    while(curr && curr->type != y){
        prev=curr;
        curr=curr->next;

    };

    if(curr == 0 || y==-1){
        back->next = newNode;
        back = newNode;         // update back pointer
        size++;
    }else if(curr==front){
        newNode->next=front;
        front=newNode;
    }else{
        newNode->next=curr;
        prev->next=newNode;
    };

}

```
## 和HW3比較
大致上想法是一樣的，HW3是使用STL的vector去實現queue，因此省去很多自己寫function時間，但HW4的funciton是自己寫的，比較彈性，能符合確切需求，兩個作業最大的不同是在判斷ENQUEUE後要如何插入，使用lilnked list減去很多判斷