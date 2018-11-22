package SourceFiles;
import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
public class Rook extends Piece{
	
	public Rook(int team){
		this.type = 3; // 3 is Rook
		this.team = team;
	}

	public ArrayList<Coordinate> getMovementPath(Coordinate start, Coordinate dest, Field f){
		int deltaX = dest.x - start.x;
		int deltaY = dest.y - start.y;
		
		if( (deltaX==0) ^ (deltaY==0) ) {
			return horizontalPath(start, deltaX, deltaY);
		}
		return null;
	}
	
	public ArrayList<Coordinate> getAllPossibleMoves(Coordinate start){
		ArrayList<Coordinate> output = new ArrayList<Coordinate>();
		
		for(int i=0; i<4; i++) {
			// HACK to get the 4 cardinal directions;
			int xDir = (i%2)*(1 - ((i/2)*2)); // 0 1 0 -1
			int yDir = ((i+1)%2)*(1 - ((i/2)*2)); // 1 0 -1 0
			for(int j=1; j<8; j++) {
				output.add(new Coordinate(start.x + j*xDir, start.y + j*yDir));
				
			}
		}
		return output;
	}
	
	public ArrayList<int[]> drawYourself(int size) {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		
		int proportion = (int)(((double)size)/16.0);
		int length = 16 * proportion;
		
		int startX = (size - length)/2 + 8 * proportion;
		int startY = (size - length)/2;
		int width1 = 2 * proportion;
		int width2 = 1 * proportion;
		int width3 = 5 * proportion;
		
		
		
		points.add(new int[] {startX,startY});
		newPoint(points, width1, "SE");
		newPoint(points, width2, "W");
		newPoint(points, width3, "S");
		newPoint(points, width3, "E");
		newPoint(points, width2, "N");
		newPoint(points, width1, "SE");
		
		newPoint(points, width1, "SW");
		newPoint(points, width2, "N");
		newPoint(points, width3, "W");
		newPoint(points, width3, "S");
		newPoint(points, width2, "E");
		newPoint(points, width1, "SW");
		
		newPoint(points, width1, "NW");
		newPoint(points, width2, "E");
		newPoint(points, width3, "N");
		newPoint(points, width3, "W");
		newPoint(points, width2, "S");
		newPoint(points, width1, "NW");
		
		newPoint(points, width1, "NE");
		newPoint(points, width2, "S");
		newPoint(points, width3, "E");
		newPoint(points, width3, "N");
		newPoint(points, width2, "W");
		
		return points;
	}
}
