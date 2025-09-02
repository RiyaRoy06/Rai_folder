# Parsing table
parsing_table = {
    "E": {"id": "T E'"},
    "E'": {"+": "+ T E'", "$": "ε"},
    "T": {"id": "F T'"},
    "T'": {"+": "ε", "*": "* F T'", "$": "ε"},
    "F": {"id": "id"},
}

# Function to check if a symbol is a terminal
def is_terminal(symbol):
    return symbol in {"id", "+", "*", "(", ")", "$"}

# Function to simulate the predictive parser
def predictive_parser(input_tokens):
    parser_stack = ["$", "E"]  # Start symbol and end marker
    index = 0

    while parser_stack:
        top = parser_stack[-1]
        current_input = input_tokens[index]

        if is_terminal(top):
            # Terminal symbol handling
            if top == current_input:
                parser_stack.pop()
                index += 1
            else:
                print(f"Error: Mismatch at {current_input}")
                return False
        elif top in parsing_table and current_input in parsing_table[top]:
            # Non-terminal symbol handling
            production = parsing_table[top][current_input]
            parser_stack.pop()

            if production != "ε":
                # Push symbols in reverse order
                symbols = production.split()
                parser_stack.extend(reversed(symbols))
        else:
            print(f"Error: Invalid input at {current_input}")
            return False

    return index == len(input_tokens)

def main():
    input_tokens = ["id", "+", "id", "*", "id", "$"]  # Input string tokenized

    print("Parsing input:", " ".join(input_tokens))

    if predictive_parser(input_tokens):
        print("Input string is successfully parsed!")
    else:
        print("Failed to parse the input string.")

if __name__ == "__main__":
    main()