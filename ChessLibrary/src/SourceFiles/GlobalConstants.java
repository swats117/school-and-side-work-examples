package SourceFiles;

import java.awt.Color;

public interface GlobalConstants {
	public static final int NOMINAL = 0;
	public static final int NOTHING = 0;
	public static final int KING = 1;
	public static final int QUEEN = 2; 
	public static final int ROOK = 3;
	public static final int BISHOP = 4;
	public static final int KNIGHT = 5;
	public static final int PAWN = 6;
	public static final int MUST_MOVE_A_PIECE = 7;
	public static final int OUT_OF_TURN = 8;
	public static final int CANNOT_ATTACK_YOUR_OWN_PIECE = 9;
	public static final int ATTACK_PATH_IS_NOT_CLEAR = 10;
	public static final int MOVE_IS_NOT_POSSIBLE = 11;
	public static final int MUST_ESCAPE_CHECK = 12;
	public static final int CHECK = 13;
	public static final int CHECKMATE = 14;
	public static final int STALEMATE = 15;
	// Return Animation frames must be a multiple of 2
	public static final int RETURN_ANIMATION_FRAMES = 38;
	public static final Color TEAM_ONE_COLOR = Color.BLUE;
	public static final Color TEAM_TWO_COLOR = Color.ORANGE;
}
