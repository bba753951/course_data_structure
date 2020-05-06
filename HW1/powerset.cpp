#include<iostream>
#include<vector>
using namespace std;


void subsets(vector<string>& inputs, int i, vector<string>& sub, vector< vector<string> >& subs) {
	subs.push_back(sub);
	for (int j = i; j < inputs.size(); j++) {
		sub.push_back(inputs[j]);
		subsets(inputs, j + 1, sub, subs);
		sub.pop_back();
	}
}
int main()
{
while(!cin.eof()) {
	vector< vector<string> > subs;
        vector<string> sub;
	vector<string> inputs;
	string i;  
	cin >> i;
	inputs.push_back(i);
	while (cin.get() != '\n')   { 
		cin >> i; 
		inputs.push_back(i);
	}  	

        subsets(inputs, 0, sub, subs);

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
}
	return 0;
}
