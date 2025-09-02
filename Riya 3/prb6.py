import re

MAX_IDENTIFIER_LENGTH = 20

# Manually define C-like language keywords
language_keywords = {
    'int', 'float', 'char', 'double', 'long', 'short', 'void', 'main',
    'if', 'else', 'while', 'for', 'do', 'return', 'switch', 'case',
    'break', 'continue', 'default', 'const', 'sizeof', 'struct', 'typedef'
}

operators = {'+', '-', '*', '/', '=', '==', '!=', '<', '<=', '>', '>=', '++', '--', '%'}
symbols = {'(', ')', '{', '}', '[', ']', ';', ','}

def remove_comments(code):
    # Remove single-line comments
    code = re.sub(r'//.*', '', code)
    # Remove multi-line comments
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    return code

def lexical_analyzer(code):
    code = remove_comments(code)
    code = re.sub(r'\s+', ' ', code)  # Remove excessive whitespace

    # Regex pattern for tokenizing
    token_pattern = r'[A-Za-z_]\w*|\d+\.\d+|\d+|==|!=|<=|>=|[+\-*/=<>;:.,(){}\[\]]'
    tokens = re.findall(token_pattern, code)

    symbol_table = []

    for token in tokens:
        entry = {"token": token}

        if token in language_keywords:
            entry["type"] = "Keyword"
        elif token in operators:
            entry["type"] = "Operator"
        elif token in symbols:
            entry["type"] = "Symbol"
        elif re.match(r'^\d+\.\d+$', token):
            entry["type"] = "Float Constant"
        elif token.isdigit():
            entry["type"] = "Integer Constant"
        elif re.match(r'^[A-Za-z_]\w*$', token):
            # Restrict identifier length
            if len(token) > MAX_IDENTIFIER_LENGTH:
                token = token[:MAX_IDENTIFIER_LENGTH]
                entry["token"] = token
            entry["type"] = "Identifier"
        else:
            entry["type"] = "Unknown"

        symbol_table.append(entry)

    return symbol_table

# ------ MAIN ------
print("Enter code (type END in a new line to finish):")
lines = []
while True:
    line = input()
    if line.strip().upper() == "END":
        break
    lines.append(line)

code_input = '\n'.join(lines)
table = lexical_analyzer(code_input)

# Display Symbol Table
print("\nSymbol Table:")
print("{:<20} {:<20}".format("Token", "Type"))
print("-" * 40)
for entry in table:
    print("{:<20} {:<20}".format(entry['token'], entry['type']))

