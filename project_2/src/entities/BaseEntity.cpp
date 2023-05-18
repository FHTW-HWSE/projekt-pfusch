#include "BaseEntity.hpp"
#include "result.hpp"
#include "conversion_helper.hpp"

namespace Entities
{
    BaseEntity::~BaseEntity(){

    }

    uuids::uuid BaseEntity::create_new_uuid()
    {
        std::random_device rd;
        auto seed_data = std::array<int, std::mt19937::state_size> {};
        std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
        std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
        std::mt19937 generator(seq);
        uuids::uuid_random_generator gen{generator};

        return gen();
    }

    int BaseEntity::get_persitable_prop_count(){
        return this->persitable_prop_count;
    }

    std::string BaseEntity::parse_to_csv(){
        return Helper::id_to_string(this->id);
    }
}

