#include <iostream>
#include <cstdint>
#include <vector>

class PayloadAgregation {
private:
    std::vector<const uint8_t*> payloads;
    std::vector<int> payload_sizes;

public:
    // Método para adicionar um payload
    void addPayload(const uint8_t* payload) {
        payloads.push_back(payload);
        payload_sizes.push_back(32);
    }

    // Método para obter um payload por índice
    const uint8_t* getPayload(int index) const {
        if (index < 0 || index >= payloads.size()) {
            throw std::out_of_range("Índice fora do intervalo");
        }
        return payloads[index];
    }

    // Método para obter o tamanho de um payload por índice
    int getPayloadSize(int index) const {
        if (index < 0 || index >= payload_sizes.size()) {
            throw std::out_of_range("Índice fora do intervalo");
        }
        return payload_sizes[index];
    }

    // Método para obter o número de payloads
    int getNumPayloads() const {
        return payloads.size();
    }

    // Método para exibir os payloads
    void displayPayloads() const {
        for (int i = 0; i < payloads.size(); ++i) {
            std::cout << "Payload " << i << ": ";
            for (int j = 0; j < payload_sizes[i]; ++j) {
                std::cout << std::hex << static_cast<int>(payloads[i][j]) << " ";
            }
            std::cout << std::dec << std::endl; // Voltar para decimal
        }
    }
};
