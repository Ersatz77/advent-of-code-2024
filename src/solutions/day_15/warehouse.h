#ifndef AOC_2024_DAY_15_WAREHOUSE_H
#define AOC_2024_DAY_15_WAREHOUSE_H

#include <unordered_set>
#include <vector>

#include "utility/vec.h"

namespace aoc
{
    // --------------------------------------------------------------------------------
    // Robot move direction
    // --------------------------------------------------------------------------------

    struct RobotMoveDirection
    {
        static constexpr Point up = { 0, -1 };
        static constexpr Point down = { 0, 1 };
        static constexpr Point left = { -1, 0 };
        static constexpr Point right = { 1, 0 };
    };

    // --------------------------------------------------------------------------------
    // Warehouse box
    // --------------------------------------------------------------------------------

    class WarehouseBox
    {
    public:
        explicit WarehouseBox(const Point& p);
        WarehouseBox(const Point& left, const Point& right);

        bool contains(const Point& p) const;
        void move(const Point& dir);

        int gps() const;

        std::vector<Point> positions;
    };

    // --------------------------------------------------------------------------------
    // Warehouse
    // --------------------------------------------------------------------------------

    class Warehouse
    {
    public:
        Warehouse(const std::unordered_set<Point>& walls, const std::vector<WarehouseBox>& boxes, const Point& robot);

        void move_robot(const Point& p);
        int gps_sum() const;

    private:
        WarehouseBox* const get_box_at(const Point& p);
        const WarehouseBox* const  get_box_at(const Point& p) const;

        bool is_wall_at(const Point& p) const;
        bool is_box_at(const Point& p) const;
        bool is_empty_at(const Point& p) const;

        std::unordered_set<Point> m_walls;
        std::vector<WarehouseBox> m_boxes;
        Point m_robot;
    };

} // aoc

#endif // !AOC_2024_DAY_15_WAREHOUSE_H
