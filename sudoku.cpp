#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int s = 9;
const int easy = 15;
const int mid = 30;
const int hard = 60;

// Function to print the Sudoku board with grid lines
void sudokuboard(const vector<vector<int>>& board) {
    for (int row = 0; row < s; ++row) {
        if (row % 3 == 0 && row != 0) {
            cout << "------+-------+------" << endl;
        }
        for (int col = 0; col < s; ++col) {
            if (col % 3 == 0 && col != 0) {
                cout << "| ";
            }
            if (board[row][col] == 0) {
                cout << ". ";
            } else {
                cout << board[row][col] << " ";
            }
        }
        cout << endl;
    }
}


bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    for (int i = 0; i < s; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            if (board[i][j] == num)
                return false;
        }
    }
    return true;
}


bool fillBoard(vector<vector<int>>& board) {
    for (int row = 0; row < s; ++row) {
        for (int col = 0; col < s; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= s; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (fillBoard(board))
                            return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}


void createPuzzle(vector<vector<int>>& board) {
    fillBoard(board);
}


void removeNumbers(vector<vector<int>>& board, int difficulty) {
    int removecells = difficulty;
    srand(static_cast<unsigned>(time(0)));
    while (removecells > 0) {
        int row = rand() % s;
        int col = rand() % s;
        if (board[row][col] != 0) {
            board[row][col] = 0;
            --removecells;
        }
    }
}


bool isSolved(const vector<vector<int>>& board) {
    for (int row = 0; row < s; ++row) {
        for (int col = 0; col < s; ++col) {
            if (board[row][col] == 0 || !isValid(board, row, col, board[row][col]))
                return false;
        }
    }
    return true;
}

int main() {
    vector<vector<int>> board(s, vector<int>(s, 0));
    int difficulty;
    
    // Difficulty selection menu
    cout << "Select difficulty level:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "Enter choice (1-3): ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            difficulty = easy;
            break;
        case 2:
            difficulty = mid;
            break;
        case 3:
            difficulty = hard;
            break;
        default:
            cout << "Invalid choice. Defaulting to EASY.\n";
            difficulty = easy;
    }

    createPuzzle(board);
    removeNumbers(board, difficulty);

    cout << "Sudoku Puzzle (Difficulty level: " << (difficulty == easy ? "EASY" : difficulty == mid ? "MEDIUM" : "HARD") << "):" << endl;
    sudokuboard(board);

    time_t startTime = time(0);

    while (true) {
        int row, col, num;
        cout << "Enter row (1-9), column (1-9), and number (1-9) or -1 to quit: ";
        cin >> row;

        if (row == -1) break; 

        cin >> col >> num;
        if (row >= 1 && row <= s && col >= 1 && col <= s && num >= 1 && num <= s) {
            row -= 1;
            col -= 1;
            if (board[row][col] == 0) {
                board[row][col] = num;
                if (isSolved(board)) {
                    cout << "Congratulations! You solved the Sudoku!" << endl;
                    time_t endTime = time(0);
                    cout << "Time taken: " << difftime(endTime, startTime) << " seconds." << endl;
                    break;
                }
            } else {
                cout << "Cell is not editable." << endl;
            }
        } else {
            cout << "Invalid input. Try again." << endl;
        }
        sudokuboard(board); 
    }

    return 0;
}
