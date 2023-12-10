# TODO
# first prompt the user with get_int for the half-pyramid’s height, a positive integer between 1 and 8, inclusive.
while True:
    try:
        height = int(input("Height: "))
        if height in range(1, 9):
            break
    except ValueError:
        print("INVALID_INDEX")
"""
for i in range(height):
    print('#', end="")
    for x in range(i):
        print('#', end="")
    print()
"""
for i in range(height):
    for x in range(height - i - 1):
        print(" ", end="")
    for n in range(i + 1):
        print("#", end="")
    print()
