# Simple Chess

This is a simple chess app for me to practice OOP in C++. The app has a text-based
output using standard out and will support a windows GUI in the near future.

## Observations

The basics of implementing chess is not difficult but when you get to the more edge-case
rules and moves the seemingly solid structure of the game comes apart. Things like:

- The fact that pawns *might* move differently on their first move.
- The en passant move which depends on the state of the piece being captured (must be a pawn and 
  can only happen immediately after their first move) __and__ the relative position of the capturing
  pawn.
- The rules around castling:
  - The king and rook must not have moved before
  - The king must have line-of-sight to the rook.
  - The king (not the rook) cannot be in check before, after or on any square during the movement.

These edge cases got me thinking about the framework around building turn-based games in general.
I find myself having to do a lot of checks at specific times during the players turn to the point where
I thought is would be useful to take a page from the book of more established turn-based games, i.e. table-top
games. These games typically have "turns" but also have "phases" within those turns when special things
can happen and certain actions can be taken at a predefined time. Such phases would be handing if only
to check entity states, reset flags etc.