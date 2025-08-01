#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

// Function declarations
vector<vector<State>> ReadBoard(string file);
vector<State> ParseLine(string s);
vector<vector<State>> Search(vector<vector<State>> board, int start[2], int end[2]);
int Heuristic(int x1, int y1, int x2, int y2);
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openVect, vector<vector<State>> &board);
void CellSort(vector<vector<int>> *open);
bool Compare(vector<int> node1, vector<int> node2);
void expandNeighbours(vector<int> curr_node, int end[2], vector<vector<int>> &open, vector<vector<State>> &board);
bool checkValidCell(int x, int y, vector<vector<State>> &board);
void PrintBoard(vector<vector<State>> &board);
string CellString(State st);

vector<vector<State>> ReadBoard(string file) {
    ifstream f (file);
    vector<vector<State>> board;
    if (f) {
        string line;
        while(getline(f, line)) {
            vector<State> newl = ParseLine(line);
            board.push_back(newl);
        }
    }
    return board;
}

vector<State> ParseLine(string s) {
    vector<State> v;
    int n;
    char c;
    istringstream mys(s);
    while(mys >> n) {
        if (n == 0) {
            v.push_back(State::kEmpty);
        }
        else {
            v.push_back(State::kObstacle);
        }
        mys >> c;
    }
    return v;
}

vector<vector<State>> Search(vector<vector<State>> board, int start[2], int end[2]) {
    vector<vector<int>> open{};
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, y, end[0], end[1]);
    AddToOpen(x, y, g, h, open, board);
    while (!open.empty()) {
        CellSort(&open);
        auto current_node = open.back();
        open.pop_back();
        x = current_node[0];
        y = current_node[1];
        board[x][y] = State::kPath;
        if (x == end[0] && y == end[1]) {
            board[start[0]][start[1]] = State::kStart;
            board[end[0]][end[1]] = State::kFinish;
            return board;
        }
        else {
            expandNeighbours(current_node, end, open, board);
        }
    }
}

int Heuristic(int x1, int y1, int x2, int y2) {
    int md = abs(x2 - x1) + abs(y2 - y1);
    return md;
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openVect, vector<vector<State>> &board) {
    vector<int> node = {x,y,g,h};
    openVect.push_back(node);
    board[x][y] = State::kClosed;
}

void CellSort(vector<vector<int>> *open) {
    sort(open->begin(), open->end(), Compare);
}

bool Compare(vector<int> node1, vector<int> node2) {
    int f1 = node1[2] + node1[3];
    int f2 = node2[2] + node2[3];
    return f1 > f2;
}

void expandNeighbours(vector<int> curr_node, int end[2], vector<vector<int>> &open, vector<vector<State>> &board) {
    int x = 0;
    int y = 0;
    int g = curr_node[2];
    const int dir[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (auto i : dir) {
        x = curr_node[0] + i[0];
        y = curr_node[1] + i[1];
        if (checkValidCell(x, y, board)) {
            int h = Heuristic(x, y, end[0], end[1]);
            int gf = g + 1;
            AddToOpen(x, y, gf, h, open, board);
        }
    }
    
}

bool checkValidCell(int x, int y, vector<vector<State>> &board) {
    if ((x >= 0 && x < board.size()) && (y >= 0 && y < board[0].size())) {
        if (board[x][y] == State::kEmpty) {
            return true;
        }
    }
    else {
        return false;
    }
}

void PrintBoard(vector<vector<State>> &board) {
    for (auto row : board) {
        for(State i : row) {
            cout << CellString(i);
        }
        cout << "\n";
    }
}

string CellString(State st) {
    switch(st) {
        case State::kObstacle: return "⛰️ ";
        case State::kEmpty: return "0 ";
        case State::kClosed: return "x ";
        case State::kPath: return "🚗";
        case State::kStart: return "🚦";
        case State::kFinish: return "🏁";
        default: return "? ";
    }
}

int main() {
    int init[2]{0, 0};
    int goal[2]{4, 5};
    auto board = ReadBoard("board.txt");
    auto soln = Search(board, init, goal);
    PrintBoard(soln);
}