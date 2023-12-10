import re

input_string = input("Enter a sequence of digits: ")


# Create a checksum method.
def validate_luhn(credit_card_number):
    # Sum of the digits that are not multiplied by 2
    sum_of_digits = 0

    # Flag to indicate whether to double the next digit or not
    double_next = False

    # Iterate over the credit card number from right to left
    for digit in reversed(credit_card_number):
        if double_next:
            # Double the digit and subtract 9 if the result is greater than 9
            digit = int(digit) * 2
            if digit > 9:
                digit -= 9
        sum_of_digits += int(digit)
        double_next = not double_next

    # If the sum of the digits modulo 10 is equal to 0, then the credit card number is valid
    return sum_of_digits % 10 == 0


if len(input_string) not in [13, 15, 16]:
    print("INVALID")

else:
    # Matches strings starting with 37 or 34
    patten_AMEX = r"^(37|34)"

    match_AMEX = re.match(patten_AMEX, input_string)

    # Matches strings starting with 51, 52, 53, 54, or 55 for Mastercard
    patten_MASTERCARD = r"^(51|52|53|54|55)"

    match_MASTERCARD = re.match(patten_MASTERCARD, input_string)
    # Matches strings starting with 4 for Visa
    patten_VISA = r"^(4)"

    match_VISA = re.match(patten_VISA, input_string)

    if match_AMEX and validate_luhn(input_string):
        print("AMEX")
    elif match_MASTERCARD and validate_luhn(input_string):
        print("MASTERCARD")
    elif match_VISA and validate_luhn(input_string):
        print("VISA")
    else:
        print("INVALID")
