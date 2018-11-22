package SourceFiles;

public class MoveRecord {
	public Coordinate start;
	public Coordinate dest;
	public Piece attacker;
	public Piece target;
	public MoveRecord(Coordinate start, Coordinate dest, Piece attacker, Piece target) {
		this.start = start;
		this.dest = dest;
		this.attacker = attacker;
		this.target = target;
	}
}
