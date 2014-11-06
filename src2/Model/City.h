//
//  City.h
//  VoltaOSX
//
//  Created by X S.G. on 10/7/14.
//  Copyright (c) 2014 Fellowship of the Game. All rights reserved.
//

#ifndef __CITY_H__
#define __CITY_H__

class City
{
protected:
    int x;
    int y;

public:
    City();
    ~City();
    virtual void activate() = 0;
};


#endif
