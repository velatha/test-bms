"""
Main chess game module
"""

import chess


class ChessGame:
    """
    Main Chess Game class that handles game logic and state
    """
    
    def __init__(self):
        """Initialize a new chess game"""
        self.board = chess.Board()
        self.move_history = []
    
    def make_move(self, move_str: str) -> bool:
        """
        Make a move on the board
        
        Args:
            move_str: Move in UCI format (e.g., e2e4)
        
        Returns:
            True if move was successful, False otherwise
        """
        try:
            move = chess.Move.from_uci(move_str)
            if move in self.board.legal_moves:
                self.board.push(move)
                self.move_history.append(move)
                return True
            return False
        except (ValueError, chess.InvalidMoveError):
            return False
    
    def get_legal_moves(self) -> list:
        """
        Get all legal moves in current position.
        
        This method retrieves all legal moves available for the current player
        in the current board position. Legal moves are those that comply with
        chess rules including:
        - Piece movement rules (e.g., bishops move diagonally, knights in L-shape)
        - Not leaving the king in check
        - Not moving into check
        - Castling restrictions (king and rook have not moved, no pieces between them,
          king not in check, does not pass through or land on attacked squares)
        - En passant capture rules (if applicable)
        - Pawn promotion rules (if applicable)
        
        The method leverages the python-chess library built-in legal move generator
        which efficiently computes all possible legal moves according to FIDE chess rules.
        
        Logic Flow:
        1. Access the board legal_moves property, which is a generator object
        2. Convert the generator to a list for easier manipulation and iteration
        3. Return the list of Move objects
        
        Returns:
            list: A list of chess.Move objects representing all legal moves.
                  Each Move object contains:
                  - from_square: The starting square of the piece (0-63)
                  - to_square: The destination square (0-63)
                  - promotion: The piece type for pawn promotion (if applicable)
                  - drop: The piece type for dropping in variants (None for standard chess)
                  
                  The list will be empty if there are no legal moves (checkmate or stalemate).
                  In a starting position, this will return 20 legal moves 
                  (16 pawn moves: 8 one-square and 8 two-square, 4 knight moves: 2 per knight).
        
        Parameters:
            None - operates on the current board state
        
        Example:
            game = ChessGame()
            moves = game.get_legal_moves()
            print(len(moves))  # Starting position outputs: 20
            # Iterate through legal moves
            for move in moves:
                print(move.uci())  # Print move in UCI notation
        
        Note:
            - The returned Move objects can be used directly with make_move() method
              by converting them to UCI notation using move.uci()
            - The method does not modify the board state
            - The legal moves are dynamically generated based on current position
            - This is computationally efficient as it uses the underlying C library
              optimizations from the python-chess package
        """
        return list(self.board.legal_moves)
    
    def is_game_over(self) -> bool:
        """Check if the game is over"""
        return self.board.is_game_over()
    
    def get_result(self) -> str:
        """Get the game result"""
        if self.board.is_checkmate():
            return "Checkmate"
        elif self.board.is_stalemate():
            return "Stalemate"
        elif self.board.is_insufficient_material():
            return "Draw - Insufficient Material"
        elif self.board.is_fifty_moves():
            return "Draw - Fifty Move Rule"
        elif self.board.is_repetition():
            return "Draw - Threefold Repetition"
        return "Game in progress"
    
    def reset(self):
        """Reset the game to initial position"""
        self.board.reset()
        self.move_history = []
    
    def __str__(self) -> str:
        """String representation of the board"""
        return str(self.board)
