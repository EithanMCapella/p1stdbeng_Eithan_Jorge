#include "PartGenerator.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <string>

namespace bufman {
    namespace {

        // Materials cycle by part id
        constexpr std::array<const char*, 12> kMaterials = {
            "steel", "brass", "aluminum", "copper",
            "gold", "silver", "iron", "wood",
            "titanium", "plastic", "rubber", "nylon"
        };

        constexpr std::array<PartColor, 6> kColors = {
            PART_COLOR_WHITE, PART_COLOR_BLACK, PART_COLOR_RED,
            PART_COLOR_GREEN, PART_COLOR_YELLOW, PART_COLOR_BLUE
        };

    }

    /* Generation isn't random, generate based on id, so we always get the same parts generated
     * helps with testing and reproducibility of results.
     */

    std::vector<Part> generate_parts(std::size_t count, int first_part_id) {
        std::vector<Part> parts;
        parts.reserve(count);

        for (std::size_t i = 0; i < count; ++i) {
            Part part{};
            part.part_id = first_part_id + static_cast<int>(i);


            /* Unsigned so % can never produce a negative remainder, avoids undefined behavior
            * Kinda unnecessary but makes the code robust to bad inputs
            * We could just use part.part_id directly given that when we generate them
            * IDs are positive.
            */
            const auto key = static_cast<unsigned>(part.part_id);

            const std::string name = "PT" + std::to_string(part.part_id);
            name.copy(part.part_name, std::min(name.size(), sizeof(part.part_name) - 1));

            // Multiples of 1/8 and 1/4, cleaner print out
            part.part_weight = 0.125f * static_cast<float>(1 + key % 40);  // 0.125 .. 5.0
            part.part_price  = 0.25f  * static_cast<float>(1 + key % 200); // 0.25 .. 50.0

            part.part_color = kColors[key % kColors.size()];

            const char* material = kMaterials[key % kMaterials.size()];
            std::memcpy(part.part_material, material,
                        std::min(std::strlen(material), sizeof(part.part_material) - 1));

            parts.push_back(part);
        }
        return parts;
    }

}