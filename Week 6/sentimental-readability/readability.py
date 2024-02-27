from cs50 import get_string

text = get_string("Text: ")
words = 1
letters = 0
sentences = 0

# checks whether the character value is a question mark, an exclamation mark, or a period, if so, it adds 1.
for i in text:
    if i.isalpha():
        letters = letters + 1
    if i == ' ':
        words = words + 1
    if i == '.' or i == '?' or i == '!':
        sentences = sentences + 1

# calculates the average number of letters per 100 words
Let = (letters / words) * 100
# and sentences
Sen = (sentences / words) * 100
# find the coleman-Liau index provided
grade = round(0.0588 * Let - 0.296 * Sen - 15.8)

# If number is less than 1
if grade < 1:
    print("Before Grade 1")
# If the index number is 16 or higher
elif grade >= 16:
    print("Grade 16+")
# if none of the above do.
else:
    print(f"Grade {grade}")