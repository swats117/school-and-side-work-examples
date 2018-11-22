package GUI;

import javax.swing.*;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.ArrayList;

import SourceFiles.*;

public class GUIMain extends JFrame {

	
	GameScreen game_screen;
	
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new GUIMain().setVisible(true);
			}
		});
	}
	
	public GUIMain() {
		
		setTitle("Space Chess!");
		game_screen = new GameScreen();
		add(game_screen);
		pack();
		game_screen.checkerboard.createBoard(8,8);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}

