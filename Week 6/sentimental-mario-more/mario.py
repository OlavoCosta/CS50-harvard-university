from cs50 import get_int

# Repeat condition until user cooperates
height = 0

while (height > 8 or height < 1):
    height = get_int("Height: ")

    for i in range(1, height + 1):
        # Pyramid  height
        print(" " * (height - i), end="")
        # Double pyramid spacing
        print("#" * i, end="  ")
        # Pyramid width
        print("#" * i)

