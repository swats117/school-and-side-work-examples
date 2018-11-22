package GUI;

import java.awt.Polygon;
import java.awt.Color;

public class ColoredPolygon extends Polygon{
	public Color color;
	public ColoredPolygon(int[] xpoints, int[] ypoints, int numpoints, Color color){
		super(xpoints, ypoints, numpoints);
		this.color = color;
	}
	public void rotate(int tile_height) {
		for(int i=0; i<npoints; i++) {
			ypoints[i] = (-1*ypoints[i]) + tile_height;
		}
	}
}
