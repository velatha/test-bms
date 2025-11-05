"""
Main entry point for the chess program
"""

from chess_program.game import ChessGame


def main():
    """Main function to run the chess program"""
    game = ChessGame()
    print("Welcome to Chess Program!")
    print("=" * 50)
    print(game)
    print("\nEnter moves in UCI format (e.g., e2e4) or quit to exit")
    print("Type help for more commands\n")
    
    while not game.is_game_over():
        try:
            user_input = input("Enter move: ").strip().lower()
            
            if user_input == quit:
                print("Thanks for playing!")
                break
            elif user_input == help:
                print("\nCommands:")
                print("  - Enter move in UCI format (e.g., e2e4)")
                print("  - legal - Show all legal moves")
                print("  - reset - Reset the game")
                print("  - quit - Exit the game\n")
                continue
            elif user_input == legal:
                print(f"\nLegal moves: {[str(m) for m in game.get_legal_moves()]}\n")
                continue
            elif user_input == reset:
                game.reset()
                print("\nGame reset!\n")
                print(game)
                continue
            
            if game.make_move(user_input):
                print(f"\nMove {user_input} played!\n")
                print(game)
                print()
            else:
                print(f"\nInvalid move: {user_input}\n")
                
        except KeyboardInterrupt:
            print("\n\nGame interrupted. Thanks for playing!")
            break
        except Exception as e:
            print(f"\nError: {e}\n")
    
    if game.is_game_over():
        print(f"\nGame Over! Result: {game.get_result()}")


if __name__ == "__main__":
    main()
