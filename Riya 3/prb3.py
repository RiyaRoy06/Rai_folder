def precedence(op):
    if op in ('+', '-'):
        return 1
    if op in ('*', '/'):
        return 2
    return 0

def apply_op(a, b, op):
    a, b = int(a), int(b)
    if op == '+': return a + b
    if op == '-': return a - b
    if op == '*': return a * b
    if op == '/': 
        # Handle division by zero gracefully
        if b == 0:
            raise ValueError("Division by zero")
        return a // b
    return 0

def print_operator_stack(ops):
    # Nest operators inside angle brackets from left to right
    if not ops:
        return ''
    s = ops[-1]
    for op_ in reversed(ops[:-1]):
        s = f'<{op_}{s}>'
    return f'<{s}>'

def operator_precedence_parser(expr):
    # Print expression wrapped in $ and < >
    formatted_expr = '$' + ''.join(f'<{c}>' if c.isdigit() else c for c in expr) + '$'
    print(formatted_expr)

    operands = []
    operators = []

    i = 0
    while i < len(expr):
        c = expr[i]

        if c.isdigit():
            operands.append(c)
            i += 1
        elif c in "+-*/":
            # Reduce operators on stack with higher or equal precedence
            while (operators and 
                   precedence(operators[-1]) >= precedence(c)):
                op = operators.pop()
                b = operands.pop()
                a = operands.pop()
                val = apply_op(a, b, op)
                operands.append(str(val))
                print(f"${print_operator_stack(operators)}$")
            operators.append(c)
            i += 1
        else:
            # Skip spaces or invalid chars (optional: handle error)
            i += 1

    # Final reductions after expression end
    while operators:
        op = operators.pop()
        b = operands.pop()
        a = operands.pop()
        val = apply_op(a, b, op)
        operands.append(str(val))
        print(f"${print_operator_stack(operators)}$")

    print(f"\nValue is {operands[-1]}.")

# Example of usage:
expr = input("Enter the arithmetic expression: ")
operator_precedence_parser(expr)


