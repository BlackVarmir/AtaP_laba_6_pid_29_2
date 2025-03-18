#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

const int MAX_WORDS = 1000;
const int MAX_LENGTH = 50;

void toLowerCase(char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 'a' - 'A';
		}
	}
}

void Task1() {
	ifstream file("text.txt");
	if (!file) {
		cout << "Error opening file" << endl;
		return;
	}

	char** words = new char*[MAX_WORDS];
	for (int i = 0; i < MAX_WORDS; i++) {
		words[i] = new char[MAX_LENGTH];
	}

	int wordCount = 0;

	while (file >> words[wordCount] && wordCount < MAX_WORDS) {
		wordCount++;
	}
	file.close();

	char** threeLetterWords = new char*[MAX_WORDS];
	char** capitalWords = new char*[MAX_WORDS];

	for (int i = 0; i < MAX_WORDS; i++) {
		threeLetterWords[i] = new char[MAX_LENGTH];
		capitalWords[i] = new char[MAX_LENGTH];
	}

	int threeCount = 0, capitalCount = 0;

	for (int i = 0; i < wordCount; i++) {

		if (strlen(words[i]) == 3) {
			strcpy(threeLetterWords[threeCount], words[i]);
			threeCount++;
		}
		if (isupper(words[i][0])) {
			strcpy(capitalWords[capitalCount], words[i]);
			capitalCount++;
		}
	}

	cout << "Words with exactly 3 letters: ";
	for (int i = 0; i < threeCount; i++) cout << threeLetterWords[i] << " ";
	cout << endl;

	cout << "Words starting with a capital letter: ";
	for (int i = 0; i < capitalCount; i++) cout << capitalWords[i] << " ";
	cout << endl;

	char searchWord[MAX_LENGTH];
	cout << "Enter a word to search for: ";
	cin >> searchWord;

	toLowerCase(searchWord);

	int count = 0;
	for (int i = 0; i < wordCount; i++) {
		char lowerWord[MAX_LENGTH];
		strcpy(lowerWord, words[i]);
		toLowerCase(lowerWord);

		if (strcmp(lowerWord, searchWord) == 0) count++;
	}
	cout << "Occurrences of the word: " << count << endl;

	for (int i = 0; i < MAX_WORDS; i++) {
		delete[] words[i];
		delete[] threeLetterWords[i];
		delete[] capitalWords[i];
	}
	delete[] words;
	delete[] threeLetterWords;
	delete[] capitalWords;
}

void Task2() {
	int n, m;
	cout << "Enter matrix dimensions (n, m): ";
	cin >> n >> m;

	char** matrix = new char* [n];
	for (int i = 0; i < n; i++) 
		matrix[i] = new char[m];

	srand(time(nullptr));
	char vowels[] = "AEIOUaeiou";
	char consonants[] = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j || i + j == m - 1) {
				matrix[i][j] = vowels[rand() % 10];
			}
			else {
				matrix[i][j] = consonants[rand() % 42];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cout << matrix[i][j] << " ";
		cout << endl;
	}

	char searchWord[MAX_LENGTH];
	cout << "Enter a word to search: ";
	cin >> searchWord;

	for (int i = 0; i < n; i++) {
		char row[MAX_LENGTH] = "";
		for (int j = 0; j < m; j++) row[j] = matrix[i][j];
		row[m] = '\0';

		char* pos = strstr(row, searchWord);
		if (pos != nullptr) {
			cout << "Found at row " << i + 1 << " from column " << (pos - row) + 1 << " to " << (pos - row) + strlen(searchWord) << endl;
		}
	}

	for (int i = 0; i < n; i++) delete[] matrix[i];
	delete[] matrix;
}

int main()
{
	int choice;
	do {
		cout << "\nMenu:" << endl;
		cout << "1. Process text file" << endl;
		cout << "2. Process character matrix" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1: Task1(); break;
		case 2: Task2(); break;
		case 0: cout << "Exiting..." << endl; break;
		default: cout << "Invalid choice, try again!" << endl;
		}
	} while (choice != 0);

	return 0;
}

