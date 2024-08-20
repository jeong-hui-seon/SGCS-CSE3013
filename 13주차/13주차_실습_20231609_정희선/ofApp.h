

#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon

struct Line {
	float startX;
	float startY;
	float endX;
	float endY;
};

struct Graph {
	int numVertices; //노드(셀) 총 개수
	std::vector<std::list<int>> adjLists; //인접 리스트

	Graph(int V) : numVertices(V), adjLists(V) {}

	void addEgde(int src, int dest) {

	}
};

struct BLOCK {
	int x, y;
};


class ofApp : public ofBaseApp {

public:
	std::vector<std::vector<bool>> visited; //add
	//ofPolyline allPath;
	//ofPolyline shortPath;

	void setup();
	void update();
	void draw();

	void keyPressed(int key); // Traps escape key if exit disabled
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	bool readFile();
	void freeMemory();
	bool DFS();
	bool BFS();//
	void dfs_draw();//
	void bfs_draw();//

	int HEIGHT;//미로의 높이
	int WIDTH;//미로의 너비
	int realHeight; int realWidth; //추가
	char** input;//텍스트 파일의 모든 정보를 담는 이차원 배열이다.
	int maze_col;//미로칸의 열의 인덱스를 가리킨다.
	int maze_row;//미로칸의 행의 인덱스를 가리킨다.
	int k;
	int isOpen; //파일이 열렸는지를 판단하는 변수. 0이면 안열렸고 1이면 열렸다.
	int isDFS;//DFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
	int isBFS;//BFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
	// Menu
	ofxWinMenu* menu; // Menu object
	void appMenuFunction(string title, bool bChecked); // Menu return function

	// Used by example app
	ofTrueTypeFont myFont;
	ofImage myImage;
	float windowWidth, windowHeight;
	HWND hWnd; // Application window
	HWND hWndForeground; // current foreground window

	// Example menu variables
	bool bShowInfo;
	bool bFullscreen;
	bool bTopmost;
	bool isdfs;
	// Example functions
	void doFullScreen(bool bFull);
	void doTopmost(bool bTop);

	//me
	std::vector<std::vector<char>> maze;

	std::vector<Line> LINES;
	std::vector<BLOCK> all_vec;
	std::vector<Line> allPath;
	std::vector<BLOCK> sq_vec;
	std::vector<Line> shortPath;


	int x_dir[4] = { 0,-1,0,1 };
	int y_dir[4] = { -1,0,1,0 };

	//int x_dir[4] = { 1, 0, 0, -1 }; 
	//int y_dir[4] = { 0, 1, -1, 0 };
	stack<struct BLOCK> s;
	stack<struct BLOCK> all_path;
	queue<struct BLOCK> q;
	queue<struct BLOCK> q_all_path;

};
