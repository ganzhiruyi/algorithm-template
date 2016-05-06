class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode* next[26];
    bool isWord;
    TrieNode() {
        isWord = false;
        memset(next,NULL,sizeof(next));
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        int idx,i = 0,n = word.length();
        TrieNode *p = root;
        while(i < n){
            idx = word[i]-'a';
            if(!next[idx]) p->next[idx] = new TrieNode();
            p = p->next[idx];
            ++i;
        }
        p->isWord = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *p = root;
        int i = 0,n = word.length();
        while(i < n){
            idx = word[i]-'a';
            if(!next[idx]) return false;
            p = p->next[idx];
            ++i;
        }
        return p->isWord;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *p = root;
        int i = 0,n = word.length();
        while(i < n){
            idx = word[i]-'a';
            if(!next[idx]) return false;
            p = p->next[idx];
            ++i;
        }
        return true;
    }

private:
    TrieNode* root;
};
