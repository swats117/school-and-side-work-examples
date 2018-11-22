package GUI;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class GameScreen extends JPanel {

	CheckerboardCoordinateOverlay CCO;
	public Checkerboard checkerboard;
	ErrorMessage error_messages;
	
	GameScreen(){
		
		error_messages = new ErrorMessage("");
		setLayout(new BorderLayout());
		
		
		CCO = new CheckerboardCoordinateOverlay(8,8); 
		CCO.setPreferredSize(new Dimension(710,713));
		checkerboard = new Checkerboard(error_messages);
		checkerboard.setPreferredSize(new Dimension(696,696));
		CCO.add(checkerboard, BorderLayout.CENTER);
		
		GameControls gc = new GameControls(checkerboard, error_messages);
//		gc.setPreferredSize(new Dimension(714,15));
		add(gc,BorderLayout.NORTH);
		
		
		
		add(CCO, BorderLayout.CENTER);
	}
	
}

class GameControls extends JPanel implements ActionListener {
	Checkerboard checkerboard;
	JButton undo;
	JButton new_game;
	JButton forfeit;
	
	int numClicks;
	public GameControls(Checkerboard checkerboard, ErrorMessage error_messages){
		
		this.checkerboard = checkerboard;
		
		forfeit = new JButton("forfeit");
		forfeit.addActionListener(new NewGameActionListener()); 
		forfeit.setMargin(new Insets(0, 0, 0, 0));
		
		undo = new JButton("undo");
		undo.addActionListener(new UndoActionListener()); 
		undo.setMargin(new Insets(0, 0, 0, 0));
		
		new_game = new JButton("new game");
		new_game.addActionListener(new NewGameActionListener());
		new_game.setMargin(new Insets(0, 0, 0, 0));
		
		
		add(new_game);
		add(undo);
		add(forfeit);
		add(error_messages);
		
	}
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	private class UndoActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
	        checkerboard.undo();
		}
	}
	private class NewGameActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
	        checkerboard.newGame();
		}
	}
	
	
}
