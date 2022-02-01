package core;

import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/** Game logic module for text-based
 *  Connect 4 game.
 *
 * @author Matthew Wihebrink
 * @version 1.0
 * */
public class Connect4 {

    private int columns;
    private int rows;
    private char[][] board;
    private int last_play_Col = -1;
    private int last_play_Row = -1;

    /** Constructor for Connect4 board */
    public Connect4(int width, int height) {
        rows = width;
        columns = height;
        board = new char[height][];

        for (int i = 0; i < height; i++) {
            Arrays.fill(board[i] = new char[width], '|');
        }
    }

    /** Checks row containing last play from player*/
    public String horizontal() {
        return new String(board[last_play_Row]);
    }

    /** Checks column containing last play from player*/
    public String vertical() {
        StringBuilder sb = new StringBuilder(columns);

        for (int h = 0; h < columns; h++) {
            sb.append(board[h][last_play_Col]);
        }

        return sb.toString();
    }

    /** Checks "/" diagonal containing last play from player*/
    public String diagonal_1() {
        StringBuilder sb = new StringBuilder(columns);

        for (int h = 0; h < columns; h++) {
            int w = last_play_Col + last_play_Row - h;

            if (0 <= w && w < rows) {
                sb.append(board[h][w]);
            }
        }

        return sb.toString();
    }

    /** Checks "\" diagonal containing last play from player*/
    public String diagonal_2() {
        StringBuilder sb = new StringBuilder(columns);

        for (int i = 0; i < columns; i++) {
            int w = last_play_Col - last_play_Row + i;

            if (0 <= w && w < rows) {
                sb.append(board[i][w]);
            }
        }

        return sb.toString();
    }

    /** Helper method for winCheck()*/
    public static boolean contains(String str, String sub) {
        return str.indexOf(sub) >= 0;
    }

    /** Checks if last coin placed by player was the winner*/
    public boolean isARENA_WIN() {
        char sym = board[last_play_Row][last_play_Col];
        String streak = String.format("%c%c%c%c", sym, sym, sym, sym);

        /** Checks for 4 in a row horizontally, vertically, diagonally*/
        return contains(horizontal(), streak) || contains(vertical(), streak) ||
                contains(diagonal_1(), streak) || contains(diagonal_2(), streak);
    }

    /** Displays the game board for Connect4TextConsole*/
    public String toString() {
        return IntStream.range(1, rows + 1).mapToObj(Integer::toString).collect(Collectors.joining())
                + "\n" + Arrays.stream(board).map(String::new).collect(Collectors.joining("\n"));
    }

    /** Method to place coin in column of Connect4 board*/
    public void placeCoin(char symbol, Scanner input) {
        do {
            int col = input.nextInt() - 1;

            if (!(0 <= col && col < rows)) {
                System.out.println("Column must be between 1 and " + (rows + 1));
                continue;
            }

            for (int h = columns - 1; h >= 0; h--) {
                if (board[h][col] == '|') {
                    board[last_play_Row = h][last_play_Col = col] = symbol;
                    return;
                }
            }

            System.out.println("Column " + col + " is full.");
        } while (true);
    }
}