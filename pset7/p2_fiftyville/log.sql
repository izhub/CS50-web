-- A Mystery in Fiftyville
-- The CS50 Duck has been stolen! The town of Fiftyville has called upon you to solve the mystery of the
-- stolen duck. Authorities believe that the thief stole the duck and then, shortly afterwards, took a
-- flight out of town with the help of an accomplice. Your goal is to identify:

-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape
-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.
-- Once you solve the mystery, complete each of the lines in answers.txt

-- Execute sqlite3 fiftyville.db to begin running queries on the database.
-- While running sqlite3, executing .tables will list all of the tables in the database.
-- While running sqlite3, executing .schema TABLE_NAME
-- You may find it helpful to start with the crime_scene_reports table. Start by looking for a
-- crime scene report that matches the date and the location of the crime.

-- Keep a log of any SQL queries you execute as you solve the mystery.

.tables
airports                  crime_scene_reports       people
atm_transactions          flights                   phone_calls
bank_accounts             interviews
courthouse_security_logs  passengers

SELECT * FROM crime_scene_reports WHERE month =  7 and day = 28;

-- Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their
-- interview transcripts mentions the courthouse.

SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2020;

-- 161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in
-- the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot,
-- you might want to look for cars that left the parking lot in that time frame.

-- 162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier
-- this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the
-- thief there withdrawing some money.

-- 163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked
-- to them for less than a minute. In the call, I heard the thief say that they were planning to take the
-- earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone
-- to purchase the flight ticket.

SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10;

-- id  | year | month | day | hour  | minute | activity | license_plate
-- 260 | 2020 | 7     | 28 | 10     | 16     | exit     | 5P2BI95
-- 261 | 2020 | 7     | 28 | 10     | 18     | exit     | 94KL13X
-- 262 | 2020 | 7     | 28 | 10     | 18     | exit     | 6P58WS2
-- 263 | 2020 | 7     | 28 | 10     | 19     | exit     | 4328GD8
-- 264 | 2020 | 7     | 28 | 10     | 20     | exit     | G412CB7
-- 265 | 2020 | 7     | 28 | 10     | 21     | exit     | L93JTIZ
-- 266 | 2020 | 7     | 28 | 10     | 23     | exit     | 322W7JE
-- 267 | 2020 | 7     | 28 | 10     | 23     | exit     | 0NTHK55

SELECT * FROM people
WHERE license_plate IN ('5P2BI95','94KL13X','6P58WS2','4328GD8','G412CB7','L93JTIZ','322W7JE','0NTHK55');

-- id     | name        | phone_number   | passport_number  | license_plate
-- 221103 | Patrick     | (725) 555-4692 | 2963008352       | 5P2BI95
-- 243696 | Amber       | (301) 555-4174 | 7526138472       | 6P58WS2
-- 396669 | Elizabeth   | (829) 555-5269 | 7049073643       | L93JTIZ
-- 398010 | Roger       | (130) 555-0289 | 1695452385       | G412CB7
-- 467400 | Danielle    | (389) 555-5198 | 8496433585       | 4328GD8
-- 514354 | Russell     | (770) 555-1861 | 3592750733       | 322W7JE
-- 560886 | Evelyn      | (499) 555-9472 | 8294398571       | 0NTHK55
-- 686048 | Ernest      | (367) 555-5533 | 5773159633       | 94KL13X

-----------------------

SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND atm_location = 'Fifer Street';

-- id | account_number  | year  | month| day | atm_location | transaction_type | amount
-- 246 | 28500762       | 2020  | 7    | 28  | Fifer Street | withdraw         | 48
-- 264 | 28296815       | 2020  | 7    | 28  | Fifer Street | withdraw         | 20
-- 266 | 76054385       | 2020  | 7    | 28  | Fifer Street | withdraw         | 60
-- 267 | 49610011       | 2020  | 7    | 28  | Fifer Street | withdraw         | 50
-- 269 | 16153065       | 2020  | 7    | 28  | Fifer Street | withdraw         | 80
-- 288 | 25506511       | 2020  | 7    | 28  | Fifer Street | withdraw         | 20
-- 313 | 81061156       | 2020  | 7    | 28  | Fifer Street | withdraw         | 30
-- 336 | 26013199       | 2020  | 7    | 28  | Fifer Street | withdraw         | 35

