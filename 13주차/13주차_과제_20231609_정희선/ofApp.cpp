#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isDFS = false;
	isBFS = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked

	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS", false, false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if (title == "Open") {
		readFile();
	}
	if (title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if (title == "Show DFS") {
		bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			DFS();
			isDFS=true;
		}
		else
			cout << "you must open file first" << endl;

	}

	if (title == "Show BFS") {
		//doTopmost(bChecked); // Use the checked value directly
		bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			BFS();
			isBFS = true;
		}
		else
			cout << "you must open file first" << endl;

	}

	if (title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if (title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(5);
	int i, j;

	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	for (const Line& line : LINES) {
		ofDrawLine(15*line.startX, 15*line.startY, 15*line.endX, 15*line.endY);
	}
	ofSetColor(ofColor::red);
	for (const Line& line : allPath) {
		ofDrawLine(15 * line.startX, 15 * line.startY, 15 * line.endX, 15 * line.endY);
	}
	ofSetColor(ofColor::green);
	for (const Line& line : shortPath) {
		ofDrawLine(15 * line.startX, 15 * line.startY, 15 * line.endX, 15 * line.endY);
	}

	if (isDFS)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen) {
			dfs_draw();

		}
		else
			cout << "You must open file first" << endl;
	}
	if (isBFS)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen) {
			bfs_draw();

		}
		else
			cout << "You must open file first" << endl;
	}
	if (bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight() - 20);
	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if (bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else {
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU));
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth() - ofGetWidth()) / 2, (ofGetScreenHeight() - ofGetHeight()) / 2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if (bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if (bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if (GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// Escape key exit has been disabled but it can be checked here
	if (key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if (bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if (key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if (key == 'f') {
		bFullscreen = !bFullscreen;
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
bool ofApp::readFile()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;

	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//fileName = "maze0.maz"; 
		//printf("file name is %s\n", fileName);
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;


			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다
			freeMemory();
			realHeight = 0; realWidth = 0;
			for (auto line : buffer.getLines()) {
				realHeight++;
				int lineLen = line.length();
				if (lineLen > realWidth) realWidth = lineLen;
				maze.push_back(vector<char>(line.begin(), line.end()));
			}
			WIDTH = realWidth / 2; HEIGHT = realHeight / 2;
			cout << "Maze Width: " << WIDTH << " characters." << endl;
			cout << "Maze Height: " << HEIGHT << " lines." << endl;

			for (auto& row : maze) {
				row.resize(realWidth, ' ');  // Fill with spaces if not enough data
			}
			//testing
			for (const auto& row : maze) {  // 각 행에 대해 반복
				for (char cell : row) {     // 행 내의 각 셀에 대해 반복
					cout << cell;     // 셀의 값을 출력
				}
				cout << '\n';         // 행이 끝나면 줄바꿈
			}
			//
			Line tmp;
			for (int i = 0; i < realHeight; i++) {
				for (int j = 0; j < realWidth; j++) {
					if (maze[i][j] == '-') {
						tmp.startX = j - 0.5; tmp.startY = i + 0.5;
						tmp.endX = j + 1.5; tmp.endY = i + 0.5;
						this->LINES.push_back(tmp);
					}

					else if (maze[i][j] == '|') {
						tmp.startX = j + 0.5; tmp.startY = i - 0.5;
						tmp.endX = j + 0.5; tmp.endY = i + 1.5;
						this->LINES.push_back(tmp);

					}
				}
			}
			return true;


		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {

	//TO DO
	// malloc한 memory를 free해주는 함수
	LINES.clear();
	LINES.shrink_to_fit(); // Optional: reduce capacity to fit size (which is now 0)

	// Clear the maze data
	maze.clear();
	maze.shrink_to_fit(); // Optional: to free memory used by the maze

	// 추가된 s_vec 벡터 메모리 해제
	sq_vec.clear();
	sq_vec.shrink_to_fit();

	// 추가된 allPath 벡터 메모리 해제
	shortPath.clear();
	shortPath.shrink_to_fit();

	all_vec.clear();
	all_vec.shrink_to_fit();

	allPath.clear();
	allPath.shrink_to_fit();

}
void printVisited(const std::vector<std::vector<bool>>& visited) {
	std::cout << "Visited array:\n";
	for (const auto& row : visited) {
		for (bool cell : row) {
			std::cout << (cell ? "1 " : "0 ");
		}
		std::cout << "\n";
	}
}

void printStack(const std::stack<BLOCK>& s) {
	std::stack<BLOCK> temp = s;  // 복사본을 사용하여 원본 스택을 유지
	std::cout << "Stack contents (top to bottom):\n";
	while (!temp.empty()) {
		BLOCK b = temp.top();
		temp.pop();
		std::cout << "(" << b.y << ", " << b.x << ") ";
	}
	std::cout << "\n";
}

void printAllPath(const std::stack<BLOCK>& all_path) {
	std::stack<BLOCK> temp = all_path;  // 복사본을 사용하여 원본 스택을 유지
	std::cout << "All path (top to bottom):\n";
	while (!temp.empty()) {
		BLOCK b = temp.top();
		temp.pop();
		std::cout << "(" << b.y << ", " << b.x << ") ";
	}
	std::cout << "\n";
}

void printQUEUE(const std::queue<BLOCK>& q) {
	std::queue<BLOCK> temp = q;  // 복사본을 사용하여 원본 큐를 유지
	std::cout << "Queue contents (front to back):\n";
	while (!temp.empty()) {
		BLOCK b = temp.front();
		temp.pop();
		std::cout << "(" << b.y << ", " << b.x << ") ";
	}
	std::cout << "\n";
}

void printQAllPath(const std::queue<BLOCK>& q_all_path) {
	std::queue<BLOCK> temp = q_all_path;  // 복사본을 사용하여 원본 큐를 유지
	std::cout << "All path (front to back):\n";
	while (!temp.empty()) {
		BLOCK b = temp.front();
		temp.pop();
		std::cout << "(" << b.y << ", " << b.x << ") ";
	}
	std::cout << "\n";
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)

	// visited 2D 벡터 메모리 해제
	for (auto& row : visited) {
		row.clear();
		row.shrink_to_fit();
	}
	visited.clear();
	visited.shrink_to_fit();

	// s 스택 메모리 해제
	while (!s.empty()) {
		s.pop();
	}

	// all_path 스택 메모리 해제
	while (!all_path.empty()) {
		all_path.pop();
	}


	visited.resize(realHeight, vector<bool>(realWidth));
	BLOCK current, next; // 현재 좌표와 이동할 좌표를 BLOCK 구조체를 사용하여 관리
	BLOCK target = { realWidth - 2, realHeight - 2 }; // 목표 좌표


	for (int i = 0; i < realHeight; i++) {
		for (int j = 0; j < realWidth; j++) {
			visited.at(i).at(j) = (maze[i][j] != ' ') ? true : false;
		}
	}

	current = { 1,1 };
	s.push(current);
	all_path.push(current);
	visited.at(1).at(1) = true;

	while (!s.empty()) {
		current = s.top();
		all_path.push(current);
		if (current.y == target.y && current.x == target.x) {
			return true;
		}
		int move_possible = 0;

		for (int i = 0; i < 4; i++) {
			next.y = current.y + y_dir[i];
			next.x = current.x + x_dir[i];
			if (!visited.at(next.y).at(next.x)) {
				all_path.push(next);
				s.push(next);
				visited.at(next.y).at(next.x) = true;
				move_possible = 1;
				break;
			}
		}
		if (!move_possible) s.pop();

	}
}
bool ofApp::BFS()
{

	// visited 2D 벡터 메모리 해제
	for (auto& row : visited) {
		row.clear();
		row.shrink_to_fit();
	}
	visited.clear();
	visited.shrink_to_fit();

	// s 스택 메모리 해제
	while (!q.empty()) {
		q.pop();
	}

	// all_path 스택 메모리 해제
	while (!q_all_path.empty()) {
		q_all_path.pop();
	}


	visited.resize(realHeight, vector<bool>(realWidth));
	BLOCK current, next; // 현재 좌표와 이동할 좌표를 BLOCK 구조체를 사용하여 관리
	BLOCK target = { realWidth - 2, realHeight - 2 }; // 목표 좌표


	for (int i = 0; i < realHeight; i++) {
		for (int j = 0; j < realWidth; j++) {
			visited.at(i).at(j) = (maze[i][j] != ' ') ? true : false;
		}
	}

	current = { 1,1 };
	q.push(current);
	q_all_path.push(current);
	visited.at(1).at(1) = true;

	while (!q.empty()) {
		current = q.front();
		q.pop();
		//q_all_path.push(current);
		
		for (int i = 0; i < 4; i++) {
			next.y = current.y + y_dir[i];
			next.x = current.x + x_dir[i];

			while (!visited.at(next.y).at(next.x)) {
				q_all_path.push(next);
				q.push(next);
				visited.at(next.y).at(next.x) = true;
				if (next.y == target.y && next.x == target.x) {
					return true;
				}
				break;
			}
		}
	}
}
void ofApp::dfs_draw()
{
	//TO DO 
	//DFS를 수행한 결과를 그린다. (3주차 내용)
	
	// 추가된 s_vec 벡터 메모리 해제
	sq_vec.clear();
	sq_vec.shrink_to_fit();

	// 추가된 allPath 벡터 메모리 해제
	shortPath.clear();
	shortPath.shrink_to_fit();

	all_vec.clear();
	all_vec.shrink_to_fit();

	allPath.clear();
	allPath.shrink_to_fit();

	printVisited(visited);
	printStack(s);
	printAllPath(all_path);

	//모든 경로 그리기
	while (!all_path.empty()) {
		all_vec.push_back(all_path.top());
		all_path.pop();
	}
	for (int i = 0; i < all_vec.size() - 1; ++i) {
		Line tmp;
		tmp.startX = all_vec[i].x + 0.5;
		tmp.startY = all_vec[i].y + 0.5;
		tmp.endX = all_vec[i + 1].x + 0.5;
		tmp.endY = all_vec[i + 1].y + 0.5;
		allPath.push_back(tmp);
	}

	
	//최적 경로 그리기
	while (!s.empty()) {
		sq_vec.push_back(s.top());
		s.pop();
	}
	for (int i = 0; i < sq_vec.size() - 1; ++i) {
		Line tmp;
		tmp.startX = sq_vec[i].x +0.5;
		tmp.startY = sq_vec[i].y +0.5;
		tmp.endX = sq_vec[i + 1].x +0.5;
		tmp.endY = sq_vec[i + 1].y +0.5;
		shortPath.push_back(tmp);
	}

	isDFS = false;

}
void ofApp::bfs_draw()
{
	//TO DO 

	// 추가된 s_vec 벡터 메모리 해제
	sq_vec.clear();
	sq_vec.shrink_to_fit();

	// 추가된 allPath 벡터 메모리 해제
	shortPath.clear();
	shortPath.shrink_to_fit();

	all_vec.clear();
	all_vec.shrink_to_fit();

	allPath.clear();
	allPath.shrink_to_fit();

	printVisited(visited);
	printQUEUE(q);
	printQAllPath(q_all_path);

	//최적 경로 그리기
	while (!q_all_path.empty()) {
		sq_vec.push_back(q_all_path.front());
		all_vec.push_back(q_all_path.front());
		q_all_path.pop();
	}

	int path_index = sq_vec.size() - 1;
	BLOCK current = sq_vec[path_index];
	BLOCK next;
	Line tmp;
	tmp.startX = current.x + 0.5;
	tmp.startY = current.y + 0.5;
	tmp.endX = current.x + 0.5;
	tmp.endY = current.y + 0.5;
	shortPath.push_back(tmp);
	path_index--;

	while (path_index >= 0) {
		next = all_vec[path_index];
		// Check if next block is adjacent to current block
		if (abs(next.x - current.x) + abs(next.y - current.y) == 1) {
			tmp.startX = current.x + 0.5;
			tmp.startY = current.y + 0.5;
			tmp.endX = next.x + 0.5;
			tmp.endY = next.y + 0.5;
			shortPath.push_back(tmp);
			current = next;
		}
		path_index--;
	}

	for (int i = 0; i < all_vec.size(); ++i) {
		current = all_vec[i];
		for (int j = i + 1; j < all_vec.size(); ++j) {
			next = all_vec[j];
			// Check if next block is adjacent to current block
			if (abs(next.x - current.x) + abs(next.y - current.y) == 1) {
				tmp.startX = current.x + 0.5;
				tmp.startY = current.y + 0.5;
				tmp.endX = next.x + 0.5;
				tmp.endY = next.y + 0.5;
				allPath.push_back(tmp);
			}
		}
	}


	isBFS = false;

}

