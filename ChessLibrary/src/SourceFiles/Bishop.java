package SourceFiles;
import static org.junit.Assert.assertEquals;

import java.util.ArrayList; 
public class Bishop extends Piece {

	public Bishop(int team){
		this.type = 4; // 4 is Bishop
		this.team = team;
	}
	
	public ArrayList<Coordinate> getMovementPath(Coordinate start, Coordinate dest, Field f){
		int deltaX = dest.x - start.x;
		int deltaY = dest.y - start.y;
		int absDeltaX = java.lang.Math.abs(deltaX);
		int absDeltaY = java.lang.Math.abs(deltaY);
		
		if(absDeltaX == absDeltaY) {
			return diagonalPath(start, deltaX, deltaY);
		}
		return null;
	}
	public ArrayList<Coordinate> getAllPossibleMoves(Coordinate start){
		ArrayList<Coordinate> output = new ArrayList<Coordinate>();
		
		for(int i=0; i<4; i++) {
			// HACK to get diagonal directions;
			int xDir = 1 - ((i/2) * 2);
			int yDir = 1 - ((i % 2) * 2);
			for(int j=1; j<8; j++) {
				output.add(new Coordinate(start.x + j*xDir, start.y + j*yDir));
			}
		}
		return output;
	}
	
	public ArrayList<int[]> drawYourself(int size) {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int proportion = (int)(((double)size) / (16 * 1.2));
		int length = 16*proportion;
		
		int start = (size-length)/2;
		int width1 = 4*proportion;
		int width2 = 1*proportion;
		int width3 = 5*proportion;
		

		
		points.add(new int[] {start,start});
		newPoint(points, width1, "E");
		newPoint(points, width2, "SW");
		newPoint(points, width3, "SE");
		newPoint(points, width3, "NE");
		newPoint(points, width2, "NW");
		newPoint(points, width1, "E");
		
		newPoint(points, width1, "S");
		newPoint(points, width2, "NW");
		newPoint(points, width3, "SW");
		newPoint(points, width3, "SE");
		newPoint(points, width2, "NE");
		newPoint(points, width1, "S");
		
		newPoint(points, width1, "W");
		newPoint(points, width2, "NE");
		newPoint(points, width3, "NW");
		newPoint(points, width3, "SW");
		newPoint(points, width2, "SE");
		newPoint(points, width1, "W");
		
		newPoint(points, width1, "N");
		newPoint(points, width2, "SE");
		newPoint(points, width3, "NE");
		newPoint(points, width3, "NW");
		newPoint(points, width2, "SW");
		
		return points;
	}
	
}
