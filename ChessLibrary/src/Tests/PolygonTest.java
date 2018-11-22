package Tests;

import javax.swing.*;
import javax.imageio.ImageIO;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import SourceFiles.Piece;

public class PolygonTest extends JFrame {

	JButton btn;
	JLabel lbl;
	JPanel panel;
	public PolygonTest() {
		setTitle("Space Chess!");
		panel = new myPolygon();
		panel.setPreferredSize(new Dimension(720,720));
		add(panel);
		pack();
		BufferedImage image;
		
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
	}
	
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new PolygonTest().setVisible(true);;
			}
		});
	}
	
}

class myPolygon extends JPanel{
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2 = (Graphics2D) g;
		
		ArrayList<int[]> points = makePawn();
		
		int[] x = new int[points.size()];
		int[] y = new int[points.size()];
		for(int i=0; i<points.size(); i++) {
			x[i] = points.get(i)[0];
			y[i] = points.get(i)[1];
		}
		g2.fillPolygon( x, y, points.size());
	}
	
	public void newPoint(ArrayList<int[]> points, int width, String dir) {
		dir = dir.toUpperCase();
		int[] oldPoint = points.get(points.size()-1);
		int[] newPoint = new int[]{oldPoint[0],oldPoint[1]};
		if(dir.contains("N")) {
			newPoint[1] -= width;
		}
		if(dir.contains("E")) {
			newPoint[0] += width;
		}
		if(dir.contains("S")) {
			newPoint[1] += width;
		}
		if(dir.contains("W")) {
			newPoint[0] -= width;
		}
		points.add(newPoint);
	}
	
	private ArrayList<int[]> makePawn() {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int size = 270;
		
		int proportion = (int)(((double)size) / ((4.0+3.0+4.0) + (3.0*1.41421356237)));
		int length = (int)(((4+3+4)+ (3*1.41421356237)) * ((double) proportion));
		int height = (int)((6.0+(2.0*1.41421356237))* proportion);
		int startX = (int)((size - length)/2 + (( ((3.0/2.0)*1.41421356237) + 7) * proportion));
		int startY = (size - height)/2;
		int width1 = 2 * proportion;
		int width2 = 4 * proportion;
		int width3 = (int) (((double)width1)*1.41421356237);
		int width4 = (int) (((double)proportion)/1.41421356237);
		int width5 = 3 * proportion;
		int width6 = width2 + ((width3 - (2*width4)));
		
		
		
		points.add(new int[] {startX,startY});
		newPoint(points, width1, "SE");
		newPoint(points, width1, "W");
		newPoint(points, width2, "S");
		newPoint(points, width2, "NE");
		newPoint(points, width4, "NW");
		newPoint(points, width3, "E");
		
		newPoint(points, width3, "S");
		newPoint(points, width4, "NW");
		newPoint(points, width6, "SW");
		newPoint(points, width5, "W");
		newPoint(points, width6, "NW");
		newPoint(points, width4, "SW");
		newPoint(points, width3, "N");
		
		newPoint(points, width3, "E");
		newPoint(points, width4, "SW");
		newPoint(points, width2, "SE");
		newPoint(points, width2, "N");
		newPoint(points, width1, "W");
		newPoint(points, width1, "NE");
		
		
		
		return points;
	}
	
	private ArrayList<int[]> makeKnight() {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int size = 270;
		
		int proportion = size / 20;
		int length = 20 * proportion;
		int startX = (size - length) / 2 + (5 * proportion) ;
		int startY = (size - length)/ 2 + (2 * proportion) ;
		int width1 = 2 * proportion;
		int width2 = 1 * proportion;
		int width3 = 6 * proportion; // width3 > 2*width 6
		int width4 = (width3 - (2*( width1 - width2)))/2; 
		int width5 = (width3/2) + width4 + width2; // makes piece look like 2:1 ratio of knight.
		
		points.add(new int[] {startX,startY});
		newPoint(points, width1, "NE");
		newPoint(points, width2, "S");
		newPoint(points, width3, "E");
		newPoint(points, width2, "N");
		newPoint(points, width1, "SE");
		
		newPoint(points, width1, "SW");
		newPoint(points, width2, "N");
		newPoint(points, width4, "W");
		newPoint(points, width5, "S");
		newPoint(points, width5, "E");
		newPoint(points, width4, "N");
		newPoint(points, width2, "W");
		newPoint(points, width1, "NE");
		
		newPoint(points, width1, "SE");
		newPoint(points, width2, "W");
		newPoint(points, width3, "S");
		newPoint(points, width2, "E");
		newPoint(points, width1, "SW");
		
		newPoint(points, width1, "NW");
		newPoint(points, width2, "E");
		newPoint(points, width4, "N");
		newPoint(points, width5, "W");
		newPoint(points, width5, "S");
		newPoint(points, width4, "E");
		newPoint(points, width2, "N");
		newPoint(points, width1, "SE");
		
		newPoint(points, width1, "SW");
		newPoint(points, width2, "N");
		newPoint(points, width3, "W");
		newPoint(points, width2, "S");
		newPoint(points, width1, "NW");
		
		newPoint(points, width1, "NE");
		newPoint(points, width2, "S");
		newPoint(points, width4, "E");
		newPoint(points, width5, "N");
		newPoint(points, width5, "W");
		newPoint(points, width4, "S");
		newPoint(points, width2, "E");
		newPoint(points, width1, "SW");
		
		newPoint(points, width1, "NW");
		newPoint(points, width2, "E");
		newPoint(points, width3, "N");
		newPoint(points, width2, "W");
		newPoint(points, width1, "NE");
		
		newPoint(points, width1, "SE");
		newPoint(points, width2, "W");
		newPoint(points, width4, "S");
		newPoint(points, width5, "E");
		newPoint(points, width5, "N");
		newPoint(points, width4, "W");
		newPoint(points, width2, "S");
		newPoint(points, width1, "NW");
		
		return points;
	}
	
	private ArrayList<int[]> makeKing() {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int size = 90;
		
		int proportion = (int)(((double)size) / ((1.2)*(6.0 * 1.41421356237 + 14.0)));
		int length = (int)((6.0 * 1.41421356237 + 14.0) * proportion);
		int start =  (size - length)/2 + (int)((2.0 * 1.41421356237 - 1.0) * ((double)proportion));
		int width1 = 4 * proportion;
		int width2 = 1 * proportion;
		int width3 = 5 * proportion;
		int width4 = width3;
		int width5 = (int)(((double)width2)*1.41421356237);
		int width6 = (int)(((double)width1)/1.41421356237); 
		 
	 
		points.add(new int[] {start,start});
		newPoint(points, width1, "E");
		newPoint(points, width2, "SW");
		newPoint(points, width3, "SE");
		newPoint(points, width3, "N");
		newPoint(points, width5, "W");
		newPoint(points, width6, "NE");
		
		newPoint(points, width6, "SE");
		newPoint(points, width5, "W");
		newPoint(points, width3, "S");
		newPoint(points, width3, "NE");
		newPoint(points, width2, "NW");
		newPoint(points, width1, "E");
		
		newPoint(points, width1, "S");
		newPoint(points, width2, "NW");
		newPoint(points, width3, "SW");
		newPoint(points, width3, "E");
		newPoint(points, width5, "N");
		newPoint(points, width6, "SE");
		
		newPoint(points, width6, "SW");
		newPoint(points, width5, "N");
		newPoint(points, width3, "W");
		newPoint(points, width3, "SE");
		newPoint(points, width2, "NE");
		newPoint(points, width1, "S");
		
		newPoint(points, width1, "W");
		newPoint(points, width2, "NE");
		newPoint(points, width3, "NW");
		newPoint(points, width3, "S");
		newPoint(points, width5, "E");
		newPoint(points, width6, "SW");
		
		newPoint(points, width6, "NW");
		newPoint(points, width5, "E");
		newPoint(points, width3, "N");
		newPoint(points, width3, "SW");
		newPoint(points, width2, "SE");
		newPoint(points, width1, "W");
		
		newPoint(points, width1, "N");
		newPoint(points, width2, "SE");
		newPoint(points, width3, "NE");
		newPoint(points, width3, "W");
		newPoint(points, width5, "S");
		newPoint(points, width6, "NW");
		
		newPoint(points, width6, "NE");
		newPoint(points, width5, "S");
		newPoint(points, width3, "E");
		newPoint(points, width3, "NW");
		newPoint(points, width2, "SW");
		newPoint(points, width1, "N");
		
		return points;
	}
	
	private ArrayList<int[]> makeQueen() {
		ArrayList<int[]> points = new ArrayList<int[]>();
		int proportion = 32;
		int length = (int)((6.0 * 1.41421356237 + 14.0) * proportion);
		int start =  (getWidth() - length)/2 + (int)((2.0 * 1.41421356237 - 1.0) * ((double)proportion));
		int width1 = 4 * proportion;
		int width2 = 1 * proportion;
		int width3 = 5 * proportion;
		int width4 = width3;
		int width5 = (int)(((double)width2)*1.41421356237);
		int width6 = (int)(((double)width1)/1.41421356237); 
	 
		points.add(new int[] {start,start});
		newPoint(points, width1, "E");
		newPoint(points, width2, "SW");
		newPoint(points, width3, "SE");
		newPoint(points, width3, "N");
		newPoint(points, width5, "W");
		newPoint(points, width6, "NE");
		
		newPoint(points, width6, "SE");
		newPoint(points, width5, "W");
		newPoint(points, width3, "S");
		newPoint(points, width3, "NE");
		newPoint(points, width2, "NW");
		newPoint(points, width1, "E");
		
		newPoint(points, width1, "S");
		newPoint(points, width2, "NW");
		newPoint(points, width3, "SW");
		newPoint(points, width3, "E");
		newPoint(points, width5, "N");
		newPoint(points, width6, "SE");
		
		newPoint(points, width6, "SW");
		newPoint(points, width5, "N");
		newPoint(points, width3, "W");
		newPoint(points, width3, "SE");
		newPoint(points, width2, "NE");
		newPoint(points, width1, "S");
		
		newPoint(points, width1, "W");
		newPoint(points, width2, "NE");
		newPoint(points, width3, "NW");
		newPoint(points, width3, "S");
		newPoint(points, width5, "E");
		newPoint(points, width6, "SW");
		
		newPoint(points, width6, "NW");
		newPoint(points, width5, "E");
		newPoint(points, width3, "N");
		newPoint(points, width3, "SW");
		newPoint(points, width2, "SE");
		newPoint(points, width1, "W");
		
		newPoint(points, width1, "N");
		newPoint(points, width2, "SE");
		newPoint(points, width3, "NE");
		newPoint(points, width3, "W");
		newPoint(points, width5, "S");
		newPoint(points, width6, "NW");
		
		newPoint(points, width6, "NE");
		newPoint(points, width5, "S");
		newPoint(points, width3, "E");
		newPoint(points, width3, "NW");
		newPoint(points, width2, "SW");
		newPoint(points, width1, "N");
		
		return points;
	}
	
	private ArrayList<int[]> makeBishop() {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int size = 90;
		
		int proportion = (int)(((double)size) / (16 * 1.41421356237));
		int length = 16*proportion;
		
		int start = (size-length)/2;
		int width1 = 4*proportion;
		int width2 = 1*proportion;
		int width3 = 5*proportion;
		

		
		points.add(new int[] {start,start});
		newPoint(points, width1, "E");
		newPoint(points, width2, "SW");
		newPoint(points, width3, "SE");
		newPoint(points, width3, "NE");
		newPoint(points, width2, "NW");
		newPoint(points, width1, "E");
		
		newPoint(points, width1, "S");
		newPoint(points, width2, "NW");
		newPoint(points, width3, "SW");
		newPoint(points, width3, "SE");
		newPoint(points, width2, "NE");
		newPoint(points, width1, "S");
		
		newPoint(points, width1, "W");
		newPoint(points, width2, "NE");
		newPoint(points, width3, "NW");
		newPoint(points, width3, "SW");
		newPoint(points, width2, "SE");
		newPoint(points, width1, "W");
		
		newPoint(points, width1, "N");
		newPoint(points, width2, "SE");
		newPoint(points, width3, "NE");
		newPoint(points, width3, "NW");
		newPoint(points, width2, "SW");
		
		return points;
	}
	
	private ArrayList<int[]> makeRook() {
		ArrayList<int[]> points = new ArrayList<int[]>();
		
		int size = 90;
		
		int proportion = (int)(((double)size)/16.0);
		int length = 16 * proportion;
		
		int startX = (size - length)/2 + 8 * proportion;
		int startY = (size - length)/2;
		int width1 = 2 * proportion;
		int width2 = 1 * proportion;
		int width3 = 5 * proportion;
		
		
		
		points.add(new int[] {startX,startY});
		newPoint(points, width1, "SE");
		newPoint(points, width2, "W");
		newPoint(points, width3, "S");
		newPoint(points, width3, "E");
		newPoint(points, width2, "N");
		newPoint(points, width1, "SE");
		
		newPoint(points, width1, "SW");
		newPoint(points, width2, "N");
		newPoint(points, width3, "W");
		newPoint(points, width3, "S");
		newPoint(points, width2, "E");
		newPoint(points, width1, "SW");
		
		newPoint(points, width1, "NW");
		newPoint(points, width2, "E");
		newPoint(points, width3, "N");
		newPoint(points, width3, "W");
		newPoint(points, width2, "S");
		newPoint(points, width1, "NW");
		
		newPoint(points, width1, "NE");
		newPoint(points, width2, "S");
		newPoint(points, width3, "E");
		newPoint(points, width3, "N");
		newPoint(points, width2, "W");
		
		return points;
	}
	
}






