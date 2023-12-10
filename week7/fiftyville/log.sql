-- Keep a log of any SQL queries you execute as you solve the mystery.

-- FIRST i used these information that the theft took place on July 28, 2021 and that it took place on Humphrey -- -- Street and get out the desription of roppery FROM crime_scene_reports.

SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7
AND street = "Humphrey Street";

-- To know the all data about the three interviews
SELECT * FROM interviews
WHERE month = 7 AND day = 28
AND transcript LIKE '%bakery%';
--
# THE DATA ABOUT INFO...
# FIRST
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left
-- the parking lot in that time frame.

# SECOND
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning,
-- before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief
-- there withdrawing some money.

# THREED
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket..

-- FIND the thief
SELECT * FROM people AS p
WHERE p.passport_number IN (
        SELECT ps.passport_number
        FROM passengers ps
        WHERE ps.flight_id IN (
                SELECT f.id
                FROM flights f
                    JOIN airports a  ON a.id = f.origin_airport_id
                WHERE f.month=7
                    AND f.day=29
                    AND f.year=2021
                    AND a.city='Fiftyville' ))
AND passport_number = (
SELECT passport_number FROM people AS p
JOIN bakery_security_logs AS b ON b.license_plate = p.license_plate
JOIN phone_calls AS pc ON pc.caller = p.phone_number
JOIN bank_accounts AS ba ON ba.person_id = p.id
JOIN atm_transactions AS at ON at.account_number = ba.account_number
WHERE activity = 'exit' AND b.day = 28 AND b.month = 7 AND b.hour = 10 AND b.minute BETWEEN 15 AND 25 AND duration < 60
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

-- FIND The city the thief ESCAPED TO:
SELECT city FROM airports
WHERE id =
(SELECT destination_airport_id FROM passengers AS ps
JOIN flights AS f ON ps.flight_id = f.id
JOIN airports AS a ON a.id = f.origin_airport_id
WHERE f.month=7
AND f.day=29
AND f.year=2021
AND a.city='Fiftyville'
AND passport_number = 5773159633 );

-- The ACCOMPLICE is:
SELECT name FROM people
WHERE phone_number = (
SELECT receiver FROM people AS p
JOIN phone_calls AS pc ON pc.caller = p.phone_number
WHERE pc.caller = "(367) 555-5533" AND day = 28 AND month = 7 AND duration < 60);

"""
SOME HELPER QUERIES:

SELECT name FROM people AS p
JOIN bank_accounts AS ba ON ba.person_id = p.id
JOIN atm_transactions AS at ON at.account_number = ba.account_number
WHERE day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

SELECT name FROM people AS p
JOIN phone_calls AS pc ON pc.caller = p.phone_number
WHERE day = 28 AND month = 7 AND duration < 60;

SELECT * FROM flights
WHERE origin_airport_id IN (
SELECT id FROM airports
WHERE city = 'Fiftyville' AND day = 29);
"""
