#include <iostream>
#include <string>

struct TimeCapsule {
    int year;
    std::string eventName;
    TimeCapsule* left;
    TimeCapsule* right;

    TimeCapsule(int y, std::string e) : year(y), eventName(e), left(nullptr), right(nullptr) {}
};

class TimeStreamStabilizer {
public:
    TimeStreamStabilizer() : root(nullptr) {}

    void inject(int year, std::string eventName) {
        root = insert(root, year, eventName);
    }

    void paradox(int year) {
        root = remove(root, year);
    }

    void search(int year) {
        TimeCapsule* node = find(root, year);
        if (node) {
            std::cout << "> Result: Event Found! [" << node->year << ": " << node->eventName << "]" << std::endl;
        } else {
            std::cout << "> Result: Year " << year << " not found in current timeline." << std::endl;
        }
    }

    void report() {
        std::cout << "> COMMAND: CHRONOLOGICAL REPORT" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        inOrderTraversal(root);
        std::cout << "-------------------------------" << std::endl;
    }

    int calculateTimeSpan() {
        int minYear = findMin(root)->year;
        int maxYear = findMax(root)->year;
        return maxYear - minYear;
    }

private:
    TimeCapsule* root;

    TimeCapsule* insert(TimeCapsule* node, int year, std::string eventName) {
        if (!node) {
            std::cout << "> System: Injecting " << year << "... Timeline stable." << std::endl;
            return new TimeCapsule(year, eventName);
        }

        if (year < node->year) {
            node->left = insert(node->left, year, eventName);
        } else if (year > node->year) {
            node->right = insert(node->right, year, eventName);
        } else {
            // Year already exists, do nothing
        }

        return node;
    }

    TimeCapsule* remove(TimeCapsule* node, int year) {
        if (!node) return nullptr;

        if (year < node->year) {
            node->left = remove(node->left, year);
        } else if (year > node->year) {
            node->right = remove(node->right, year);
        } else {
            std::cout << "> Alert: Paradox detected at " << year << "!" << std::endl;
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            } else if (!node->left) {
                TimeCapsule* temp = node;
                node = node->right;
                delete temp;
            } else if (!node->right) {
                TimeCapsule* temp = node;
                node = node->left;
                delete temp;
            } else {
                TimeCapsule* temp = findMin(node->right);
                node->year = temp->year;
                node->eventName = temp->eventName;
                node->right = remove(node->right, temp->year);
            }
            std::cout << "> System: Year " << year << " removed. Timeline stabilized." << std::endl;
        }

        return node;
    }

    TimeCapsule* find(TimeCapsule* node, int year) {
        if (!node) return nullptr;

        if (year < node->year) {
            return find(node->left, year);
        } else if (year > node->year) {
            return find(node->right, year);
        } else {
            return node;
        }
    }

    void inOrderTraversal(TimeCapsule* node) {
        if (node) {
            inOrderTraversal(node->left);
            std::cout << node->year << ": " << node->eventName << std::endl;
            inOrderTraversal(node->right);
        }
    }

    TimeCapsule* findMin(TimeCapsule* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    TimeCapsule* findMax(TimeCapsule* node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }
};

int main() {
    TimeStreamStabilizer stabilizer;

    stabilizer.inject(2050, "Mars Colony Established");
    stabilizer.inject(1969, "Moon Landing");
    stabilizer.inject(2100, "Warp Drive Invented");
    stabilizer.inject(2000, "Y2K Bug");
    stabilizer.search(1969);
    stabilizer.inject(1990, "World Wide Web");
    stabilizer.paradox(2000);
    stabilizer.report();
    stabilizer.search(2000);

    return 0;
}