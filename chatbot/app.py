from flask import Flask, render_template, request, jsonify
from nltk.chat.util import Chat, reflections

app = Flask(__name__)

# Define movies and showtimes (same as console version)
movies = {
    'Interstellar': ['Morning: 10:00 AM', 'Afternoon: 2:00 PM', 'Evening: 6:00 PM'],
    'The Dark Knight': ['Morning: 11:00 AM', 'Afternoon: 3:00 PM', 'Evening: 7:00 PM'],
    'Dune': ['Morning: 9:30 AM', 'Afternoon: 1:30 PM', 'Evening: 5:30 PM']
}

# Same patterns as console version
patterns = [
    (r'hi|hello|hey', 
     ['Hello! How can I assist you today?', 'Hey there! What can I do for you?', 'Hi! Ready to book some movie tickets?']),
    (r'how are you', 
     ['I am just a bot, but I am always ready to help you book tickets!', 'I am doing well, thanks for asking. How can I assist you today?']),
    (r'(.*) available|movies|currently', 
     ['Here is the list of movies: ' + ', '.join(movies.keys()) + '. Which movie would you like to watch?', 
      'Sure! Here are the movies currently playing: ' + ', '.join(movies.keys()) + '.']),
    (r'(.*) showtime|show times|yes show', 
     ['Here are the showtimes for the available movies: ' + '; '.join([f"{movie}: {', '.join(timings)}" for movie, timings in movies.items()])]),
    (r'(.*) timing|movie timings|show timings', 
     ['Here are the timings for each movie: ' + '; '.join([f"{movie}: {', '.join(timings)}" for movie, timings in movies.items()])]),
    (r'(.*) (morning|afternoon|evening|night)', 
     ['We have showtimes available in the morning, afternoon, evening, and night. When would you like to watch?']),
    (r'(.*) book|want|get|tickets', 
     ['Sure! Let\'s proceed with booking tickets.']),
]

# Create chatbot instance
movie_bot = Chat(patterns, reflections)

# Booking function (same as console version)
def book_tickets(movie, tickets, showtime):
    ticket_price = 100  # fixed price
    total_bill = tickets * ticket_price
    return f"Booking confirmed! You have booked {tickets} tickets for {movie} at {showtime}.\nTotal amount: Rs. {total_bill}."

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/chat', methods=['POST'])
def chat():
    user_input = request.form['message']
    response = movie_bot.respond(user_input)
    
    # Initialize context if not present
    if 'context' not in request.form:
        context = {
            'awaiting_movie': False,
            'awaiting_tickets': False,
            'awaiting_showtime': False,
            'booking_data': {}
        }
    else:
        context = request.form['context']
    
    # Handle booking flow
    if any(keyword in user_input.lower() for keyword in ["reserve", "buy", "book", "book tickets", "confirm"]):
        context['awaiting_movie'] = True
        response = "Which movie would you like to watch? (Interstellar/The Dark Knight/Dune)"
    
    elif context.get('awaiting_movie'):
        if user_input in movies:
            context['booking_data']['movie'] = user_input
            context['awaiting_movie'] = False
            context['awaiting_tickets'] = True
            response = f"Great! You selected {user_input}. How many tickets would you like?"
        else:
            response = "Sorry, I couldn't find that movie. Please choose from: " + ', '.join(movies.keys())
    
    elif context.get('awaiting_tickets'):
        if user_input.isdigit():
            context['booking_data']['tickets'] = int(user_input)
            context['awaiting_tickets'] = False
            context['awaiting_showtime'] = True
            response = "At what time would you like to watch the movie? (morning/afternoon/evening)"
        else:
            response = "Please enter a valid number of tickets (1,2,3...)"
    
    elif context.get('awaiting_showtime'):
        if user_input.lower() in ['morning', 'afternoon', 'evening']:
            context['booking_data']['showtime'] = user_input.lower()
            response = book_tickets(
                context['booking_data']['movie'],
                context['booking_data']['tickets'],
                context['booking_data']['showtime']
            )
            # Reset context after booking
            context = {
                'awaiting_movie': False,
                'awaiting_tickets': False,
                'awaiting_showtime': False,
                'booking_data': {}
            }
        else:
            response = "Please choose a valid showtime: morning, afternoon, or evening"
    
    # Handle goodbye/exit
    elif any(word in user_input.lower() for word in ['bye', 'goodbye', 'exit', 'ok']):
        response = "Goodbye! Have a great day!"
    
    # Default response if no match
    if not response:
        response = "Sorry, I didn't quite understand that. Could you please provide more details?"
    
    return jsonify({
        'bot_message': response,
        'context': context
    })

if __name__ == '__main__':
    app.run(debug=True)