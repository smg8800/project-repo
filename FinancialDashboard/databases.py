from xml.etree.ElementTree import tostring
from click import command
from functions import *
import pandas as pd

# This file creates the overall table for the database. The main function reads in
# and loops through the rows of the CSV, calling the classify function on each row.
# This function reads portions of the current row and gets all of the required
# information, which in this case is info on options trading transactions.



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

    # currently refactoring 'classify' to an order creator and a SQL code creator, this creates the SQL table
    # def create_table_SQL_code(self, file):
    #     f = open(file, 'w')
    #     description = data.loc[i][2]
    #     words = description.split()
    #     b_or_s = ""
    #     c_or_p = ""
    #     if words[0] == "Bought":
    #         b_or_s = "Buy To Open"
    #         unit_cost = "-"+words[9]
    #     elif words[0] == "Sold":
    #         b_or_s = "Sell To Close"
    #         unit_cost = words[9]
    #     else:
    #         values = "'" + self.ID + "', 'other type', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'"
    #         f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")
    #         return

    #     ticker = words[2]
    #     quant = words[1]
    #     expi= words[3] + " " + words[4] + " " + words[5]
    #     expire = reformat_date(expi)
    #     strike = words[6]
    #     optionType = words[7]
    #     cost_basis = float(quant) * float(unit_cost)
    #     current = order(i+1,b_or_s,ticker,optionType,strike,expire,data.loc[i][0],unit_cost,str(quant),str(cost_basis),'0.65','0.01')
    #     values = "'" + self.ID + "', '" + self.bs + "', '" + self.ticker + "', '" + self.type + "', '" + self.strike + "', '" + self.exp + "', '" + self.tdate + "', '" + self.ucost + "', '" + self.quant + "', '" + self.cbasis + "', '0.65','0.01'"
    #     f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")

    def find_full_trades():
        print()


class trade:
    def __init__(self, ID, tick, type, strike, exp, pdate, sdate, quant, cbasis, proceeds, comm, fees):
        self.ID = ID
        self.tick = tick
        self.type = type
        self.strike = strike
        self.exp = exp
        self.pdate = pdate
        self.sdate = sdate
        self.quant = quant
        self.cbasis = cbasis
        self.proceeds = proceeds
        self.comm = comm
        self.fees = fees
        self.PL = float(quant)*(float(proceeds) - (float(cbasis) + float(comm) + float(fees)))


# This function 'classifies' each row of data by stripping apart the data
# and using the relevant components to form the table with desired information.
# Nothing is returned, but the SQL code to load everything is written to an output file.
# Params: data - pandas dataframe file of read CSV,
#         f - name of output file to write code to,
#         i - current integer row index we are checking
def classify(data, f, i):
    description = data.loc[i][2]
    words = description.split()
    b_or_s = ""
    c_or_p = ""
    if words[0] == "Bought":
        b_or_s = "Buy To Open"
        unit_cost = "-"+words[9]
    elif words[0] == "Sold":
        b_or_s = "Sell To Close"
        unit_cost = words[9]
    else:
        values = "'" + str(i+1) + "', 'other type', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'"
        f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")
        return

    ticker = words[2]
    quant = words[1]
    expi= words[3] + " " + words[4] + " " + words[5]
    expire = reformat_date(expi)
    strike = words[6]
    optionType = words[7]
    cost_basis = float(quant) * float(unit_cost)
    current = order(i+1,b_or_s,ticker,optionType,strike,expire,data.loc[i][0],unit_cost,str(quant),str(cost_basis),'0.65','0.01')
    values = "'" + str(i+1) + "', '" + b_or_s + "', '" + ticker + "', '" + optionType + "', '" + strike + "', '" + expire + "', '" + data.loc[i][0] + "', '" + unit_cost + "', '" + str(quant) + "', '" + str(cost_basis) + "', '0.65','0.01'"
    f.write("INSERT INTO orders(OrderID, BTOSTC, TICK, OTYPE, STRIKE, EXP, PDATE, UCOST, QUANTITY, CBASIS, COMM, FEES) VALUES(" + values +");" + "\n")
    
# driver code loops through each row of the input data
def main(filename, outputname):
    data = pd.read_csv(filename)
    output = open(outputname, "a")
    output.write("")
    rows = len(data)
    for i in range(rows-1):
        classify(data, output, i)
    output.close()



# run code

file = '/Users/sean/Coding/Projects/FinancialDashboard/transactions.csv'
out = '/Users/sean/Coding/Projects/FinancialDashboard/code.txt'
main(file, out)

