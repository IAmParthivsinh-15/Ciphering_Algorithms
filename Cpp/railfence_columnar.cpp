#include <bits/stdc++.h>
using namespace std;

string decryptRailfence(string str, int k)
{
    int n = str.length();
    vector<vector<char>> rail(k, vector<char>(n, 0));

    for (int r = 0, c = 0, d = 1; c < n; c++)
    {
        rail[r][c] = '*';
        r += d;
        if (r == k - 1)
            d = -1;
        else if (r == 0)
            d = 1;
    }

    int count = 0;
    for(int r = 0 ; r < k ; r++){
        for(int c = 0 ;  c < n ; c++){
            if(rail[r][c] == '*'){
                rail[r][c] = str[count++];
            }
        }
    }

    string decryptedString = "";
    for (int r = 0, c = 0, d = 1; c < n; c++)
    {
        decryptedString += rail[r][c];
        r += d;
        if (r == k - 1)
            d = -1;
        else if (r == 0)
            d = 1;
    }

    return decryptedString;
}


void RailFence(string str, int k)
{
    int n = str.length();
    vector<vector<char>> rail(k, vector<char>(n, 0));

    // Encryption
    for (int r = 0, c = 0, d = 1; c < n; c++)
    {
        rail[r][c] = str[c];
        r += d;
        if (r == k - 1)
            d = -1;
        else if (r == 0)
            d = 1;
    }

    string encryptedString = "";

    for (auto &i : rail)
    {
        for (auto &j : i)
        {
            if (j != 0)
                encryptedString += j;
        }
    }

    cout << encryptedString << endl;

    // Decryption

    string decryptedString = decryptRailfence(encryptedString, k);

    cout << decryptedString << endl;
}

//==================================================COLUMNAR CIPHER===================================================


string decryptColumnarCipher(string str, string key)
{
    int numRows = (str.length() + key.length() - 1) / key.length(); 
    int numCols = key.length(); 

    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < numCols; i++)
    {
        keyOrder.push_back({key[i], i});
    }

    sort(keyOrder.begin(), keyOrder.end());
 
    vector<vector<char>> matrix(numRows, vector<char>(numCols, ' '));
    int index = 0;
    for (auto &k : keyOrder)
    {
        int col = k.second;
        for (int r = 0; r < numRows; r++)
        {
            matrix[r][col] = str[index++];
        }
    }

    string decryptedStr = "";
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
        {
            if (matrix[r][c] != 'X') 
                decryptedStr += matrix[r][c];
        }
    }

    return decryptedStr;
}

void encryptColumnarCipher(string plaintext, string key)
{
    int numRows = (plaintext.length() + key.length() - 1) / key.length(); 
    int numCols = key.length(); 

    
    vector<vector<char>> matrix(numRows, vector<char>(numCols, ' '));

    int index = 0;
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
        {
            if (index < plaintext.length())
                matrix[r][c] = plaintext[index++];
            else
                matrix[r][c] = 'X'; 
        }
    }

    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < numCols; i++)
    {
        keyOrder.push_back({key[i], i});
    }

    sort(keyOrder.begin(), keyOrder.end());

    string ciphertext = "";
    for (auto &k : keyOrder)
    {
        int col = k.second;
        for (int r = 0; r < numRows; r++)
        {
            ciphertext += matrix[r][col];
        }
    }

    cout << ciphertext << endl;
    string decryptedStr = decryptColumnarCipher(ciphertext,key) ;
    cout << decryptedStr << endl;
}


int main()
{
    string str;
    cout << "Enter Plain Text : ";
    cin >> str;
    int k;
    cout << "Enter number of rails : ";
    cin >> k;
    RailFence(str, 4);


    cout << "\n columner" << endl;
    string str1;
    cout << "Enter Plain Text : ";
    cin >> str1;
    string key;
    cout << "Enter key : ";
    cin >> key;
    encryptColumnarCipher(str1,key);
    return 0;
}
