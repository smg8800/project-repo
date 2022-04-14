USE options

-- temporary SQL code that simply creates a table (or deletes, depending on whats commented out), 
-- then selects everything from the table to display it


CREATE TABLE orders(
    OrderID varchar(255),
    BTOSTC varchar(255),
    TICK varchar(255),
    OTYPE varchar(255),
    STRIKE varchar(255),
    EXP varchar(255),
    PDATE varchar(255),
    UCOST varchar(255),
    QUANTITY varchar(255),
    CBASIS varchar(255),
    COMM varchar(255),
    FEES varchar(255)
);

--DROP TABLE orders;

SELECT * FROM orders;

-- get number of orders trading the ticker 'SPY'
SELECT COUNT (TICK)
FROM orders
WHERE TICK = 'SPY';



