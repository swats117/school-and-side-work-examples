package SourceFiles;
import java.util.ArrayList;

public class Field {
	Piece[][] field;
	int ROWS;
	int COLS;
	public Field(int rows, int cols) {
		field = new Piece[rows][cols];
		ROWS = rows;
		COLS = cols;
	}
	public Piece at(Coordinate c) {
		if(! inBounds(c)) {
			return null;
		}
		return field[c.x][c.y];
	}
	public void set(Coordinate c, Piece p) {
		if(! inBounds(c)) {
			return;
		}
		field[c.x][c.y] = p;
	}
	public boolean inBounds(Coordinate c) {
		if(	c.x >= 0 &&
			c.x < ROWS &&
			c.y >= 0 &&
			c.y < COLS ) {
			return true;
		}
		return false;
	}
	public ArrayList<Coordinate> noNullsTraverse() {
		ArrayList<Coordinate> output = new ArrayList<Coordinate>();
		for(int i=0; i<ROWS; i++) {
			for(int j=0; j<COLS; j++) {
				if(field[i][j] != null) {
					output.add(new Coordinate(i,j));
				}
			}
		}
		return output;
	}
}
