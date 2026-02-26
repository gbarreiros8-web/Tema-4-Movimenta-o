#include <stdio.h>
#include "board.h"

Piece board[SIZE][SIZE];

void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = (Piece){' ', ' '};

    for (int i = 0; i < SIZE; i++) {
        board[1][i] = (Piece){'P', 'B'};
        board[6][i] = (Piece){'P', 'W'};
    }

    board[0][0] = board[0][7] = (Piece){'R', 'B'};
    board[7][0] = board[7][7] = (Piece){'R', 'W'};

    board[0][1] = board[0][6] = (Piece){'N', 'B'};
    board[7][1] = board[7][6] = (Piece){'N', 'W'};

    board[0][2] = board[0][5] = (Piece){'B', 'B'};
    board[7][2] = board[7][5] = (Piece){'B', 'W'};

    board[0][3] = (Piece){'Q', 'B'};
    board[7][3] = (Piece){'Q', 'W'};

    board[0][4] = (Piece){'K', 'B'};
    board[7][4] = (Piece){'K', 'W'};
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j].type == ' ' ? '.' : board[i][j].type);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}

int isValidMove(Piece p, int sr, int sc, int er, int ec) {
    int dr = er - sr;
    int dc = ec - sc;

    switch (p.type) {
        case 'P': return (p.color == 'W') ? (dr == -1 && dc == 0) : (dr == 1 && dc == 0);
        case 'R': return (sr == er || sc == ec);
        case 'N': return ((dr*dr + dc*dc) == 5);
        case 'B': return (dr == dc || dr == -dc);
        case 'Q': return (sr == er || sc == ec || dr == dc || dr == -dc);
        case 'K': return (dr >= -1 && dr <= 1 && dc >= -1 && dc <= 1);
        default: return 0;
    }
}

int movePiece(int sr, int sc, int er, int ec) {
    Piece p = board[sr][sc];

    if (p.type == ' ')
        return 0;

    if (isValidMove(p, sr, sc, er, ec)) {
        board[er][ec] = p;
        board[sr][sc] = (Piece){' ', ' '};
        return 1;
    }

    return 0;
}
