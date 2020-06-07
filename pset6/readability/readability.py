from cs50 import get_string

text = get_string("Text: ")
letters = 0
words = 1
sentences = 0

for c in text:
    if c.isalpha():
        letters += 1
    elif c == " ":
        words += 1
    elif c in [".", "!", "?"]:
        sentences += 1
        
indexL = (letters / words) * 100
indexS = (sentences / words) * 100
index = round(0.0588 * indexL - 0.296 * indexS - 15.8)

print(letters)
print(words)
print(sentences)
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")