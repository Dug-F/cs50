from numb3rs import validate

def test_validate_invalid_invalid_chars():
    assert validate("a.a.a.a") == False


def test_validate_invalid_insufficient_nodes():
    assert validate("1") == False
    assert validate("1.") == False
    assert validate("1.1") == False
    assert validate("1.1.1") == False


def test_validate_invalid_too_many_nodes():
    assert validate("1.1.1.1.1") == False


def test_validate_out_of_range():
    assert validate("256.1.1.1") == False
    assert validate("1.256.1.1") == False
    assert validate("1.1.256.1") == False
    assert validate("1.1.1.256") == False


def test_validate_true():
    assert validate("1.1.1.1") == True
    assert validate("12.12.12.12") == True
    assert validate("123.123.123.123") == True
