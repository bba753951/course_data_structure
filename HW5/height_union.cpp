#include <iostream>
#include <vector>

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
int Find(std::vector<int> &subset, int i){      

    int root,count=0;  
    for (root = i; subset[root] >= 0; root = subset[root])  // 找到root
        count++;

    while (i != root) {             // 進行collapsing
        int parent = subset[i];
        subset[i] = root;
        i = parent;
        count++;
    };
    count--;

    return count;
}

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

int main() {
    int tree_count=0,nodes=0,pos=0,count=0,q=0,u1=0,u2=0;
    std::string op;
    std::vector<int> array,answer;

    std::cout << "Input:" << std::endl;
    std::cin >> tree_count;
    while(tree_count--){
        std::cin >> nodes;
        count+=nodes;
        array.resize(count);
        while(nodes--){
            std::cin >>q;
            std::cin >>q;
            array[pos++]=q;
        };


    }
    // for(int i =0;i<count;i++){
    //     std::cout << array[i] << " ";
    // }
    // std::cout << std::endl;
    // heightUnion(array, 0, 3);
    // for(int i =0;i<count;i++){
    //     std::cout << array[i] << " ";
    // }
    // std::cout << std::endl;
    // Find(array,5);
    // Find(array,1);
    // Find(array,1);

    std::cin >> op;
    while(op != "STOP"){
        if(op=="UNION"){
            std::cin >> u1;
            std::cin >> u2;
            heightUnion(array, u1, u2);
            std::cin >> op;

        }else if(op=="FIND"){
            std::cin >> u1;
            u2=Find(array,u1);
            answer.push_back(u2);
            std::cin >> op;

        }else
            break;
    }  

    if(op=="STOP"){
        std::cout << std::endl;
        std::cout << "Output:" << std::endl;
        for(int i=0;i<answer.size();i++){
            std::cout << answer[i] << std::endl;
        }

    }else{
        std::cout << "input error" << std::endl;
    }

    return 0;

}
