#include "DbFascade.hpp"
#include "Base.hpp"
#include "TableEntity.hpp"
#include "Query.hpp"
#include "conversion_helper.hpp"

namespace Fascades
{
    template<class T>
    auto DbFascade::fill_vector(std::vector<std::unique_ptr<T>> &tables, std::vector<std::unique_ptr<Entities::BaseEntity>> &items) noexcept -> cpp::result<bool, std::string>
    {
        for (const auto &s : items)
        {
            auto t_ptr = dynamic_cast<T*>(s.get());

            if(t_ptr == nullptr)
            {
                return cpp::fail("Read wrong Entity from DB.");
            }

            auto unique_table = std::make_unique<T>(*t_ptr);
            tables.push_back(std::move(unique_table));
        }

        return true;
    }

#pragma region  TableEntity

    auto DbFascade::create_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::create_table(table);
    }

    auto DbFascade::get_tables_by_x_y(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, const int &x, const int &y) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity table(x, y, 0);

        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_tables_by_x_y(items, table);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_vector(tables, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::get_tables_by_id(std::vector<std::unique_ptr<Entities::TableEntity>> &tables, const uuids::uuid &id) noexcept -> cpp::result<bool, std::string>
    {
        Entities::TableEntity table(0, 0, 0);
        table.id = id;

        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_tables_by_id(items, table);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_vector(tables, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::get_all_tables(std::vector<std::unique_ptr<Entities::TableEntity>> &tables) noexcept -> cpp::result<bool, std::string>
    {
        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_all_tables(items);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_vector(tables, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::update_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::update_table(table);
    }

    auto DbFascade::delete_table(Entities::TableEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::delete_table(table);
    }

#pragma endregion

#pragma region ReservationEntity

    auto DbFascade::create_reservation(Entities::ReservationEntity &table) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::create_reservation(table);
    }

    auto DbFascade::get_reservations_by_x_y(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations, const int &x, const int &y) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity reservation;
        reservation.table.get()->x = x;
        reservation.table.get()->y = y;

        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_reservations_by_x_y(items, reservation);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_vector(reservations, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::get_reservations_by_id(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations, const uuids::uuid &id) noexcept -> cpp::result<bool, std::string>
    {
        Entities::ReservationEntity res;
        res.id = id;

        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_reservations_by_id(items, res);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_vector(reservations, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }

    auto DbFascade::get_all_open_reservations(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations) noexcept -> cpp::result<bool, std::string>
    {
        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        Entities::ReservationEntity res;

        auto query_result = DataBase::Query::read_all_open_reservations(items, res);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_vector(reservations, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;

    }

    auto DbFascade::get_all_reservations(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations) noexcept -> cpp::result<bool, std::string>
    {
        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto query_result = DataBase::Query::read_all_reservations(items);

        if(query_result.has_error()){
            return query_result;
        }

        auto fill_r = fill_vector(reservations, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        return items.size() > 0;
    }


    auto DbFascade::update_reservation(Entities::ReservationEntity &reservation) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::update_reservation(reservation);
    }

    auto DbFascade::delete_reservation(Entities::ReservationEntity &reservation) noexcept -> cpp::result<bool, std::string>
    {
        return DataBase::Query::delete_reservation(reservation);
    }

    auto DbFascade::get_reservations_within_radius_of_reservation(std::vector<std::unique_ptr<Entities::ReservationEntity>> &reservations, const Entities::ReservationEntity &reservation, const int &radius) noexcept -> cpp::result<bool, std::string>
    {
        std::vector<std::unique_ptr<Entities::BaseEntity>> items;

        auto r_res = DataBase::Query::read_all_reservations(items);

        if(r_res.has_error())
        {
            return cpp::fail(r_res.error());
        }

        std::vector<std::unique_ptr<Entities::ReservationEntity>> all_res;

        auto fill_r = fill_vector(all_res, items);

        if(fill_r.has_error())
        {
            return fill_r;
        }

        bool output = false;
        for (auto &res : all_res)
        {
            if
            (
                *res != reservation
                && reservations_intersect(*res, reservation)
                && reservation_within_radius(reservation, *res, radius)
            )
            {
                reservations.push_back(std::move(res));
                output = true;
            }
        }

        return output;
    }

    bool DbFascade::reservations_intersect(const Entities::ReservationEntity &a, const Entities::ReservationEntity &b)
    {
        //make copy
        Entities::ReservationEntity x(a);
        Entities::ReservationEntity y(b);

        time_t t = Helper::get_time_now();

        x.end_time = a.end_time != 0 ? a.end_time : t;
        y.end_time = b.end_time != 0 ? b.end_time : t;

        return
            x.start_time <= y.end_time 
            && x.end_time >= y.start_time;
    }

    bool DbFascade::reservation_within_radius(const Entities::ReservationEntity &middle, const Entities::ReservationEntity &point, const int &radius)
    {
        double middle_x = middle.table.get()->x;
        double middle_y = middle.table.get()->y;

        double point_x = point.table.get()->x;
        double point_y = point.table.get()->y;

        double x = std::abs(middle_x - point_x);
        double y = std::abs(middle_y - point_y);

        double distance = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

        return distance <= radius;
    }



#pragma endregion
}