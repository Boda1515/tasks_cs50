# TODO
# prompet the height number between 1 and 8
while True:
    try:
        height = int(input("height: "))
        if height in range(1, 9):
            break
    except:
        pass
# Build a pyramid Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
# with a gap of size 2 separating them.

# The left pyramid


def left_right_pyrimds(height):
    for i in range(height):
        for x in range(height - i - 1):
            print(" ", end="")
        for n in range(i +1):
            print("#", end="")
        print("  #", end="")
        for x in range(i):
            print("#", end="")
        print()
    print(end="")


left_right_pyrimds(height)
