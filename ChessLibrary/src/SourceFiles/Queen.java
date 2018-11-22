package SourceFiles;
import static org.junit.Assert.assertEquals;

import java.util.ArrayList;

public class Queen extends Piece{

	public Queen(int team) {
		this.type = 2; // 2 is Queen
		this.team = team;
	}
	
	public ArrayList<Coordinate> getMovementPath(Coordinate start, Coordinate dest, Field f){
		int deltaX = dest.x - start.x; 
		int deltaY = dest.y - start.y;
		
		if(java.lang.Math.abs(deltaX) == java.lang.Math.abs(deltaY)) {
			return diagonalPath(start, deltaX, deltaY);
		}
		if( (deltaX == 0) ^ (deltaY == 0) ) {
			return horizontalPath(start, deltaX, deltaY);
		}
		return null;
	}
	
	public ArrayList<Coordinate> getAllPossibleMoves(Coordinate start){
		ArrayList<Coordinate> output = new ArrayList<Coordinate>();
		
		for(int i=0; i<8; i++) {
			// HACK to get all 8 directions;
			int xDir = (((i+5) / 3) % 3) - 1;
			int yDir = ((i+5) % 3) - 1;
			for(int j=1; j<8; j++) {
				output.add(new Coordinate(start.x + j*xDir, start.y + j*yDir));
			}
		}
		return output;
	}
	
	public ArrayList<int[]> drawYourself(int size) {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int proportion = (int)(((double)size) / (6.0 * 1.41421356237 + 14.0));
		int length = (int)((6.0 * 1.41421356237 + 14.0) * proportion);
		int start =  (size - length)/2 + (int)((2.0 * 1.41421356237 - 1.0) * ((double)proportion));
		int width1 = 4 * proportion;
		int width2 = 1 * proportion;
		int width3 = 5 * proportion;
		int width4 = width3;
		int width5 = (int)(((double)width2)*1.41421356237);
		int width6 = (int)(((double)width1)/1.41421356237); 
		 
	 
		points.add(new int[] {start,start});
		newPoint(points, width1, "E");
		newPoint(points, width2, "SW");
		newPoint(points, width3, "SE");
		newPoint(points, width3, "N");
		newPoint(points, width5, "W");
		newPoint(points, width6, "NE");
		
		newPoint(points, width6, "SE");
		newPoint(points, width5, "W");
		newPoint(points, width3, "S");
		newPoint(points, width3, "NE");
		newPoint(points, width2, "NW");
		newPoint(points, width1, "E");
		
		newPoint(points, width1, "S");
		newPoint(points, width2, "NW");
		newPoint(points, width3, "SW");
		newPoint(points, width3, "E");
		newPoint(points, width5, "N");
		newPoint(points, width6, "SE");
		
		newPoint(points, width6, "SW");
		newPoint(points, width5, "N");
		newPoint(points, width3, "W");
		newPoint(points, width3, "SE");
		newPoint(points, width2, "NE");
		newPoint(points, width1, "S");
		
		newPoint(points, width1, "W");
		newPoint(points, width2, "NE");
		newPoint(points, width3, "NW");
		newPoint(points, width3, "S");
		newPoint(points, width5, "E");
		newPoint(points, width6, "SW");
		
		newPoint(points, width6, "NW");
		newPoint(points, width5, "E");
		newPoint(points, width3, "N");
		newPoint(points, width3, "SW");
		newPoint(points, width2, "SE");
		newPoint(points, width1, "W");
		
		newPoint(points, width1, "N");
		newPoint(points, width2, "SE");
		newPoint(points, width3, "NE");
		newPoint(points, width3, "W");
		newPoint(points, width5, "S");
		newPoint(points, width6, "NW");
		
		newPoint(points, width6, "NE");
		newPoint(points, width5, "S");
		newPoint(points, width3, "E");
		newPoint(points, width3, "NW");
		newPoint(points, width2, "SW");
		newPoint(points, width1, "N");
		
		return points;
	}
}
