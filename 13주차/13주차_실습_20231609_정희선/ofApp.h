

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
	int numVertices; //���(��) �� ����
	std::vector<std::list<int>> adjLists; //���� ����Ʈ

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

	int HEIGHT;//�̷��� ����
	int WIDTH;//�̷��� �ʺ�
	int realHeight; int realWidth; //�߰�
	char** input;//�ؽ�Ʈ ������ ��� ������ ��� ������ �迭�̴�.
	int maze_col;//�̷�ĭ�� ���� �ε����� ����Ų��.
	int maze_row;//�̷�ĭ�� ���� �ε����� ����Ų��.
	int k;
	int isOpen; //������ ���ȴ����� �Ǵ��ϴ� ����. 0�̸� �ȿ��Ȱ� 1�̸� ���ȴ�.
	int isDFS;//DFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
	int isBFS;//BFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
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
