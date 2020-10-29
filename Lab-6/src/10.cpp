#include<iostream>
#include<string.h>
#include<pthread.h>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

vector<string> str1_subseq;

void* check_common_seq (void* arg);
void subsequence(string str);


string str1, str2;
vector<string> common;

int main(int argc, char const *argv[]){

	if(strlen(argv[1]) < strlen(argv[2])){
		str1=argv[1];
		str2=argv[2];
	}
	else{
		str1=argv[2];
		str2=argv[1];
	}

	// finds all the subsequences of str1
	subsequence(str1);
	sort(str1_subseq.begin(), str1_subseq.end());
	str1_subseq.erase(std::unique(str1_subseq.begin(), str1_subseq.end()), str1_subseq.end());

	pthread_t threads[100];
	int itr=0;

	// find all common subsequences
	for(int i=0; i<str1_subseq.size(); i++){

		pthread_create(&threads[itr], NULL, check_common_seq, (void*)&str1_subseq[i]);
		pthread_join(threads[itr], NULL);
		itr++;
	}

	// Find the longest common sequence from all common sequences
	string lcs = common[0];
	for(int i=1; i<common.size(); i++){
		if(lcs.length() < common[i].length())
			lcs = common[i];\
	}

	if(lcs.length() >= 2){
		cout<<"Longest Common Subsequence: "<<lcs<<endl;
	}
	else{
		cout<<"Longest Common Subsequence of length more than 2 does not exist"<<endl;
	}
	return 0;
}

void* check_common_seq (void* arg){
	
	string* s = (string*)arg;

	int i, j=0;
	for(i=0; i<(*s).length(); i++){
		int flag=0;
		for(j; j<str2.length(); j++){
			if((*s)[i] == str2[j]){
				j++;
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			break;
		}
	}
	if(i == (*s).length()){
		// cout<<*s<<endl;
		common.push_back(*s);
	}

	pthread_exit(NULL);
}

void subsequence(string str){
	for (int i = 0; i < str.length(); i++) 
	{
		for (int j = str.length(); j > i; j--) 
		{
			string sub_str = str.substr(i, j);
			str1_subseq.push_back(sub_str);
 
			for (int k = 1; k < sub_str.length() - 1; k++) 
			{
				string sb = sub_str;
				sb.erase(sb.begin() + k);
				subsequence(sb);
			}
		}
	}
}