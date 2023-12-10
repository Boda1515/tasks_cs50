# TODO
# ---------------------------------------------------------------------------------#
# Your program should count the number of letters, words,
# and sentences in the text. You may assume that a letter is any lowercase character
# from a to z or any uppercase character from A to Z,
# any sequence of characters separated by spaces should count as a word,
# and that any occurrence of a period, exclamation point,
# or question mark indicates the end of a sentence.z
# This func to count how many number of letters in the text.

text = str(input("Text: "))


def count_letters(text):
    letters = 0
    for i in range(len(text)):
        if text[i].isupper() or text[i].islower():
            letters += 1
        else:
            letters += 0
    # count_letters is number of letters in the text.
    return int(letters)


# func count numbers of words by space


def count_words(text):
    # I put the 1 as intial value to word to count the last space in text.
    word = 1
    # isspace is a great func to know a tab or a space in string.
    for i in text:
        if (i.isspace()) == True:
            word += 1
    return int(word)


# func to count sentences in the text.


def count_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            sentences += 1
    return int(sentences)


# ---------------------------------------------------------------------------------#
# Recall that the Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8,
# where L is the average number of letters per 100 words in the text,
# and S is the average number of sentences per 100 words in the text.


L = (count_letters(text) / count_words(text)) * 100

S = (count_sentences(text) / count_words(text)) * 100

Coleman_Liau = 0.0588 * L - 0.296 * S - 15.8

# ----------------------------------------------------------------------------------#
# Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula,
# rounded to the nearest integer.
# If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level),
# your program should output "Grade 16+" instead of giving the exact index number. If the index number is less than 1,
# your program should output "Before Grade 1"
# ----------------------------------------------------------------------------------#
if round(Coleman_Liau) >= 16:
    print("Grade 16+")
elif round(Coleman_Liau) < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(Coleman_Liau)}")
