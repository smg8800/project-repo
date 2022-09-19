# Script to take a small sample of larger Amazon data from Stanford dataset
# This script assumes that raw data is stored in a folder called "full_data"
# All trimmed data will be saved to a folder called "data"
# Raw data taken from file "amazon.txt" and saved to "amazon.txt"
# Raw meta data from file "amazon-meta.txt" and saved to "amazon-meta.txt"

import re

totalVert = 20000  # Save all vertices from 0 to lastId (exclusive)

# Extract vertices form metadata
afterIdMarker = "Id:   " + str(totalVert)  # Line after last metadata

with open("full_data/amazon-meta.txt", 'r') as readData:
    with open("data/amazon-meta.txt", 'w') as writeData:
        # First line is a comment
        writeData.write(readData.readline())

        # Second line has total nodes
        writeData.write("Total items: " + str(totalVert))
        readData.readline()  # Drop line from readData

        for line in readData:
            stripped = line.rstrip()  # Remove '\n' at end of line
            if stripped == afterIdMarker:
                # Stop once we are done with all id's
                break

            # Prepend newline at every line
            writeData.write('\n' + stripped)



# Extract vertices from data
with open("full_data/amazon.txt", 'r') as readData:
    with open("data/amazon.txt", 'w') as writeData:
        lineNumber = 0
        for line in readData:
            matches = re.findall('\d+', line)
            start = int(matches[0])
            end = int(matches[1])

            stripped = line.rstrip()

            # Only store lines where both vertices are < lastId
            if start < totalVert and end < totalVert:
                # Prepend newline at every line except first. This prevents trailing newline
                if lineNumber == 0:
                    writeData.write(stripped)
                else:
                    writeData.write('\n' + stripped)

            lineNumber += 1
