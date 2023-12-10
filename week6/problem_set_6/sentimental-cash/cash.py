# Calculates the minimum number of coins required to give a user change
# assume that the user will input their change in dollars (e.g., 0.50 dollars instead of 50 cents).
while True:
    try:
        dollars = float(input("Change owed: "))

        # Convert dollars to cents
        cents = round(dollars * 100)

        # Check if the dollars is float or not.
        if isinstance(dollars, float) and dollars > 0:
            break

    except ValueError:
        pass
# Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).
# Calculate the number of each type of coin.
# Using a floor division and moduls
quarters = cents // 25
dimes = (cents % 25) // 10
nickels = ((cents % 25) % 10) // 5
pennies = ((cents % 25) % 10) % 5

cents = quarters + dimes + nickels + pennies
print(cents)
