class Jar:
    def __init__(self, capacity=12):
        self.capacity = capacity
        self.size = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.size + n > self.capacity:
            raise ValueError("Too many cookies to add")
        self.size += n

    def withdraw(self, n):
        if self.size - n < 0:
            raise ValueError("Too many cookies to add")
        self.size -= n

    @property
    def capacity(self):
        return self._capacity

    @capacity.setter
    def capacity(self, capacity):
        if not isinstance(capacity, int):
            raise ValueError("Invalid capacity")
        if int(capacity) < 0:
            raise ValueError("Invalid capacity")
        self._capacity = capacity


    @property
    def size(self):
        return self._size


    @size.setter
    def size(self, size):
        self._size = size


def main():
    jar = Jar()
    jar.deposit(5)
    print(jar.size)
    jar.withdraw(1)
    print(jar.size)
    print(jar)
    print(jar.capacity)


if __name__ == "__main__":
    main()