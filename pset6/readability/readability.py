text = input("Text: ")
countLetters = 0
countWords = 0
countSentences = 0

# counting the number of letters
for i in range(len(text)):
    if text[i].isalpha() != 0:
        countLetters += 1

    elif text[i].isspace() != 0:
        countWords += 1

    elif text[i] in [".", "!", "?"]:
        countSentences += 1
countWords += 1

# calculating L
L = (float(countLetters) / float(countWords)) * 100

# calculating S
S = (float(countSentences) / float(countWords)) * 100

# calculating the Coleman-Liau index
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")

elif index > 0 and index <= 16:
    print(f"Grade {int(index)}")

else:
    print("Grade 16+")
