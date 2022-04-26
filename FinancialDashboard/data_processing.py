from functions import *

# This file creates the overall table for the database. The main function reads in
# and loops through the rows of the CSV, calling the classify function on each row.
# This function reads portions of the current row and gets all of the required
# information, which in this case is info on options trading transactions.

class trades:
    all_trades = []

    # add trade to list all_trades
    def add_trade(self, trade):
        self.all_trades.append(trade)
    
    # computes overall PL
    def total_PL(self):
        PL = 0
        for trade in self.all_trades:
            PL += trade.PL
        print("Overall P/L: " + str(PL))
        
    # computes average winning PL
    def avg_winner(self):
        q = 0
        sum = 0
        for trade in self.all_trades:
            if trade.PL > 0:
                sum += trade.PL
                q += 1
        print("Average winner (" + str(q) + "): " + str(sum/q))
    
    # computes average losing PL
    def avg_loser(self):
        q = 0
        sum = 0
        for trade in self.all_trades:
            if trade.PL <= 0:
                sum += trade.PL
                q += 1
        print("Average loser (" + str(q) + "): " + str(sum/q))
    
    # writes all trades to a file 'trades.txt'
    def writeToFile(self):
        f = open("trades.txt", "w")
        for trade in self.all_trades:
            f.write("Trade " + str(trade.ID) + ", Ticker: " + trade.tick + ", Strike: " + str(trade.strike) + ", Quantity: " + str(trade.quant) +", Expiration: " + trade.exp + ", Acquired: " + trade.pdate + ", Sold: " + trade.sdate + ", Cost: " + str(trade.cbasis) + ", Proceeds: " + str(trade.proceeds) + ", PL: " + str(trade.PL) + "\n")
        f.close()
    
    # ==== will adapt this code to create a table of trades instead of just orders ====
    # def create_table_SQL_code(self, output):
    #     f = open(output, "w")
    #     for x in self.orders:
    #         if x.bs == 'other':
    #             values = "'" + str(x.ID) + "', 'other', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'"
    #             f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")
    #         else:
    #             values = "'" + str(x.ID) + "', '" + x.bs + "', '" + x.tick + "', '" + x.type + "', '" + str(x.strike) + "', '" + x.exp + "', '" + x.tdate + "', '" + str(x.ucost) + "', '" + str(x.quant) + "', '" + str(x.cbasis) + "', '" + str(x.comm) + "', '" + str(x.fees) + "'"
    #             f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")
    #     f.close()

class trade:
    def __init__(self, orders, i):
        self.ID = i
        cost = 0
        proceeds = 0
        quant = 0
        selldate = ""
        buydate = ""
        for order in orders:
            if order.cbasis[0] == '-':
                quant += int(order.quant)
                cost += float(order.cbasis[1:])*100
                buydate = order.tdate
            else:
                proceeds += float(order.cbasis)*100
                selldate = order.tdate
        if selldate == "":
            selldate = "Expired"
        self.sdate = selldate
        self.pdate = buydate
        self.tick = orders[0].tick
        self.type = orders[0].type
        self.strike = orders[0].strike
        self.exp = orders[0].exp
        self.quant = quant
        self.cbasis = cost
        self.proceeds = proceeds
        self.comm = 2*0.65 * int(quant)
        self.fees = 2*0.01 * int(quant)
        self.PL = (float(proceeds) - (float(cost) + float(self.comm) + float(self.fees)))

class order:
    def __init__(self, ID, bs, tick, type, strike, exp, tdate, ucost, quant, cbasis, comm, fees):
        self.ID = ID
        self.bs = bs
        self.tick = tick
        self.type = type
        self.strike = strike
        self.exp = exp
        self.tdate = tdate
        self.ucost = ucost
        self.quant = quant
        self.cbasis = cbasis
        self.comm = 0.65 * int(quant)
        self.fees = 0.01 * int(quant)


# parent class of order; stores all orders from the csv file.
class orderbook:
    orders = [] # array of order object
    
    # add an order to the total list of orders
    def add_order(self, order):
        self.orders.append(order)

    # writes SQL statements to a file which can be copied into a SQL editor and run to create a
    # table of all orders in a database
    def create_table_SQL_code(self, output):
        f = open(output, "w")
        for x in self.orders:
            if x.bs == 'other':
                values = "'" + str(x.ID) + "', 'other', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'"
                f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")
            else:
                values = "'" + str(x.ID) + "', '" + x.bs + "', '" + x.tick + "', '" + x.type + "', '" + str(x.strike) + "', '" + x.exp + "', '" + x.tdate + "', '" + str(x.ucost) + "', '" + str(x.quant) + "', '" + str(x.cbasis) + "', '" + str(x.comm) + "', '" + str(x.fees) + "'"
                f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")
        f.close()


    # Create_trades creates a trades object, then iterates through all of the orders twice,
    # matching orders of the same position into one single trade. These trades are then added
    # to the list of trades made, then the trades object is returned.
    def create_trades(self):
        seen = []
        i = 0
        all_trades = trades()
        for order in self.orders:
            if order.ID in seen or order.bs == "other":
                continue
            seen.append(order.ID)
            current_orders = []
            current_orders.append(order)
            for order2 in self.orders:
                if order.ID == order2.ID or order2.bs == "other":
                    continue
                if (order.tick == order2.tick) and (order.strike == order2.strike) and (order.exp == order2.exp) and (order.type == order2.type):
                    if order2.ID not in seen:
                        seen.append(order2.ID)
                        current_orders.append(order2)
            current_trade = trade(current_orders, i)
            all_trades.add_trade(current_trade)
            i+=1

        return all_trades


# This function 'classifies' each row of data by stripping apart the data
# and using the relevant components to form an order object with the correct information.
# Params: data - pandas dataframe file of read CSV,
#         i - current integer row index
# Returns: populated order object
def create_order(data, i):
    description = data.loc[i][2]
    words = description.split()
    b_or_s = ""
    if len(words) < 10:
        return order(i+1, 'other', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

    if words[0] == "Bought":
        b_or_s = "Buy To Open"
        unit_cost = "-"+words[9]
    elif words[0] == "Sold":
        b_or_s = "Sell To Close"
        unit_cost = words[9]
    else:
        return order(i+1, 'other', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

    ticker = words[2]
    quant = words[1]
    expi= words[3] + " " + words[4] + " " + words[5]
    expire = reformat_date(expi)
    strike = words[6]
    optionType = words[7]
    cost_basis = float(quant) * float(unit_cost)
    current = order(i+1,b_or_s,ticker,optionType,strike,expire,data.loc[i][0],unit_cost,str(quant),str(cost_basis),'0.65','0.01')
    return current
    

