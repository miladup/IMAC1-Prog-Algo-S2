#include <iostream>
#include <string>

// QUESTION 1

size_t folding_string_hash(std::string const& s, size_t max) {
    size_t hash {0}; 
    for(size_t i {0}; i < s.size(); ++i) {
        hash += s[i];
        hash %= max;
    }

    return hash;
}

// QUESTION 2

size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t hash {0}; 
    for(size_t i {0}; i < s.size(); ++i) {
        hash += s[i] * (i + 1);
        hash %= max;
    }

    return hash;
}

int main () {
    std::string str {};
    std::cout << "Entrez une chaine de caracteres : ";
    
    // espaces
    std::getline(std::cin, str); 

    // stocker et afficher les hash
    size_t h1 = folding_string_hash(str, 100);
    size_t h2 = folding_string_ordered_hash(str, 100);

    std::cout << "Hash exo 1 : " << h1 << std::endl;
    std::cout << "Hash exo 2 : " << h2 << std::endl;

    return 0;
}