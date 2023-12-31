#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define MAX_PLAIN_LENGTH 10000
#define MAX_KEY_LENGTH 1000
#define MAX_STEP 16

//Initial Permutation Table
int IP_t[64] = { 58 ,50 ,42 ,34 ,26 ,18 ,10 ,2 , 
				 60 ,52 ,44 ,36 ,28 ,20 ,12 ,4 ,
				 62 ,54 ,46 ,38 ,30 ,22 ,14 ,6 ,
				 64 ,56 ,48 ,40 ,32 ,24 ,16 ,8 ,
				 57 ,49 ,41 ,33 ,25 ,17 ,9  ,1 ,
				 59 ,51 ,43 ,35 ,27 ,19 ,11 ,3 ,
				 61 ,53 ,45 ,37 ,29 ,21 ,13 ,5 ,
				 63 ,55 ,47 ,39 ,31 ,23 ,15 ,7 };
				 
// Expansion D-box Table
int exp_d[64] = { 32, 1, 2, 3, 4, 5, 4, 5,
         		  6, 7, 8, 9, 8, 9, 10, 11,
        		  12, 13, 12, 13, 14, 15, 16, 17,
        		  16, 17, 18, 19, 20, 21, 20, 21,
        		  22, 23, 24, 25, 24, 25, 26, 27,
        		  28, 29, 28, 29, 30, 31, 32, 1};
        		  
// Straight Permutation Table
int per[32] = { 16,  7, 20, 21,
       			29, 12, 28, 17,
       			1, 15, 23, 26,
       			5, 18, 31, 10,
       			2,  8, 24, 14,
       			32, 27,  3,  9,
       			19, 13, 30,  6,
       			22, 11,  4, 25 };

