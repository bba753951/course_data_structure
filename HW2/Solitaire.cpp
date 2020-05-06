#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;  
  
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

void QueueArrayCircular::Push(string x){

    back = (back + 1)%capacity;
    queue[back] = x;
}
void QueueArrayCircular::Pop(){

    front = (front + 1)%capacity;
}
bool QueueArrayCircular::IsEmpty(){
    return (front == back);
}

void QueueArrayCircular::printq(){
    if (back >= front){
        end=back;
    }else{
        end=back+capacity;
    }
    for (int i = front+1; i <= end;i++){
        cout << queue[(i%capacity)] << " ";
    }
    cout << endl;
}
string QueueArrayCircular::getFront(){

    return queue[(front + 1)%capacity];
}

void QueueArrayCircular::deleteq(){
    delete [] queue;
}
  
int main()  
{  
    string arr[] = {"K","Q","J","10","9","8","7","6","5","4","3","2","A"};  
    string arr_og[] = {"K","Q","J","10","9","8","7","6","5","4","3","2","A"};  
    QueueArrayCircular q;
    string ch;
    int count=0;

    // total:312  one element:24
    int n = sizeof(arr) / sizeof(arr[0]);  
    // random array
    randomize (arr, n);  

    for (int i=0;i<n;i++){
        q.Push(arr[i]);
    }

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


    q.deleteq();

    return 0;  
}  
