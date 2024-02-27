from cs50 import get_int

height = 0

# Repeat condition until the user cooperates
while (height > 8 or height < 1):
    height = get_int("Height: ")

# Drawing the pyramid
    for i in range(1, height + 1):
        print(' ' * (height - i) + '#' * i)
