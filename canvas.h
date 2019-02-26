#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Axes {
	int x, y;
	Axes (int a, int b) {
		x = a;
		y = b;
	}
	Axes () {}
	friend class Canvas;
};

class Canvas {
	//friend class Axes;
private:
	int w, h;
	vector<vector<char>> canvas;
	Axes axes;
	bool haveaxes = false;
	pair<int, int> plot(int, int);
public:
	Canvas (int a, int b) {
		w = a;
		h = b;
		for (int i = 0; i < h; ++i) {
			canvas.push_back(vector<char>(w, ' '));
		}
	}
	int height() {return h;}
	int width() {return w;}
	void print(ostream&);
	char& operator() (int, int);
	void plotaxes(int, int);
	void plotpoint(pair<int, int>, char);
	void plotpoint(pair<int, int>);
	void plotfunction(int (*func)(int), char);
	void plotfunction(int (*func)(int));

};

pair<int, int> Canvas::plot(int a, int b) {
	pair<int, int> point;
	point.second = a + axes.x;
	point.first = axes.y - b;
	return point;
}

void Canvas::print(ostream& dest) {
	for (int n = 0; n < h; n++) {
		for (int m = 0; m < w; n++) {
			dest << canvas[n][m];
		}
		dest << endl;
	}
	return;
}

char& Canvas::operator() (int i, int j) { //i vertical coordinate, j horizontal coordinate
	if (j > w || i > h) {
		cerr << "Coordinate out of Canvas" << endl;
	}
	else {
		return canvas[i][j];
	}
}

void Canvas::plotaxes(int i, int j) {
	for (int n = 0; n < h; ++n) {
		canvas[n][j] = '|';
	}
	for (int n = 0; n < w; ++n) {
		canvas[i][n] = '-';
	}
	canvas[i][j] = '+';
	axes = Axes(j, i);
	haveaxes = true;
}

void Canvas::plotpoint(pair<int, int> coord, char c) {
	if (haveaxes == false) {
		cerr << "No Axes on Canvas" << endl;
	}
	else {
		canvas[coord.first][coord.second] = c;
	}
}

void Canvas::plotpoint(pair<int, int> coord) {
	if (haveaxes == false) {
		cerr << "No Axes on Canvas" << endl;
	}
	else {
		canvas[coord.first][coord.second] = '@';
	}
}

void Canvas::plotfunction(int (*func)(int)) {
	for(int n = 0; n < w; n++) {
		int x = n - axes.x;
		int y = int(func(x));
		int m = axes.y - x;
		cout << n << x << y << m << endl;
		if ((m * m) > 0 && m >= 0 && m < h) {
			canvas[m][n] = '@';
		}
	}
}