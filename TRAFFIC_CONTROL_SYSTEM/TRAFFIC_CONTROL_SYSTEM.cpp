#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void showTrafficLight(string color) {
    cout << "====================\n";
    cout << "|                  |\n";
    if (color == "RED") {
        cout << "|   RED  |\n";
    }
    else {
        cout << "|   OFF  |\n";
    }
    if (color == "GREEN") {
        cout << "|   GREEN |\n";
    }
    else {
        cout << "|   OFF  |\n";
    }
    cout << "|                  |\n";
    cout << "====================\n";
}

class TrafficSignal {
private:
    int redTime, greenTime;
    queue<string> vehicleQueue;
    bool emergencyDetected;

public:
    TrafficSignal() {
        redTime = 10;
        greenTime = 10;
        emergencyDetected = false;
    }

    void detectVehicles(int numVehicles) {
        for (int i = 0; i < numVehicles; i++) {
            if (rand() % 10 == 0) {
                vehicleQueue.push("Emergency Vehicle");
                emergencyDetected = true;
            }
            else {
                vehicleQueue.push("Car");
            }
        }
    }

    void adjustSignal() {
        int queueSize = vehicleQueue.size();

        if (queueSize > 10) {
            greenTime = 20;
        }
        else if (queueSize > 5) {
            greenTime = 15;
        }
        else {
            greenTime = 10;
        }

        if (emergencyDetected) {
            greenTime += 5;
        }
    }

    void processTraffic() {
        showTrafficLight("GREEN");
        cout << "\nTraffic Light: GREEN for " << greenTime << " seconds\n";
        int count = 0;
        while (!vehicleQueue.empty() && count < greenTime) {
            cout << vehicleQueue.front() << " is passing...\n";
            vehicleQueue.pop();
            count++;
        }

        showTrafficLight("RED");
        cout << "\nTraffic Light: RED for " << redTime << " seconds\n";
        emergencyDetected = false;
    }

    void logTrafficData() {
        ofstream file("traffic_log.txt", ios::app);
        if (file.is_open()) {
            file << "Traffic Light Cycle:\n";
            file << "Vehicles Processed: " << greenTime << "\n";
            file << "Red Time: " << redTime << " seconds\n";
            file << "Green Time: " << greenTime << " seconds\n";
            file << "-----------------------------------\n";
            file.close();
        }
        else {
            cout << "Error logging data!\n";
        }
    }
};

int main() {
    srand(time(0));

    TrafficSignal signal;
    int numCycles;

    cout << "Enter the number of traffic cycles: ";
    cin >> numCycles;

    for (int cycle = 1; cycle <= numCycles; cycle++) {
        cout << "\n===== Traffic Cycle " << cycle << " =====\n";

        int numVehicles = rand() % 15;
        cout << "Detected " << numVehicles << " vehicles in queue.\n";

        signal.detectVehicles(numVehicles);
        signal.adjustSignal();
        signal.processTraffic();
        signal.logTrafficData();

        cout << "============================\n";
    }

    cout << "\nTraffic control simulation completed! Data logged in 'traffic_log.txt'.\n";
    return 0;
}