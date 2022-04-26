from data_processing import *

# driver code loops through each row of the input data
def main(filename, outputname):
    orders = read_data(filename)
    rows = len(orders)
    book = orderbook()
    for i in range(rows-1):
        new_order = create_order(orders, i)
        book.add_order(new_order)
    book.create_table_SQL_code(outputname)

    # process all_trades and print out interesting information
    all_trades = book.create_trades()
    all_trades.total_PL()
    all_trades.avg_winner()
    all_trades.avg_loser()
    all_trades.writeToFile()

# run code

file = '/Users/sean/Coding/Projects/FinancialDashboard/transactions.csv'
out = '/Users/sean/Coding/Projects/FinancialDashboard/code.txt'
main(file, out)