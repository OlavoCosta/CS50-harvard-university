from cs50 import get_float

while True:
    # Function that will get the input value
    cash = get_float("Enter your Cash: ")

    if cash >= 0.0:
        break

cash = round(cash * 100)

# just like the first week in C, we will check the amount of coins and add them to the Coins
Coins = cash // 25
cash = cash % 25

# Check how many dimes
Coins += cash // 10
cash = cash % 10

# Check how many nickles
Coins += cash // 5
cash = cash % 5

# Finally, the remaining value is added to Coins
Coins += cash

print(Coins)