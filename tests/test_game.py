"""
Tests for the chess game module
"""

import pytest
from chess_program.game import ChessGame


class TestChessGame:
    """Test cases for ChessGame class"""
    
    def test_init(self):
        """Test game initialization"""
        game = ChessGame()
        assert game.board is not None
        assert len(game.move_history) == 0
    
    def test_valid_move(self):
        """Test making a valid move"""
        game = ChessGame()
        assert game.make_move("e2e4") is True
        assert len(game.move_history) == 1
    
    def test_invalid_move(self):
        """Test making an invalid move"""
        game = ChessGame()
        assert game.make_move("e2e5") is False
        assert len(game.move_history) == 0
    
    def test_legal_moves(self):
        """Test getting legal moves"""
        try:
            game = ChessGame()
            legal_moves = game.get_legal_moves()
            assert len(legal_moves) == 20  # Starting position has 20 legal moves
        except Exception as e:
            pytest.fail(f"Unexpected exception raised: {e}")
    
    def test_game_not_over_initially(self):
        """Test that game is not over at start"""
        game = ChessGame()
        assert game.is_game_over() is False
    
    def test_reset(self):
        """Test resetting the game"""
        game = ChessGame()
        game.make_move("e2e4")
        game.reset()
        assert len(game.move_history) == 0
        assert len(game.get_legal_moves()) == 20
