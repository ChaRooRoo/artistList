// readArtistList.cpp : Defines the entry point for the console application.
//

//Notes for later. Try and figure out how to use fstream so that way you can use the ios::trunc flag to reset the text file to empty to ready for printing

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void storeLines(string* txtLines, const int SIZE, fstream& file);
void storeCharacters(const string* txtLines, char* firstLetters, const int SIZE);
int* convertToAscii(char* firstLetters, const int SIZE);
void insertionSort(string* txtLines, int*artistsAscii, const int SIZE);
void writeToFile(fstream& file, string* txtLines, const int numberOfArtists);


int main()
{
	fstream myfile;
	myfile.open("Songs.txt");

	if (myfile.is_open()) {
			string line; int numberOfArtists = 0;

			//get the number of artists
			while (!myfile.eof()) {
				getline(myfile, line);
				numberOfArtists++;
			}
			//istream& seekg (streamoff off, ios_base::seekdir way) --use this to reset to the beg. of txt file
			myfile.seekg(0, myfile.beg);

			string* txtLines = new string[numberOfArtists];
			storeLines(txtLines, numberOfArtists, myfile);

			myfile.seekg(0, myfile.beg);

			char* firstLetters = new char[numberOfArtists + 1];
			firstLetters[numberOfArtists] = '\0';

			storeCharacters(txtLines, firstLetters, numberOfArtists);

			int *artistsAscii = convertToAscii(firstLetters, numberOfArtists);

			insertionSort(txtLines, artistsAscii, numberOfArtists);

			myfile.close();
		
			ofstream sortedfile("SongsSorted.txt");
			if (sortedfile.is_open()) {

			}
			else {
				cout << "Unable to open file.";
			}
			sortedfile.close();


			delete[] artistsAscii;
			delete[] firstLetters;
			delete[] txtLines;
			

		}
	
	else {
		cout << "Unable to open file";
	}

    return 0;
}


void storeLines(string* txtLines, const int SIZE, fstream& file) {
	string line;
	for (int i = 0; i < SIZE; i++) {
		getline(file, line);
		txtLines[i] = line;
	}
	return;
}

void storeCharacters(const string* txtLines, char* firstLetters, const int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		firstLetters[i] = txtLines[i][0];
	}
	return;
}

int* convertToAscii(char* firstLetters, const int SIZE) {
	int* artistNumbers = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		artistNumbers[i] = int(firstLetters[i]);
	}
	return artistNumbers;
}

void insertionSort(string* txtLines, int*artistsAscii, const int SIZE) {
	int j, key;
	string keyString;
	for (int i = 1; i < SIZE; i++) {
		j = i - 1;
		key = artistsAscii[i];
		keyString = txtLines[i];
		while (j >= 0 && artistsAscii[j] > key) {
			//change in int array
			artistsAscii[j + 1] = artistsAscii[j];
			//change in character array 
			txtLines[j + 1] = txtLines[j];
			j = j - 1;
		}
		artistsAscii[j+1] = key;
		txtLines[j + 1] = keyString;
	}
	return;
}

void writeToFile(fstream& sortedfile, string* txtLines, const int numberOfArtists) {
	for (int i = 0; i < numberOfArtists; i++) {
		sortedfile << txtLines[i] << "\n";
	}
	return;
}