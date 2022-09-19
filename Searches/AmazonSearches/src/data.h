#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

class Data {
    public:
        /*
        * Reads the file line by line, capturing two integers per line and storing
        * the first in nodesFrom, and the second in nodesTo.
        */
        void read_from_file(std::string name);

        /*
        * returns nodesFrom
        */
        std::vector<int> getNodesFrom() const;
        /*
        * Returns nodesTo
        */
        std::vector<int> getNodesTo() const;
    private:
        std::vector<int> nodesFrom;
        std::vector<int> nodesTo;
};

#endif