SELECT * FROM bank_accounts
WHERE account_number IN ('28500762','28296815','76054385','49610011','16153065','25506511','81061156','26013199');

-- account_number | person_id | creation_year
-- 49610011       | 686048    | 2010
-- 26013199       | 514354    | 2012
-- 16153065       | 458378    | 2012
-- 28296815       | 395717    | 2014
-- 25506511       | 396669    | 2014
-- 28500762       | 467400    | 2014
-- 76054385       | 449774    | 2015
-- 81061156       | 438727    | 2018

SELECT * FROM people WHERE id IN ('686048','514354','458378','395717','396669','467400','449774','438727');

-- id     | name        | phone_number   | passport_number  | license_plate
-- 395717 | Bobby       | (826) 555-1652 | 9878712108       | 30G67EN
-- 396669 | Elizabeth * | (829) 555-5269 | 7049073643       | L93JTIZ
-- 438727 | Victoria    | (338) 555-6650 | 9586786673       | 8X428L0
-- 449774 | Madison     | (286) 555-6063 | 1988161715       | 1106N58
-- 458378 | Roy         | (122) 555-4581 | 4408372428       | QX4YZN3
-- 467400 | Danielle *  | (389) 555-5198 | 8496433585       | 4328GD8
-- 514354 | Russell  *  | (770) 555-1861 | 3592750733       | 322W7JE
-- 686048 | Ernest   *  | (367) 555-5533 | 5773159633       | 94KL13X

----------------------

SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60;

-- id  | caller         | receiver       | year | month | day | duration
-- 221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7     | 28  | 51
-- 224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7     | 28  | 36
-- 233 | (367) 555-5533*| (375) 555-8161 | 2020 | 7     | 28  | 45
-- 251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7     | 28  | 50
-- 254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7     | 28  | 43
-- 255 | (770) 555-1861*| (725) 555-3243 | 2020 | 7     | 28  | 49
-- 261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7     | 28  | 38
-- 279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7     | 28  | 55
-- 281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7     | 28  | 54


SELECT * FROM people WHERE phone_number IN ('(375) 555-8161','(725) 555-3243');

-- receiver
-- id     | name        | phone_number   | passport_number  | license_plate
-- 847116 | Philip      | (725) 555-3243 | 3391710505       | GW362R6
-- 864400 | Berthold    | (375) 555-8161 |                  | 4V16VO0

---------------------

SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2020 ;

-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 18 | 8                  | 6                     | 2020 | 7     | 29  | 16   | 0
-- 23 | 8                  | 11                    | 2020 | 7     | 29  | 12   | 15
-- 36 | 8                  | 4                     | 2020 | 7     | 29  | 8 *  | 20
-- 43 | 8                  | 1                     | 2020 | 7     | 29  | 9    | 30
-- 53 | 8                  | 9                     | 2020 | 7     | 29  | 15   | 20

SELECT * FROM airports WHERE id = 4;

-- id | abbreviation | full_name        | city
-- 4  | LHR          | Heathrow Airport | London

SELECT * FROM passengers WHERE passport_number IN ('3592750733', '5773159633');

-- flight_id | passport_number  | seat
-- 18        | 3592750733       | 4C
-- 24        | 3592750733       | 2C
-- 36        | 5773159633 *     | 4A
-- 54        | 3592750733       | 6C


-- check50 cs50/problems/2021/x/fiftyville
-- submit50 cs50/problems/2021/x/fiftyville