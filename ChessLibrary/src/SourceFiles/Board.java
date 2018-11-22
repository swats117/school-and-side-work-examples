package SourceFiles;
import java.util.ArrayList;

public class Board implements GlobalConstants {
	
	private int turn = 0;
	private int num_players = 2;
	Field field;
	private ArrayList<MoveRecord> moveHistory;
	
	public Board(int rows, int cols) {
		field = new Field(rows,cols);
		moveHistory = new ArrayList<MoveRecord>();
	}
	
	public int getTurn() {
		return Math.max(0, turn);
	}
	public Field getField() {
		return field;
	}
	
	public void addPiece (Piece p, Coordinate c) {
		if(!field.inBounds(c)) {
			return;
		}
		field.set(c, p);
	}
	
	public int move(Coordinate start, Coordinate dest) {
		System.out.println("A");
		Piece atckPiece = field.at(start);
		Piece targPiece = field.at(dest);
		System.out.println("B");
		int playerWhoseTurnItIs = (turn % num_players);
		int otherPlayer = 1 ^ playerWhoseTurnItIs; // Hack to get the other player 1^0=1 1^1=0 
		System.out.println("C");
		if( atckPiece == null ) { return NOMINAL; /* cannot move nothing, but too obvious for error */ }
		if( atckPiece.team != playerWhoseTurnItIs ) { return OUT_OF_TURN;}
		System.out.println("D");
		if( start.eq(dest) ) { return NOMINAL; /*They put the piece back*/ }
		System.out.println("E");
		if( !atckPiece.canMove(start, dest, field) ) {return MOVE_IS_NOT_POSSIBLE; }
		System.out.println("F");
		
		moveAndRecord(start, dest);
		
		if(inCheck(playerWhoseTurnItIs) ) {
			undoMove();
			return MUST_ESCAPE_CHECK;
		}
		if(inCheck(otherPlayer) && kingIsSurrounded(otherPlayer) && !canBlockToEscapeCheck(otherPlayer)) 
		{turn--; return CHECKMATE;}
		else if (inCheck(otherPlayer)) {return CHECK;}
		else if (kingIsSurrounded(otherPlayer) && !someNonKingPieceCanMove(otherPlayer)) 
		{turn--; return STALEMATE;}
		return NOMINAL;
	}

	private void moveAndRecord(Coordinate start, Coordinate dest) {
		moveHistory.add(new MoveRecord(start, dest, field.at(start), field.at(dest)));
		field.set(dest, field.at(start));
		field.set(start, null);
		turn++;
	}
	
	public MoveRecord undoMove() {
		if(turn==0) {return null;} // Can't undo nothing. 
		MoveRecord lastMove = moveHistory.get(moveHistory.size() - 1);
		field.set(lastMove.start, lastMove.attacker);
		field.set(lastMove.dest , lastMove.target  );
		turn--;
		moveHistory.remove(moveHistory.size() - 1);
		return lastMove;
	}
	
	private boolean someNonKingPieceCanMove(int team){
		ArrayList<Coordinate> traversal = field.noNullsTraverse();
		for(Coordinate start : traversal) {
			Piece anyPiece = field.at(start);
			if(anyPiece.type == KING) { continue; }
			if(anyPiece.team != team) { continue; }
			
			ArrayList<Coordinate> potentialMoves = anyPiece.getAllPossibleMoves(start);
			for(Coordinate dest : potentialMoves) {
				if(!anyPiece.canMove(start, dest, field)) { continue; }
				return true;
			}
		}
		return false;
	}
	
	public boolean inCheck(int team) {
		Coordinate kingCord = findKing(team);
		return isInDanger(kingCord);
	}
	
	public boolean kingIsSurrounded(int team) {
		
		Coordinate kingCord = findKing(team);
		Piece king = field.at(kingCord);
		// Try to move the king out of check.
		for(Coordinate exit : king.getAllPossibleMoves(kingCord)) {
			if(!king.canMove(kingCord, exit, field)) { continue; }
			moveAndRecord(kingCord, exit);
			if( isInDanger(exit) ) { undoMove(); continue; }
			undoMove();
			return false;
		}
		
		return true;
	}
	
	public boolean canBlockToEscapeCheck(int team){
		Coordinate kingCord = findKing(team);
		
		// Try to block all attackers with another piece.
		ArrayList<Coordinate> traversal = field.noNullsTraverse();
		for(Coordinate start : traversal) {
			Piece blocking_piece = field.at(start);
			if(blocking_piece.team != team) { continue; }
			if(blocking_piece.type == KING) { continue; }
			for(Coordinate dest : blocking_piece.getAllPossibleMoves(start)) {
				if(!blocking_piece.canMove(start, dest, field)) { continue; }
				moveAndRecord(start, dest);
				if(isInDanger(kingCord)) { undoMove(); continue; }
				undoMove();
				return true;
			}
		}
		return false;
	}
	
	// Searches entire board for king from team.
	public Coordinate findKing (int team) {
		ArrayList<Coordinate> traversal = field.noNullsTraverse();
		for(Coordinate kingCord: traversal) {
			Piece maybeKing     = field.at(kingCord);
			if(maybeKing.type != KING ) { continue; }
			if(maybeKing.team != team) { continue; }
			return kingCord;
		}
		return null;
	}
	
	// Searches entire board for enemy piece that can attack dest.
	public boolean isInDanger(Coordinate dest) {
		int team = field.at(dest).team;
		ArrayList<Coordinate> traversal = field.noNullsTraverse();
		for(Coordinate start: traversal) {
			Piece attacker = field.at(start);
			if(attacker.team == team) { continue; }
			if(!attacker.canMove(start, dest, field)) { continue; }
			return true;
		}
		return false;
	}
	
	public void setupNormalGame() {
		addPiece(new King(1),new Coordinate(4,0));
		addPiece(new King(0),new Coordinate(4,7));
		
		addPiece(new Queen(1),new Coordinate(3,0));
		addPiece(new Queen(0),new Coordinate(3,7));
		
		addPiece(new Bishop(1),new Coordinate(2,0));
		addPiece(new Bishop(1),new Coordinate(5,0));
		addPiece(new Bishop(0),new Coordinate(2,7));
		addPiece(new Bishop(0),new Coordinate(5,7));
		
		addPiece(new Knight(1),new Coordinate(1,0));
		addPiece(new Knight(1),new Coordinate(6,0));
		addPiece(new Knight(0),new Coordinate(1,7));
		addPiece(new Knight(0),new Coordinate(6,7));
		
		addPiece(new Rook(1),new Coordinate(0,0));
		addPiece(new Rook(1),new Coordinate(7,0));
		addPiece(new Rook(0),new Coordinate(0,7));
		addPiece(new Rook(0),new Coordinate(7,7));
		
		for(int i=0; i<8; i++) {
			addPiece(new Pawn(1), new Coordinate(i,1));
		}
		for(int i=0; i<8; i++) {
			addPiece(new Pawn(0), new Coordinate(i,6));
		}
	}
}


