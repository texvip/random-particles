#include "main.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Command-line arguments error" << std::endl;
        std::exit(-1);
    }

    auto d  = 2;                            // Dimension
    auto n  = std::stoi(argv[1]);           // Number of division (N^D is the number of subsystems)
    auto m  = std::stoi(argv[2]);           // Number of particles
    auto t  = std::stoi(argv[3]);           // Number of trials
    auto dx = 1. / static_cast<double>(n);  // Width and height of subsystem

    std::stringstream filename;

    filename << "params(d=" << std::to_string(d) << ", n=" << std::to_string(n) << ", m=" << std::to_string(m) << ", t=" << std::to_string(t) << ").txt";
    
    std::ofstream out_params(filename.str());

    std::cout << "################################" << std::endl;
    std::cout << "Dimension: " << d << std::endl;
    std::cout << "Number of division: " << n << std::endl;
    std::cout << "Number of particles: " << m << std::endl;
    std::cout << "Number of trials: " << t << std::endl;
    std::cout << "Average number of particles per subsystem: " << static_cast<double>(m) / static_cast<double>(n * n)
              << std::endl;
    std::cout << "################################" << std::endl;

    std::map<int, int> hist_all;

    for (auto c = 0; c < t; ++c) {
        // Counter for subsystems
        std::vector<std::vector<int>> counter(n, std::vector(n, 0));

        // Uniform random number
        std::random_device               rd;
        std::mt19937                     mt(rd());
        std::uniform_real_distribution<> rand(0, 1);
        for (auto i = 0; i < m; ++i) {
            auto x = static_cast<int>(rand(mt) / dx);
            auto y = static_cast<int>(rand(mt) / dx);
            counter[x][y]++;
        }

        // Make histogram
        std::map<int, int> hist;

        for (auto x = 0; x < n; ++x) {
            for (auto y = 0; y < n; ++y) {
                hist[counter[x][y]]++;
            }
        }

        // Merge histogram
        for (auto h : hist) {
            hist_all[h.first] += h.second;
        }
    }

    // Output histogram
    for (auto h : hist_all) {
        std::cout << h.first << ": " << h.second / static_cast<double>(t) << std::endl;
        out_params << h.first << "\t" << h.second / static_cast<double>(t) << std::endl;
    }
    out_params.close();
    return 0;
}