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
        ptr->isCompleteWord = true;
        ptr->isComplete.pop_back();
        ptr->isComplete.push_back(true);
        
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
        //for(list<int>::iterator i=ptr->fromFile.begin(),list<bool>::iterator j=ptr->isComplete.begin();i!=)
        return ptr->exactcompare();
    }
    bool prefix_search(string str){
        node *ptr = root;
 
        for (int i = 0; i < str.length(); i++){
            int index = str[i] - 'a';
            if (!ptr->children[index]) return false;
            
            ptr = ptr->children[index];
            //char k=index+'a';
            //cout<<k;
        }
        return true;
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

