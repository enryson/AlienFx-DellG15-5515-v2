#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

class PayloadBuilder
{
private:
    std::vector<uint8_t> payload;

public:
    // Construtor
    PayloadBuilder(const uint8_t *initialPayload, size_t size)
    {
        payload.insert(payload.end(), initialPayload, initialPayload + size);
    }

    // Método para adicionar um byte no final do payload
    void pushEnd(uint8_t byte)
    {
        payload.push_back(byte);
    }

    // Método para adicionar um byte no início do payload
    void pushStart(uint8_t byte)
    {
        payload.insert(payload.begin(), byte);
    }

    // Método para retornar o payload completo com o tamanho final de 32
    const uint8_t* getCompletePayload() const
    {
        static uint8_t completePayload[32] = {0}; // Inicializa com 0x00

        size_t copySize = std::min(payload.size(), static_cast<size_t>(32)); // Calcula o tamanho de cópia

        // Copia os bytes do payload atual para o payload completo
        std::copy(payload.begin(), payload.begin() + copySize, completePayload);

        return completePayload;
    }
};