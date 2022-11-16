-- Keep a log of any SQL queries you execute as you solve the mystery.


-- =========================================

-- find out what is known about the crime
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;

-- Findings
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 293 | 2021 | 7     | 28  | Axmark Road     | Vandalism took place at 12:04. No known witnesses.                                                                                                                                                                       |
-- | 294 | 2021 | 7     | 28  | Boyce Avenue    | Shoplifting took place at 03:01. Two people witnessed the event.                                                                                                                                                         |
-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews
--                                                were conducted today with three witnesses who were present at the time – each of their
--                                                interview transcripts mentions the bakery.                                                                                                                                                                               |
-- | 296 | 2021 | 7     | 28  | Widenius Street | Money laundering took place at 20:30. No known witnesses.                                                                                                                                                                |
-- | 297 | 2021 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- =========================================

-- Get interview transcripts from 2021/07/28
SELECT * FROM interviews WHERE transcript LIKE('%bakery%');

-- Findings
-- ----------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot
--                                        and drive away. If you have security footage from the bakery parking lot, you might want to look
--                                        for cars that left the parking lot in that time frame.                                                                                                                                                                                                                                                              |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived
--                                        at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                                                                                                                        |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the
--                                        call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--                                        The thief then asked the person on the other end of the phone to purchase the flight ticket.                                                                                                                                                                                                                        |
-- | 192 | Kiana   | 2021 | 5     | 17  | I saw Richard take a bite out of his pastry at the bakery before his pastry was stolen from him.                                                                                                                                                                                                                    |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- So our clues are:
-- 1. Thief left bakery parking lot between 10:15 and 10:25.  Can look at security footage to find cars leaving lot
-- 2. Thief made ATM withdrawal on Leggett Street before 10:15 on 2021/07/28.  Can look at ATM transaction logs
-- 3. Thief made phone call lasting less than 1 minute at or just after 10:15 on 2021/07/28.  Can check phone logs.  Phone call was to accomplice.
-- 4. Thief took earliest flight out of Fiftyville on 2021/07/29.  Can check flights to find the flight and who was on it.
-- 5. Accomplice bought flight tickets


-- =========================================
-- 1. Thief left bakery parking lot between 10:15 and 10:25.  Can look at security footage to find cars leaving lot

-- Get bakery security footage to identify who owned the cars that left the parking lot between 10:15 and 10:25 on 2021/07/28

-- a. Get the log entries
SELECT * FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute >= 15
   AND minute <= 25
   AND activity = 'exit';

-- b. Find out who owns these vehicles
SELECT * FROM people
 WHERE license_plate IN
       (SELECT license_plate FROM bakery_security_logs
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute >= 15
           AND minute <= 25
           AND activity = 'exit');

-- Findings
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+

-- =========================================
-- 2. Thief made ATM withdrawal on Leggett Street before 10:15 on 2021/07/28.  Can look at ATM transaction logs

-- a. ATM withdrawals on Leggett Street before 10:15 on 2021/07/28
SELECT * FROM atm_transactions
 WHERE transaction_type = 'withdraw'
   AND atm_location = 'Leggett Street'
   AND year = 2021
   AND month = 7
   AND day = 28;

-- Findings
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+

-- b. Who made these withdrawals

SELECT * FROM people
 WHERE id IN
       (SELECT person_id FROM bank_accounts
         WHERE account_number IN
               (SELECT account_number FROM atm_transactions
                 WHERE transaction_type = 'withdraw'
                   AND atm_location = 'Leggett Street'
                   AND year = 2021
                   AND month = 7
                   AND day = 28));

-- Findings
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+

-- =========================================
-- 3. Thief made phone call lasting less than 1 minute at or just after 10:15 on 2021/07/28.  Can check phone logs.  Phone call was to accomplice.

-- a. Calls logs between 10:15 and 10:25 on 2021/07/28 lasting less than 1 minute
SELECT * FROM phone_calls, people as cx, people as rx
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration <= 60
   AND cx.phone_number = phone_calls.caller
   AND rx.phone_number = phone_calls.receiver;

