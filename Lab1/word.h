#ifndef WORD
#define WORD
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

class Word
{
private:
    string wordList[10000];
    vector<int>Edge[10000];
    //init
    int wordNumber = 0;
    int wordHead[26][1000];
    int wordTail[26][1000];

    int mmaxWord[10000]; //当前最长单词数目
    int maxWordPre[10000];//最长单词路径
    int mmaxLength[10000];//当前最长单词字母
    int maxLengthPre[10000];//最长字母路径
    int nodeIn[10000];//入度
    bool flag[10000];//是否被标记
    queue<int>node;
public:
    int Init(FILE * fin);
    void Print();
    void makeEdge();//建边
    void maxWord();
    void maxLength();
    void Print_DFS(int *a, int x);
};

int Word::Init(FILE * fin)
{
    while(!feof(fin)){
        char ch = fgetc(fin);
        if (ch == EOF){
            wordNumber++;
            break;
        }
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
            if (ch >= 'a' && ch <= 'z')
                wordList[wordNumber] += ch;
            else wordList[wordNumber] += (ch - 'A' + 'a');
        }
        else {
            wordNumber++;
        }
    }
}

void Word::Print()
{
    for (int i = 0; i < wordNumber; i++){
        cout << wordList[i] << endl;
    }
}

void Word::makeEdge()
{
    for (int i = 0; i < wordNumber; i++){
        int h = wordList[i][0] - 'a';
        int t = wordList[i][wordList[i].size() - 1] - 'a';
        wordHead[h][++wordHead[h][0]] = i;
        wordTail[t][++wordTail[t][0]] = i;
    }
    for (int i = 0; i < wordNumber; i++){
        int t = wordList[i][wordList[i].size() - 1] - 'a';
        for (int j = 1; j <= wordHead[t][0]; j++){
            if (i == wordHead[t][j]) continue;
            Edge[i].push_back(wordHead[t][j]);
            nodeIn[wordHead[t][j]]++;
        }
    }
}

void Word::maxWord()
{
    while(!node.empty())node.pop();
    memset(flag, 0, sizeof(flag));
    memset(mmaxWord, 0, sizeof(mmaxWord));
    memset(maxWordPre, 0, sizeof(maxWordPre));

    int minNodeIn = 1000000;
    for (int i = 0; i < wordNumber; i++){
        minNodeIn = min(minNodeIn, nodeIn[i]);
    }
    for (int i = 0; i < wordNumber; i++){
        if(minNodeIn == nodeIn[i]){
            node.push(i); mmaxWord[i] = 1; flag[i] = true; maxWordPre[i] = -1;
        }
    }
    vector<int>::iterator It;
    while(!node.empty()){
        int curNode = node.front();
        node.pop();
        for (It = Edge[curNode].begin(); It != Edge[curNode].end(); It++){
            // cout << curNode << " " << *It << endl;
            if (flag[*It]) continue;
            // mmaxWord[*It] = max(mmaxWord[*It], mmaxWord[curNode] + 1);
            if (mmaxWord[*It] < mmaxWord[curNode] + 1){
                mmaxWord[*It] = mmaxWord[curNode] + 1;
                maxWordPre[*It] = curNode;
            }
            nodeIn[*It]--;
            if(nodeIn[*It] == 0){
                node.push(*It);
                flag[*It] = true;
            } 
        }
    }
    int mmmaxWord = 0;
    for (int i = 0; i < wordNumber; i++){
        mmmaxWord = max(mmmaxWord, mmaxWord[i]);
    }
    if (mmmaxWord == 1){
        printf("No Word Chain\n");
        return;
    }
    cout << mmmaxWord << endl;
    for (int i = 0; i < wordNumber; i++){
        if(mmaxWord[i] == mmmaxWord){
            Print_DFS(maxWordPre, i);
            cout << wordList[i] << endl;
        }
    }
}

void Word::Print_DFS(int *a, int x){
    if(a[x] == -1)return;
    Print_DFS(a, a[x]);
    cout << wordList[a[x]] << endl;
}

void Word::maxLength()
{
    
}

#endif