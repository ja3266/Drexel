## Database Project
The project is to design and develop a db backend for a board game. More details will come each milestone at the end of weeks 2,4,6, and 8.

## Project Deliverable and SUbmission
1. Documentation is required.
2. ER Diagrams will be available on Vertabelo.com
3. SQL script files required to deploy each project phase according to spec.

## PEF
Submit a PEF with each milestone to grade team participation.

## Specifications
### Objective
Design the database to support the "Play-Color" game's backend according to the following specs and requirements.

This game as originally designed to be implemented as a web-page game. In this project instead, you will design the backend database only, and all tests and sims will happen using SQL and CLI statements.

### Game Rules
- A ref much start each game round establishing some initial parameters:
	- Number of players: 2-5
	- Game board Size: 
		- Min: 3x3
		- Max: 8x8
	- Number of available colors: 2-8
- When a ref starts each new game board, it must wait until the max number of players join before starting the first round.
- Each other player can list and decide to which game board they will join.
- Each player must start by selecting a color.
	- Color selection can be changed at any time.
- In each round, each player can "paint" one cell of the game board either when:
	- The position is NOT painted yet
	- OR the position is already painted by the same player
- When a player paints a cell with color X, that player will steal all adjacent cells in all four directions if they are painted with the same color by other players.
- A player can have only a partial view of the game board:
	- White cells
	- Cells owned by the player
	- Cells owned by the other players
- Game is over when the game board is fully painted
- The player with the most cells painted wins.
![[Pasted image 20240930175459.png]]