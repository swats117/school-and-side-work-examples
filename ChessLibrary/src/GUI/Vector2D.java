package GUI;

import SourceFiles.Coordinate;

public class Vector2D extends Coordinate {
	Vector2D(int x, int y){ super(x,y); }
	

	public Vector2D add(VectorFloat2D rhs) {
		return new Vector2D( ((int)rhs.x) + x , ((int)rhs.y) + y );
	}
	public Vector2D sub(Vector2D rhs) {
		return new Vector2D(x - rhs.x, y - rhs.y);
	}
	public void print() {
		System.out.print("Vector2D x:");
		System.out.print(x);
		System.out.print(" y:");
		System.out.println(y);
	}
}
