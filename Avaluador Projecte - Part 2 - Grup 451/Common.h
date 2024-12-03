#pragma once

#include "pch.h"

#include <functional>
#include <string>
#include <vector>

typedef std::pair<std::string, std::string> PAIR_ATTR_VALUE;
typedef std::pair<std::string, std::vector<PAIR_ATTR_VALUE>> CHILD_NODE;


struct Coordinate {
    double lat;
    double lon;

    bool operator==(const Coordinate& other) const {
        return lat == other.lat && lon == other.lon;
    }
};

extern "C" typedef struct {
    int i;
    double lat;
    double lon;
    unsigned int color;
    const char* title;
} PoiBridge;

extern "C" typedef struct {
    double* lats;
    double* lons;
    int size;
} WayBridge;

typedef struct {
    std::string id_element;
    std::vector<PAIR_ATTR_VALUE> atributs;
    std::vector<CHILD_NODE> fills;
} XmlElement;


