#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> round_keys(16, vector<int>(48));


// Permutation Tables

// Initial Permutations
const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutations
const int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};


//Expansion-P Box
const int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Parity Drop Table
int PC1[56] = {
    57,49,41,33,25,17,9,1,
    58,50,42,34,26,18,10,2,
    59,51,43,35,27,19,11,3,
    60,52,44,36,63,55,47,39,
    31,23,15,7,62,54,46,38,
    30,22,14,6,61,53,45,37,
    29,21,13,5,28,20,12,4
};


// Compression P-Box
const int PC2[48] = {
    14,17,11,24,1,5,3,28,
    15,6,21,10,23,19,12,4,
    26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,
    51,45,33,48,44,49,39,56,
    34,53,46,42,50,36,29,32
};

// 1,2,9,16 - one shift
const int shifts_per_round[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// S-Boxes
const int S_BOXES[8][4][16] = {
    // S-box 1
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 11, 3, 15, 12, 9, 7, 5, 0, 6, 10},
        {1, 15, 6, 8, 13, 11, 3, 4, 7, 9, 5, 12, 0, 14, 10, 2}
    },
    // S-box 2
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 15, 2},
        {12, 7, 6, 5, 10, 15, 13, 8, 9, 1, 3, 14, 0, 11, 4, 2}
    },
    // S-box 3
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 8, 2, 4},
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 9, 1, 14, 10},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2}
    },
    // S-box 4
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 9, 1, 14, 10},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {14, 7, 11, 6, 0, 9, 10, 1, 5, 3, 12, 8, 2, 13, 15, 4}
    },
    // S-box 5
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15}
    },
    // S-box 6
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 14, 5, 11, 7, 4},
        {2, 7, 12, 1, 10, 6, 15, 13, 8, 9, 11, 5, 3, 14, 4, 0},
        {4, 11, 2, 14, 15, 0, 8, 13, 9, 5, 7, 12, 3, 10, 1, 6},
        {11, 8, 12, 2, 4, 7, 1, 14, 10, 15, 6, 0, 9, 3, 5, 13}
    },
    // S-box 7
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 9, 5, 7, 12, 3, 10, 1, 6},
        {11, 8, 12, 2, 4, 7, 1, 14, 10, 15, 6, 0, 9, 3, 5, 13},
        {0, 9, 4, 7, 6, 10, 11, 15, 8, 12, 2, 5, 13, 14, 1, 3},
        {1, 8, 12, 5, 9, 0, 15, 2, 14, 7, 13, 10, 3, 4, 6, 11}
    },
    // S-box 8
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 14, 9, 10, 1, 3, 11, 5, 12, 6, 8, 13, 15, 0, 2, 4},
        {10, 5, 9, 12, 3, 7, 8, 1, 2, 6, 11, 0, 13, 14, 15, 4}
    }
};

// Straight Permutation function P
const int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// Initial Permutation function IP
vector<int> permute(const vector<int>& input, const int* table, int size) {
    vector<int> output(size);
    for (int i = 0; i < size; ++i) {
        output[i] = input[table[i] - 1];
    }
    return output;
}

vector<vector<int>> key_schedule(const vector<int>& key) {
    vector<int> permuted_key = permute(key, PC1, 56);
    vector<int> left_half(permuted_key.begin(), permuted_key.begin() + 28);
    vector<int> right_half(permuted_key.begin() + 28, permuted_key.end());
    int temp = 1;
    for (int i = 0; i < 16; ++i) {
        rotate(left_half.begin(), left_half.begin() + shifts_per_round[i], left_half.end());
        rotate(right_half.begin(), right_half.begin() + shifts_per_round[i], right_half.end());

        vector<int> combined_key(left_half);
        combined_key.insert(combined_key.end(), right_half.begin(), right_half.end());

        // cout << "combined : " << temp++ << " ";
        // for(auto c : combined_key){
        //     cout << c ;
        // }
        // cout << endl;

        round_keys[i] = permute(combined_key, PC2, 48);
    }
    // cout << "keys started" << endl;

    // for(auto i : round_keys){
    //     for(auto j : i){
    //         cout << j ;
    //     }
    //     cout << endl;
    // }
    // cout << "keys done" << endl;


    return round_keys;
}

