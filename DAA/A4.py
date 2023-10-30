def is_safe(board, row, col, n):
    """
    Checks if it is safe to place a Queen at the given row and column.

    Args:
        board: A 2D list representing the n-Queens board.
        row: The row where the Queen is to be placed.
        col: The column where the Queen is to be placed.
        n: The size of the n-Queens board.

    Returns:
        True if it is safe to place a Queen at the given row and column, False otherwise.
    """
    # Check if there is a Queen in the same row or column.
    for i in range(n):
        if board[row][i] == 1 or board[i][col] == 1:
            return False

    # Check if there is a Queen in the diagonal directions.
    for i in range(n):
        for j in range(n):
            if (i + j == row + col or i - j == row - col) and board[i][j] == 1:
                return False

    # If we reach here, it is safe to place a Queen at the given row and column.
    return True

def solve_n_queens(board, row, n):
    """
    Solves the n-Queens problem using backtracking.

    Args:
        board: A 2D list representing the n-Queens board.
        row: The row from where to start solving the problem.
        n: The size of the n-Queens board.

    Returns:
        True if a solution is found, False otherwise.
    """
    # If we have reached the end of the board, we have found a solution.
    if row == n:
        return True

    # Try placing a Queen in each column of the current row.
    for col in range(n):
        if is_safe(board, row, col, n):
            board[row][col] = 1
            if solve_n_queens(board, row + 1, n):
                return True
            board[row][col] = 0

    # If we reach here, no solution could be found.
    return False

def print_n_queens_solution(board, n):
    """
    Prints the solution of the n-Queens problem.

    Args:
        board: A 2D list representing the n-Queens board.
        n: The size of the n-Queens board.
    """

    for i in range(n):
        for j in range(n):
            if board[i][j] == 1:
                print("Q", end=" ")
            else:
                print("-", end=" ")
        print()

def solve_n_queens(board, row, n, first_queen_row, first_queen_col):
    """
    Solves the n-Queens problem using backtracking.

    Args:
        board: A 2D list representing the n-Queens board.
        row: The row from where to start solving the problem.
        n: The size of the n-Queens board.
        first_queen_row: The row of the first Queen.
        first_queen_col: The column of the first Queen.

    Returns:
        True if a solution is found, False otherwise.
    """
    # If we have reached the end of the board, we have found a solution.
    if row == n:
        return True

    # Try placing a Queen in each column of the current row, except for the column where the first Queen is placed.
    for col in range(n):
        if col != first_queen_col and is_safe(board, row, col, n):
            board[row][col] = 1
            if solve_n_queens(board, row + 1, n, first_queen_row, first_queen_col):
                return True
            board[row][col] = 0

    # If we reach here, no solution could be found.
    return False

def main():
    n = int(input("Enter the size of the n-Queens board: "))
    first_queen_row = int(input("Enter the row of the first Queen: "))
    first_queen_col = int(input("Enter the column of the first Queen: "))

    # Create an empty n-Queens board.
    board = [[0 for i in range(n)] for j in range(n)]

    # Place the first Queen at the given row and column.
    board[first_queen_row][first_queen_col] = 1

    # Solve the n-Queens problem using backtracking.
    if solve_n_queens(board, 1, n, first_queen_row, first_queen_col):
        print("The solution to the n-Queens problem is:")
        print_n_queens_solution(board, n)
    else:
        print("No solution found for the given n-Queens problem.")

if __name__ == "__main__":
    main()