class Jar:
    def __init__(self, capacity=12):
        if not isinstance(capacity, int) or capacity < 0:
            raise ValueError("Capacity must be a non-negative integer.")
        self._capacity = capacity
        self._cookies = []

    def __str__(self):
        cookies = "".join(["🍪"] * self.size)
        return f"There are {cookies} cookies in the cookie jar."

    def deposit(self, n):
        if n < 0:
            raise ValueError("Cannot deposit a negative number of cookies.")
        if self.size + n > self.capacity:
            raise ValueError("Cannot exceed the cookie jar's capacity.")
        self._cookies.extend(["🍪"] * n)

    def withdraw(self, n):
        if n < 0:
            raise ValueError("Cannot withdraw a negative number of cookies.")
        if n > self.size:
            raise ValueError("Cannot withdraw more cookies than are in the jar.")
        self._cookies = self._cookies[: -n]

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return len(self._cookies)

def main():
    jar = Jar()
    jar.withdraw(1)
    print(str(jar))

main()