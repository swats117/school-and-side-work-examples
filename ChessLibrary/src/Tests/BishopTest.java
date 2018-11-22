package Tests;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;

import SourceFiles.Coordinate;
import SourceFiles.Field;
import SourceFiles.Bishop;

public class BishopTest {

	@Test
	public void cannotMoveToCurrentLocationTest() {
		Field f = new Field(8,8);
		Bishop bishop_guy = new Bishop(0);
		Coordinate x = new Coordinate(0,0);
		assertEquals(null, bishop_guy.getMovementPath(x,x,f));
	}
	@Test
	public void moveToValidLocationsTest() {
		Field f = new Field(8,8);
		Bishop bishop_guy = new Bishop(0);
		
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest = null;
		
		for(int i=0; i<4; i++) {
			// HACK to get diagonal directions;
			int xDir = 1 - ((i/2) * 2);
			int yDir = 1 - ((i % 2) * 2);
			for(int j=1; j<8; j++) {
				dest = new Coordinate(j*xDir, j*yDir);
				actualPath = bishop_guy.getMovementPath(start, dest, f);
				assertEquals(j, actualPath.size());
			}
		}
	}
	@Test
	public void moveToInvalidLocationsTest() {
		Field f = new Field(8,8);
		Bishop bishop_guy = new Bishop(0);
		
		ArrayList<Coordinate> expectedPath = null;
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest = null;
		
		for(int i=-7; i<8; i++) {
			for(int j=-7; j<8; j++) {
				if( !(java.lang.Math.abs(i)==java.lang.Math.abs(j)) ) {
					dest = new Coordinate(i, j);
					actualPath = bishop_guy.getMovementPath(start, dest, f);
					assertEquals(expectedPath, actualPath);
				}
				
			}
		}
	}
	@Test
	public void upToTheRightTest() {
		Field f = new Field(8,8);
		Bishop bishop_guy = new Bishop(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(7,7);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(i,i));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}
	@Test
	public void downToTheRightTest() {
		Field f = new Field(8,8);
		Bishop bishop_guy = new Bishop(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(7,-7);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(i,-i));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}
	@Test
	public void downToTheLeftTest() {
		Field f = new Field(8,8);
		Bishop bishop_guy = new Bishop(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(-7,-7);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(-i,-i));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}
	@Test
	public void upToTheLeftTest() {
		Field f = new Field(8,8);
		Bishop bishop_guy = new Bishop(0);
		
		ArrayList<Coordinate> expectedPath = new ArrayList<Coordinate>();
		ArrayList<Coordinate> actualPath = null;
		Coordinate start = new Coordinate(0,0);
		Coordinate dest =  new Coordinate(-7,7);
		
		for(int i=1; i<8; i++) {
			expectedPath.add(new Coordinate(-i,i));
		}
		actualPath = bishop_guy.getMovementPath(start, dest, f);
		assertEquals(expectedPath.size(), actualPath.size());
		for(int i=0; i<expectedPath.size(); i++) {
			assertEquals(true, expectedPath.get(i).eq(actualPath.get(i)));
		}
	}
}
