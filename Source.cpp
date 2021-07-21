#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

string message;
string mappedKey;

string Affine_decryption(string, int, int);
string Affine_encryption(string,int,int);
string caesar_Encipher(string, int);
string caesar_Decipher(string, int);
string originalText(string , string );
string generateKey(string , string );
string cipherText(string, string);
string VcipherEncryption(string, string);
string VcipherDecryption(string, string);
void messageAndKey(string, string);
void encryptByPlayfairCipher(char[], char[]);
void decryptByPlayfairCipher(char[], char[]);

int main(int argc, char** argv)
{
	string caesar_encrypted, Affine_encrypted, Affine_decrypted, vencrypted;
	char str[30];
	char key[30];
	//char encryptedpf[30];
	cout << "======================================\nOriginal Text is: mohamed\n";
	//Encrypt With Caesar
	cout << "======================================\n";
	cout << "Caesar Encrypted Text is: " <<caesar_Encipher("mohamed", 3) << "\n";
	cout << "======================================\n";
	//Saving the caesar encryption in a var
	caesar_encrypted = caesar_Encipher("mohamed", 3);
	//encrypt with Affine encryption
	cout << "Affine Encryption is: " << Affine_encryption(caesar_encrypted,5,6) << "\n";
	cout << "======================================\n";
	//Saving Affine encrypted text in a var
	Affine_encrypted = Affine_encryption(caesar_encrypted,5,6);
	//Simple shift vignere
	//string vkey = generateKey("mohamed", "key");
	//string cipher = cipherText("mohamed", "key");
	//Simple Shift Decryption
	//string dkey = generateKey(cipher, "key");
	//string original = originalText(cipher, dkey);
	//Vignere Encryption
	messageAndKey(Affine_encrypted, "kemo");
	cout << "Encryption of Vignere: " << VcipherEncryption(message, mappedKey) << "\n";
	cout << "======================================\n";
	//Playfair Encryption
	strcpy_s(key, "kemo");
	strcpy_s(str, "NRQJNTW");
	encryptByPlayfairCipher(str, key);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 32;
		}
	}
	printf("PLayfair Encrypted text: %s\n", str);
	cout << "======================================\n";
	//Playfair Decryption
	strcpy_s(str, "itrhtyxv");
	decryptByPlayfairCipher(str, key);
	str[strlen(str) - 1] = '\0';
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 32;
		}
	}
	printf("Playfair decrypted text: %s\n", str);
	cout << "======================================\n";
	//Vignere Decryption
	messageAndKey(VcipherEncryption(message, mappedKey), "kemo");
	cout << "Decryption of Vignere: " << VcipherDecryption(message, mappedKey) << "\n";
	cout << "======================================\n";
	//Decrypt with Affine
	cout << "Decryption of Affine: " << Affine_decryption(Affine_encrypted,5,6) << "\n";
	cout << "======================================\n";
	//Save Decrypted text
	Affine_decrypted = Affine_decryption(Affine_encrypted,5,6);
	//decrypt with caesar
    cout << "Caesar Decryption of the previous cipher is: " << caesar_Decipher(Affine_decrypted, 3) << "\n";
	cout << "======================================\n";
    return 0;
}
void messageAndKey(string msg, string key) {
	//message to uppercase
	for (int i = 0; i < msg.length(); i++) {
		msg[i] = toupper(msg[i]);
	}

	
	//key to uppercase
	for (int i = 0; i < key.length(); i++) {
		key[i] = toupper(key[i]);
	}

	//mapping key to message
	string keyMap = "";
	for (int i = 0, j = 0; i < msg.length(); i++) {
		if (msg[i] == 32) {
			keyMap += 32;
		}
		else {
			if (j < key.length()) {
				keyMap += key[j];
				j++;
			}
			else {
				j = 0;
				keyMap += key[j];
				j++;
			}
		} //if-else
	} //for

//    cout << msg << "\n" << keyMap;
	message = msg;
	mappedKey = keyMap;
}

//Creating Vignere Table
int tableArr[26][26];
void createVigenereTable() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			int temp;
			if ((i + 65) + j > 90) {
				temp = ((i + 65) + j) - 26;

				//adding ASCII of alphabet letter in table index position
				tableArr[i][j] = temp;
			}
			else {
				temp = (i + 65) + j;

				//adding ASCII of alphabet letter in table index position
				tableArr[i][j] = temp;
			}
		} // for j loop
	} // for i loop
}

