//
// Created by Suhrudh Reddy on 11/15/19.
//

#ifndef ADS_BUILDING_H
#define ADS_BUILDING_H
class Building
{
public:
    int building_num,exec_time,total_time;

    Building(int x, int y, int z)
    {
        building_num = x;
        exec_time = y;
        total_time = z;
    }
};


#endif //ADS_BUILDING_H