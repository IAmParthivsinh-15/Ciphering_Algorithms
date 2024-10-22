#include<bits/stdc++.h>
using namespace std;

// Afine Cipher
int inverse(string str , int b){
    int r1 = 26;
    int r2 = b;
    int t1 = 0;
    int t2 = 1;
    while(r2 > 0){
        int q = r1 / r2;
        int r = r1 - q * r2 ;
        r1 = r2 ;
        r2 = r ;
        int t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
    if( r1 == 1){
        return (t1+26)%26 ;
    }
    return 0;
}

string decAffine(string str , int a , int b){
    int bInv = inverse(str,a);

    string decryptedStr = "";
    for(int i = 0 ; i < str.length() ; i++){
        char c = str[i];
        int decChar = bInv*((c - 'a') - b)%26;
        decryptedStr += char((decChar+26)%26 + 'a');
    }

    return decryptedStr;
}

void encAffine(string str , int a , int b){
    string encryptedStr = "";

    for(int i = 0 ; i  < str.size() ; i++){
        char c = str[i];
        int encryptedChar = (a * (c - 'a') + b) % 26;
        encryptedStr += char(encryptedChar + 'a');
    }

    cout << encryptedStr << endl;
    string decryptedstr = decAffine(encryptedStr,a,b);
    cout << decryptedstr << endl;
}


// feistel

vector<string> rounds(const string& l0, const string& r0, const string& key) {
    string r1;
    for (size_t i = 0; i < key.size(); ++i) {
        r1 += (key[i] - '0') ^ (r0[i] - '0') ^ (l0[i] - '0') ? '1' : '0';
    }
    string l1 = r0;
    return {l1, r1};
}

vector<string> convertToBinary(const string& pt) {
    vector<string> bin;
    for (char c : pt) {
        bitset<8> b(c);
        bin.push_back(b.to_string());
    }
    return bin;
}

char convertToAscii(const string& bin) {
    return static_cast<char>(stoi(bin, nullptr, 2));
}

string encryptText(const string& plainText, const vector<string>& keys, int krounds) {
    string cipherText;
    vector<string> bin = convertToBinary(plainText);

    for (const string& b : bin) {
        string l0 = b.substr(0, b.size() / 2);
        string r0 = b.substr(b.size() / 2);

        for (int j = 0; j < krounds; ++j) {
            auto lr = rounds(l0, r0, keys[j]);
            l0 = lr[0];
            r0 = lr[1];
        }

        cipherText += convertToAscii(r0 + l0);
    }

    return cipherText;
}

string decryptText(const string& cipherText, const vector<string>& keys, int krounds) {
    string plainText;
    vector<string> bin = convertToBinary(cipherText);

    for (const string& b : bin) {
        string l0 = b.substr(0, b.size() / 2);
        string r0 = b.substr(b.size() / 2);

        int keyNum = keys.size() - 1;
        for (int j = 0; j < krounds; ++j) {
            auto lr = rounds(l0, r0, keys[keyNum]);
            l0 = lr[0];
            r0 = lr[1];
            keyNum--;
        }

        plainText += convertToAscii(r0 + l0);
    }

    return plainText;
}

vector<string> generateRandomKeys(int length, int numKeys) {
    vector<string> keys;
    srand(time(0)); 

    for (int i = 0; i < numKeys; ++i) {
        string key;
        for (int j = 0; j < length; ++j) {
            key += rand() % 2 == 0 ? '0' : '1';
        }
        keys.push_back(key);
    }

    return keys;
}

int main() {
    string str;
    cout << "Enter Your String for Affine Cipher: ";
    cin >> str;
    int a, b;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;

    encAffine(str, a, b);  
    cout << endl;

    cout << "Feistel Cipher" << endl;
    
    string plainText = "test";
    int krounds = 2;
    int keyLength = 4;
    
    vector<string> keys = generateRandomKeys(keyLength, 2);

    cout << "Generated Keys: ";
    for (auto& key : keys) {
        cout << key << " ";
    }
    cout << endl;

    string enc = encryptText(plainText, keys, krounds);  
    cout << "Encrypted Text (Feistel): " << enc << endl;

    string dec = decryptText(enc, keys, krounds);
    cout << "Decrypted Text (Feistel): " << dec << endl;

    return 0;
}


