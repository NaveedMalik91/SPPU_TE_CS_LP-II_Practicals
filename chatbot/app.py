from flask import Flask, request, jsonify, render_template
import nltk
import re
import random

nltk.download('punkt')
nltk.download('averaged_perceptron_tagger')

app = Flask(__name__)

# Movie database
MOVIE_DB = [
    {"title": "Avengers", "genre": "Action", "times": ["1 PM", "4 PM", "7 PM"]},
    {"title": "Inception", "genre": "Sci-Fi", "times": ["10 AM", "1 PM", "7 PM"]},
    {"title": "Oppenheimer", "genre": "Drama", "times": ["4 PM", "7 PM", "10 PM"]},
    {"title": "Barbie", "genre": "Comedy", "times": ["10 AM", "1 PM", "4 PM"]},
    {"title": "The Batman", "genre": "Action", "times": ["1 PM", "4 PM", "10 PM"]},
    {"title": "Interstellar", "genre": "Sci-Fi", "times": ["1 PM", "7 PM", "10 PM"]},
    {"title": "Frozen 2", "genre": "Animation", "times": ["10 AM", "1 PM", "4 PM"]},
    {"title": "Coco", "genre": "Animation", "times": ["10 AM", "1 PM"]},
    {"title": "Parasite", "genre": "Thriller", "times": ["4 PM", "7 PM"]},
    {"title": "La La Land", "genre": "Musical", "times": ["7 PM", "10 PM"]},
]

GENRES = list(set(movie['genre'] for movie in MOVIE_DB))

# Pattern-response rules
patterns = [
    (r'hi|hello|hey',
     ['Hello! How can I assist you today?', 'Hey there! What can I do for you?', 'Hi! Ready to book some movie tickets?']),

    (r'how are you',
     ['I am just a bot, but always ready to help!', 'Doing well, thanks! What movie can I help you book?']),

    (r'(.*)(available|movies|currently)',
     [f'Here is the list of movies: {", ".join([movie["title"] for movie in MOVIE_DB])}. Which movie would you like to watch?']),

    (r'(.*)(showtime|show time|yes show)',
     [f'Showtimes:\n' + '\n'.join([f'{movie["title"]}: {", ".join(movie["times"])}' for movie in MOVIE_DB])]),

    (r'(.*)(morning|afternoon|evening|night)',
     ['We have showtimes across morning, afternoon, evening, and night. When would you like to watch?']),

    (r'(.*)(book|want|get|tickets)',
     ['Sure! Let\'s proceed with booking. Please mention the movie and time.'])
]

# Helper functions
def get_movie_by_name(user_input):
    for movie in MOVIE_DB:
        if movie["title"].lower() in user_input.lower():
            return movie
    return None

def get_movies_by_genre(genre):
    return [m["title"] for m in MOVIE_DB if m["genre"].lower() == genre.lower()]

def extract_entities(user_input):
    tokens = nltk.word_tokenize(user_input)
    tags = nltk.pos_tag(tokens)

    # Tickets
    tickets = 1
    for i, word in enumerate(tokens):
        if word.isdigit() and i + 1 < len(tokens) and "ticket" in tokens[i + 1].lower():
            tickets = int(word)
            break

    # Time
    time_pattern = r"\d{1,2}\s?(?:AM|PM|am|pm)"
    time_match = re.search(time_pattern, user_input)
    time = time_match.group(0).upper() if time_match else None

    # Movie
    movie = get_movie_by_name(user_input)

    return movie, time, tickets

def classify_intent(user_input):
    user_input = user_input.lower()
    if any(kw in user_input for kw in ["list", "show", "available", "now playing"]):
        return "show_movies"
    elif "genre" in user_input or any(g.lower() in user_input for g in GENRES):
        return "show_genre"
    elif any(kw in user_input for kw in ["book", "ticket", "want to watch", "reserve"]):
        return "book_ticket"
    elif "recommend" in user_input:
        return "recommend"
    return "unknown"

# Flask routes
@app.route('/')
def home():
    return render_template('index.html')

@app.route('/chat', methods=['POST'])
def chat():
    user_input = request.json.get('message').strip().lower()

    # 1. Pattern-based quick response
    for pattern, responses in patterns:
        if re.search(pattern, user_input):
            return jsonify({'reply': random.choice(responses)})

    # 2. NLP-based intent processing
    intent = classify_intent(user_input)

    if intent == "show_movies":
        titles = [movie['title'] for movie in MOVIE_DB]
        return jsonify({'reply': "🎬 Now Playing: " + ", ".join(titles)})

    elif intent == "show_genre":
        for genre in GENRES:
            if genre.lower() in user_input:
                movies = get_movies_by_genre(genre)
                return jsonify({'reply': f"🎭 {genre} Movies: {', '.join(movies)}"})
        return jsonify({'reply': "Available genres: " + ", ".join(GENRES)})

    elif intent == "recommend":
        rec = random.choice(MOVIE_DB)
        return jsonify({'reply': f"🍿 I recommend watching '{rec['title']}' – it's a great {rec['genre']} movie!"})

    elif intent == "book_ticket":
        movie, time, tickets = extract_entities(user_input)
        if not movie:
            return jsonify({'reply': "🎥 Which movie would you like to watch?"})
        if not time:
            return jsonify({'reply': f"🕒 What time for '{movie['title']}'? Available: {', '.join(movie['times'])}"})
        return jsonify({'reply': f"✅ Booked {tickets} ticket(s) for '{movie['title']}' at {time}. Enjoy the show!"})

    else:
        return jsonify({'reply': "🤔 Sorry, I didn't understand. You can say things like 'Book 2 tickets for Inception at 4 PM', 'Show me Sci-Fi movies', or 'Recommend a movie'."})

if __name__ == '__main__':
    app.run(debug=True)
