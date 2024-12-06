import random

# Part 1: Generate the three-digit secret code
def generate_secret_code():
    return str(random.randint(0, 999)).zfill(3)  # Generate a random number and pad with zeros

# Part 2: Get a three-digit value from the user
def get_user_guess():
    while True:
        user_input = input("Guess a number: ")
        if len(user_input) == 3 and user_input.isdigit():
            return user_input
        print("Invalid input. Please enter a three-digit number.")

# Part 3: Provide feedback based on the guess
def provide_feedback(secret_code, user_guess):
    feedback = []
    for i in range(3):
        if user_guess[i] == secret_code[i]:
            feedback.append("Bullseye")
        elif user_guess[i] in secret_code:
            feedback.append("Off-target")
        else:
            feedback.append("Null")
    return feedback

# Part 4: Check win or lose conditions
def check_game_status(guess_count, max_guesses):
    if guess_count >= max_guesses:
        print("You've reached the maximum number of guesses. You lost!")
        return True
    return False

# Part 5: Ask if the user wants to play again
def play_again():
    return input("Do you want to play again? (y/n) ").strip().lower() == 'y'

# Main game function
def play_game():
    max_guesses = 10  # Set a maximum number of guesses
    while True:
        secret_code = generate_secret_code()
        print("Welcome to 'Conundrum Code'. Try to guess the three-digit number.")
        print("\nHere are some clues:")
        print("When I say 'Off-target', that means one of your digits is correct but in the wrong position.")
        print("When I say 'Bullseye', that means one of your digits is correct but in the right position.")
        print("When I say 'Null', that means one of your digits is incorrect.")

        guess_count = 0
        while guess_count < max_guesses:
            user_guess = get_user_guess()
            guess_count += 1

            feedback = provide_feedback(secret_code, user_guess)
            print(" ".join(feedback))

            if user_guess == secret_code:
                print("You got it!")
                break
            
            if check_game_status(guess_count, max_guesses):
                print(f"The secret code was: {secret_code}")
                break

        if not check_game_status(guess_count, max_guesses):
            print("Congratulations! You guessed the secret code.")

        if not play_again():
            print("Thank you for playing!")
            break

# Start the game
if __name__ == "__main__":
    play_game()
