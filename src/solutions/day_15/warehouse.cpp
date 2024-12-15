#include "solutions/day_15/warehouse.h"

#include <algorithm>
#include <cstddef>
#include <queue>
#include <unordered_set>
#include <vector>

#include "utility/vec.h"

namespace aoc
{
    // --------------------------------------------------------------------------------
    // Warehouse box
    // --------------------------------------------------------------------------------

    WarehouseBox::WarehouseBox(const Point& p) :
        positions({ p })
    {
    }

    WarehouseBox::WarehouseBox(const Point& left, const Point& right) :
        positions({ left, right })
    {
    }

    bool WarehouseBox::contains(const Point& p) const
    {
        auto it = std::ranges::find(positions, p);
        return it != positions.end();
    }

    void WarehouseBox::move(const Point& dir)
    {
        for (auto& position : positions)
        {
            position += dir;
        }
    }

    int WarehouseBox::gps() const
    {
        const auto& [x, y] = positions.front();
        return static_cast<int>(y) * 100 + static_cast<int>(x);
    }

    // --------------------------------------------------------------------------------
    // Warehouse
    // --------------------------------------------------------------------------------

    Warehouse::Warehouse(const std::unordered_set<Point>& walls, const std::vector<WarehouseBox>& boxes, const Point& robot) :
        m_walls(walls), m_boxes(boxes), m_robot(robot)
    {
    }

    void Warehouse::move_robot(const Point& dir)
    {
        // Check if the next position is a wall
        if (Point next = m_robot + dir; is_wall_at(next))
        {
            return;
        }

        // Check if the next position is empty
        if (Point next = m_robot + dir; is_empty_at(next))
        {
            m_robot = next;
            return;
        }

        // Next position is a box, so we need to BFS to figure out what to push
        std::unordered_set<WarehouseBox*> connected_boxes;
        bool can_move = true;

        std::queue<Point> to_visit;
        to_visit.push_range(get_box_at(m_robot + dir)->positions);
        std::unordered_set<Point> visited;
        while (!to_visit.empty())
        {
            const Point current = to_visit.front();
            to_visit.pop();

            // Skip iteration if this postion was visited
            if (visited.contains(current))
            {
                continue;
            }

            // Mark this position as visited and get a pointer to the box at this position
            visited.insert(current);
            connected_boxes.insert(get_box_at(current));

            // Get the next position and check if it's a box or wall
            Point next = current + dir;
            if (auto box = get_box_at(next))
            {
                to_visit.push_range(box->positions);
            }
            else if (is_wall_at(next))
            {
                can_move = false;
                break;
            }
        }

        // Move robot and boxes
        if (can_move)
        {
            for (auto& box : connected_boxes)
            {
                box->move(dir);
            }

            m_robot += dir;
        }
    }

    int Warehouse::gps_sum() const
    {
        int sum = 0;
        for (const auto& box : m_boxes)
        {
            sum += box.gps();
        }

        return sum;
    }

    WarehouseBox* const Warehouse::get_box_at(const Point& p)
    {
        for (std::size_t i = 0; i < m_boxes.size(); ++i)
        {
            if (m_boxes[i].contains(p))
            {
                return &m_boxes[i];
            }
        }

        return nullptr;
    }

    const WarehouseBox* const Warehouse::get_box_at(const Point& p) const
    {
        for (std::size_t i = 0; i < m_boxes.size(); ++i)
        {
            if (m_boxes[i].contains(p))
            {
                return &m_boxes[i];
            }
        }

        return nullptr;
    }

    bool Warehouse::is_wall_at(const Point& p) const
    {
        return m_walls.contains(p);
    }

    bool Warehouse::is_box_at(const Point& p) const
    {
        return get_box_at(p);
    }

    bool Warehouse::is_empty_at(const Point& p) const
    {
        return !(is_wall_at(p) || is_box_at(p));
    }

} // aoc
