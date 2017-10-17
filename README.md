# Reversi

### About the Project

This project is an implementation of the famous game Reversi and an AI for the game.

### How to Play

After running make, you should an executable file inside `build/`. Run from the root directory with `build/reverse`. This will begin a new game between two human players. To set the players on each side, use the -playerOne and -playerTwo options as follows.

To begin a game with a human player as dark (player one) and the AI "Greedy" as light (player two), run:
`build/reverse -playerOne human -playerTwo greedy`

### About the Game

"Reversi is a strategy board game for two players, played on an 8×8 uncheckered board. There are sixty-four identical game pieces called disks (often spelled "discs"), which are light on one side and dark on the other. Players take turns placing disks on the board with their assigned color facing up. During a play, any disks of the opponent's color that are in a straight line and bounded by the disk just placed and another disk of the current player's color are turned over to the current player's color.

The object of the game is to have the majority of disks turned to display your color when the last playable empty square is filled." - [Wikipedia](https://en.wikipedia.org/wiki/Reversi)

### Status

- Multi-threading
- Alpha-Beta Pruning
