#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<list>
#include<cstring>
#include<vector>
#include<iostream>

using namespace std;
string reverse(string str);

class node{
	public:
    friend class Trie;
	node(char c,bool iscom){
		//ch=c;
		for(int i=0;i<26;i++){
            children[i]=nullptr;
        }
		isCompleteWord=iscom;
	}
    node(int from){
        //ch=c;
		for(int i=0;i<26;i++){
            children[i]=nullptr;
        }
        fromFile.push_back(from);
        isComplete.push_back(false);
		isCompleteWord=false;
    }
    void record(int from,int isCom){
        if(fromFile.back()==from){
            if(isCom){
                isComplete.pop_back();
                isComplete.push_back(true);
            }
        }
        else{
            fromFile.push_back(from);
            isComplete.push_back(isCom);
        }
    }
    vector<int>exactcompare(){
        list<int>::iterator i=fromFile.begin();
        list<bool>::iterator j=isComplete.begin();
        vector<int>res;
        while(i!=fromFile.end()){
            if(*j==true)res.push_back(*i);
            i++;
            j++;
        }
        return res;
    }
    vector<int>pre_compare(){
        list<int>::iterator i=fromFile.begin();
        vector<int>res;
        while(i!=fromFile.end()){
            res.push_back(*i);
            i++;
        }
        return res;
    }
	private:
	node* children[26];
	bool isCompleteWord;
    list<int> fromFile;
    list<bool> isComplete;
};
class Trie{
	public:
	Trie(){
		root=new node('0',false);
	}
	void insert(string str,int from){
        node* ptr=root;
        for (int i = 0; i < str.length(); i++){
            int index = str[i] - 'a';
            if (!ptr->children[index]) ptr->children[index] = new node(from);
            else{
                ptr->children[index]->record(from,false);
            }
                ptr = ptr->children[index];
        }
        if(str.length()>0){
            ptr->isCompleteWord = true;
            ptr->isComplete.pop_back();
            ptr->isComplete.push_back(true);
        }
        
        
    }
    vector<int> exact_search(string str){
        node *ptr = root;
        vector<int> empty;
        for (int i = 0; i < str.length(); i++){
            int index = str[i] - 'a';
            if (!ptr->children[index]) return empty;
            
            ptr = ptr->children[index];
            //char k=index+'a';
            //cout<<k;
        }
        return ptr->exactcompare();
    }
    vector<int> prefix_search(string str){
        node *ptr = root;
        vector<int>empty;
        for (int i = 0; i < str.length(); i++){
            int index = str[i] - 'a';
            if (!ptr->children[index]) return empty;
            
            ptr = ptr->children[index];
            //char k=index+'a';
            //cout<<k;
        }
        return ptr->pre_compare();
    }
    void Tra(){
        traverse(root);
    }
    void traverse(node*rt){
        for(int i=0;i<26;i++){
            if(rt->children[i]){
                cout<<(char)(i+'a')<<endl;
                traverse(rt->children[i]);
            }
        }
    }
	~Trie(){
        destroy(root);
	}
    
	private:
	node* root;

void destroy(node *rt){
        for(auto it:rt->children){
            if(it)destroy(it);
        }
        delete rt;
    }
};

string tolower(string str){
    for(int i=0;i<str.length();i++){
        if(isupper(str[i])){
            str[i]=str[i]-'A'+'a';
        }
    }
    return str;
}

string reverse(string str){
    string result;
    for(int i=str.length()-1;i>=0;i--){
        result+=str[i];
    }
    return result;
}
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
vector<int> setoper(vector<int> res,vector<int> tem,int oper){
	vector<int>ans;
	if(oper==0){//no
		return tem;
	}
	else if(oper==1){//and
		int i=0;
		int j=0;
		while(i<res.size()&&j<tem.size()){
			if(res[i]==tem[j])ans.push_back(res[i]),i++,j++;
			else if(res[i]>tem[j])j++;
			else if(res[i]<tem[j])i++;
		}
		return ans;
	}
	else if(oper==2){//or
		int i=0;
		int j=0;
		while(i<res.size()||j<tem.size()){
			if(i<res.size()&&j<tem.size()){
				if(res[i]==tem[j])ans.push_back(res[i]),i++,j++;
				else if(res[i]>tem[j])ans.push_back(tem[j]),j++;
				else if(res[i]<tem[j])ans.push_back(res[i]),i++;
			}
			else if(i<res.size()&&j==tem.size()){
				ans.push_back(res[i]),i++;
			}
			else if(i==res.size()&&j<tem.size()){
				ans.push_back(tem[j]),j++;
			}
		}
		return ans;
	}
	return ans;
}
