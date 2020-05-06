#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
using namespace std;
typedef struct{
    int type;
    string name;

}person_info;

int findGroup(vector<person_info> groups,string ch){
    for(int i = 0;i<groups.size();i++){
        if(groups[i].name==ch) return i;
    }
    return -1; 
}

int findPos(vector<person_info> groups,int type){
    for(int i = 0;i<groups.size();i++){
        if(groups[i].type==type) return i;
    }
    return -1; 
}

int main ()
{
    int group_count=0,i=0,count=0,pos=0,insert_pos=0,j;
    string person="";
    string queue="";
    vector< person_info > groups;
    vector< person_info > que;
    vector<string> result;
    person_info p;
    
    cin >> group_count;
    while(i<group_count){
        cin >> count;
        for(j=0;j<count;j++){
            cin >> person;
            p.type=i;
            p.name=person;
            groups.push_back(p);
        }
        i++;
    }

    while(!cin.eof()){
        queue="";
        cin >> queue;
        if (queue == "ENQUEUE"){
            cin >> person;
            pos=findGroup(groups,person);
            if (pos == -1){
                p.type=group_count;
                p.name=person;
                que.push_back(p);
            }else{
                insert_pos=findPos(que,groups[pos].type);
                if(insert_pos == -1){
                    que.push_back(groups[pos]);
                }else{
                    que.insert(que.begin()+insert_pos,groups[pos]);
                }
            }
        }else if(queue == "DEQUEUE"){
            result.push_back(que[0].name);
            que.erase(que.begin());
        }else{
            break;
        }
    };

    for(i=0;i<result.size();i++){
        cout << result[i] << "\n";
    }
};
