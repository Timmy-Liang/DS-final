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
    node(){
        //ch=c;
		for(int i=0;i<26;i++){
            children[i]=nullptr;
        }
        
		isCompleteWord=false;
    }
	private:
	//char ch;
	node* children[26];
	bool isCompleteWord;
    //list<int> fromFile;
    //list<bool> isComplete;
};
class Trie{
	public:
	Trie(){
		root=new node('0',false);
	}
	void insert(string str){
        node* ptr=root;
        for (int i = 0; i < str.length(); i++){
            int index = str[i] - 'a';
            if (!ptr->children[index]) ptr->children[index] = new node();
                ptr = ptr->children[index];
        }
        ptr->isCompleteWord = true;
        
    }
    bool exact_search(string str){
        node *ptr = root;
 
        for (int i = 0; i < str.length(); i++){
            int index = str[i] - 'a';
            if (!ptr->children[index]) return false;
            
            ptr = ptr->children[index];
            //char k=index+'a';
            //cout<<k;
        }
        return (ptr->isCompleteWord);
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

/*
int main(void){

    Trie tr;
    Trie s_tr;
    // Construct trie
    string str,op;
    while(cin>>op>>str){
        
        if(op[0]=='p'){
            tr.prefix_search(str)? cout << "Yes\n" :cout << "No\n";
        }
        else if(op[0]=='e'){
            tr.exact_search(str)? cout << "Yes\n" :cout << "No\n";
        }
        else if(op[0]=='s'){
            s_tr.prefix_search(reverse(str))? cout << "Yes\n" :cout << "No\n";
        }
        else if(op[0]=='0'){
            s_tr.insert(reverse(str));
            tr.insert(str);
        }
    }
    return 0;
    
}*/
string reverse(string str){
    string result;
    for(int i=str.length()-1;i>=0;i--){
        result+=str[i];
    }
    return result;
}

