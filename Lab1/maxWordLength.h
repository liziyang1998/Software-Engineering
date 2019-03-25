#ifndef MAXWORDLENGTH
#define MAXWORDLENGTH
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

class max_Word_Length
{
private:
    string wordList[10000];
    vector<int>Edge[2][10000];
    //init
    int wordNumber = 0;
    int wordHead[26][1000];
    int wordTail[26][1000];

    int mmaxWord[10000]; //当前最长单词数目
    int maxWordPre[10000];//最长单词路径
    int tmpWordPre[10000];
    int tmp_max = 0;
    int tmp_x = 0;
    int mmaxLength[10000]; //当前最长单词字母
    int maxLengthPre[10000];//最长字母路径
    int tmpLengthPre[10000];
    int nodeIn[2][10000];//0 = 入度 1 = 出度
    bool flag[10000];//是否被标记
    queue<int>node;
public:
    int Init(FILE * fin);
    void Print();
    void makeEdge();//建边
    void maxWord();
    void maxLength();
    void Print_DFS(int *a, int x);
    void maxWordDfs(int x);
    void maxLengthDfs(int x);

    void maxWordHeadAndTail(char head, char tail);
    void maxWordHead(char head);
    void maxWordTail(char tail);
    void maxWordHeadAndTailDfs(int flag_head, char h, int flag_tail, char t, int anti);
};

int max_Word_Length::Init(FILE *fin)
{
    char tmp;
    while(!feof(fin)){
        char ch = fgetc(fin);
        if(ch == EOF){
            if((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z'))
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
        tmp = ch;
    }
}

void max_Word_Length::Print()
{
    for (int i = 0; i < wordNumber; i++){
        cout << wordList[i] << endl;
    }
}

void max_Word_Length::makeEdge()
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
            Edge[0][i].push_back(wordHead[t][j]);
            Edge[1][wordHead[t][j]].push_back(i);
            nodeIn[0][wordHead[t][j]]++;
            nodeIn[1][i]++;
        }
    }
}

void max_Word_Length::maxWord()
{
    while(!node.empty())node.pop();
    memset(flag, 0, sizeof(flag));
    memset(mmaxWord, 0, sizeof(mmaxWord));
    memset(maxWordPre, 0, sizeof(maxWordPre));

    int minNodeIn = 1000000;
    for (int i = 0; i < wordNumber; i++){
        minNodeIn = min(minNodeIn, nodeIn[0][i]);
    }
    for (int i = 0; i < wordNumber; i++){
        mmaxWord[i] = 1;
        if(nodeIn[i] == 0){
            node.push(i); flag[i] = true; maxWordPre[i] = -1;
        }
    }
    vector<int>::iterator It;
    while(!node.empty()){
        int curNode = node.front();
        node.pop();
        for (It = Edge[0][curNode].begin(); It != Edge[0][curNode].end(); It++){
            if (flag[*It]) continue;
            if (mmaxWord[*It] < mmaxWord[curNode] + 1){
                mmaxWord[*It] = mmaxWord[curNode] + 1;
                maxWordPre[*It] = curNode;
            }
            nodeIn[0][*It]--;
            if(nodeIn[*It] == 0){
                node.push(*It);
                flag[*It] = true;
            } 
        }
    }
    bool tmp_flag = false;
    for (int i = 0; i < wordNumber; i++){
        if (nodeIn[i] != 0)//有环 dfs
            tmp_flag = true;
    }
    if(!tmp_flag){
        int mmmaxWord = 0;
        for (int i = 0; i < wordNumber; i++){
            mmmaxWord = max(mmmaxWord, mmaxWord[i]);
        }
        if (mmmaxWord == 1){
            printf("No Word Chain\n");
            return;
        }
        // cout << mmmaxWord << endl;
        for (int i = 0; i < wordNumber; i++){
            if (mmaxWord[i] == mmmaxWord){
                Print_DFS(maxWordPre, i);
                cout << wordList[i] << endl;
                return;
            }
        }
    }
    else {
        tmp_max = 0;
        for (int j = 0; j < wordNumber; j++)
            tmpWordPre[j] = maxWordPre[j];
        for (int i = 0; i < wordNumber; i++){
            if (nodeIn[i] != 0 && flag[i] == false){
                flag[i] = true;
                maxWordDfs(i);
                flag[i] = false;
            }
        }
        Print_DFS(maxWordPre, tmp_x);
        cout << wordList[tmp_x] << endl;
    }
}

void max_Word_Length::Print_DFS(int *a, int x)
{
    if(a[x] == -1 || a[x] == x)return;
    Print_DFS(a, a[x]);
    cout << wordList[a[x]] << endl;
}

void max_Word_Length::maxWordDfs(int x) //对于环查dfs
{
    vector<int>::iterator It;
    for (It = Edge[0][x].begin(); It != Edge[0][x].end(); It++){
        if(!flag[*It]){
            if(mmaxWord[*It] < mmaxWord[x] + 1){
                int tmp = mmaxWord[*It];

                mmaxWord[*It] = mmaxWord[x] + 1;
                flag[*It] = true;
                tmpWordPre[*It] = x;
                
                maxWordDfs(*It);

                mmaxWord[*It] = tmp;
                flag[*It] = false;
                tmpWordPre[*It] = 0;
            } 
        }
    }
    if (tmp_max < mmaxWord[x]){
        tmp_max = mmaxWord[x];
        tmp_x = x;
        for (int i = 0; i < wordNumber; i++)
            maxWordPre[i] = tmpWordPre[i];
    }
}

void max_Word_Length::maxLength()
{
    for (int i = 0; i < wordNumber; i++){
        flag[i] = true;
        maxLengthDfs(i);
        flag[i] = false;
    }
    Print_DFS(maxLengthPre, tmp_x);
    cout << wordList[tmp_x] << endl;
}

void max_Word_Length::maxLengthDfs(int x)
{
    vector<int>::iterator It;
    for (It = Edge[0][x].begin(); It != Edge[0][x].end(); It++){
        if(flag[*It])continue;
        if (mmaxLength[*It] < mmaxLength[x] + wordList[*It].size()){
            int tmp = mmaxLength[*It];
            mmaxLength[*It] = mmaxLength[x] + wordList[*It].size();
            flag[*It] = true;
            tmpLengthPre[*It] = x;

            maxLengthDfs(*It);
            
            flag[*It] = false;
            mmaxLength[*It] = tmp;
            tmpLengthPre[*It] = 0;
        }
    }
    if(tmp_max < mmaxLength[x]){
        tmp_max = mmaxLength[x];
        tmp_x = x;
        for (int i = 0; i < wordNumber; i++)
            maxLengthPre[i] = tmpLengthPre[i];
    }
}

void max_Word_Length::maxWordHead(char head)
{
    int h = head - 'a';
    for (int i = 1; i <= wordHead[h][0]; i++){
        flag[wordHead[h][i]] = true;
        maxWordHeadAndTailDfs(1, wordHead[h][i], 0, '\0', 0);
        flag[wordHead[h][i]] = false;
    }
}

void max_Word_Length::maxWordTail(char tail)
{

}

void max_Word_Length::maxWordHeadAndTail(char head, char tail)
{

}

void max_Word_Length::maxWordHeadAndTailDfs(int flag_head, char h, int flag_tail, char t, int anti)
{
    if (flag_head){
        if (flag_tail){

        }
        else {
            
        }
    }
    else {

    }
}

#endif