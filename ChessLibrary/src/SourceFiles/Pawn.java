package SourceFiles;

import java.util.ArrayList;
public class Pawn extends Piece{
	public Pawn(int team) {
		this.team = team;
		this.type = 6; // 6 is Pawn
	}
	public ArrayList<Coordinate> getMovementPath(Coordinate start, Coordinate dest, Field field){
		int deltaX = dest.x - start.x;
		int deltaY = dest.y - start.y;
		
		// Handle diagonal move
		if( (java.lang.Math.abs(deltaX) == 1) && (deltaY == direction()) ) {
			Piece target = field.at(dest);
			if( (target != null) && (target.team != this.team) ) {
				ArrayList<Coordinate> output = new ArrayList<Coordinate>();
				output.add(dest);
				return output;
			}
		}
		System.out.println("Pawn not diagonal");
		// The pawn cannot move sideways except in an attack.
		if(dest.x != start.x) { return null; }
		// Pawns can't attack by moving forward.
		if(field.at(dest) != null) { return null; }
		
		if(atStartingPosition(start)) {
			return firstMove(deltaY, start, dest);
		}
		else {
			return subsequentMove(deltaY,dest);
		}
	}

	private ArrayList<Coordinate> subsequentMove(int deltaY, Coordinate dest) {
		System.out.println("Subsequent Move");
		
		if(deltaY != direction()) {
			return null;
		}
		ArrayList<Coordinate> outputPath = new ArrayList<Coordinate>();
		outputPath.add(dest);
		return outputPath;
 	}
	
	private ArrayList<Coordinate> firstMove(int deltaY, Coordinate start, Coordinate dest){
		System.out.println("First Move");
		if(! ((deltaY == 2*direction()) || (deltaY == direction())) ) {
			return null;
		}
		ArrayList<Coordinate> outputPath = new ArrayList<Coordinate>();
		
		outputPath.add(new Coordinate(start.x, start.y+direction()) );
		if(deltaY == 2*direction()) {
			outputPath.add(new Coordinate(start.x, start.y+(2*direction())) );
		}
		return outputPath;
	}
	
	public ArrayList<Coordinate> getAllPossibleMoves(Coordinate start){
		ArrayList<Coordinate> output = new ArrayList<Coordinate>();
		
		// One forward
		output.add(new Coordinate(start.x, start.y+direction()) );
		// Two forward
		output.add(new Coordinate(start.x, start.y+(2*direction())) );
		// Diagonals
		output.add(new Coordinate(start.x+1, start.y+direction()) );
		output.add(new Coordinate(start.x-1, start.y+direction()) );
		return output;
	}
	
	private boolean atStartingPosition(Coordinate start) {
		return  (((start.y == 1) && (team == 1)) ||
				((start.y == 6) && (team == 0)));
	}
	
	public ArrayList<int[]> drawYourself(int size) {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int proportion = (int)(((double)size) / ((4.0+3.0+4.0) + (3.0*1.41421356237)));
		int length = (int)(((4+3+4)+ (3*1.41421356237)) * ((double) proportion));
		int height = (int)((6.0+(2.0*1.41421356237))* proportion);
		int startX = (int)((size - length)/2 + (( ((3.0/2.0)*1.41421356237) + 7) * proportion));
		int startY = (size - height)/2;
		int width1 = 2 * proportion;
		int width2 = 4 * proportion;
		int width3 = (int) (((double)width1)*1.41421356237);
		int width4 = (int) (((double)proportion)/1.41421356237);
		int width5 = 3 * proportion;
		int width6 = width2 + ((width3 - (2*width4)));
		
		points.add(new int[] {startX,startY});
		newPoint(points, width1, "SE");
		newPoint(points, width1, "W");
		newPoint(points, width2, "S");
		newPoint(points, width2, "NE");
		newPoint(points, width4, "NW");
		newPoint(points, width3, "E");
		
		newPoint(points, width3, "S");
		newPoint(points, width4, "NW");
		newPoint(points, width6, "SW");
		newPoint(points, width5, "W");
		newPoint(points, width6, "NW");
		newPoint(points, width4, "SW");
		newPoint(points, width3, "N");
		
		newPoint(points, width3, "E");
		newPoint(points, width4, "SW");
		newPoint(points, width2, "SE");
		newPoint(points, width2, "N");
		newPoint(points, width1, "W");
		newPoint(points, width1, "NE");
		
		return points;
	}
	
	private int direction() {
		return -1 + (2*team);
	}
}
 

 
