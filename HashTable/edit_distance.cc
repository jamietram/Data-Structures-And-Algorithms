
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;
void print_head()
{
    cout.setf(ios::left);
    cout << setw(16) << "Operation"
        << setw(32) << "z"
        << setw(8) << "Cost"
        << setw(8) << "Total" << endl;

    for (int i = 0; i < 64; ++i)
        cout << "-";
    cout << endl;
}

// Transformation operations
enum Operation {
    RIGHT,
    REPLACE,
    DELETE,
    INSERT
};

// Structure to store operation details
struct OperationDetails {
    Operation operation;
    char character;
	char position;
    int cost;
	OperationDetails(Operation op, char ch, int cst)
        : operation(op), character(ch), cost(cst) {}
};

// Function to calculate minimum of three integers
int min(int a, int b, int c) {
    int temp = (a < b) ? a : b;
    return (temp < c) ? temp : c;
}
std::string getOperationName(Operation operation) {
    switch (operation) {
        case RIGHT:
            return "right";
        case REPLACE:
            return "replace by";
        case DELETE:
            return "delete";
        case INSERT:
            return "insert";
        default:
            return "";
    }
}

// Function to calculate edit distance and generate operation sequence
int calculateEditDistance(const std::string& x, const std::string& y, std::vector<std::vector<int> >& dp,
                          std::vector<OperationDetails>& operationSequence) {
    int m = x.length();
    int n = y.length();

    // Initialize the dynamic programming table
    dp.resize(m + 1, std::vector<int>(n + 1, 0));

    // Fill in the base cases
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i * 2;  // delete operation
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j * 3;  // insert operation
    }

    // Fill in the remaining table entries
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // no operation required
            } else {
                dp[i][j] = min(dp[i - 1][j - 1] + 4,  // replace operation
                               dp[i][j - 1] + 3,      // insert operation
                               dp[i - 1][j] + 2);     // delete operation
            }
        }
    }

    // Generate the operation sequence
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && x[i - 1] == y[j - 1]) {
           operationSequence.push_back(OperationDetails(RIGHT, x[i - 1], 0));
            i--;
            j--;
        } else {
            if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 4) {
                operationSequence.push_back(OperationDetails(REPLACE, y[j - 1], 4));
                i--;
                j--;
            } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 3) {
                operationSequence.push_back(OperationDetails(INSERT, y[j - 1], 3));
                j--;
            } else {
                operationSequence.push_back(OperationDetails(DELETE, x[i - 1], 2));
                i--;
            }
        }
    }

    // Reverse the operation sequence
    std::reverse(operationSequence.begin(), operationSequence.end());

    // Return the edit distance
    return dp[m][n];
}

// Function to print the operation sequence in a table format
void printOperationSequence(const std::string& x, const std::string& y, const std::vector<OperationDetails>& operationSequence) {
    int m = x.length();
    int n = y.length();

    // Print the table header
    print_head();

    // Print the initial string
    std::cout << std::setw(16) << "initial string"
              << std::setw(32) << x
              << std::setw(8) << "0"
              << std::setw(8) << "0" << std::endl;

    // Perform the transformation operations and print the table entries
    std::string z = x;
    int totalCost = 0;
    int cursorPosition = 0;
    for (std::vector<OperationDetails>::const_iterator it = operationSequence.begin(); it != operationSequence.end(); ++it) {
        if (it->operation == RIGHT) {
			std::cout << std::setw(16) << getOperationName(it->operation);
            if (cursorPosition < m) {
                cursorPosition++;
                if (it->character == x[cursorPosition - 1]) {
                    totalCost -= it->cost;  // Subtract the cost if the character remains the same
                }
            }
        } else if (it->operation == REPLACE) {
			std::cout << getOperationName(it->operation) << " " << it->character << "\t";
            if (cursorPosition < m) {
                z[cursorPosition] = it->character;
                cursorPosition++;
            }
        } else if (it->operation == DELETE) {
			std::cout << getOperationName(it->operation) << "\t\t";
            if (cursorPosition < m) {
                z.erase(cursorPosition, 1);
                m--;
            }
        } else if (it->operation == INSERT) {
			std::cout << getOperationName(it->operation) << " " << it->character <<"\t";
            if (cursorPosition <= m) {
                z.insert(cursorPosition, 1, it->character);
                cursorPosition++;
                m++;
            }
        }
        totalCost += it->cost;
        
        std::cout << std::setw(32) << z.substr(0, cursorPosition) + "*" + z.substr(cursorPosition)
                  << std::setw(8) << it->cost
                  << std::setw(8) << totalCost << std::endl;
    }

}
int main(int argc, char* argv[]) {
     if (argc >= 4 ) {
        std::string str1;
        int i = 1;
        while (i < argc && std::string(argv[i]) != "to") {
            str1 += std::string(argv[i]);
            if (string(argv[i + 1]) != "to")
				str1 += " ";
            i++;
        }
        i++;
        std::string str2;
        while (i < argc) {
            str2 += std::string(argv[i]);
            if (i < argc - 1) { // check if it's not the last argument
                str2 += " ";
            }
            i++;
        }

        std::vector<std::vector<int> > dp;
        std::vector<OperationDetails> operationSequence;

        int editDistance = calculateEditDistance(str1, str2, dp, operationSequence);

        std::cout << "Edit Distance: " << editDistance << "\n";
        printOperationSequence(str1, str2, operationSequence);
    } else if (argc == 2) {
        // Command-line input: ./edit_distance filename
         std::string inputFilename = argv[1];
        std::string filename = inputFilename + ".txt";
        std::ifstream inputFile(filename.c_str());

        if (inputFile.is_open()) {
            std::string x, y;
            int m, n;

            // Read the input from the file
            inputFile >> m;
            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(inputFile, x);

            inputFile >> n;
            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(inputFile, y);

            inputFile.close();

            std::vector<std::vector<int> > dp;
            std::vector<OperationDetails> operationSequence;

            int editDistance = calculateEditDistance(x, y, dp, operationSequence);

            std::cout << "Edit Distance: " << editDistance << "\n";
        } else {
            std::cerr << "Failed to open the input file.\n";
        }
    } else {
        std::cerr << "Invalid number of command-line arguments.\n";
        std::cerr << "Usage:\n";
        std::cerr << "  ./edit_distance string1 to string2\n";
        std::cerr << "or\n";
        std::cerr << "  ./edit_distance filename\n";
    }

    return 0;
}
