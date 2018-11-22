package SourceFiles;
import java.util.ArrayList;
public class King extends Piece{
	public King(int team){
		this.type = 1; // 1 is King
		this.team = team;
	}
	
	public ArrayList<Coordinate> getMovementPath(Coordinate start, Coordinate dest, Field f) {
		if(start.eq(dest)) { return null; }
		
		int deltaX = dest.x - start.x;
		int deltaY = dest.y - start.y;
		if( (-1 <= deltaX) && (deltaX <= 1) &&
			(-1 <= deltaY) && (deltaY <= 1)) {
			ArrayList<Coordinate> outputPath = new ArrayList<Coordinate>();
			outputPath.add(dest);
			return outputPath;
		} 
		else {
			return null;
		}
	}
	public ArrayList<Coordinate> getAllPossibleMoves(Coordinate c) {
		ArrayList<Coordinate> possibleMoves = new ArrayList<Coordinate>();
		possibleMoves.add(new Coordinate(c.x + -1, c.y + -1));
		possibleMoves.add(new Coordinate(c.x + -1, c.y + 0));
		possibleMoves.add(new Coordinate(c.x + -1, c.y + 1));
		possibleMoves.add(new Coordinate(c.x + 0, c.y + -1));
		possibleMoves.add(new Coordinate(c.x + 0, c.y + 1));
		possibleMoves.add(new Coordinate(c.x + 1, c.y + -1));
		possibleMoves.add(new Coordinate(c.x + 1, c.y + 0));
		possibleMoves.add(new Coordinate(c.x + 1, c.y + 1));
		return possibleMoves;
	}
	
	public ArrayList<int[]> drawYourself(int size) {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int proportion = (int)(((double)size) / ((1.3)*(6.0 * 1.41421356237 + 14.0)));
		int alternate_proportion = (int)(((double)size) / (6.0 * 1.41421356237 + 14.0)) - 1;
		proportion = proportion < alternate_proportion ? proportion : alternate_proportion;
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
