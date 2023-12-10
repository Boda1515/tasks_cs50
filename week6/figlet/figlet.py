# Expects zero or two command-line arguments:
import sys
from pyfiglet import Figlet

figlet = Figlet()
figlet.getFonts()

# Zero if the user would like to output text in a random font.
if len(sys.argv) == 1:
    take = input("Input: ")
    print(f"Output:{figlet.renderText(take)}")
elif len(sys.argv) == 3:
    list = ["-f", "--font"]
    figlet = Figlet()
    fontname = figlet.getFonts()
    if sys.argv[1] not in list or sys.argv[2].lower() not in fontname:
        print("Invalid usage")
        sys.exit(1)
    else:
        take = input("Input: ")
        figlet.setFont(font = sys.argv[2])
        print(figlet.renderText(take))
else:
    print("Invalid usage")
    sys.exit(1)
