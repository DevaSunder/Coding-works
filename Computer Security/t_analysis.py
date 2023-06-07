import pytaut as taint

# Define a function to check if a string is tainted
def is_tainted(s):
    return taint.is_tainted(s)

# Define a function to sanitize a tainted string
def sanitize(s):
    return taint.sanitize(s)

# Define a function to check if a SQL query is safe
def is_query_safe(query):
    # Check if the query is tainted
    if is_tainted(query):
        # Sanitize the query
        sanitized_query = sanitize(query)
        # Check if the sanitized query is safe
        if sanitized_query == query:
            return True
        else:
            return False
    else:
        return True

# Example usage
user_input = "SELECT * FROM users WHERE username = 'admin' OR 1=1 --' AND password = 'password'"
if is_query_safe(user_input):
    print("Query is safe!")
else:
    print("Query is not safe.")