vector<int> s_box_substitution(const vector<int>& input) {
    vector<int> output(32);
    for (int i = 0; i < 8; ++i) {
        vector<int> block(input.begin() + i * 6, input.begin() + (i + 1) * 6);
        int row = (block[0] << 1) | block[5];
        int col = (block[1] << 3) | (block[2] << 2) | (block[3] << 1) | block[4];
        int s_value = S_BOXES[i][row][col];
        for (int j = 0; j < 4; ++j) {
            output[i * 4 + j] = (s_value >> (3 - j)) & 1;
        }
    }
    return output;
}

// XOR operation for vectors
vector<int> xor_vectors(const vector<int>& a, const vector<int>& b) {
    vector<int> result(a.size());
    for (int i = 0; i < a.size(); ++i) {
        result[i] = a[i] ^ b[i];
    }
    return result;
}

// Round Function
vector<int> des_round(const vector<int>& left, const vector<int>& right, const vector<int>& subkey) {
    vector<int> expanded_right = permute(right, E, 48);
    vector<int> xor_result = xor_vectors(expanded_right, subkey);
    vector<int> s_box_result = s_box_substitution(xor_result);
    return permute(s_box_result, P, 32);
}

vector<int> des_encrypt(const vector<int>& plaintext, const vector<int>& key) {
    vector<int> ip_plaintext = permute(plaintext, IP, 64);
    vector<int> left(ip_plaintext.begin(), ip_plaintext.begin() + 32);
    vector<int> right(ip_plaintext.begin() + 32, ip_plaintext.end());

    vector<vector<int>> round_keys = key_schedule(key);

    for (int i = 0; i < 16; ++i) {
        vector<int> new_right = xor_vectors(left, des_round(left, right, round_keys[i]));
        left = right;
        right = new_right;
    }

    vector<int> combined(right);
    combined.insert(combined.end(), left.begin(), left.end());

    return permute(combined, FP, 64);
}

vector<int> des_decrypt(const vector<int>& ciphertext, const vector<int>& key) {
    vector<int> ip_ciphertext = permute(ciphertext, IP, 64);
    vector<int> left(ip_ciphertext.begin(), ip_ciphertext.begin() + 32);
    vector<int> right(ip_ciphertext.begin() + 32, ip_ciphertext.end());

    vector<vector<int>> round_keys = key_schedule(key);

    for (int i = 15; i >= 0; --i) {
        vector<int> new_right = xor_vectors(left, des_round(left, right, round_keys[i]));
        left = right;
        right = new_right;
    }

    vector<int> combined(right);
    combined.insert(combined.end(), left.begin(), left.end());

    return permute(combined, FP, 64);
}

vector<int> string_to_vector(const string& str) {
    vector<int> vec;
    for (char ch : str) {
        bitset<8> bits(ch);  
        for (int i = 7; i >= 0; --i) { 
            vec.push_back(bits[i]);
        }
    }
    return vec;
}

string binaryToASCII(const string& binaryStr) {
    string result;

    for (int i = 0; i < binaryStr.length(); i += 8) {
        string byte = binaryStr.substr(i, 8);
        int decimalValue = 0;
        for (int j = 0; j < 8; j++) {
            if (byte[j] == '1') {
                decimalValue += (1 << (7 - j)); 
            }
        }

        char ac = static_cast<char>(decimalValue);
        result += ac;
    }

    return result;
}

int main() {
    string key;  
    cout << "Key : ";
    cin >> key;

    string plaintext;
    cout << "PlainText : ";
    cin >> plaintext;

    vector<int> key_vector = string_to_vector(key);
    vector<int> plaintext_vector = string_to_vector(plaintext);

    cout << "Key (Binary): ";
    for(auto i : key_vector) cout << i ;
    cout << endl;

    cout << "PlainText (Binary): ";
    for(auto i : plaintext_vector) cout << i;
    cout << endl;

    vector<int> ciphertext = des_encrypt(plaintext_vector, key_vector);
    vector<int> decrypted = des_decrypt(ciphertext, key_vector);

    string ct = "", dt = "";
    
    cout << "Ciphertext (Binary): ";
    for (int bit : ciphertext) {
        cout << bit;
        ct += (bit == 1 ? '1' : '0'); 
    }
    cout << endl;
    
    cout << "Decrypted (Binary): ";
    for (int bit : decrypted) {
        cout << bit;
        dt += (bit == 1 ? '1' : '0'); 
    }
    cout << endl;

    cout << "Decrypted ASCII: " << binaryToASCII(dt) << endl;

    return 0;
}
