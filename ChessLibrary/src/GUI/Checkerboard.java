package GUI;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;

import javax.swing.JPanel;
import javax.swing.Timer;

import SourceFiles.Board;
import SourceFiles.Coordinate;
import SourceFiles.Field;
import SourceFiles.GlobalConstants;
import SourceFiles.MoveRecord;
import SourceFiles.Piece;



class Checkerboard extends JPanel implements MouseListener, MouseMotionListener, GlobalConstants {
	private ArrayList<Rectangle> squares = new ArrayList<Rectangle>();
	private ColoredPolygon[][] polygon_lookup;
	private int ROWS = 8;
	private int COLS = 8;
	private int tile_width;
	private int tile_height;
	private Board board_guy;
	private ErrorMessage error_message;
	// Keep track of piece being moved by user.
	private ColoredPolygon piece_being_moved;
	private Vector2D moving_piece_location;
	private Vector2D center_of_piece_offset;
	private Coordinate piece_start;
	private Coordinate piece_dest ;
	// Keep track of piece being moved back by computer.
	private ColoredPolygon piece_being_returned;
	private Vector2D returning_piece_start;
	private Vector2D returning_piece_locat;
	private Vector2D returning_piece_dest;
	private Timer move_back_timer;
	private VectorFloat2D init_return_step;
	private VectorFloat2D total_dist_returned;
	private int move_piece_animation_step;
	
	public Checkerboard(ErrorMessage er){
		error_message = er;
		addMouseListener(this);
		addMouseMotionListener(this);
	}
	
	public void createBoard (int rows, int cols) {
		ROWS = rows;
		COLS = cols;
		polygon_lookup = new ColoredPolygon[ROWS][COLS];
		tile_width = getWidth()/8;
		tile_height = getHeight()/8;
		for(int x=0; x<8; x++) {
			for(int y=0; y<8; y++) {
				Rectangle rectum = new Rectangle(
						x * tile_width,
						y * tile_height,
						tile_width,
						tile_height 
				);
				squares.add(rectum);
			}
		}
		initializeMoveBackTimer();
	}
	public void undo() {
		MoveRecord lastMove = board_guy.undoMove();
		if(lastMove == null) { return; }
		Coordinate dest = lastMove.dest;
		Coordinate start = lastMove.start;
		Piece attacker = lastMove.attacker;
		Piece target = lastMove.target;
		
		// Move Attacker from dest to start
		movePieceBack(polygon_lookup[dest.x][dest.y], 
				new Vector2D(	(dest.x * tile_width) + (tile_width/2) ,
								(dest.y * tile_height) + (tile_height/2) ) ,
				start);
		polygon_lookup[start.x][start.y] = polygon_lookup[dest.x][dest.y];
		
		if(target != null) {
			// Bring target back from the grave.
			ColoredPolygon targ_poly = target.getColoredPolygon(tile_width);
			if(targ_poly.color == TEAM_TWO_COLOR) {
				targ_poly.rotate(tile_height);
			}
			targ_poly.translate(dest.x * tile_width , dest.y * tile_height);
			polygon_lookup[dest.x][dest.y] = targ_poly;
			repaint();
		}
	}
	
	public void newGame() {
		// Wipe the board clean.
		polygon_lookup = new ColoredPolygon[ROWS][COLS];
		// Instantiate the game board, which contains the logic.
		board_guy = new Board(8,8);
		board_guy.setupNormalGame();
		// For each piece, get its polygon and place it on the panel 
		// at the correct location and in the correct direction.
		Field field_guy = board_guy.getField();
		ArrayList<Coordinate> piece_locations = field_guy.noNullsTraverse();
		for(Coordinate piece_location : piece_locations) {
			
			ColoredPolygon polygon = field_guy.at(piece_location).getColoredPolygon(tile_width);
			
			// rotate all of the black pieces.
			if(polygon.color == TEAM_TWO_COLOR) {
				polygon.rotate(tile_height);
			};
			int deltaX = piece_location.x * tile_width;
			int deltaY = piece_location.y * tile_height;
			polygon.translate(deltaX, deltaY);
			System.out.println(piece_location.x);
			System.out.println(piece_location.y);
			polygon_lookup [piece_location.x][piece_location.y] = polygon;
		}
		repaint();
	}
	
	
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		Graphics2D g2 = (Graphics2D) g;
		int alternate = 1;
		
		// Draw the checkered background.
		for(Rectangle rect : squares) {
			if(alternate % 9 == 0) {alternate++;}
			if(alternate % 2 == 1){ g2.setColor(Color.LIGHT_GRAY); }
			else { g2.setColor(Color.DARK_GRAY); }
			
			alternate++;
			
			g2.fill(rect);
		}
		// Draw the pieces on the background.
		for(int x=0; x<ROWS; x++) {
			for(int y=0; y<COLS; y++) {
				ColoredPolygon piece = polygon_lookup[x][y];
				if(piece != null) {
					g2.setColor( piece.color );
					g2.fill(piece);
				}
			}
		}
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		System.out.println("Mouse pressed");
		
