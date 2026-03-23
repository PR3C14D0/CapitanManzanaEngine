#pragma once

namespace cme {
    class JsonSerializer;

    /// @brief Interfaz que hace que los objetos se vuelvan serializables
    class Serializable {
    public:
        virtual void serialize(cme::JsonSerializer& s) const = 0;
        virtual void deserialize(cme::JsonSerializer& s) = 0;
    };
}