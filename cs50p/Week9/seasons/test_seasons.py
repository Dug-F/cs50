import pytest
from seasons import calc_elapsed_minutes, number_to_words


def test_calc_elapsed_minutes_valid():
    assert calc_elapsed_minutes("2021-10-28") == 525600
    assert calc_elapsed_minutes("2020-10-28") == 1051200


def test_calc_elapsed_minutes_invalid():
    with pytest.raises(SystemExit):
        calc_elapsed_minutes("2021-20-28")


def test_number_to_words_valid():
    assert number_to_words(525600) == "Five hundred twenty-five thousand, six hundred minutes"
    assert number_to_words(1051200) == "One million, fifty-one thousand, two hundred minutes"