#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
using namespace std;

struct person_info{
    int type;
    string name;
    person_info *next;
    person_info():name(0),next(0),type(0){};
    person_info(int y,string x):name(x),next(0),type(y){};
};

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

void QueueList::Push(int y,string x){

    if (IsEmpty()) {
        front = new person_info(y,x);
        back = front;
        size++;
        return;
    }

    person_info *newNode = new person_info(y,x);
    back->next = newNode;
    back = newNode;         // update back pointer
    size++;
}

void QueueList::Pop(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    person_info *deletenode = front;
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

    return front->name;
}

string QueueList::getBack(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return "-1";
    }

    return back->name;
}

bool QueueList::IsEmpty(){

//    return (size == 0);
    return ((front && back) == 0);
}

int QueueList::getSize(){

    return size;
}
void QueueList::printq(){
	
    person_info *temp=front;
	while(front){
		cout << front->name<<endl;
		front=front->next;
	}
	front=temp;
}



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

int main ()
{
    
    int group_count=0,i=0,count=0,pos=0,insert_pos=0,j;
    string person="";
    string queue="";
    string p="";
    QueueList groups;
    QueueList que;
    QueueList result;

    cin >> group_count;
    while(i<group_count){
        cin >> count;
        for(j=0;j<count;j++){
            cin >> person;
            groups.Push(i,person);
        }
        i++;
    };

    while(!cin.eof()){
        queue="";
        cin >> queue;
        if (queue == "ENQUEUE"){
            cin >> person;
            pos=groups.findGroup(person);
            que.insert(pos,person);
        }else if(queue == "DEQUEUE"){
            p = que.getFront();
            que.Pop();
            result.Push(0,p);
        }else{
            break;
        }
    };
    result.printq();
}




