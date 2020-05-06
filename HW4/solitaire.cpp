#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;  

struct QueueNode{
    string data;
    QueueNode *next;
    QueueNode():data(0),next(0){};
    QueueNode(string x):data(x),next(0){};
};

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

void QueueList::Push(string x){

    if (IsEmpty()) {
        front = new QueueNode(x);
        back = front;
        size++;
        return;
    }

    QueueNode *newNode = new QueueNode(x);
    back->next = newNode;
    back = newNode;         // update back pointer
    size++;
}

void QueueList::Pop(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    QueueNode *deletenode = front;
    front = front->next;    // update front pointer
    delete deletenode;
    deletenode = 0;
    size--;
}

string QueueList::getFront(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return "-1";
    }

    return front->data;
}

string QueueList::getBack(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return "-1";
    }

    return back->data;
}

bool QueueList::IsEmpty(){

//    return (size == 0);
    return ((front && back) == 0);
}

int QueueList::getSize(){

    return size;
}
void QueueList::printq(){
	
    QueueNode *temp=front;
	while(front){
		cout << front->data<<" ";
		front=front->next;
	}
	front=temp;
	cout << endl;
}


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

int main()  
{  
    string arr[] = {"K","Q","J","10","9","8","7","6","5","4","3","2","A"};  
    string arr_og[] = {"K","Q","J","10","9","8","7","6","5","4","3","2","A"};  


    QueueList q;
    string ch;
    int count=0;

    int n = sizeof(arr) / sizeof(arr[0]);  
    randomize (arr, n);  


    for (int i=0;i<n;i++){
        q.Push(arr[i]);
    };
	q.printq();
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

}
