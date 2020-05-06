Data Structure Assignment 1
===
###### tags:`Data Structure`
[TOC]

## Ackerman’s function
![](https://i.imgur.com/zc6Xata.png)

根據上面的方程式，定義一個Ackerman function
使用recursive的寫法

- 終止條件為：
m=0時，return n+1

- 其他條件
在n=0時繼續呼叫Ａ(m,n)
其他情況下呼叫Ａ(m-1,A(m,n-1))
```cpp=
int ackerman(int m, int n)
{
	if(m == 0){
		return n+1;
	}
	else if(n == 0){
		return ackerman(m-1,1);
	}else{
		return ackerman(m-1,ackerman(m,n-1));
	}
}
```

## powerset

### 讀取未知的多個輸入
因為不知輸入個數，因此使用了vector來動態存取輸入
設定終止條件為cin.get()得到換行“\n”時
```cpp=
vector<string> inputs;
string i;  
cin >> i;
inputs.push_back(i);
while (cin.get() != '\n')   { 
    cin >> i; 
    inputs.push_back(i);
}  	
```
### backtracking 基本概念


### 參考backtracking 演算法
- 使用二維vector儲存結果
```cpp=
vector< vector<string> > subs;
vector<string> sub;
```

- 因為是小於輸入集的所有組合，因此在每次呼叫的一開始就先儲存一次答案
- 接下來開始從剩下的答案集繼續抽取答案
- 最後一行必須做backtracking,把加入到结果中的點去除掉
```cpp=
void subsets(vector<string>& inputs, int i, vector<string>& sub, vector< vector<string> >& subs) {
	subs.push_back(sub);
	for (int j = i; j < inputs.size(); j++) {
		sub.push_back(inputs[j]);
		subsets(inputs, j + 1, sub, subs);
		sub.pop_back();
	}
}
```
### 輸出
利用兩個for迴圈輸出二維vector
為了符合規定格式{}
在第一個for迴圈的開頭與結束加上"{","}"
```cpp=
    for(int i=0; i< subs.size(); i++){
	cout<<"{";
		for(int j=0;j<subs[i].size();j++){
		    if(j==subs[i].size()-1){
			cout<<subs[i][j];
			break;
		    }
		    cout<<subs[i][j]<<" ";
	    }
	cout<<"} ";
	}
	cout<<"\n";

```