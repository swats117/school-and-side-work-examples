package GUI;

import javax.swing.JLabel;

import SourceFiles.GlobalConstants;

public class ErrorMessage extends JLabel implements GlobalConstants {
	public ErrorMessage(String blah) {
		super(blah);
	}
	
	public void handleErrorMessage(int error){
		System.out.println("printing error");
		switch (error) {
			case NOMINAL: this.setText(""); break ;
			case MUST_MOVE_A_PIECE: this.setText("Must move a piece."); break ;
			case CANNOT_ATTACK_YOUR_OWN_PIECE: this.setText("Cannot attack your own piece"); break ;
			case ATTACK_PATH_IS_NOT_CLEAR: this.setText("Attack path is not clear."); break ;
			case MOVE_IS_NOT_POSSIBLE: this.setText("Move is not Possible."); break ;
			case CHECK: this.setText("Check"); break ;
			case CHECKMATE: this.setText("Checkmate"); break ;
			case STALEMATE: this.setText("Stalemate"); break ;
			case MUST_ESCAPE_CHECK: this.setText("Must escape Check."); break ;
		}
	}
}
