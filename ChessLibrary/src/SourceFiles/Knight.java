package SourceFiles;
import java.util.ArrayList;

public class Knight extends Piece{
	public Knight(int team) {
		this.team = team; 
		this.type = 5; // 5 is Knight
	}
	public ArrayList<Coordinate> getMovementPath(Coordinate start, Coordinate dest, Field f) {
		int deltaX = dest.x - start.x;
		int deltaY = dest.y - start.y;
		if((deltaX==0) || (deltaY==0)) {
			return null;
		}
		if(3 != (java.lang.Math.abs(deltaX) + java.lang.Math.abs(deltaY)) ) {
			return null;
		}
		ArrayList<Coordinate> outputPath = new ArrayList<Coordinate>();
		outputPath.add(dest);
		return outputPath;
	}
	public ArrayList<Coordinate> getAllPossibleMoves(Coordinate start){
		ArrayList<Coordinate> output = new ArrayList<Coordinate>();
		output.add(new Coordinate( (start.x + -2), (start.y + -1) ));
		output.add(new Coordinate( (start.x + -2), (start.y +  1) ));
		output.add(new Coordinate( (start.x + -1), (start.y + -2) ));
		output.add(new Coordinate( (start.x + -1), (start.y +  2) ));
		output.add(new Coordinate( (start.x +  1), (start.y + -2) ));
		output.add(new Coordinate( (start.x +  1), (start.y +  2) ));
		output.add(new Coordinate( (start.x +  2), (start.y + -1) ));
		output.add(new Coordinate( (start.x +  2), (start.y +  1) ));
		return output;
	}
	
	
	public ArrayList<int[]> drawYourself(int size){
		
		int proportion = size / 20;
		int length = 20 * proportion;
		int startX = (size - length) / 2 + (5 * proportion) ;
		int startY = (size - length)/ 2 + (2 * proportion) ;
		int width1 = 2 * proportion;
		int width2 = 1 * proportion;
		int width3 = 6 * proportion; // width3 > 2*width 6
		int width4 = (width3 - (2*( width1 - width2)))/2; 
		int width5 = (width3/2) + width4 + width2; // makes piece look like 2:1 ratio of knight.
		
		ArrayList<int[]> points = new ArrayList<int[]>();
		points.add(new int[] {startX,startY});
		newPoint(points, width1, "NE");
		newPoint(points, width2, "S");
		newPoint(points, width3, "E");
		newPoint(points, width2, "N");
		newPoint(points, width1, "SE");
		
		newPoint(points, width1, "SW");
		newPoint(points, width2, "N");
		newPoint(points, width4, "W");
		newPoint(points, width5, "S");
		newPoint(points, width5, "E");
		newPoint(points, width4, "N");
		newPoint(points, width2, "W");
		newPoint(points, width1, "NE");
		
		newPoint(points, width1, "SE");
		newPoint(points, width2, "W");
		newPoint(points, width3, "S");
		newPoint(points, width2, "E");
		newPoint(points, width1, "SW");
		
		newPoint(points, width1, "NW");
		newPoint(points, width2, "E");
		newPoint(points, width4, "N");
		newPoint(points, width5, "W");
		newPoint(points, width5, "S");
		newPoint(points, width4, "E");
		newPoint(points, width2, "N");
		newPoint(points, width1, "SE");
		
		newPoint(points, width1, "SW");
		newPoint(points, width2, "N");
		newPoint(points, width3, "W");
		newPoint(points, width2, "S");
		newPoint(points, width1, "NW");
		
		newPoint(points, width1, "NE");
		newPoint(points, width2, "S");
		newPoint(points, width4, "E");
		newPoint(points, width5, "N");
		newPoint(points, width5, "W");
		newPoint(points, width4, "S");
		newPoint(points, width2, "E");
		newPoint(points, width1, "SW");
		
		newPoint(points, width1, "NW");
		newPoint(points, width2, "E");
		newPoint(points, width3, "N");
		newPoint(points, width2, "W");
		newPoint(points, width1, "NE");
		
		newPoint(points, width1, "SE");
		newPoint(points, width2, "W");
		newPoint(points, width4, "S");
		newPoint(points, width5, "E");
		newPoint(points, width5, "N");
		newPoint(points, width4, "W");
		newPoint(points, width2, "S");
		newPoint(points, width1, "NW");
		
		return points;
	}
}
