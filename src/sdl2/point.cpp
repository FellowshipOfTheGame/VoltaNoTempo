#include <iostream>

using namespace std;

// Class Point

class Point {

private:
	int xval, yval;

public:

	//Contructor setting zero by default
	Point(int x=0, int y=0) {
		xval = x;
		yval = y;
	}

	//Extractors
	int x() { return xval; }
  	int y() { return yval; }

  	// Set point
  	void set(int x, int y) {
  		xval = x;
  		yval = y;
  	}


};