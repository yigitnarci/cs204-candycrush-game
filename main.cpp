#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string InputFile;
    ifstream OpenedFile;
    string line;
    int count = 0;
    do {
        if (count == 0){
            cout << "Please enter the file name: " << endl;
            count += 1;
        }
        else{
            cout << "Please enter a valid file name: " << endl;
        }
        cin >> InputFile;
        OpenedFile.open(InputFile);
        
        if (!OpenedFile) {
            cout << "The file couldn't be opened." << endl;
            OpenedFile.clear();
            OpenedFile.close();
            cin.clear();
            //when file cannot open = 0, so output erro message in here
        }
        
    } while (!OpenedFile);
    
    vector<vector<char>> charmatrix;
    size_t expectedSize = 0;
    while (getline(OpenedFile, line)) {
        //cout << line << endl;
        vector<char> row;
        for (char c : line) { //int i = 0; i++; line.length()
            row.push_back(c);
        }
        if (charmatrix.empty()) { //since charmatrix is empty in here
            expectedSize = row.size();
        }
        else if (row.size() != expectedSize) {
            cout << "The matrix either has invalid dimensions or contains invalid characters." << endl;
            cout << "Exiting the game. Bye bye.";
            return 1;
        }
        charmatrix.push_back(row);
        for (char c : row) {
            if (c != 'X' and c != 'O' and c != 'S') {
                cout << "The matrix either has invalid dimensions or contains invalid characters." << endl;
                cout << "Exiting the game. Bye bye.";
                return 1;
            }
        }
    }
    cout << "The content of the matrix is: " << endl;
    for (const auto& row : charmatrix) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
    
    int row, col;
    char direction;
    
    int count1= 0;
    while (true) {
        if (count1 == 0){
            cout << "Enter row, col, and direction (r/l/u/d). Type '0 0 q' to exit. " << endl;
            count1 += 1;
        }
        
        cin >> row >> col >> direction;
        cout << "Move: " << endl;
        //cout << row << " " << col << " " << direction << endl;
        
        //validating input
        if (row == 0 && col == 0 && direction == 'q') {
            cout << "Exiting the game. Bye bye." << endl;
            break;
        }
        
        if ((col < 0 || row < 0) ||(direction != 'r' && direction != 'l' && direction != 'u' && direction != 'd')) {
            cout << "Invalid input. Try again." << endl;
            continue;
        }
        
        if (row >= charmatrix.size() ||  col >= charmatrix[0].size()) {
            cout << "Invalid coordinates!" << endl;
            continue;
        }
        
        int newRow = row;
        int newCol = col;
        
        if (direction == 'r') newCol++;
        else if (direction == 'l') newCol--;
        else if (direction == 'u') newRow--;
        else if (direction == 'd') newRow++;
        
        if (newRow < 0 || newRow >= charmatrix.size() || newCol < 0 || newCol >= charmatrix[0].size()) {
            cout << "Move out of bounds!" << endl;
            continue;
        }
        
        
        if (charmatrix[newRow][newCol] == '-' || charmatrix[row][col] == '-'){
            cout << "Cannot swap with an empty cell!" << endl;
            continue;
        }
        //swaping
        char temp = charmatrix[row][col];
        charmatrix[row][col] = charmatrix[newRow][newCol];
        charmatrix[newRow][newCol] = temp;
        
        bool matchFound = false;
        
        vector<vector<char>> copiedMatrix = charmatrix;

        vector<vector<bool>> toClear(charmatrix.size(), vector<bool>(charmatrix[0].size(), false));
        bool hasMatch = false;
   

        // Mark vertical matches
        for (int i = 0; i < charmatrix.size(); i++) {
            for (int j = 0; j < charmatrix[0].size() - 2; j++) {
                if (charmatrix[i][j] != '-' && charmatrix[i][j] == charmatrix[i][j + 1] && charmatrix[i][j] == charmatrix[i][j + 2]) {
                    toClear[i][j] = toClear[i][j + 1] = toClear[i][j + 2] = true;
                    
                    hasMatch = true;
                
                }
            }
        }
        // Replace matched elements with '-'
        for (int i = 0; i < charmatrix.size(); i++) {
            for (int j = 0; j < charmatrix[0].size(); j++) {
                if (toClear[i][j]) {
                    charmatrix[i][j] = '-';
                }
            }
        }
        
        // Mark horizontal matches
        for (int j = 0; j < charmatrix[0].size(); j++) {
            for (int i = 0; i < charmatrix.size() - 2; i++) {
                if (charmatrix[i][j] != '-' &&
                    charmatrix[i][j] == charmatrix[i + 1][j] &&
                    charmatrix[i][j] == charmatrix[i + 2][j]) {
                    toClear[i][j] = toClear[i + 1][j] = toClear[i + 2][j] = true;
                    hasMatch = true;
                }
            }
        }
        
        // Replace matched elements with '-'
        for (int i = 0; i < charmatrix.size(); i++) {
            for (int j = 0; j < charmatrix[0].size(); j++) {
                if (toClear[i][j]) {
                    charmatrix[i][j] = '-';
                }
            }
        }


        // Undo swap if no match is found
        if (!hasMatch) {
            char temp1 = charmatrix[row][col];
            charmatrix[row][col] = charmatrix[newRow][newCol];
            charmatrix[newRow][newCol] = temp1;

        }
        

        // If no matches were found, exit the loop
        if (!hasMatch) {
            cout << "Invalid move: No match found!" << endl;
            continue;
        }
        
        cout << "After swap: " << endl; //AFTER SWAP YERİ
        for (const auto& row : copiedMatrix) {
            for (char c : row) {
                cout << c;
            }
            cout << endl;
        }
        cout << endl;

        
        // Print matrix after clearing
        cout << "Move successful. Clearing matches..." << endl;
        cout << "After clearing matches: " << endl;
        for (const auto& row : charmatrix) {
            for (char c : row) {
                cout << c;
            }
            cout << endl;
        }
        cout << endl;
        
        //gravity part
        for (int k = 0 ; k < charmatrix.size() - 1; k++){
            for(int j=0; j < charmatrix[0].size(); j++){
                for (int i = 0 ; i < charmatrix.size() - 1; i++){
                    if(charmatrix[i][j] != '-' && charmatrix[i+1][j] == '-'){
                        char temp2 = charmatrix[i+1][j];
                        charmatrix[i+1][j] = charmatrix[i][j];
                        charmatrix[i][j] = temp2;
                    }
                }
            }
        }

        cout << "After applying gravity: " << endl;
        for (const auto& row : charmatrix) {
            for (char c : row) {
                cout << c;
            }
            cout << endl;
        }
        cout << endl;
        vector<vector<bool>> toClear1(charmatrix.size(), vector<bool>(charmatrix[0].size(), false));
        vector<vector<char>> copiedMatrix1 = charmatrix;
        bool hasMatch1 = false;

        // Mark vertical matches
        for (int i = 0; i < charmatrix.size(); i++) {
            for (int j = 0; j < charmatrix[0].size() - 2; j++) {
                if (charmatrix[i][j] != '-' && charmatrix[i][j] == charmatrix[i][j + 1] && charmatrix[i][j] == charmatrix[i][j + 2]) {
                    toClear1[i][j] = toClear1[i][j + 1] = toClear1[i][j + 2] = true;
                    
                    hasMatch1 = true;
                
                }
            }
        }
        // Replace matched elements with '-'
        for (int i = 0; i < charmatrix.size(); i++) {
            for (int j = 0; j < charmatrix[0].size(); j++) {
                if (toClear1[i][j]) {
                    charmatrix[i][j] = '-';
                }
            }
        }
        
        // Mark horizontal matches
        for (int j = 0; j < charmatrix[0].size(); j++) {
            for (int i = 0; i < charmatrix.size() - 2; i++) {
                if (charmatrix[i][j] != '-' &&
                    charmatrix[i][j] == charmatrix[i + 1][j] &&
                    charmatrix[i][j] == charmatrix[i + 2][j]) {
                    toClear1[i][j] = toClear1[i + 1][j] = toClear1[i + 2][j] = true;
                    hasMatch1 = true;
                }
            }
        }
        
        // Replace matched elements with '-'
        for (int i = 0; i < charmatrix.size(); i++) {
            for (int j = 0; j < charmatrix[0].size(); j++) {
                if (toClear1[i][j]) {
                    charmatrix[i][j] = '-';
                }
            }
        }
        if (copiedMatrix1 != charmatrix){
            cout << "After clearing matches: " << endl;
            for (const auto& row : charmatrix) {
                for (char c : row) {
                    cout << c;
                }
                cout << endl;
            }
            cout << endl;
            
            //gravity part
            for (int k = 0 ; k < charmatrix.size() - 1; k++){
                for(int j=0; j < charmatrix[0].size(); j++){
                    for (int i = 0 ; i < charmatrix.size() - 1; i++){
                        if(charmatrix[i][j] != '-' && charmatrix[i+1][j] == '-'){
                            char temp3 = charmatrix[i+1][j];
                            charmatrix[i+1][j] = charmatrix[i][j];
                            charmatrix[i][j] = temp3;
                        }
                    }
                }
            }
            cout << "After applying gravity: " << endl;
            for (const auto& row : charmatrix) {
                for (char c : row) {
                    cout << c;
                }
                cout << endl;
            }
            cout << endl;
        }

        
    }
}
    
