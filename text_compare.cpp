#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Logger {
private:
    std::ostringstream logStream; // Use an in-memory stream for logging differences

public:
    void logDifference(const std::string& diff) {
        logStream << diff << std::endl;
    }

    void printLog() const {
        std::cout << logStream.str();
    }
};

class TextComparer {
private:
    std::vector<std::string> text1Lines;
    std::vector<std::string> text2Lines;
    Logger& logger;

    std::vector<std::string> splitIntoLines(const std::string& text) {
        std::vector<std::string> lines;
        std::istringstream stream(text);
        std::string line;
        while (std::getline(stream, line)) {
            lines.push_back(line);
        }
        return lines;
    }

public:
    TextComparer(const std::string& text1, const std::string& text2, Logger& log)
        : logger(log) {
        text1Lines = splitIntoLines(text1);
        text2Lines = splitIntoLines(text2);
    }

    void compare() {
        size_t maxLines = std::max(text1Lines.size(), text2Lines.size());
        for (size_t i = 0; i < maxLines; ++i) {
            std::string line1 = (i < text1Lines.size()) ? text1Lines[i] : "(No line)";
            std::string line2 = (i < text2Lines.size()) ? text2Lines[i] : "(No line)";

            if (line1 != line2) {
                std::ostringstream diff;
                diff << "Line " << i + 1 << " differs:\n";
                diff << "Text1: " << line1 << "\n";
                diff << "Text2: " << line2 << "\n";
                logger.logDifference(diff.str());
            }
        }
    }
};

int main() {
    try {
        // Input texts from the user
        std::string text1, text2;

        std::cout << "Enter the first text (end with an empty line):\n";
        std::string line;
        while (std::getline(std::cin, line) && !line.empty()) {
            text1 += line + "\n";
        }

        std::cout << "Enter the second text (end with an empty line):\n";
        while (std::getline(std::cin, line) && !line.empty()) {
            text2 += line + "\n";
        }

        // Create a logger
        Logger logger;

        // Compare texts
        TextComparer comparer(text1, text2, logger);
        comparer.compare();

        // Print the differences
        std::cout << "\nComparison Results:\n";
        logger.printLog();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
