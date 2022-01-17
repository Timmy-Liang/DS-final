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
vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch))
				new_str.push_back(ch);
		}
		parse_string.emplace_back(new_str);
	}
	return parse_string;
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	//先將要切割的字串從string型別轉換為char*型別
	char * strs = new char[str.length() + 1] ; //不要忘了
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字串轉換為string型別
		res.push_back(s); //存入結果陣列
		p = strtok(NULL, d);
	}

	return res;
}


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
	cout<<data_dir<<endl;
	cout<<query<<endl;
	cout<<output<<endl;
	string file, title_name, tmp;
	fstream fi;
	vector<string> tmp_string;

	Trie tr;
	Trie s_tr;
	// from data_dir get file ....
	// eg : use 0.txt in data directory
	int i=0;
	while(1){
		//if(i>=950)cout<<i<<endl;
		//cout<<data_dir+to_string(i)+".txt"<<endl;
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
		tr.insert(low);
		s_tr.insert(reverse(low));
	}

    // GET CONTENT LINE BY LINE
	while(getline(fi, tmp)){
        // GET CONTENT WORD VECTOR
		tmp_string = split(tmp, " ");
		// PARSE CONTENT
		vector<string> content = word_parse(tmp_string);
		for(auto &word : content){
			//cout << word << endl;
			string low=tolower(word);
			tr.insert(low);
			s_tr.insert(reverse(low));
		}
		//......
	}
    // CLOSE FILE
	fi.close();
	i++;
	}

	fi.open(query, ios::in);
	while(getline(fi,tmp)){
		cout<<tmp<<endl;
		int idx=0;

		while(idx<tmp.length()){
			if(tmp[idx]=='"'){
				string tofind;
				idx++;
				while(tmp[idx]!='"'){
					tofind+=tmp[idx];
					idx++;
				}
				cout<<tofind<<endl;
				cout<<tr.prefix_search(tofind)<<endl;
				idx+=2;
				
				continue;
			}
			else if(tmp[idx]=='*'){
				string tofind;
				idx++;
				while(tmp[idx]!='*'){
					tofind+=tmp[idx];
					idx++;
				}
				cout<<tofind<<endl;
				cout<<s_tr.prefix_search(reverse(tofind))<<endl;
				idx+=2;
				
				continue;
			}
			else if(tmp[idx]=='/'){
				idx+=2;
				continue;
				
			}
			else if(tmp[idx]=='+'){
				idx+=2;
				continue;
			}
			else{
				string tofind;
				while(tmp[idx]!=' '&&idx<tmp.length()){
					tofind+=tmp[idx];
					idx++;
				}
				cout<<tofind<<endl;
				cout<<tr.exact_search(tofind)<<endl;
				idx+=1;
				
			}
		}
		
		
		
	}
	end=clock();
	cout << (double)((end-start)/CLOCKS_PER_SEC)<<endl;
	
	/*string op,st;
	while(cin>>op>>st){
		if(op[0]=='p'){
            tr.prefix_search(st)? cout << "Yes\n" :cout << "No\n";
        }
        else if(op[0]=='e'){
            tr.exact_search(st)? cout << "Yes\n" :cout << "No\n";
        }
        else if(op[0]=='s'){
            s_tr.prefix_search(reverse(st))? cout << "Yes\n" :cout << "No\n";
        }
	}*/
	
}


// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
