-- According to the proposed exercise we must find out who are the thieves that stole the duck CS50. The city fiftyville has asked us to find out Who is the thief, To which city did the thief escape, and Who is the thief's accomplice that helped them escape.
-- So far all we know is that the theft occurred on July 28, 2021 and took place on Humphrey Street.

-- Take a look at the table report, crime_scene_reports.
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- New info: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. Littering took place at 16:36. No known witnesses.

-- Given this information we should check out the table interviews.
SELECT *
  FROM interviews
 WHERE year = 2021 AND month = 7 AND day = 28;
-- New info:| 161 |Ruth   | 2021 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- New info:| 162 |Eugene | 2021 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- New info:| 163 |Raymond| 2021 | 7 | 28 | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Now we must look at the bakery_security_log table
SELECT *
  FROM bakery_security_logs
 WHERE year = 2021 AND month = 7 AND day = 28;
-- We can see that there are several cars leaving the bakery 10 minutes after the robbery

-- The owners of the cars are:
SELECT *
  FROM people
 WHERE license_plate IN (
       SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- As mentioned above, the respective owners of the vehicles that left the bakery after the robbery was: Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce.

-- Now let's check if anyone on the list has boarded a flight.
SELECT *
  FROM passengers
 WHERE passport_number IN (
       SELECT passport_number FROM people
        WHERE license_plate IN (
              SELECT license_plate FROM bakery_security_logs
               WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25));
-- Let's filter which of these flights are on 7/29 with airport_id of fiftyville.
SELECT *
  FROM airports;
--| 8 | CSF | Fiftyville Regional Airport | Fiftyville |

SELECT *
  FROM flights
 WHERE id IN (
       SELECT flight_id FROM passengers
        WHERE passport_number IN (
              SELECT passport_number FROM people
               WHERE license_plate IN (
                     SELECT license_plate FROM bakery_security_logs
                      WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)))
                        AND origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29;
-- According to the results two passengers plan to leave the airport and they are: 2021/7/29 8:20 -> flight_id = 36, 2021/7/29 16:00 -> flight_id = 18.

-- Checking id 36.
SELECT *
  FROM passengers
 WHERE flight_id = 36;

-- As we can see, the list returned 8 passengers. Let's narrow down the number of suspects.
SELECT *
  FROM passengers
 WHERE flight_id = 36 AND passport_number IN (
       SELECT passport_number FROM people
        WHERE license_plate IN (
              SELECT license_plate FROM bakery_security_logs
               WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25));

-- Number was reduced to 4 people.
SELECT *
  FROM people
 WHERE passport_number IN (
       SELECT passport_number FROM passengers
        WHERE flight_id = 36 AND passport_number IN (
              SELECT passport_number FROM people
               WHERE license_plate IN (
                     SELECT license_plate FROM bakery_security_logs
                      WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)));
-- The names returned were: Sofia, Luca, Kelsey, Bruce.

-- Next step is to check the phone calls by calling the phone_calls table to get more information about the suspects.
SELECT *
  FROM phone_calls
 WHERE caller IN (
       SELECT phone_number
         FROM people
        WHERE name IN ('Sofia', 'Luca', 'Kelsey', 'Bruce'));

-- Since several calls were returned in the table, let's check if any calls were made on 7/28.
SELECT *
  FROM phone_calls
 WHERE caller IN (
       SELECT phone_number
         FROM people
        WHERE name IN ('Sofia', 'Luca', 'Kelsey', 'Bruce')) AND year = 2021 AND month = 7 AND day = 28;

-- Looking closely, we can see that it has only 3 urban identification numbers.
SELECT name
  FROM people
 WHERE phone_number IN (
       SELECT caller
         FROM phone_calls
        WHERE caller IN (
              SELECT phone_number
                FROM people
               WHERE name IN ('Sofia', 'Luca', 'Kelsey', 'Bruce')) AND year = 2021 AND month = 7 AND day = 28);
-- The suspects are: Sofia, Kelsey, Bruce.

-- We know that the suspect talks on the phone for about 30 minutes, and that someone is: | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7 | 28 | 36 |.
SELECT name
  FROM people
 WHERE phone_number = '(499) 555-9472';
-- Only 1 number is displayed, this suspect is: Kelsey

-- Let's see if any of the suspects withdrew money at Leggett Street.
SELECT account_number
  FROM atm_transactions
 WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw';

-- Let's check the name on the list.
SELECT name
  FROM people
       JOIN bank_accounts ON bank_accounts.person_id = people.id
 WHERE account_number IN (
       SELECT account_number
         FROM atm_transactions
        WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw');
-- Upon analysis, Kelsey did not use the ATM on 7/28 so Bruce is the prime suspect.

SELECT *
  FROM people
 WHERE name = 'Bruce';
 -- Let's verify that Bruce really committed the robbery.

 -- Check bakery security records.
SELECT *
  FROM bakery_security_logs
 WHERE license_plate = (
       SELECT license_plate
         FROM people
        WHERE name = 'Bruce');
-- Bruce enter the at 8:23 and exit at 10:18.

-- Checking Bruce's phone calls.
SELECT *
  FROM phone_calls
 WHERE caller = (
       SELECT phone_number
         FROM people
        WHERE name = 'Bruce');
-- Bruce made a 45-minute call.

-- The flights are coming in.
SELECT *
  FROM flights
       JOIN passengers ON passengers.flight_id = flights.id
 WHERE passengers.passport_number = (
       SELECT passport_number
         FROM people
        WHERE name = 'Bruce');
-- Only 1 result was presented, flight 7/28 8:20 with id = 36, seat=4A, origin_airport_id = 8, destination_airport_id = 4

-- The destination of the flight is.
SELECT *
  FROM airports
 WHERE id = 4;
-- 4, LGA, LaGuardia Airport, New York City.

-- Let's check who is your accomplice. Knowing that Bruce talked for 45 minutes on 7/28 to (375) 555-8161.
SELECT *
  FROM people
 WHERE phone_number = '(375) 555-8161';
-- His accomplice is Robin.