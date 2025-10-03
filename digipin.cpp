#include "digipin.h"
// Implement your code here

using namespace std;

// SOME HELPER FUNCTIONS DECLATIONS, WHICH MAY HELP YOU IMPLEMENT THE TASK

// Digipin symbols grid
array<array<char, 4>, 4> GRID = {{{'F', 'C', '9', '8'},
                                  {'J', '3', '2', '7'},
                                  {'K', '4', '5', '6'},
                                  {'L', 'M', 'P', 'T'}}};

// function to get the grid index corresponding to a Digipin symbols
pair<int, int> symbolToRC(char s)
{
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            if (GRID[r][c] == s)
                return {r, c};
    return {0, 0};
}

void applyGridlineRules(double &lat, double &lon,
                        double latMin, double latMax,
                        double lonMin, double lonMax)
{
    // To handle coordinates coinciding with DIGIPIN Grid Lines
    // shift by 1e-12 in the correct direction according to the specification;
    if(lat == latMax) lat -= 1e-12;
    else if(lat == latMin) lat += 1e-12;
    if(lon == lonMax) lon -= 1e-12;
    else if(lon == lonMin) lon += 1e-12;
    double latgap = (latMax - latMin)/4;
    double dumlatMin = latMin;
    for(int i=1; i<4; i++){
        dumlatMin += latgap;
        if(lat==dumlatMin){
            lat +=1e-12;
            break;
        }
    }
    double longap = (lonMax - lonMin)/4;
    double dumlonMin = lonMin;
    for(int i=1; i<4; i++){
        dumlonMin += longap;
        if(lon==dumlonMin){
            lon +=1e-12;
            break;
        }
    }
}

// TASK IS TO IMPLEMENT THE FOLLOWING TWO FUNCTIONS

string Digipin::encode(double lat, double lon)
{
    // Implement to get Digipin from latitude and longitude values
    double latMax = LAT_MAX;
    double latMin = LAT_MIN;
    double lonMax = LON_MAX;
    double lonMin = LON_MIN;
    string ans="";
    if(lat>LAT_MAX || lat<LAT_MIN || lon>LON_MAX || lon<LON_MIN) return "-1"; 
    for(int _=0; _<10;_++){
        int row = 0, col =0;
        applyGridlineRules(lat,lon,latMin,latMax,lonMin,lonMax);
        double latgap = (latMax - latMin)/4;
        double dumlatMin = latMin;
        for(int i=0; i<4; i++){
            dumlatMin += latgap;
            if(lat<dumlatMin){
                row = 3-i;
                break;
            }
        }
        latMax = dumlatMin;
        latMin = dumlatMin - latgap;
        double longap = (lonMax - lonMin)/4;
        double dumlonMin = lonMin;
        for(int i=0; i<4; i++){
            dumlonMin += longap;
            if(lon<dumlonMin){
                col = i;
                break;
            }
        }
        lonMax = dumlonMin;
        lonMin = dumlonMin - longap;
        ans+=GRID[row][col];
    }
    return ans;
}

pair<double, double> Digipin::decode(string &code)
{
    // Implement to get the center of the bounding box
    if(code.length()!=10) return { -1, -1 };
    double latCenter = 0;
    double lonCenter = 0;
    double latMin = LAT_MIN;
    double latMax = LAT_MAX;
    double lonMin = LON_MIN;
    double lonMax = LON_MAX;
    for (int i = 0; i < 10; i++)
    {
        int row,col;
        row= 3 - symbolToRC(code[i]).first;
        col = symbolToRC(code[i]).second;
        double latgap = (latMax - latMin)/4;
        latMin += row*latgap;
        latMax = latMin + latgap;
        double longap = (lonMax - lonMin)/4;
        lonMin += col*longap;
        lonMax = lonMin + longap;
    }
    latCenter = (latMax + latMin)/2;
    lonCenter = (lonMax + lonMin)/2;
    return {latCenter, lonCenter}; // Return center of the cell
}
