#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Simplified Leaky Bucket Algorithm
void leakyBucketCongestionControl(int bucketCapacity, int outputRate, const vector<int>& incomingPackets) {
    int stored = 0;  // Number of packets currently in the bucket
    int dropped = 0; // Total number of dropped packets

    for (int time = 0; time < incomingPackets.size(); ++time) {
        int packets = incomingPackets[time];
        cout << "\nTime " << time + 1 << ":\n";
        cout << "Incoming packets: " << packets << endl;

        // Leak packets according to the output rate
        stored = max(0, stored - outputRate);  // Remove packets from bucket (leak)

        // Check if incoming packets exceed bucket capacity
        if (packets + stored > bucketCapacity) {
            dropped += (packets + stored) - bucketCapacity;  // Drop excess packets
            stored = bucketCapacity;  // Fill bucket to capacity
            cout << "Bucket overflow! Dropped packets: " << (packets + stored - bucketCapacity) << endl;
        } else {
            stored += packets;  // Add incoming packets to bucket
            cout << "No packets dropped.\n";
        }

        // Transmit packets from the bucket at the output rate
        int transmitted = min(stored, outputRate);
        stored -= transmitted;  // Remove transmitted packets
        cout << "Transmitted packets: " << transmitted << endl;
        cout << "Packets left in bucket: " << stored << endl;
    }

    // Continue transmitting any remaining packets after all incoming packets are processed
    while (stored > 0) {
        cout << "\nTime " << incomingPackets.size() + 1 << ":\n";
        int transmitted = min(stored, outputRate);
        stored -= transmitted;
        cout << "Transmitted packets: " << transmitted << endl;
        cout << "Packets left in bucket: " << stored << endl;
    }

    cout << "\nAll packets transmitted successfully." << endl;
    cout << "Total dropped packets: " << dropped << endl;
}

int main() {
    int bucketCapacity, outputRate, n;

    // Input parameters
    cout << "Enter bucket capacity (packets): ";
    cin >> bucketCapacity;

    cout << "Enter output rate (packets/sec): ";
    cin >> outputRate;

    cout << "Enter number of time slots: ";
    cin >> n;

    vector<int> incomingPackets(n);
    for (int i = 0; i < n; ++i) {
        cout << "Packets arriving at time " << i + 1 << ": ";
        cin >> incomingPackets[i];
    }

    // Simulate the congestion control process
    leakyBucketCongestionControl(bucketCapacity, outputRate, incomingPackets);

    return 0;
}
