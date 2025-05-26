#include<bits/stdc++.h>
using namespace std;
string removeSpace(string s1){
	string s;
	for(char ch:s1){
		if(isalpha(ch)){
			s+=tolower(ch);
		}
	}
	cout<<"REMOVE SPACE:"<<s<<endl;
	return s;
}
void check(string s1){
	stack<char> s;
	for(char ch :s1){
		s.push(ch);
	}
	
	for(char ch:s1){
		if(s.top()!=ch){
			cout<<"Not palindrome";
			return;
		}
		s.pop();
	}
	cout<<"Palindrome";
	
}
string reverse(string s1){
	stack<char>st;
	for(char ch:s1)st.push(ch);
	string rev;
	while(!st.empty()){
		rev+=st.top();
		st.pop();
	}
	return rev;
}
int main(){
	string s1;
	cout<<"Enter the String"<<endl;
	getline(cin,s1);
	cout<<"Reverese of the String is :"<<reverse(s1)<<endl;
	string s2=removeSpace(s1);
	check(s2);
}