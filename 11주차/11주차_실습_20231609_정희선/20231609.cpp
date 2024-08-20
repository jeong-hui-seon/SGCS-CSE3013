#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unordered_map>

using namespace std;

// 미로의 너비와 높이
int W, H;
// 전체 미로 맵, 방문 여부, 각 방의 집합 번호
vector<vector<char> > map;
vector<vector<int> > numSet;

int setId=1;

// 미로 출력
void printMaze() {
    for (int i = 0; i < H * 2 + 1; i++) {
        for (int j = 0; j < W * 2 + 1; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}
void printNumSet() {
    cout << "Current numSet configuration:" << endl;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << numSet[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------------" << endl;
}


// 미로 초기화
void initMaze() {
    map.resize(H * 2 + 1, vector<char>(W * 2 + 1,' '));
    numSet.resize(H, vector<int>(W));
    
    for(int i=0; i<H; i++){
        for (int j = 0; j < W; j++) {
            numSet[i][j] = setId++;
        }
    }
    for (int i = 0; i < H * 2 + 1; i++) {
        for (int j = 0; j < W * 2 + 1; j++) {
            if (i % 2 == 0) {
                map[i][j] = (j % 2 == 0) ? '+' : '-';
            } else {
                map[i][j] = (j % 2 == 0) ? '|' : ' ';
            }
        }
    }
}
void find_all(int row, int col, int row_final, int col_final){
    int num=numSet[row][col];
    for (int j = 0; j < W; j++) {
        for (int i=0; i<H ; i++) {
            if (numSet[i][j]==num) { // 벽 제거 조건
                numSet[i][j] = numSet[row_final][col_final];
            }
        }
    }
}

void removeHorizontalWalls(int row) {
    for (int j = 0; j < W-1; j++) {
        if (numSet[row][j] != numSet[row][j + 1] && rand() % 2) { // 벽 제거 조건
            //numSet[row][j+1] = numSet[row][j];
            find_all(row, j+1, row, j);
            map[row * 2 + 1][j * 2 + 2] = ' '; // 벽 제거
        }
    }
}
void createVerticalConnections(int row) {
    unordered_map<int, vector<int>> setMembers;  // 각 집합의 구성원을 저장

    // 현재 행의 모든 셀을 순회하며 각 집합에 속하는 셀 인덱스를 수집
    for (int j = 0; j < W; j++) {
        setMembers[numSet[row][j]].push_back(j);
    }

    // 각 집합에 대해 무작위로 하나의 수직 연결을 확실히 생성
    for (auto& entry : setMembers) {
        vector<int>& indices = entry.second;
        int randomIndex = indices[rand() % indices.size()];  // 무작위 인덱스 선택

        // 선택된 인덱스에 대해 수직 연결 생성
        numSet[row+1][randomIndex] = numSet[row][randomIndex];
        map[row * 2 + 2][randomIndex * 2 + 1] = ' ';  // 수직 연결 생성
    }

    // 모든 셀에 대해 추가적인 수직 연결을 임의로 생성할 가능성
    for (int j = 0; j < W; j++) {
        if (map[row * 2 + 2][j * 2 + 1] != ' ' && rand() % 2) {  // 추가적인 연결 생성 여부
            numSet[row + 1][j] = numSet[row][j];
            map[row * 2 + 2][j * 2 + 1] = ' ';
        }
    }
}
// 미로 생성 (엘러 알고리즘)
void generateMaze() {
    srand(static_cast<unsigned int>(time(NULL)));

    for (int i = 0; i < H - 1; i++) { // 마지막 행 전까지 반복
        removeHorizontalWalls(i); //과정2
        createVerticalConnections(i); //과정3
    }
    // 마지막 행에서 수평 벽 제거만 처리
    for (int j = 0; j < W - 1; j++) {
        if (numSet[H-1][j] != numSet[H-1][j + 1]) { // 벽 제거 조건
            //numSet[H-1][j+1] = numSet[H-1][j];
            find_all(H-1, j+1, H-1, j);
            map[(H-1) * 2 + 1][j * 2 + 2] = ' '; // 벽 제거
        }
    }
}

int main() {
    cout << "Enter the width of the maze: ";
    cin >> W;
    cout << "Enter the height of the maze: ";
    cin >> H;

    initMaze();
    generateMaze();
    printMaze();

    return 0;
}