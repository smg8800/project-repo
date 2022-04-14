from data_processing import *

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