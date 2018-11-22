package Tests;

import static org.junit.Assert.*;

import org.junit.Test;
import SourceFiles.*;

public class BoardTest {

	@Test
	public void setupChessGametest() {
		Board board_guy = new Board(8,8);
		board_guy.setupNormalGame();
	}
	

}
