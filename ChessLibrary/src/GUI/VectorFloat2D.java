package GUI;

import SourceFiles.Coordinate;

public class VectorFloat2D {
	public double x;
	public double y;
	
	public VectorFloat2D(double i, double j) {
		x=i; y=j;
	}
	
	public boolean eq(Coordinate rhs) {
		return (this.x == rhs.x && this.y == rhs.y);
	}
	
	public VectorFloat2D add(VectorFloat2D rhs) {
		x += rhs.x;
		y += rhs.y;
		return this;
	}
	
	public VectorFloat2D mult(int coef) {
		return new VectorFloat2D(x * coef, y * coef);
	}
	
	public void print() {
		System.out.print("VectorFloat2D x:");
		System.out.print(x);
		System.out.print(" y:");
		System.out.println(y);
	}
}
