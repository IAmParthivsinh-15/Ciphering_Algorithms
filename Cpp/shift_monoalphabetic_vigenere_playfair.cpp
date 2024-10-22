#include <bits/stdc++.h>
using namespace std;

void ShiftCipher(string str , int k){
    
    string str2 = "";

    for(int i = 0; i < str.size(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str2 += (str[i] - 'a' + k) % 26 + 'a';
        }
        else if(str[i] >= 'A' && str[i] <= 'Z'){
            str2 += (str[i] - 'A' + k) % 26 + 'A';
        }
    }
    
    cout << endl;
    cout << "Cipher Text For K=3 : " << str2 << endl;
    
    string ans1 = "" ;
    
    for(int i = 0 ; i < str2.size() ; i++){
        if (str2[i] >= 'a' && str2[i] <= 'z') {
            ans1 += (str2[i] - 'a' - k+26) % 26 + 'a';
        }
        else if(str2[i] >= 'A' && str2[i] <= 'Z'){
            ans1 += (str2[i] - 'A' - k+26) % 26 + 'A';
        }
    }
    
    cout << "Decryption Of Str1 :" << ans1;
    
    
}


void monoalphabeticDecrypt(string& cipherText) {
    const vector<char> relfreqs = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'C', 'U', 'M', 'W', 'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'J', 'X', 'Q', 'Z'};
    
    string text = cipherText;
    transform(text.begin(), text.end(), text.begin(), ::tolower);  
    
    map<char, int> freqMap; 

    for (char ch : text) {
        if (isalpha(ch)) {
            freqMap[ch]++;
        }
    }

    vector<pair<char, int>> frequencyArray(freqMap.begin(), freqMap.end());
    sort(frequencyArray.begin(), frequencyArray.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return b.second < a.second;
    });

    for(auto &it : frequencyArray){
        cout << it.first << " " << it.second << endl;
    }

    map<char, char> substitutionMap; 
    int size = min(frequencyArray.size(), relfreqs.size());
    for (int i = 0; i < size; ++i) {
        substitutionMap[frequencyArray[i].first] = tolower(relfreqs[i]);
    }

    string decryptedText;
    for (char ch : text) {
        if (isalpha(ch)) {
            decryptedText += substitutionMap.count(ch) ? substitutionMap[ch] : ch;
        } else {
            decryptedText += ch;
        }
    }

    cout << decryptedText << endl;
}

void Vigenere(string str, string key) {
    int n = str.size();
    int k = key.size();
    string str2 = "";

    for (int i = 0; i < n; i++) {
        key += key[i % k];
    }

    cout << "Extended key: " << key.substr(0, n) << endl;

    string encryptedString = "";

    for (int i = 0; i < n; i++) {
        char ch1 = str[i] - 'A';
        char ch2 = key[i] - 'A'; 
        char ch = (ch1 + ch2) % 26 + 'A'; 
        encryptedString += ch;
    }

    cout << "Encrypted String: " << encryptedString << endl;

    string decryptedString = "";

    for (int i = 0; i < n; i++) {
        char ch1 = encryptedString[i] - 'A';
        char ch2 = key[i] - 'A';
        char ch = (ch1 - ch2 + 26) % 26 + 'A'; 
        decryptedString += ch;
    }

    cout << "Decrypted String: " << decryptedString << endl;
}


pair<int, int> findElement(vector<vector<char>>& matrix, char target) {
    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < matrix[row].size(); ++col) {
            if (matrix[row][col] == target) {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}



// Helper function to find the position of a character in the Playfair table
pair<int, int> findElement(const vector<vector<char>>& table, char ch) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (table[i][j] == ch) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; 
}

