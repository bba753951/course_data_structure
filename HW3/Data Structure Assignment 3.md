Data Structure Assignment 3
===
###### tags:`Data Structure`
[TOC]

# Queueing in Costco 

## indroduce parametmer
```cpp=
    int group_count=0,i=0,count=0,pos=0,insert_pos=0,j;
    string person="";
    string queue="";
    vector< person_info > groups;
    vector< person_info > que;
    vector<string> result;
    person_info p;

```
- **group_count**: for first line input(N groups).
- **count**: for how much people in each group.
- **pos**: for whether the ENQUEUE person in the groups or not.
- **insert_pos**: whether the ENQUEUE person have freind in queue.
- **person**: ENQUEUE person
- **queue** : check input is ENQUEUE or DEQUEUE
- **groups**: record a person which have friends and their group.
- **que**:record the queue after the ENQUEUE atcion
- **restult**:record the queue after the DEQUEUE atcion
- **struct** person_info p:record each person information

## record the information for each person have group
```cpp=
while(i<group_count){
|   cin >> count;
|   for(j=0;j<count;j++){
|   |   cin >> person;
|   |   p.type=i;
|   |   p.name=person;
|   |   groups.push_back(p);
|   }
|   i++;
}
```
## function
```cpp=
int findGroup(vector<person_info> groups,string ch){
    for(int i = 0;i<groups.size();i++){
    |   if(groups[i].name==ch) return i;
    }
    return -1;
}

int findPos(vector<person_info> groups,int type){
    for(int i = 0;i<groups.size();i++){
    |   if(groups[i].type==type) return i;
    }
    return -1;
}

```
- **findGroup**:find the ENQUEUE person have groups or not
- **findPos**: find the ENQUEUE person have friends in the queue or not

## main program
```cpp=
    |   |   pos=findGroup(groups,person);
    |   |   if (pos == -1){
    |   |   |   p.type=group_count;
    |   |   |   p.name=person;
    |   |   |   que.push_back(p);
```
if the person doesn't have friend in group，I will create a new group ,and the group "type" will use the "group_cout" beacuse I just use "0 to (group_cout -1)" for group type.

And findGroup() is find the group from "groups",so other people doesn't have group,but I define their "type" all as "group_count" will not be confused. 