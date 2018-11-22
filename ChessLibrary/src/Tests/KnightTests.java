package Tests;
import static org.junit.Assert.*;

import SourceFiles.*;
import org.junit.Test;
import java.util.ArrayList;

public class KnightTests {

	@Test
	public void correctKnightMoves() {
		Field f = new Field(8,8);
		Knight knight_guy = new Knight(0);
		
		ArrayList<Coordinate> expectedPath = null;
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		
		int[] validMovesX = {1,1,2,2,-1,-1,-2,-2};
		int[] validMovesY = {2,-2,1,-1,2,-2,1,-1};
		
		for(int i=0; i<validMovesX.length; i++) {
			Coordinate dest = new Coordinate(validMovesX[i],validMovesY[i]);
			
			expectedPath = new ArrayList<Coordinate>();
			expectedPath.add(dest);
			
			actualPath = knight_guy.getMovementPath(start, dest, f);

			assertEquals(expectedPath, actualPath);
		}
	}
	
	@Test
	public void moveToInvalidLocationsTest() {
		Field f = new Field(8,8);
		Knight queen_guy = new Knight(0);
		
		ArrayList<Coordinate> expectedPath = null;
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest = null;
		
		for(int i=-7; i<8; i++) {
			for(int j=-7; j<8; j++) {
				
				if( !(((java.lang.Math.abs(i) == 1) ^ (java.lang.Math.abs(j) == 1)) &&
					  ((java.lang.Math.abs(i) == 2) ^ (java.lang.Math.abs(j) == 2))) ){
					dest = new Coordinate(i, j);
					actualPath = queen_guy.getMovementPath(start, dest, f);
					assertEquals(expectedPath, actualPath);
				}
				
			}
		}
	}
}
