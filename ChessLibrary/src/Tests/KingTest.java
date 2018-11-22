package Tests;

import static org.junit.Assert.*;

import org.junit.Test;

import java.util.ArrayList;
import SourceFiles.King;
import SourceFiles.Bishop;
import SourceFiles.Coordinate;
import SourceFiles.Field;

public class KingTest {

	@Test
	public void oneTestToRuleThemAll() {
		Field f = new Field(8,8);
		King king_guy = new King(0);
		
		Coordinate start = new Coordinate(0,0);
		Coordinate dest  = null;
		
		for(int i=-7; i<8; i++) {
			for(int j=-7; j<8; j++) {
				dest = new Coordinate(i,j);
				ArrayList<Coordinate> actualPath = king_guy.getMovementPath(start, dest, f);
				if(	(java.lang.Math.abs(i) < 2) &&
					(java.lang.Math.abs(j) < 2) ) {
					if(start.eq(dest)) {
						assertEquals(null, actualPath);
						continue;
					}
					assertEquals(1,actualPath.size());
					assertEquals(dest, actualPath.get(0));
				} else {
					assertEquals(null, actualPath);
				}
			}
		}
	}

}
