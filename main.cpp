#include <iostream>
#include "stdio.h"
#include "string.h"
#include <set>
#include <queue>

using namespace std;

#define ERROR_COW   -1
#define ERROR_ROW   -2

static const int N = 9;


int row_ar[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col_ar[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

bool valid(int32_t cow, int32_t row)
{
    if (cow < 0 || row < 0 || cow >= N || row >= N)
        return false;

    return true;
}

struct Node
{
    int32_t cow, row, dist;

    bool operator<(const Node& o) const
    {
        return cow < o.cow || (cow == o.cow && row < o.row);
    }
};


int32_t moves_and_find_min_step(Node src, Node dest)
{
    set<Node> visited;

    queue<Node> q;
    q.push(src);

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        int cow = node.cow;
        int row = node.row;
        int dist = node.dist;

        if (cow == dest.cow && row == dest.row)
            return dist;

        if (!visited.count(node))
        {
            visited.insert(node);

            for (int i = 0; i < 8; ++i)
            {
                int cow_temp = cow + row_ar[i];
                int row_temp = row + col_ar[i];

                if (valid(cow_temp, row_temp))
                    q.push({ cow_temp, row_temp, dist + 1 });
            }

        }
    }

    return INT_MAX;
}

int32_t translate_check_pos(string pos, int32_t *row_ptr, int32_t *cow_ptr)
{
        switch (pos[0])
        {
        case *"a":
            *cow_ptr = 1;
            break;
        case *"b":
            *cow_ptr = 2;
            break;
        case *"c":
            *cow_ptr = 3;
            break;
        case *"d":
            *cow_ptr = 4;
            break;
        case *"e":
            *cow_ptr = 5;
            break;
        case *"f":
            *cow_ptr = 6;
            break;
        case *"g":
            *cow_ptr = 7;
            break;
        case *"h":
            *cow_ptr = 8;
            break;
        default:
            return ERROR_COW;
            break;
        }

        switch (pos[1])
        {
        case *"1":
            *row_ptr = 1;
            break;
        case *"2":
            *row_ptr = 2;
            break;
        case *"3":
            *row_ptr = 3;
            break;
        case *"4":
            *row_ptr = 4;
            break;
        case *"5":
            *row_ptr = 5;
            break;
        case *"6":
            *row_ptr = 6;
            break;
        case *"7":
            *row_ptr = 7;
            break;
        case *"8":
            *row_ptr = 8;
            break;
        default:
            return ERROR_ROW;
            break;
        }

        return 1;
}

int32_t knight(std::string pos_1, std::string pos_2)
{
    Node start_pos, dest_pos;
    int32_t ret = 0;
    uint32_t step = 0;

    ret = translate_check_pos(pos_1,&start_pos.row,&start_pos.cow);

    if(ret!=1)
    {
        cout << "The starting position is not set correctly" << endl;
        return ret;
    }

    ret = translate_check_pos(pos_2,&dest_pos.row,&dest_pos.cow);

    if(ret!=1)
    {
        cout << "The destination position is not set correctly" << endl;
        return ret;
    }

    start_pos.dist = 0;
    dest_pos.dist = 0;

    step = moves_and_find_min_step(start_pos,dest_pos);


    return step;
}

int main()
{
    int32_t step_min;
    string pos1,pos2;
    cout << "This is a program for calculating the minimum number of moves of a chess knight" << endl;
    cout << "Enter the starting position and the destination position" << endl;

    while(1)
    {
        cin >> pos1;
        cin >> pos2;
        step_min = knight(pos1,pos2);
        if(step_min>=0)
        {
            cout << "The minimum number of moves of a chess knight - " << step_min << endl;
            cout << "Repeat enter " << endl;
        }
        else
            cout << "Repeat enter " << endl;
    }


    return 0;
}