void decryptPlayFair(string str, string key) {
    cout << endl;
    vector<vector<char>> table(5, vector<char>(5, ' '));
    unordered_set<char> visited;
    int index = 0;
    int last1 = 0, last2 = 0;

    for (auto ch : key) {
        if (visited.find(ch) == visited.end() && index < 25) {
            table[index / 5][index % 5] = ch;
            visited.insert(ch);
            index++;
            last1 = index / 5;
            last2 = index % 5;
        }
    }

    for (char i = 'A'; i <= 'Z'; i++) {
        if (i != 'J' && visited.find(i) == visited.end()) {
            table[last1][last2] = i;
            last2++;
            if (last2 == 5) {
                last2 = 0;
                last1++;
            }
            if (last1 == 5) {
                break;
            }
        }
    }

    string decryptedString = "";
    for (int i = 0; i < str.size() - 1; i += 2) {
        pair<int, int> p1 = findElement(table, str[i]);
        pair<int, int> p2 = findElement(table, str[i + 1]);

        if (p1.second == p2.second) {
            int row1 = (p1.first - 1 + 5) % 5;
            int row2 = (p2.first - 1 + 5) % 5;
            decryptedString += table[row1][p1.second];
            decryptedString += table[row2][p2.second];
        } else if (p1.first == p2.first) {
            int col1 = (p1.second - 1 + 5) % 5;
            int col2 = (p2.second - 1 + 5) % 5;
            decryptedString += table[p1.first][col1];
            decryptedString += table[p2.first][col2];
        } else {
            decryptedString += table[p1.first][p2.second];
            decryptedString += table[p2.first][p1.second];
        }
    }

    cout << "Playfair Decrypted: " << decryptedString << endl;
}

void playFair(string str, string key) {
    vector<vector<char>> table(5, vector<char>(5, ' '));
    unordered_set<char> visited;
    int index = 0;
    int last1 = 0, last2 = 0;

    for (auto ch : key) {
        if (visited.find(ch) == visited.end() && index < 25) {
            table[index / 5][index % 5] = ch;
            visited.insert(ch);
            index++;
            last1 = index / 5;
            last2 = index % 5;
        }
    }

    for (char i = 'A'; i <= 'Z'; i++) {
        if (i != 'J' && visited.find(i) == visited.end()) {
            table[last1][last2] = i;
            last2++;
            if (last2 == 5) {
                last2 = 0;
                last1++;
            }
            if (last1 == 5) {
                break;
            }
        }
    }

    string mainString = "";
    for (int i = 0; i < str.size(); i += 2) {
        if (i + 1 < str.size() && str[i] != str[i + 1]) {
            mainString += str[i];
            mainString += str[i + 1];
        } else {
            mainString += str[i];
            mainString += (str[i] == 'X' ? 'A' : 'X');  
        }
    }

    if (mainString.size() % 2 != 0) {
        mainString += (mainString.back() == 'Z' ? 'A' : 'Z');  
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    string encryptedString = "";
    for (int i = 0; i < mainString.size() - 1; i += 2) {
        pair<int, int> p1 = findElement(table, mainString[i]);
        pair<int, int> p2 = findElement(table, mainString[i + 1]);

        if (p1.second == p2.second) {
            int row1 = (p1.first + 1) % 5;
            int row2 = (p2.first + 1) % 5;
            encryptedString += table[row1][p1.second];
            encryptedString += table[row2][p2.second];
        } else if (p1.first == p2.first) {
            int col1 = (p1.second + 1) % 5;
            int col2 = (p2.second + 1) % 5;
            encryptedString += table[p1.first][col1];
            encryptedString += table[p2.first][col2];
        } else {
            encryptedString += table[p1.first][p2.second];
            encryptedString += table[p2.first][p1.second];
        }
    }

    cout << "Playfair Encrypted: " << encryptedString << endl;

    decryptPlayFair(encryptedString, key);
}

int main() {
    string str;
    cout << "Enter Original String ShiftCipher : " ;
    cin >> str;
    string key;
    cout << "Enter  Key : " ;
    cin >> key;
    ShiftCipher(str,3);

    cout << endl;

    string strv;
    cout << "Enter Original String Vigener : " ;
    cin >> strv;
    string keyv;
    cout << "Enter  Key : " ;
    cin >> keyv;
    Vigenere(strv,keyv);

    cout << endl;


    string strpf;
    cout << "Enter Original String PlayFair : " ;
    cin >> strpf;
    string keypf;
    cout << "Enter  Key pf: " ;
    cin >> key;
    playFair(strpf,keypf);

    cout << endl;

    // playFair(str , key);
    string strm;
    cout << "Enter Original String mono : " ;
    cin >> strm;

    // monoalpha
    monoalphabeticDecrypt(strm);

   
    return 0;
}


/*





*/