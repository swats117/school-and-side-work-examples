package SourceFiles;

public class Coordinate {
	public int x;
	public int y;
	
	public Coordinate(int i, int j) {
		x=i; y=j;
	}
	
	public boolean eq(Coordinate rhs) {
		return (this.x == rhs.x && this.y == rhs.y);
	}
}
