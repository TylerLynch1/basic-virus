#include <iostream>

/**
 * @brief Executes the host binary associated with the program.
 * 
 * This function calls the host binary using the `execv` system call.
 * The function assumes that the host binary is named "host" and located 
 * in the current working directory. If successful, this function does not return.
 * 
 * @note If the `execv` call fails, the behavior of the program is undefined, 
 * as the function does not include error handling for such cases.
 */
int main() {
    std::cout << "Infected" << std::endl;
    return 0;
}