string VcipherEncryption(string message, string mappedKey) {
	createVigenereTable();
	string encryptedText = "";
	for (int i = 0; i < message.length(); i++) {
		if (message[i] == 32 && mappedKey[i] == 32) {
			encryptedText += " ";
		}
		else {
			int x = (int)message[i] - 65;
			int y = (int)mappedKey[i] - 65;
			encryptedText += (char)tableArr[x][y];
		}
	}
	return encryptedText;
}

// for Vignere cipher
int itrCount(int key, int msg) {
	int counter = 0;
	string result = "";

	//starting from ASCII of letter of Key and ending at letter of message
	// to get full 26 letters of alphabet
	for (int i = 0; i < 26; i++) {
		if (key + i > 90) {
			result += (char)(key + (i - 26));
		}
		else {
			result += (char)(key + i);
		}
	} //for

	for (int i = 0; i < result.length(); i++) {
		if (result[i] == msg) {
			break;
		}
		else {
			counter++;
		}
	}
	return counter;
}

string VcipherDecryption(string message, string mappedKey) {
	string decryptedText = "";
	for (int i = 0; i < message.length(); i++) {
		if (message[i] == 32 && mappedKey[i] == 32) {
			decryptedText += " ";
		}
		else {
			int temp = itrCount((int)mappedKey[i], (int)message[i]);
			decryptedText += (char)(65 + temp);
		}
	}

	return decryptedText;
}

