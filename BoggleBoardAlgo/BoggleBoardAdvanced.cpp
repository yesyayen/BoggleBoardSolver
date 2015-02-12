/*
Given a dictionary, a method to do lookup in dictionary and a M x N board where every cell has one character.
Find all possible words that can be formed by a sequence of adjacent charactersNote that we can move to any of 8 adjacent characters,
but a word should not have multiple instances of same cell.

Example:

Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
       boggle[][]   = {{'G','I','Z'},
                       {'U','E','K'},
                       {'Q','S','E'}};
      isWord(str): returns true if str is present in dictionary
                   else false.

Output:  Following words of dictionary are present
         GEEKS
         QUIZ
http://www.geeksforgeeks.org/boggle-find-possible-words-board-characters/
*/
#include<stdio.h>
#include <sstream>
#include <string>
#include<iostream>
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<set>

#define ROW 4
#define COL 4
using namespace std;

int recCnt = 0;
int wordFound = 0;
set<string> words;
class trie
{

private:
    struct node{
    char val;
    int word;           //if its the end of a word
    node *refer[26];    //every node has 26 children
    }*head;


public:
    trie()              //root node - empty value
    {
        node *tmp;
        tmp = new node();
        tmp->val = ' ';

        for(int i = 0; i < 26; i++)
        {
            tmp->refer[i] = NULL;
        }
        head = tmp;
    }

    void addTrie(string value);
    char searchTrie(string value);
    string searchTrieG4G(string value);
    void boggleRecur(char boggle[ROW][COL], string currentWord, bool visited[ROW][COL], int row, int col);
    void boggleSolver(char boggle[ROW][COL]);
};

void trie::addTrie(string value)
{
    node *tmp = head;
    int i = 0;
    while(value.length() != i)       //loop through every character and insert it in trie if not already present
    {
        if(tmp->refer[value[i]-'a'] == NULL)
        {
            node *cha;
            cha = new node();
            cha->val = value[i];
            cha->word = 0;

            for(int i = 0; i < 26; i++)
            {
                cha->refer[i] = NULL;
            }
            tmp->refer[value[i]-'a'] = cha;
            tmp = cha;
        }
        else
        {
            tmp = tmp->refer[value[i]-'a'];
        }
        i++;
        if(value.length() == i)
            tmp->word++;
    }
}

/*
W-  its a whole word
P - part of the word is present
N - Not present
*/
char trie::searchTrie(string value)
{
    node *tmp = head;
    int i = 0;
    while(value.length() != i)
    {
        if(tmp->refer[value[i] - 'a'] == NULL)
            return 'N';

        tmp = tmp->refer[value[i] - 'a'];
        i++;
    }


    if(tmp->word > 0)
        return 'W';

    if(tmp != NULL)
        return 'P';

    return 'N';
}

void trie::boggleRecur(char boggle[ROW][COL], string currentWord, bool visited[ROW][COL], int row, int col)
{
    static int cnt = 0;
    if(currentWord.length() > ROW*COL)
        return;

    if(searchTrie(currentWord) == 'W' && currentWord.length() > 2)
    {
        wordFound++;
        words.insert(currentWord);
    }
    int traverseRow[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int traverseCol[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for(int i = 0; i < sizeof(traverseRow)/sizeof(traverseRow[0]); i++)
    {
        int newRow = row + traverseRow[i];
        int newCol = col + traverseCol[i];
        if(newRow >= 0 && newRow < ROW && newCol >= 0 && newCol < COL)
        {
            if(!visited[newRow][newCol])
            {
                visited[newRow][newCol] = true;
                if(searchTrie(currentWord + boggle[newRow][newCol]) == 'W' || searchTrie(currentWord + boggle[newRow][newCol]) == 'P')
                {
                    recCnt++;
                    boggleRecur(boggle, currentWord + boggle[newRow][newCol], visited, newRow, newCol);
                }
                visited[newRow][newCol] = false;
            }
        }
    }
}

void trie::boggleSolver(char boggle[ROW][COL])
{
    bool visited[ROW][COL];

    for(int k = 0; k < ROW; k++)
    {
        for(int l = 0; l < COL; l++)
        {
            visited[k][l] = false;
        }
    }

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            string s;
            stringstream ss;
            ss << boggle[i][j];
            ss >> s;
            visited[i][j] = true;
            boggleRecur(boggle, s, visited, i, j);
            visited[i][j] = false;
        }
    }
}


int main(int argc, char *argv[])
{
    trie tr;
    string line;

    //ifstream myfile("C:\\Users\\Anandh\\Desktop\\american-english");
    ifstream myfile("eng_com.dic");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            tr.addTrie(line);
        }
        myfile.close();
    }

    char boggle1[ROW][COL];
    string chars = argv[1];

    int index = 0;
    for(int k = 0; k < ROW; k++)
    {
        for(int l = 0; l < COL; l++)
        {
            boggle1[k][l] = chars[index];
            index++;
        }
    }

    tr.boggleSolver(boggle1);
    // cout << "\n" << recCnt << "Total words - " << wordFound;
    // cout << "\n" << recCnt << "Total unique words - " << words.size();

    for(set<string>::iterator i = words.begin(); i!= words.end(); i++)
    {
        cout << "\n"<< *i ;
    }
    return 0;
}
//thefnoizinwirssl