import pytest
from jar import Jar


def test_init():
    jar = Jar(9)
    assert jar.capacity == 9
    jar = Jar()
    assert jar.capacity == 12


def test_jar_add():
    jar = Jar(15)
    jar.deposit(4)
    assert jar.size == 4
    assert str(jar) == "🍪🍪🍪🍪"
    jar.deposit(7)
    assert jar.size == 11
    assert str(jar) == "🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪"


def test_jar_subtract():
    jar = Jar(15)
    jar.deposit(8)
    jar.withdraw(5)
    assert jar.size == 3
    assert str(jar) == "🍪🍪🍪"
    jar.withdraw(2)
    assert jar.size == 1
    assert str(jar) == "🍪"


def test_jar_errors():
    jar = Jar(5)
    jar.deposit(4)
    with pytest.raises(ValueError):
        jar.deposit(2)
    with pytest.raises(ValueError):
        jar.withdraw(5)


