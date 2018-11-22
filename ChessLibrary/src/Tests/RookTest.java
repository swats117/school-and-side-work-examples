package Tests;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;

import SourceFiles.Bishop;
import SourceFiles.Coordinate;
import SourceFiles.Field;
import SourceFiles.King;
import SourceFiles.Rook;

public class RookTest {

	@Test
	public void cannotMoveToCurrentLocationTest() {
		Field f = new Field(8,8);
		Rook rook_guy = new Rook(0);
		Coordinate x = new Coordinate(0,0);
		assertEquals(null, rook_guy.getMovementPath(x,x,f));
	}
	@Test
	public void moveToValidLocationsTest() {
		Field f = new Field(8,8);
		Rook rook_guy = new Rook(0);
		
		ArrayList<Coordinate> expectedPath = null;
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest = null;
		
		for(int i=0; i<4; i++) {
			// HACK to get the 4 cardinal directions;
			int xDir = (i%2)*(1 - ((i/2)*2)); // 0 1 0 -1
			int yDir = ((i+1)%2)*(1 - ((i/2)*2)); // 1 0 -1 0
			for(int j=1; j<8; j++) {
				dest = new Coordinate(j*xDir, j*yDir);
				actualPath = rook_guy.getMovementPath(start, dest, f);
				assertEquals(j, actualPath.size());
			}
		}
	}
	@Test
	public void moveToInvalidLocationsTest() {
		Field f = new Field(8,8);
		Rook rook_guy = new Rook(0);
		
		ArrayList<Coordinate> expectedPath = null;
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest = null;
		
		for(int i=-7; i<8; i++) {
			for(int j=-7; j<8; j++) {
				if( !((i==0) ^ (j==0)) ) {
					dest = new Coordinate(i, j);
					actualPath = rook_guy.getMovementPath(start, dest, f);
					assertEquals(expectedPath, actualPath);
				}
				
			}
		}
	}
	@Test
	public void toTheRightTest() {
		Field f = new Field(8,8);
		Rook bishop_guy = new Rook(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(7,0);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(i,0));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}
	@Test
	public void toTheDownTest() {
		Field f = new Field(8,8);
		Rook bishop_guy = new Rook(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(0,-7);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(0,-i));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}
	@Test
	public void toTheLeftTest() {
		Field f = new Field(8,8);
		Rook bishop_guy = new Rook(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(-7,0);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(-i,0));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}
	@Test
	public void toTheUpTest() {
		Field f = new Field(8,8);
		Rook bishop_guy = new Rook(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(0,7);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(0,i));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}

}
