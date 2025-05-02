from nltk.chat.util import Chat, reflections

# Define some patterns and responses
movies = {
    'Interstellar': ['Morning: 10:00 AM', 'Afternoon: 2:00 PM', 'Evening: 6:00 PM'],
    'The Dark Knight': ['Morning: 11:00 AM', 'Afternoon: 3:00 PM', 'Evening: 7:00 PM'],
    'Dune': ['Morning: 9:30 AM', 'Afternoon: 1:30 PM', 'Evening: 5:30 PM']
}

patterns = [
    (r'hi|hello|hey', 
     ['Hello! How can I assist you today?', 'Hey there! What can I do for you?', 'Hi! Ready to book some movie tickets?']),
    (r'how are you', 
     ['I am just a bot, but I am always ready to help you book tickets!', 'I am doing well, thanks for asking. How can I assist you today?']),
    (r'(.*) available|movies|currently', 
     ['Here is the list of movies: ' + ', '.join(movies.keys()) + '. Which movie would you like to watch?', 'Sure! Here are the movies currently playing: ' + ', '.join(movies.keys()) + '.']),
    (r'(.*) showtime|show times|yes show', 
     ['Here are the showtimes for the available movies:' + f"{movie}: {', '.join(timings)}" for movie, timings in movies.items()]),
    (r'(.*) timing|movie timings|show timings', 
     ['Here are the timings for each movie:' + f"{movie}: {', '.join(timings)}" for movie, timings in movies.items()]),
    (r'(.*) (morning|afternoon|evening|night)', 
     ['We have showtimes available in the morning, afternoon, evening, and night. When would you like to watch?']),
    (r'(.*) book|want|get|tickets', 
     ['Sure! Let\'s proceed with booking tickets.']),
   
]

# Create a chatbot
tea_bot = Chat(patterns, reflections)

def book_tickets(movie, tickets, showtime):
    # Calculate total bill
    ticket_price = 100  # assuming a fixed price for now
    total_bill = tickets * ticket_price
    return f"Booking confirmed! You have booked {tickets} tickets for {movie} at {showtime}.\nTotal amount: Rs. {total_bill}."

def main():
    print("\nHello! Welcome to ChatBot. How can I assist you today?")
    
    while True:
        user_input = input("You: ")
        response = tea_bot.respond(user_input)

        if response:
            print("ChatBot:", response)
        else:
            print("ChatBot: Sorry, I didn't quite understand that. Could you please provide more details?")

        # Extract information for booking tickets
        if any(keyword in user_input.lower() for keyword in ["reserve", "buy","book","book tickets","confirm"]):
            movie = input("Enter the movie name which you would you like to watch? :")
            
            # Check if movie is valid
            while movie not in movies:
                print("ChatBot: Sorry, I couldn't find that movie. Please choose from the available movies.")
                movie = input("Which movie would you like to watch? :")
                
            tickets = input("How many tickets do you need? :")
            
            # Ensure ticket input is a valid number
            while not tickets.isdigit():
                print("ChatBot: Please enter a valid number of tickets (1,2,3...).")
                tickets = input("How many tickets do you need? :")
            tickets = int(tickets)
            
            showtime = input("At what time would you like to watch the movie? (morning/afternoon/evening):")
            
            # Ensure showtime is valid
            while showtime.lower() not in ['morning', 'afternoon', 'evening']:
                print("ChatBot: Please choose a valid showtime: morning, afternoon, or evening.")
                showtime = input("At what time would you like to watch the movie? :")
            
            # Provide booking response
            booking_response = book_tickets(movie, tickets, showtime)
            print("ChatBot:", booking_response)

        # Ask if the user wants to end the conversation
        if any(word in user_input.lower() for word in ['bye', 'goodbye', 'exit', 'ok']):
            end_chat = input("ChatBot: Would you like to end the chat? (Yes/No): ")
            if end_chat.lower() == "yes":
                print("ChatBot: Goodbye! Have a great day!")
                break
       
main()
