package SourceFiles;
import java.util.ArrayList;
import java.awt.Color;
import java.awt.Polygon;
import GUI.ColoredPolygon;

public abstract class Piece implements GlobalConstants{
	
	public int team;
	public int type;
	public abstract ArrayList<Coordinate> getMovementPath(Coordinate start, Coordinate dest, Field f);
	public abstract ArrayList<Coordinate> getAllPossibleMoves(Coordinate start);
	protected abstract ArrayList<int[]>   drawYourself(int size);
	public ColoredPolygon getColoredPolygon(int size) {
		ArrayList<int[]> points = drawYourself(size);
		
		int[] x = new int[points.size()];
		int[] y = new int[points.size()];
		for(int i=0; i<points.size(); i++) {
			x[i] = points.get(i)[0];
			y[i] = points.get(i)[1];
		}
		return new ColoredPolygon(x, y, points.size(), (team == 0 ? TEAM_ONE_COLOR : TEAM_TWO_COLOR) );
	};

	public boolean canMove(Coordinate start, Coordinate dest, Field field) {
		System.out.println("G");
		if(!field.inBounds(start) || !field.inBounds(dest)) { return false; }
		Piece atckPiece = field.at(start);
		Piece targPiece = field.at(dest );
		if((targPiece != null) && (atckPiece.team == targPiece.team)) { return false; }
		System.out.println(start.x);
		System.out.println(start.y);
		System.out.println(dest.x);
		System.out.println(dest.y);
		ArrayList<Coordinate> movementPath = atckPiece.getMovementPath(start, dest, field);
		System.out.println("H");
		if( movementPath == null ) { return false; }
		System.out.println("Attack path not null");
		if( !isPathClear(movementPath, field)) { return false; }
		System.out.println("end Can Move");
		return true;
	}
	
	public boolean isPathClear(ArrayList<Coordinate> atckPath, Field field) {
		// See if any point along the attack path is occupied.
		// The last point has been already been checked.
		System.out.println("error");
		System.out.println(atckPath.size() - 1);
		for(int i=0; i<(atckPath.size() - 1); i++) {
			if(field.at(atckPath.get(i)) == null) {
				continue;
			}
			return false;
		}
		return true;
	}
	
	
			
	protected ArrayList<Coordinate> diagonalPath(Coordinate start, int deltaX, int deltaY) {
		ArrayList<Coordinate> outputPath = new ArrayList<Coordinate>();
		int X_dir = signOfInt(deltaX);
		int Y_dir = signOfInt(deltaY);
		int absDeltaX = java.lang.Math.abs(deltaX);
		
		for(int i=1; i<=absDeltaX; i++) {
			Coordinate pointInPath = new Coordinate(start.x+(i*X_dir), start.y+(i*Y_dir));
			outputPath.add(pointInPath);
		}
		return outputPath;
	}
	
	protected ArrayList<Coordinate> horizontalPath(Coordinate start, int deltaX, int deltaY){
		ArrayList<Coordinate> outputPath = new ArrayList<Coordinate>();
		
		// Only one of these for loops will execute.
		for(int i=1; i<= java.lang.Math.abs(deltaX); i++) {
			outputPath.add(new Coordinate(start.x + i*signOfInt(deltaX),  start.y));
		}
		for(int i=1; i<= java.lang.Math.abs(deltaY); i++) {
			outputPath.add(new Coordinate(start.x,  i*signOfInt(deltaY) + start.y));
		}
		return outputPath;
	}
	
	protected void newPoint(ArrayList<int[]> points, int width, String dir) {
		dir = dir.toUpperCase();
		int[] oldPoint = points.get(points.size()-1);
		int[] newPoint = new int[]{oldPoint[0],oldPoint[1]};
		if(dir.contains("N")) {
			newPoint[1] -= width;
		}
		if(dir.contains("E")) {
			newPoint[0] += width;
		}
		if(dir.contains("S")) {
			newPoint[1] += width;
		}
		if(dir.contains("W")) {
			newPoint[0] -= width;
		}
		points.add(newPoint);
	}
	
	public int signOfInt(int x) { return java.lang.Integer.signum(x); }

}