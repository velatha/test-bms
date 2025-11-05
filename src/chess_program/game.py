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
        """Get all legal moves in current position"""
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
