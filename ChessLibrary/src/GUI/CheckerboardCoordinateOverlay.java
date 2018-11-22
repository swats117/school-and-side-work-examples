package GUI;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.Box;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class CheckerboardCoordinateOverlay extends JPanel{
	public CheckerboardCoordinateOverlay(int rows, int cols){
		setLayout(new BorderLayout());
		
		LettersAcrossTheTop letters = new LettersAcrossTheTop(rows);
		letters.setPreferredSize(new Dimension(730,13));
		NumbersDownTheLeft numbers  = new NumbersDownTheLeft(cols);
		
		add(letters, BorderLayout.NORTH);
		add(numbers, BorderLayout.WEST);
	}
}

class NumbersDownTheLeft extends JPanel{
	int cols;
	NumbersDownTheLeft(int cols){
		this.cols = cols;
	}
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		for(int i=cols; i>=1; i--) {
			g.drawString(Integer.toString(cols - i + 1), 0, 
					(i * (getHeight()/cols)) - (getHeight()/(2*cols)) + 5);
		}
	}
}

class LettersAcrossTheTop extends JPanel{
	int rows;
	public LettersAcrossTheTop(int rows){
		this.rows = rows;
	}
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		for(int i=0; i<rows; i++) {
			g.drawString(Character.toString((char)(i+((int)'A'))), 
					(i * ((getWidth() - 10)/rows)) + ((getWidth() - 10)/(2*rows)) + 6, 10);
		}
	}
}
