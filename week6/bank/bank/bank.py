greeting = str(input("Greeting: ").lower())

if "hello" in greeting:
    print("$0")
elif greeting[0] == 'h' and greeting != "hello":
    print("$20")
else:
    print("$100")
