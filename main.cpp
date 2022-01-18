#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<ctime>
#include<cstring>
#include<vector>
#include<iostream>
#include "func.h"
using namespace std;

// Utility Func
// string parser : output vector of strings (words) after parsing

int main(int argc, char *argv[]){
    // INPUT :
	// 1. data directory in data folder
	// 2. number of txt files
	// 3. output route
	clock_t start,end;
	start=clock();

    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);
	// Read File & Parser Example
	string file, title_name, tmp;
	fstream fi;
	vector<string> tmp_string;

	Trie tr;
	Trie s_tr;
	// from data_dir get file ....
	// eg : use 0.txt in data directory
	int i=0;
	while(1){
		fi.open(data_dir+to_string(i)+".txt", ios::in);
		if(!fi.is_open())break;
    	// GET TITLENAME
		getline(fi, title_name);

    	// GET TITLENAME WORD ARRAY
    	tmp_string = split(title_name, " ");
		vector<string> title = word_parse(tmp_string);
		for(auto &word : title){
			//cout << word << endl;
			string low=tolower(word);
			//cout<<low<<endl;
			tr.insert(low,i);
			s_tr.insert(reverse(low),i);
		}
    	// GET CONTENT LINE BY LINE
		while(getline(fi, tmp)){
        	// GET CONTENT WORD VECTOR
			tmp_string = split(tmp, " ");
			// PARSE CONTENT
			vector<string> content = word_parse(tmp_string);
			for(auto &word : content){
				string low=tolower(word);
			//cout<<low<<endl;
				tr.insert(low,i);
				s_tr.insert(reverse(low),i);
			}
			//......
		}
    	// CLOSE FILE
		fi.close();
		i++;
	}

	fi.open(query, ios::in);
	fstream ofs;
	ofs.open(output,ios::out);
	while(getline(fi,tmp)){
		//cout<<tmp<<endl;
		int idx=0;
		vector<int>tmpres;
		vector<int>par;
		int oper=0;
		//0:no, 1:and, 2:or

		while(idx<tmp.length()){
			if(tmp[idx]=='"'){
				string tofind;
				idx++;
				while(tmp[idx]!='"') tofind+=tmp[idx],idx++;
				//cout<<tofind<<endl;
				par=tr.exact_search(tofind);
				idx+=2;
				//for(int j=0;j<par.size();j++) cout<<par[j]<<" ";
				//cout<<endl;
				tmpres=setoper(tmpres,par,oper);
			}
			else if(tmp[idx]=='*'){
				string tofind;
				idx++;
				while(tmp[idx]!='*'){
					tofind+=tmp[idx];
					idx++;
				}
				//cout<<tofind<<endl;
				par=s_tr.prefix_search(reverse(tofind));
				idx+=2;
				//for(int j=0;j<par.size();j++)cout<<par[j]<<" ";
				//cout<<endl;
				tmpres=setoper(tmpres,par,oper);
			}
			else if(tmp[idx]=='/'){
				idx+=2;
				oper=2;				
			}
			else if(tmp[idx]=='+'){
				idx+=2;
				oper=1;
			}
			else{
				string tofind;
				while(tmp[idx]!=' '&&idx<tmp.length()){
					tofind+=tmp[idx];
					idx++;
				}
				par=tr.prefix_search(tofind);
				idx+=1;
				tmpres=setoper(tmpres,par,oper);
			}
		}
		
		fstream lookfi;
		for(int i=0;i<tmpres.size();i++){
			//cout<<tmpres[i]<<" ";
			lookfi.open(data_dir+to_string(tmpres[i])+".txt", ios::in);
			string title;
			getline(lookfi,title);
			lookfi.close();
			ofs<<title<<endl;
		}
		if(tmpres.size()==0){
			ofs<<"Not Found!"<<endl;
		}
	}
	fi.close();
	ofs.close();
	tr.~Trie();
	s_tr.~Trie();

	end=clock();
	cout << (double)((double)(end-start)/CLOCKS_PER_SEC)<<endl;
}


// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