-- Findings
-- +-----+----------------+----------------+------+-------+-----+----------+--------+---------+----------------+-----------------+---------------+--------+------------+----------------+-----------------+---------------+
-- | id  |     caller     |    receiver    | year | month | day | duration |   id   |  name   |  phone_number  | passport_number | license_plate |   id   |    name    |  phone_number  | passport_number | license_plate |
-- +-----+----------------+----------------+------+-------+-----+----------+--------+---------+----------------+-----------------+---------------+--------+------------+----------------+-----------------+---------------+
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       | 567218 | Jack       | (996) 555-8899 | 9029462229      | 52R0Y8U       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       | 251693 | Larry      | (892) 555-8872 | 2312901747      | O268ZZ0       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 864400 | Robin      | (375) 555-8161 |                 | 4V16VO0       |
-- | 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       | 561160 | Kathryn | (609) 555-5876 | 6121106406      | 4ZY7I8T       | 467400 | Luca       | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       | 626361 | Melissa    | (717) 555-1342 | 7834357192      |               |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 250277 | James      | (676) 555-6554 | 2438825627      | Q13SVG6       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 847116 | Philip     | (725) 555-3243 | 3391710505      | GW362R6       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       | 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       | 712712 | Jacqueline | (910) 555-3251 |                 | 43V0R5D       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 953679 | Doris      | (066) 555-9701 | 7214083635      | M51FA04       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 484375 | Anna       | (704) 555-2131 |                 |               |
-- +-----+----------------+----------------+------+-------+-----+----------+--------+---------+----------------+-----------------+---------------+--------+------------+----------------+-----------------+---------------+

-- b.  Who made those calls

SELECT * FROM people
 WHERE phone_number IN
       (SELECT caller FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration <= 60);

-- Findings
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 561160 | Kathryn | (609) 555-5876 | 6121106406      | 4ZY7I8T       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       |
-- +--------+---------+----------------+-----------------+---------------+


-- =========================================
-- 4. Thief took earliest flight out of Fiftyville on 2021/07/29.  Can check flights to find the flight and who was on it.

-- a. Find first flight out of Fiftyville on 2021/07/29
  SELECT * FROM flights, airports
   WHERE origin_airport_id =
         (SELECT id FROM airports
         WHERE city = 'Fiftyville')
     AND year = 2021
     AND month = 7
     AND day = 29
     AND destination_airport_id = airports.id
ORDER BY hour, minute
   LIMIT 1;

-- Findings
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------+---------------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | abbreviation |     full_name     |     city      |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------+---------------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 4  | LGA          | LaGuardia Airport | New York City |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------+---------------+

-- b. Who was on that flight

SELECT * FROM people
 WHERE passport_number IN
       (SELECT passport_number FROM passengers
         WHERE flight_id IN
               (  SELECT flights.id FROM flights, airports
                   WHERE origin_airport_id =
                           (SELECT id FROM airports
                           WHERE city = 'Fiftyville')
                     AND year = 2021
                     AND month = 7
                     AND day = 29
                     AND destination_airport_id = airports.id
                ORDER BY hour, minute
                   LIMIT 1));


-- =========================================
-- 5. Putting it all together

  SELECT * FROM people
   WHERE license_plate IN
         (SELECT license_plate FROM bakery_security_logs
           WHERE year = 2021
             AND month = 7
             AND day = 28
             AND hour = 10
             AND minute >= 15
             AND minute <= 25
             AND activity = 'exit')

INTERSECT

  SELECT * FROM people
   WHERE id IN
         (SELECT person_id FROM bank_accounts
           WHERE account_number IN
                 (SELECT account_number FROM atm_transactions
                   WHERE transaction_type = 'withdraw'
                     AND atm_location = 'Leggett Street'
                     AND year = 2021
                     AND month = 7
                     AND day = 28))

INTERSECT

  SELECT * FROM people
   WHERE phone_number IN
         (SELECT caller FROM phone_calls
           WHERE year = 2021
             AND month = 7
             AND day = 28
             AND duration <= 60)

INTERSECT

  SELECT * FROM people
   WHERE passport_number IN
         (SELECT passport_number FROM passengers
           WHERE flight_id IN
                 (  SELECT flights.id FROM flights, airports
                     WHERE origin_airport_id =
                             (SELECT id FROM airports
                             WHERE city = 'Fiftyville')
                       AND year = 2021
                       AND month = 7
                       AND day = 29
                       AND destination_airport_id = airports.id
                  ORDER BY hour, minute
                     LIMIT 1));

-- Findings
    +--------+-------+----------------+-----------------+---------------+
    |   id   | name  |  phone_number  | passport_number | license_plate |
    +--------+-------+----------------+-----------------+---------------+
    | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
    +--------+-------+----------------+-----------------+---------------+


-- =========================================
-- Thief: Bruce
-- Accomplice: Robin
-- Destination: New York City