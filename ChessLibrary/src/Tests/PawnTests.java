package Tests;

import static org.junit.Assert.assertEquals;

import java.util.ArrayList;

import org.junit.Test;

import SourceFiles.Coordinate;
import SourceFiles.Field;
import SourceFiles.Pawn;

public class PawnTests {

	@Test
	public void move1Test() {
		Field f = new Field(8,8);
		Pawn pawn_guy = new Pawn(0);
		
		// Move pawn forward 1 after first move.
		Coordinate start = new Coordinate(0,3);
		Coordinate dest  = new Coordinate(0,4);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		expectedPath.add(new Coordinate(0,4));
		ArrayList<Coordinate> actualPath = pawn_guy.getMovementPath(start, dest, f);
		
		assertEquals(true, expectedPath.get(0).eq(actualPath.get(0)));
	}
	@Test
	public void move2Test() {
		Field f = new Field(8,8);
		Pawn pawn_guy = new Pawn(0);
		
		// Move pawn forward 2.
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		expectedPath.add(new Coordinate(0,2));
		expectedPath.add(new Coordinate(0,3));
		
		
		Coordinate start = new Coordinate(0,1);
		Coordinate dest = new Coordinate(0,3);
		
		ArrayList<Coordinate> actualPath = pawn_guy.getMovementPath(start, dest, f);
		
		for(int i=0; i<2; i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
		
	}
	
	@Test
	public void moveTwoInSubsequentTest() {
		Field f = new Field(8,8);
		Pawn pawn_guy = new Pawn(0);
		
		//Move pawn once.
		Coordinate start = new Coordinate(0,1);
		Coordinate dest = new Coordinate(0,2);
		pawn_guy.getMovementPath(start, dest, f);

		//Try to move pawn by two after first move.
		start = new Coordinate(0,2);
		dest  = new Coordinate(0,4);
		ArrayList<Coordinate> actualPath = pawn_guy.getMovementPath(start, dest, f);
		
		assertEquals(null, actualPath);
	}
	@Test
	public void diagonalAttackTest() {
		Field f = new Field(8,8);
		Pawn pawn_guy = new Pawn(0);
		Pawn targ_guy = new Pawn(1);
		
		//Move pawn once.
		Coordinate start = new Coordinate(1,1);
		Coordinate dest = new Coordinate(2,2);
		
		f.set(dest, targ_guy);
		
		assertEquals(true, dest.eq(pawn_guy.getMovementPath(start, dest, f).get(0)));

		dest = new Coordinate(0,2);
		f.set(dest, targ_guy);
		
		assertEquals(true, dest.eq(pawn_guy.getMovementPath(start, dest, f).get(0)));
	}
	
	@Test
	public void moveBackwardsAndSidewaysTest() {
		Field f = new Field(8,8);
		Pawn pawn_guy = new Pawn(0);
		
		//Try to move pawn backwards.
		Coordinate start = new Coordinate(0,0);
		Coordinate dest  = new Coordinate(0,-1);
		ArrayList<Coordinate> actualPath = pawn_guy.getMovementPath(start, dest, f);
				
		assertEquals(null, actualPath);
		
		//Try to move pawn sideways.
		start = new Coordinate(0,0);
		dest  = new Coordinate(1,0);
		actualPath = pawn_guy.getMovementPath(start, dest, f);
		
		assertEquals(null, actualPath);
	}
			
}