// S-Box Table
int SBox[8][4][16] = {                        
	{
		{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
		{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
		{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
		{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
	},
	{
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
		{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
		{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
		{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
	},
	{
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
		{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
		{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
		{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
	},
	{
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
		{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
		{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
		{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
	},
	{
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
		{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
		{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
		{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
	},
	{
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
		{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
		{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
		{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
	},
	{
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
		{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
		{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
		{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
	},
	{
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
		{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
		{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
		{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
	}
};

// Final Permutation Table
int final_perm[64] = { 	40, 8, 48, 16, 56, 24, 64, 32,
              			39, 7, 47, 15, 55, 23, 63, 31,
              			38, 6, 46, 14, 54, 22, 62, 30,
              			37, 5, 45, 13, 53, 21, 61, 29,
              			36, 4, 44, 12, 52, 20, 60, 28,
             			35, 3, 43, 11, 51, 19, 59, 27,
              			34, 2, 42, 10, 50, 18, 58, 26,
              			33, 1, 41, 9, 49, 17, 57, 25 };

// Parity Bit Drop
int keyp[56] = { 57, 49, 41, 33, 25, 17, 9,
				1, 58, 50, 42, 34, 26, 18,
				10, 2, 59, 51, 43, 35, 27,
    			19, 11, 3, 60, 52, 44, 36,
        		63, 55, 47, 39, 31, 23, 15,
        		7, 62, 54, 46, 38, 30, 22,
        		14, 6, 61, 53, 45, 37, 29,
        		21, 13, 5, 28, 20, 12, 4 };

// Shift Table
int shift_table[16] = { 1, 1, 2, 2,
               		   2, 2, 2, 2,
               		   1, 2, 2, 2,
        			   2, 2, 2, 1 };

// Key compression
int key_comp[48] = { 14, 17, 11, 24, 1, 5,
            		3, 28, 15, 6, 21, 10,
            		23, 19, 12, 4, 26, 8,
            		16, 7, 27, 20, 13, 2,
            		41, 52, 31, 37, 47, 55,
            		30, 40, 51, 45, 33, 48,
            		44, 49, 39, 56, 34, 53,
            		46, 42, 50, 36, 29, 32 };

string dec2bin(int a)
{
	string s;
	char c;
	while (a > 0)
	{
		c = '0' + a%2;
		s = c + s;
		a = a >> 1;
	}
	while (s.length() < 4)
	{
		s = "0" + s;
	}
	return s;
}

int bin2dec(string s)
{
	int n, num;
	num = 0;
	for (n=0; n<s.length(); n++)
	{
		num = num << 1;
		num += (s[n]-'0');
	}
	return num;
}

string dec2hex(int a)
{
	string s;
	char c;
	if (a == 0)
	{
		return "0";
	}
	while (a > 0)
	{
		if (a%16 <= 9)
		{
			c = '0' + a%16;
		}
		else
		{
			c = 'A' + a%16-10;
		}
		s = c + s;
		a = a >> 4;
	}
	return s;
}

int hex2dec(string s)
{
	int n,num;
	num = 0;
	for (n=0; n<s.length(); n++)
	{
		num = num << 4;
		if ((s[n] >= '0') and (s[n] <= '9'))
		{
			num += s[n]-'0';
		}
		else
		{
			num += (s[n]-'A') + 10;
		}
	}
	return num;
}

string bin2hex(string s)
{
	string s2, res;
	int i, n, num;
	for (n=0; n<s.length(); n+=4)
	{
		s2 = "";
		for (i=n; i<n+4; i++)
		{
			s2 += s[i];
		}
		num = bin2dec(s2);
		res += dec2hex(num);
	}
	return res;
}

string hex2bin(string s)
{
	string res, s2;
	int n, num;
	for (n=0; n<s.length(); n++)
	{
		s2 = s[n];
		num = hex2dec(s2);
		s2 = dec2bin(num);
		while(s2.length() < 4)
		{
			s2 = "0" + s2;
		}
		res += s2;
	}
	return res;
}

string permutation(string s, int arr[], int N)
{
	string permutation;
	int n;
	for (n=0; n<N; n++)
	{
		permutation += s[arr[n]-1];
	}
	return permutation;
}

string shift_left(string s, int num_shift)
{
	string s2;
	int n;
	for (n=0; n<s.length(); n++)
	{
		s2 = s2 + s[(n+num_shift)%s.length()];
	}
	return s2;
}

string bin_xor(string bin1, string bin2)
{
	string res;
	int n;
	for (n=0; n<bin1.length(); n++)
	{
		if (bin1[n] == bin2[n])
		{
			res += "0";
		}
		else
		{
			res += "1";
		}
	}
	return res;
}

pair<string, string> split_string(string input)
{
	string left, right;
	int n,i;
	n = input.length();
	for (i=0; i<n/2; i++)
	{
		left += input[i];
		right += input[n/2+i];
	}
	return make_pair(left, right);
}

string encrypt(string plainText, string key)
{
	string plain_left, plain_right, key_left, key_right, rk_bin[16], rk_hex[16], combine_key, round_key, right_expanded, xor_x, sbox_str, bin_row, bin_col, cipherText;
	int n, row, col, val, step, padByte;
	
	plainText = hex2bin(plainText);
	plainText = permutation(plainText, IP_t, 64);
	//cout << "After permutation : " << bin2hex(plainText) << "\n";
	plain_left = split_string(plainText).first;
	plain_right = split_string(plainText).second;
	
	key = hex2bin(key);
	key = permutation(key, keyp, 56);
	key_left = split_string(key).first;
	key_right = split_string(key).second;
	
	for (n=0; n<MAX_STEP; n++)
	{
		key_left = shift_left(key_left, shift_table[n]);
		key_right = shift_left(key_right, shift_table[n]);
		combine_key = key_left + key_right;
		round_key = permutation(combine_key, key_comp, 48);
		rk_bin[n] = round_key;
		rk_hex[n] = bin2hex(round_key);
	}
	
	for (step=0; step<MAX_STEP; step++)
	{
		right_expanded = permutation(plain_right, exp_d, 48);
		xor_x = bin_xor(right_expanded, rk_bin[step]);
		sbox_str = "";
		for (n=0; n<8; n++)
		{
			row = 2*bin2dec(string(1,xor_x[n*6])) + bin2dec(string(1,xor_x[n*6+5]));
			col = 8*bin2dec(string(1,xor_x[n*6+1])) + 4*bin2dec(string(1,xor_x[n*6+2])) + 2*bin2dec(string(1,xor_x[n*6+3])) + bin2dec(string(1,xor_x[n*6+4]));
			val = SBox[n][row][col];
			sbox_str += dec2bin(val);
		}
		sbox_str = permutation(sbox_str, per, 32);
		plain_left = bin_xor(plain_left, sbox_str);
		if (step != MAX_STEP-1)
		{
			swap(plain_left, plain_right);
		}
		cout << "Round " << step+1 << " " << bin2hex(plain_left) << " " << bin2hex(plain_right) << " " << rk_hex[step] << "\n";
	}
	cipherText = plain_left + plain_right;
	cipherText = permutation(cipherText, final_perm, 64);
	cipherText = bin2hex(cipherText);
	return cipherText;
}

string decrypt(string cipherText, string key)
{
	string cipher_left, cipher_right, key_left, key_right, rk_bin[16], rk_hex[16], rk_rev_bin[16], rk_rev_hex[16], combine_key, round_key, right_expanded, xor_x, sbox_str, bin_row, bin_col, result, decryptedText;
	int n, row, col, val, step, padByte;
	
	cipherText = hex2bin(cipherText);
	cipherText = permutation(cipherText, IP_t, 64);
	//cout << "After permutation : " << bin2hex(cipherText) << "\n";
	cipher_left = split_string(cipherText).first;
	cipher_right = split_string(cipherText).second;
	
	key = hex2bin(key);
	key = permutation(key, keyp, 56);
	key_left = split_string(key).first;
	key_right = split_string(key).second;
	
	for (n=0; n<MAX_STEP; n++)
	{
		key_left = shift_left(key_left, shift_table[n]);
		key_right = shift_left(key_right, shift_table[n]);
		combine_key = key_left + key_right;
		round_key = permutation(combine_key, key_comp, 48);
		rk_bin[n] = round_key;
		rk_hex[n] = bin2hex(round_key);
	}
	for (n=0; n<MAX_STEP; n++)
	{
		rk_rev_bin[n] = rk_bin[MAX_STEP-n-1];
		rk_rev_hex[n] = rk_hex[MAX_STEP-n-1];
	}
	
	for (step=0; step<MAX_STEP; step++)
	{
		right_expanded = permutation(cipher_right, exp_d, 48);
		xor_x = bin_xor(right_expanded, rk_rev_bin[step]);
		sbox_str = "";
		for (n=0; n<8; n++)
		{
			row = 2*bin2dec(string(1,xor_x[n*6])) + bin2dec(string(1,xor_x[n*6+5]));
			col = 8*bin2dec(string(1,xor_x[n*6+1])) + 4*bin2dec(string(1,xor_x[n*6+2])) + 2*bin2dec(string(1,xor_x[n*6+3])) + bin2dec(string(1,xor_x[n*6+4]));
			val = SBox[n][row][col];
			sbox_str += dec2bin(val);
		}
		sbox_str = permutation(sbox_str, per, 32);
		cipher_left = bin_xor(cipher_left, sbox_str);
		if (step != MAX_STEP-1)
		{
			swap(cipher_left, cipher_right);
		}
		cout << "Round " << step+1 << " " << bin2hex(cipher_left) << " " << bin2hex(cipher_right) << " " << rk_rev_hex[step] << "\n";
	}
	decryptedText = cipher_left + cipher_right;
	decryptedText = permutation(decryptedText, final_perm, 64);
	decryptedText = bin2hex(decryptedText);
	return decryptedText;
}

int padMessage(string& plainText)
{
	int padByte, n;
	
	padByte = 15-plainText.length()%16;
	plainText += "0";
	//cout << "Before padding : " << plainText << "\n";
	for (n=0; n<padByte; n++)
	{
		if (padByte <= 9)
		{
			plainText += (padByte+'0');
		}
		else
		{
			plainText += (padByte+'A'-10);
		}
	}
	return padByte;
}

void fixKey(string& key)
{
	string subkey;
	int n, i;
	vector<int> numbers;
	vector<int>::iterator itr;
	srand(time(0));
	
	if (key.length() > 16)
	{
		n = key.length();
		for (i=0; i<n; i++)
		{
			numbers.push_back(i);
		}
		random_shuffle(numbers.begin(), numbers.end());
		for (itr = numbers.begin(); itr != numbers.end(); itr++)
		{
			subkey += key[*itr];
			if (subkey.length() == 16)
			{
				break;
			}
		}
		key = subkey;
	}
	else
	{
		while (key.length() < 16)
		{
			n = rand()%16;
			if (n < 10)
			{
				key += (n+'0');
			}
			else
			{
				key += (n+'A'-10);
			}
		}
	}
}

string string_to_hex(string input)
{
    char hex_digits[] = "0123456789ABCDEF";
    char c;
    int i;
    string output;
    output.reserve(input.length() * 2);
    for (i=0; i<input.length(); i++)
    {
    	c = input[i];
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

int hex_value(unsigned char hex_digit)
{
    static const signed char hex_values[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    int value = hex_values[hex_digit];
    if (value == -1) throw std::invalid_argument("invalid hex digit");
    return value;
}

string hex_to_string(string& input)
{
    int len = input.length();
    if (len & 1) throw invalid_argument("odd length");

    string output;
    output.reserve(len / 2);
    string::iterator it;
    for (it = input.begin(); it != input.end(); )
    {
        int hi = hex_value(*it++);
        int lo = hex_value(*it++);
        output.push_back(hi << 4 | lo);
    }
    return output;
}

bool key_valid_check(string& key)
{
	bool isValid = true;
	int n,i;
	n = key.length();
	if (n == 0)
	{
		return false;
	}
	for (i=0; i<n; i++)
	{
		if((key[i] >= '0') and (key[i] <= '9'))
		{
			continue;
		}
		if ((key[i] >= 'a') and (key[i] <= 'f'))
		{
			key[i] = (key[i] - 'a' + 'B');
			continue;
		}
		if ((key[i] >= 'A') and (key[i] <= 'F'))
		{
			continue;
		}
		isValid = false;
		break;
	}
	if (!isValid)
	{
		cout << "Invalid key\n";
	}
	return isValid;
}

int main()
{
	string plainText, hex_plainText, key, cipherText, hex_decryptedText, decryptedText, message;
	int i, padByte, n;
	char char_plainText[MAX_PLAIN_LENGTH], char_key[MAX_KEY_LENGTH];
	
	while(1)
	{
		//plainText = "Heinto World";
		plainText = "";
		cout << "Plain text : ";
		cin.getline (char_plainText, MAX_PLAIN_LENGTH);
		plainText = char_plainText;
		
		//key = "133457799BDFFFFF125";
		key = "";
		while (!key_valid_check(key))
		{
			cout << "Key : ";
			cin.getline(char_key, MAX_KEY_LENGTH);
			key = char_key;
		}
		cout << "\n\n";
		
		cout << "Message            : " << plainText << "\n";
		hex_plainText = string_to_hex(plainText);
		cout << "Hex Message        : " << hex_plainText << "\n";
		padByte = padMessage(hex_plainText);
	
		fixKey(key);
		cout << "Key                : " << key << "\n";
		
		cipherText = "";
		for (i=0; i<hex_plainText.length(); i+=16)
		{
			message = hex_plainText.substr(i,16);
			cipherText += encrypt(message, key);
		}
		cout << "Cipher Text        : " << cipherText << "\n";
		
		hex_decryptedText = "";
		for (i=0; i<cipherText.length(); i+=16)
		{
			message = cipherText.substr(i,16);
			hex_decryptedText += decrypt(message, key);
		}
		hex_decryptedText = hex_decryptedText.substr(0, hex_decryptedText.length()-padByte-1);
		cout << "Decrypted Hex Text : " << hex_decryptedText << "\n";
		
		decryptedText = hex_to_string(hex_decryptedText);
		cout << "Decrypted Text     : " << decryptedText << "\n\n\n";
		
		memset(char_plainText, '\0', sizeof(char_plainText)); 
		memset(char_key, '\0', sizeof(char_key)); 
	}
}
