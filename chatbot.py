from nltk.chat.util import Chat, reflections

# Define available movies and their showtimes
movies = {
    'Soldier': ['Morning: 10:00 AM', 'Afternoon: 2:00 PM', 'Evening: 6:00 PM'],
    'The Dark Knight': ['Morning: 11:00 AM', 'Afternoon: 3:00 PM', 'Evening: 7:00 PM'],
    'Dune': ['Morning: 9:30 AM', 'Afternoon: 1:30 PM', 'Evening: 5:30 PM']
}

# Patterns for casual conversation
patterns = [
    (r'hi|hello|hey', ['Hello! How can I assist you today?']),
    (r'how are you', ['I am great, ready to help you book your movie tickets!']),
    (r'(.*) (bye|goodbye)', ['Thank you for visiting! Goodbye!']),
]

# Create a basic chatbot for small talk
tea_bot = Chat(patterns, reflections)

# Helper function to calculate and return booking confirmation
def book_tickets(movie, tickets, showtime):
    ticket_price = 100
    total = ticket_price * tickets
    return f"Booking confirmed! 🎟️ You have booked {tickets} tickets for '{movie}' at {showtime}.\nTotal amount: ₹{total}."

def main():
    print("\nHello! Welcome to ChatBot. I can assist you with booking movie tickets.")
    print("Please type 'bye' or 'goodbye' to exit anytime.\n")

    selected_movie = None
    ticket_count = None
    selected_showtime = None

    while True:
        user_input = input("You: ").strip()
        user_input_lower = user_input.lower()

        # Exit condition
        if user_input_lower in ["bye", "goodbye"]:
            print("ChatBot: Goodbye! Have a wonderful day!")
            break

        # Try responding with default chatbot if possible
        response = tea_bot.respond(user_input_lower)
        if response:
            print("ChatBot:", response)
            continue

        # Start the booking process
        if "book" in user_input_lower and "ticket" in user_input_lower:
            if not selected_movie:
                print("ChatBot: Here are the movies now showing: " + ', '.join(movies.keys()))
                selected_movie = input("ChatBot: Which movie would you like to watch? ").strip()
                if selected_movie not in movies:
                    print("ChatBot: Sorry, that's not available. Please pick from: " + ', '.join(movies.keys()))
                    selected_movie = None
                    continue
                print(f"ChatBot: Great choice! '{selected_movie}' it is.")

            if not ticket_count:
                try:
                    ticket_count = int(input("ChatBot: How many tickets would you like to book? ").strip())
                    if ticket_count <= 0:
                        print("ChatBot: Please enter a valid number.")
                        ticket_count = None
                        continue
                except ValueError:
                    print("ChatBot: Please enter a number.")
                    continue

            if not selected_showtime:
                print("ChatBot: Available showtimes for", selected_movie, "→", ', '.join(movies[selected_movie]))
                selected_showtime = input("ChatBot: Please choose your preferred showtime: ").strip()
                if selected_showtime not in movies[selected_movie]:
                    print("ChatBot: Invalid showtime. Please choose from:", ', '.join(movies[selected_movie]))
                    selected_showtime = None
                    continue

            # All inputs collected
            confirmation = book_tickets(selected_movie, ticket_count, selected_showtime)
            print("ChatBot:", confirmation)

            # Reset for next booking
            selected_movie = None
            ticket_count = None
            selected_showtime = None

        elif not selected_movie:
            if user_input in movies:
                selected_movie = user_input
            else:
                print("ChatBot: To begin booking, type something like 'I want to book tickets'.")
        else:
            print("ChatBot: I'm sorry, I didn't understand that. Try saying 'book tickets' to get started.")

# Start the chatbot
main()



# Hello! Welcome to ChatBot. I can assist you with booking movie tickets.
# Please type 'bye' or 'goodbye' to exit anytime.

# You: showtime
# ChatBot: To begin booking, type something like 'I want to book tickets'.
# You: i want to book tickets
# ChatBot: Here are the movies now showing: Soldier, The Dark Knight, Dune
# ChatBot: Which movie would you like to watch? Soldier
# ChatBot: Great choice! 'Soldier' it is.
# ChatBot: How many tickets would you like to book? 5
# ChatBot: Available showtimes for Soldier → Morning: 10:00 AM, Afternoon: 2:00 PM, Evening: 6:00 PM
# ChatBot: Please choose your preferred showtime: Morning: 10:00 AM
# ChatBot: Booking confirmed! 🎟️ You have booked 5 tickets for 'Soldier' at Morning: 10:00 AM.
# Total amount: ₹500.
# You: bye
# ChatBot: Goodbye! Have a wonderful day!