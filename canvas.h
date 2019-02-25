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
			canvas.push_back(vector<char>(w, ' '))
		}
	}
	int height() {return h;}
	int width() {return w;}
	void print(ostream&);
	char& operator() (int, int);
	void plotaxes(int, int);
	void plotpoint(int, int, char);
	void plotpoint(int, int);
	void plotfunction(int (*func)(int), char);

};

pair<int, int> Canvas::plot(int a, int b) {
	pair<int, int> point;
	point.second = a + axes.x;
	point.first = axes.y - b;
	return point;
}

void Canvas::print(ostream& dest) {
	for (int n = 0; n < h; ++n) {
		for (int m = 0; m < w; ++n) {
			dest << canvas[n][m];
		}
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

void Canvas::plotpoint(int a, int b, char c) {
	if (haveaxes == false) {
		cerr << "No Axes on Canvas" << endl;
	}
	else {
		pair<int, int> coord = plot(a, b);
		canvas[coord.first][coord.second] = c;
	}
}

void Canvas::plotpoint(int a, int b) {
	if (haveaxes == false) {
		cerr << "No Axes on Canvas" << endl;
	}
	else {
		pair<int, int> coord = plot(a, b);
		canvas[coord.first][coord.second] = '@';
	}
}

void Canvas::plotfunction(int (*func)(int), char c) {
	for (int n = 0; n < w; ++n) {
		plotpoint(n, func(n), c);
	}
}