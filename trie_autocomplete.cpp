#include<bits/stdc++.h>
using namespace std;

struct trienode
{
    bool is_word;
    trienode* child[26];
};

trienode* get_new_node()
{
    trienode* temp = new trienode;
    temp->is_word = false;

    for(int i=0;i<26;i++)
    {
        temp->child[i]=NULL;
    }
    return temp;
}

void insert(trienode* root,string key)
{
    trienode* temp = root;
    int l = key.length();
    for(int i=0 ; i<l ; i++)
    {
        int ind = int(key[i])-'a';
        if(temp->child[ind]==NULL)
        {
            temp->child[ind]=get_new_node();
        }

        temp=temp->child[ind];
    }
    temp->is_word=true;
}

bool search(trienode* root,string key)
{
    if(root==NULL)
        return false;
    trienode* temp = root;

    int l = key.length();

    for(int i=0 ; i<l ; i++)
    {
        int ind = int(key[i])-'a';
        if(temp->child[ind] == NULL)
            return false;
        temp = temp->child[ind];
    }

    return true;
}

trienode* helper(trienode* root,string key, int ind)
{
    //if tree is empty
    if(root==NULL)
        return NULL;

    /* helper function takes three parameters
    1) root of subtrie
    2) key to be deleted
    3) ind(index) tells about depth

    function will return root of subtrie
    */

    bool isempty=true;
    for(int i ; i<26 ; i++)
    {
        if(root->child[i] != NULL)
        {
           isempty=false;
           break;
        }
    }

    if(ind == key.length())
    {
        // hit end of key

        /*cases possible
        1) this is prefix of some other key
        set is_word as false

        2)if not prefix of some other key , delete this node
       */

       if(isempty==false)
       {
           root->is_word = false;
       }

       else
       {
           delete(root);
           root = NULL;
       }

       return root;
    }

    int pos= int(key[ind]) - 'a';
    root->child[pos]=helper(root->child[pos],key,ind+1);
    //recursively calling

    isempty=true;

    for(int i=0 ; i<26 ; i++)
    {
        if(root->child[i]!=NULL)
        {
            isempty=false;
            break;
        }
    }
     /*here are two cases
     1) if all  child nodes of root is empty and this root is not marked as
        of word then delete this node

     2) if all child nodes are not empty "OR" this root os marked as end of
        word then do nothing
    */

    if(isempty && root->is_word == false)
    {
        delete(root);
        root=NULL;
    }
    return root;
}

trienode* delete_key(trienode* root,string key)
{
    //if tree is empty
    if(root==NULL)
    return root;

    //if key is empty
    if(key=="")
        return root;

    /*delete_key function takes two parameters
    1) root of trie
    2) key to be deleted
    */

    root=helper(root,key,0);
    return root;
}

void find_all_words(trienode* root,string key,vector<string> &all_words)
{
    if(root==NULL)
        return;

        trienode*temp = root;

        for(int i=0 ; i < (int)key.size() ; i++)
        {
            int ind = int(key[i]) - 'a';

            if(temp->child[ind] == NULL )
                return;
            temp = temp->child[ind];
        }

        //if prefix exist then do BFS
        queue<pair<trienode*,string>> q;
        q.push({temp,key});
        string this_word;
        while(!q.empty())
        {
         temp = q.front().first;
         this_word = q.front().second;

          //if this is_word is true all it to all words

          if(temp->is_word)
                all_words.push_back(this_word);
          q.pop();

          for(int i=0 ; i<26 ; i++)
          {
              if(temp->child[i] != NULL)
              {
                  q.push({temp->child[i] , this_word + char(i+int('a'))});

              }

          }
}
}

void auto_complete(trienode* root , string key)
{
 /* this function takes two parameters
 1)root of trie

 2) key for which suggestion to be found
 */

 //if key is empty

 if(key.size() == 0)
        return;

 //if key is not empty

 vector<string> all_words;
 find_all_words(root,key,all_words);

 //print all words
 if(all_words.size()==0)
 {
     cout<<"There are no suggestions."<<endl;
     return;
 }

 cout<<"There are "<<all_words.size()<<" suggestions for the prefix "<<key<<endl;
 for(int i=0;i<(int)all_words.size();i++)
 {
     cout<<all_words[i]<<endl;
 }
 return;
}
int main()
{
    //creating dictionary
    cout<<"Enter the number of words :"<<endl;
    int n;
    cin>>n;

    vector<string> dict;
    string key;
     cout<<"Words are :"<<endl;
     int i;
     for(i=0;i<n;i++)
     {
         cin>>key;
         dict.push_back(key);
     }

     //creates root node
     trienode* root=get_new_node();
     //insert all words of dictionary to trie

     for(i=0;i<dict.size();i++)
     {
         insert(root,dict[i]);
     }

     cout<<"Enter key to autocomplete :"<<endl;
     cin>>key;
     auto_complete(root,key);
     return 0;
}
