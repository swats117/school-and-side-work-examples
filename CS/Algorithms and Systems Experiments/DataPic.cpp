#import <cstdio>
#import <vector>
using namespace std;


class point{

private:

	double x_cord;
	double y_cord;
	double z_cord;
public:

	point(double x, double y, double z): x_cord(x), y_cord(y), z_cord(z){

	}

	double distance(point other){
		return 0.0;
	}

};


// v  -108.5362 212.9854 190.8554
// sample line in file.
vector<point> load_in_points(char* filename){

	vector<point> points;

	double x,y,z;
	FILE* datfile = fopen(filename, "r");

	int error;
	while((error=fscanf(datfile, " v %lf %lf %lf ", &x, &y, &z))!=-1){
		printf("line recieved: v %lf %lf %lf\n",x,y,z);
	}

	if(error==-1){
		printf("ERROR!!\n");
	}

	points.push_back(point(x,y,z));

	return points;
}

int main(){

	vector<point> points = load_in_points("3dpoints.dat");


	return 0;
}