		// Measure how far from the center of the piece the user clicked.
		center_of_piece_offset = new Vector2D(
				e.getX() % tile_width  - (tile_width/2) , 
				e.getY() % tile_height - (tile_height/2) 
				);
		
		piece_start = new Coordinate(e.getX() / tile_width, e.getY() / tile_height);
		
		moving_piece_location = new Vector2D(e.getX(), e.getY());
			
	    piece_being_moved = polygon_lookup[piece_start.x][piece_start.y];
	    
	}

	
	
	@Override
	public void mouseReleased(MouseEvent e) {
		System.out.println("Mouse Release Event");
		int tile_size = getWidth() / 8;
		
		Vector2D center_of_piece = new Vector2D(	e.getX() - center_of_piece_offset.x ,
												e.getY() - center_of_piece_offset.y);
		
		piece_dest = new Coordinate(center_of_piece.x / tile_width, center_of_piece.y / tile_height );
		
		System.out.print("piece_dest x: ");
		System.out.print(piece_dest.x);
		System.out.print(" y: ");
		System.out.println(piece_dest.y);
		
		int result = board_guy.move(piece_start, piece_dest);
		error_message.handleErrorMessage(result);
		
		if(result >= MUST_MOVE_A_PIECE && result <= MUST_ESCAPE_CHECK) {
			movePieceBack(piece_being_moved, center_of_piece, piece_start);
			return;
		}
		// If the move wasn't valid, move the piece back.
//		if( result != NOMINAL ) {
//			
//			
//			return;
//		}
		
		Vector2D tile_center = new Vector2D(
				piece_dest.x * tile_width  + (tile_width / 2),
				piece_dest.y * tile_height + (tile_width / 2));
				
		// Magnetism (Puts the piece in the center of the tile automagically)
		if(piece_being_moved != null) {
			piece_being_moved.translate(tile_center.x - center_of_piece.x, tile_center.y - center_of_piece.y );
		}
		polygon_lookup[piece_start.x][piece_start.y]=null;
		polygon_lookup[piece_dest.x][piece_dest.y] = piece_being_moved;
		repaint();
	}
	
	private void movePieceBack(ColoredPolygon piece_being_moved, Vector2D center_of_piece, Coordinate piece_start) {
		
		returning_piece_start = center_of_piece;
		returning_piece_locat = center_of_piece;
		
		returning_piece_dest = new Vector2D(
				piece_start.x * tile_width + (tile_width / 2), 
				piece_start.y * tile_height + (tile_height / 2));
		
		Vector2D distance = returning_piece_dest.sub(returning_piece_start);
		
		// Has to do with sum_{i=1}^{n} = (n)(n+1)/2, but we do it twice, once forwards,
		// once backwards. So we cover n*(n+1) distance, so we divide the initial vector by that.
		double step_ratio = ((double)((RETURN_ANIMATION_FRAMES/2)*((RETURN_ANIMATION_FRAMES/2)+1)));
		init_return_step = new VectorFloat2D(distance.x / step_ratio, distance.y / step_ratio);
		
		total_dist_returned = new VectorFloat2D(0.0, 0.0);
		move_piece_animation_step = 1;
		piece_being_returned = piece_being_moved;
		move_back_timer.start();
	}
	
	private void initializeMoveBackTimer() {
		move_back_timer = new Timer(26, new ActionListener() {
			 public void actionPerformed(ActionEvent e){
				 move_returning_piece(e);
			 }
        });
		
	}
	
	public void move_returning_piece(ActionEvent e) {
        if(move_piece_animation_step > RETURN_ANIMATION_FRAMES) {
        		piece_being_returned.translate(	returning_piece_dest.x - returning_piece_locat.x,
        										returning_piece_dest.y - returning_piece_locat.y);
        		move_back_timer.stop();
        } else {
        		// Half way through we slow down
        		int step = move_piece_animation_step;
        		if( step > RETURN_ANIMATION_FRAMES / 2 ) {
        			step = (RETURN_ANIMATION_FRAMES + 1) - step;
        		}
        		total_dist_returned.add((init_return_step.mult(step)));
        		
        		Vector2D new_piece_location = returning_piece_start.add(total_dist_returned);
        		Vector2D delta = new_piece_location.sub(returning_piece_locat);
        		
        		piece_being_returned.translate(delta.x, delta.y);
        		
        		returning_piece_locat = new_piece_location;
			move_piece_animation_step ++;
        }
        repaint();
    }
	
	private void displayErrorMessage(int message) {
		
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		if(piece_being_moved != null) {
			piece_being_moved.translate(e.getX() - moving_piece_location.x, 
									 e.getY() - moving_piece_location.y);
		}
		moving_piece_location = new Vector2D( e.getX(), e.getY());
		repaint();
	}
	
	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

}