string caesar_Encipher(string message, int key)
{
	char ch;
	for (int i = 0; message[i] != '\0'; ++i) {
		ch = message[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch + key;
			if (ch > 'z') {
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			ch = ch + key;
			if (ch > 'Z') {
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	}
	return message;
}

string caesar_Decipher(string message, int key)
{
	char ch;
	for (int i = 0; message[i] != '\0'; ++i) {
		ch = message[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch - key;
			if (ch < 'a') {
				ch = ch + 'z' - 'a' + 1;
			}
			message[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			ch = ch - key;
			if (ch > 'a') {
				ch = ch + 'Z' - 'A' + 1;
			}
			message[i] = ch;
		}
	}
	return message;
}

string Affine_encryption(string plain_text, int key1, int key2) {
	string cipher_text = "";
	for (int i = 0; i < plain_text.size(); i++) {
		if (isupper(plain_text[i])) {
			cipher_text += char((key1 * int(plain_text[i] - 65) + key2) % 26 + 65);
		}
		else {
			cipher_text += char((key1 * int(plain_text[i] - 97) + key2) % 26 + 97);
		}
	}
	return cipher_text;
}

int modInverse(int k) {
	for (int i = 0; i < 26; i++) {
		int flag = (i * k) % 26;
		if (flag == 1) {
			return i;
		}
	}
	return -1;
}

string Affine_decryption(string cipher_text, int key1, int key2) {
	string plain_text = "";
	int key_inverse = modInverse(key1);
	if (key_inverse == -1) {
		return "Not exist";
	}
	//cout << "Key Inverse: " << key_inverse << endl;
	for (int i = 0; i < cipher_text.size(); i++) {
		if (isupper(cipher_text[i])) {
			plain_text += char(((((cipher_text[i] - 65 - key2) % 26 + 26) % 26) * key_inverse) % 26 + 65);
		}
		else {
			plain_text += char(((((cipher_text[i] - 97 - key2) % 26 + 26) % 26) * key_inverse) % 26 + 97);
		}
	}
	return plain_text;
}

void toLowerCase(char plain[], int ps)
{
	int i;
	for (i = 0; i < ps; i++) {
		if (plain[i] > 64 && plain[i] < 91)
			plain[i] += 32;
	}
}

// Function to remove all spaces in a string
int removeSpaces(char* plain, int ps)
{
	int i, count = 0;
	for (i = 0; i < ps; i++)
		if (plain[i] != ' ')
			plain[count++] = plain[i];
	plain[count] = '\0';
	return count;
}

// Function to generate the 5x5 key square
void generateKeyTable(char key[], int ks, char keyT[5][5])
{
	int i, j, k, flag = 0, * dicty;

	// a 26 character hashmap
	// to store count of the alphabet
	dicty = (int*)calloc(26, sizeof(int));
	for (i = 0; i < ks; i++) {
		if (key[i] != 'j')
			dicty[key[i] - 97] = 2;
	}

	dicty['j' - 97] = 1;

	i = 0;
	j = 0;

	for (k = 0; k < ks; k++) {
		if (dicty[key[k] - 97] == 2) {
			dicty[key[k] - 97] -= 1;
			keyT[i][j] = key[k];
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}

	for (k = 0; k < 26; k++) {
		if (dicty[k] == 0) {
			keyT[i][j] = (char)(k + 97);
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
}

// Function to search for the characters of a digraph
// in the key square and return their position
void search(char keyT[5][5], char a, char b, int arr[])
{
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';

	for (i = 0; i < 5; i++) {

		for (j = 0; j < 5; j++) {

			if (keyT[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyT[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}

// Function to find the modulus with 5
int mod5(int a)
{
	return (a % 5);
}

// Function to make the plain text length to be even
int prepare(char str[], int ptrs)
{
	if (ptrs % 2 != 0) {
		str[ptrs++] = 'z';
		str[ptrs] = '\0';
	}
	return ptrs;
}

// Function for performing the encryption
void encrypt(char str[], char keyT[5][5], int ps)
{
	int i, a[4];

	for (i = 0; i < ps; i += 2) {

		search(keyT, str[i], str[i + 1], a);

		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][mod5(a[1] + 1)];
			str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
		}
		else if (a[1] == a[3]) {
			str[i] = keyT[mod5(a[0] + 1)][a[1]];
			str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
		}
		else {
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

// Function to encrypt using Playfair Cipher
void encryptByPlayfairCipher(char str[], char key[])
{
	char ps, ks, keyT[5][5];

	// Key
	ks = strlen(key);
	ks = removeSpaces(key, ks);
	toLowerCase(key, ks);

	// Plaintext
	ps = strlen(str);
	toLowerCase(str, ps);
	ps = removeSpaces(str, ps);

	ps = prepare(str, ps);

	generateKeyTable(key, ks, keyT);

	encrypt(str, keyT, ps);
}

void decrypt(char str[], char keyT[5][5], int ps)
{
	int i, a[4];
	for (i = 0; i < ps; i += 2) {
		search(keyT, str[i], str[i + 1], a);
		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][mod5(a[1] - 1)];
			str[i + 1] = keyT[a[0]][mod5(a[3] - 1)];
		}
		else if (a[1] == a[3]) {
			str[i] = keyT[mod5(a[0] - 1)][a[1]];
			str[i + 1] = keyT[mod5(a[2] - 1)][a[1]];
		}
		else {
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

// Function to call decrypt
void decryptByPlayfairCipher(char str[], char key[])
{
	char ps, ks, keyT[5][5];

	// Key
	ks = strlen(key);
	ks = removeSpaces(key, ks);
	toLowerCase(key, ks);

	// ciphertext
	ps = strlen(str);
	toLowerCase(str, ps);
	ps = removeSpaces(str, ps);

	generateKeyTable(key, ks, keyT);

	decrypt(str, keyT, ps);
}

// simple shift vignere
string cipherText(string str, string key)
{

	string cipher_text;


	for (int i = 0; i < str.size();
		i++)

	{

		// converting in range 0-25

		char x = (str[i] + key[i]) % 26;


		// convert into alphabets(ASCII)

		x += 'A';


		cipher_text.push_back(x);

	}

	return cipher_text;

}

string generateKey(string str, string key)
{
	int x = str.size();

	for (int i = 0; ; i++)
	{
		if (x == i)
			i = 0;
		if (key.size() == str.size())
			break;
		key.push_back(key[i]);
	}
	return key;
}

string originalText(string cipher_text, string keys)
{
	string orig_text;

	for (int i = 0; i < cipher_text.size(); i++)

	{
		// converting in range 0-25
		char x = (cipher_text[i] - keys[i] + 26) % 26;

		// convert into alphabets(ASCII)
		x += 'A';

		orig_text.push_back(x);

	}
	return orig_text;
}