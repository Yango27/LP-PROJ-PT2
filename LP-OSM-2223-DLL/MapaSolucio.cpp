#include "pch.h"
#include "MapaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "CamiSolucio.h"
#include "PuntDeInteresBotigaSolucio.h"
#include <unordered_map>
#include "Util.h"
#include "GrafSolucio.h"

std::string MapaSolucio::getId(const XmlElement& x)const
{
    for (auto atributs : x.atributs)
        if (atributs.first == "id")
            return atributs.second;
    return "";
}
std::string MapaSolucio::getLat(const XmlElement& x)const
{
    for (auto atributs : x.atributs)
        if (atributs.first == "lat")
            return atributs.second;
    return "";
}
std::string MapaSolucio::getLon(const XmlElement& x) const
{
    for (auto atributs : x.atributs)
        if (atributs.first == "lon")
            return atributs.second;
    return "";
}
void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{
    std::vector<PuntDeInteresBase*>::iterator it;
    for (it = m_puntsDeInteres.begin(); it != m_puntsDeInteres.end(); it++)
    {
        pdis.push_back((*it)->clone());
    }
}
void MapaSolucio::getCamins(std::vector<CamiBase*>& caminsRetornats)
{
    std::vector<CamiBase*>::iterator it;
    for (it = m_camins.begin(); it != m_camins.end(); it++)
    {
        caminsRetornats.push_back((*it)->clone());
    }
}

void MapaSolucio::getAtributName(std::string& name, XmlElement& xElem)
{
    for (int i = 0; i < xElem.fills.size(); i++)
    {
        if (xElem.fills[i].first == "tag")
        {
            std::pair<std::string, std::string> valorTag = Util::kvDeTag(xElem.fills[i].second);
            if (valorTag.first == "name")
            {
                name = valorTag.second;
            }
        }
    }
}
void MapaSolucio::getAtributsRestaurant(std::string& cuisine, std::string& wheelchair, std::string& name, XmlElement& xElem)
{
    for (int i = 0; i < xElem.fills.size(); i++)
    {
        if (xElem.fills[i].first == "tag")
        {
            std::pair<std::string, std::string> valorTag = Util::kvDeTag(xElem.fills[i].second);
            if (valorTag.first == "cuisine") {
                cuisine = valorTag.second;
            }
            else if (valorTag.first == "wheelchair")
            {
                wheelchair = valorTag.second;
            }
            else if (valorTag.first == "name")
            {
                name = valorTag.second;
            }
        }
    }
}

void MapaSolucio::getAtributsBotiga(std::string& shop, std::string& openH, std::string& wheelchair, std::string& name, XmlElement& xElem)
{
    for (int i = 0; i < xElem.fills.size(); i++)
    {
        if (xElem.fills[i].first == "tag")
        {
            std::pair<std::string, std::string> valorTag = Util::kvDeTag(xElem.fills[i].second);
            if (valorTag.first == "shop") {
                shop = valorTag.second;
            }
            else if (valorTag.first == "opening_hours")
            {
                openH = valorTag.second;
            }
            else if (valorTag.first == "wheelchair")
            {
                wheelchair = valorTag.second;
            }
            else if (valorTag.first == "name")
            {
                name = valorTag.second;
            }
        }
    }
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements)
{
    if (!m_puntsDeInteres.empty()) {
        for (auto& pdi : m_puntsDeInteres) {
            delete pdi;
        }
        m_puntsDeInteres.clear();
    }

    if (!m_camins.empty()) {
        for (auto& cami : m_camins) {
            delete cami;
        }
        m_camins.clear();
    }
    std::unordered_map<std::string, std::pair<double, double>> nodes;
    for (auto& element : xmlElements)
    {
        if (element.id_element == "node")
        {
            std::string id = getId(element);
            std::string latString = getLat(element);
            std::string lonString = getLon(element);
            double lat = stod(latString);
            double lon = stod(lonString);
            if (esPuntInteres(element))
            {
                if (esRestaurant(element)) //falta conseguir atributos para rellenar el pdi
                {
                    Coordinate c;
                    c.lat = lat;
                    c.lon = lon;
                    std::string cuisine, wheelchair, name;
                    getAtributsRestaurant(cuisine, wheelchair, name, element);
                    PuntDeInteresBase* punt = new PuntDeInteresRestaurantSolucio(cuisine, wheelchair, c, name);
                    m_puntsDeInteres.push_back(punt);
                }
                else if (esBotiga(element)) //falta conseguir atributos para rellenar el pdi
                {
                    Coordinate c;
                    c.lat = lat;
                    c.lon = lon;
                    std::string shop, openH, wheelchair, name;
                    getAtributsBotiga(shop, openH, wheelchair, name, element);
                    PuntDeInteresBase* punt = new PuntDeInteresBotigaSolucio(shop, openH, wheelchair, c, name);
                    m_puntsDeInteres.push_back(punt);
                }
                else
                {
                    Coordinate c;
                    c.lat = lat;
                    c.lon = lon;
                    std::string name;
                    getAtributName(name, element);
                    PuntDeInteresBase* punt = new PuntDeInteresBase(c, name);
                    m_puntsDeInteres.push_back(punt);
                }
            }
            nodes[id] = std::make_pair(lat, lon);
        }
        else if (esCami(element))
        {
            CamiBase* cami = new CamiSolucio(element, nodes);
            m_camins.push_back(cami);
        }
    }
}

MapaSolucio::~MapaSolucio()
{
    for (auto& pdi : m_puntsDeInteres)
    {
        delete pdi;
        if (!m_puntsDeInteres.empty()) {
            m_puntsDeInteres.erase(m_puntsDeInteres.begin());
        }
    }


    for (auto& cami : m_camins)
    {
        delete cami;
        if (!m_camins.empty()) {
            m_camins.erase(m_camins.begin());
        }
    }
}

bool MapaSolucio::esCami(XmlElement& x) const
{
    if (x.id_element != "way")
        return false;
    for (int i = 0; i < x.fills.size(); i++)
    {
        if (x.fills[i].first == "tag")
        {
            std::pair<std::string, std::string>valorTag = Util::kvDeTag(x.fills[i].second);
            if (valorTag.first == "highway")
                return true;
        }
    }
    return false;
}

bool MapaSolucio::esPuntInteres(XmlElement& x) const
{
    if (x.id_element != "node")
        return false;
    bool name = false, ret = true;
    for (int i = 0; i < x.fills.size(); i++)
    {
        if (x.fills[i].first == "tag")
        {
            std::pair<std::string, std::string>valorTag = Util::kvDeTag(x.fills[i].second);
            if (valorTag.first == "name")
                name = true;
            if (valorTag.first == "highway" || valorTag.first == "public_transport" || valorTag.first == "access" || valorTag.first == "entrance")
                ret = false;
        }
    }
    return (name && ret);
}

bool MapaSolucio::esRestaurant(XmlElement& x) const
{
    for (int i = 0; i < x.fills.size(); i++)
    {
        if (x.fills[i].first == "tag")
        {
            std::pair<std::string, std::string>valorTag = Util::kvDeTag(x.fills[i].second);
            if (valorTag.second == "restaurant")
                return true;
        }
    }
    return false;
}

bool MapaSolucio::esBotiga(XmlElement& x) const
{
    for (int i = 0; i < x.fills.size(); i++)
    {
        if (x.fills[i].first == "tag")
        {
            std::pair<std::string, std::string>valorTag = Util::kvDeTag(x.fills[i].second);
            if (valorTag.first == "shop")
                return true;
        }
    }
    return false;
}

CamiBase* MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a)
{
    std::vector<CamiBase*> caminsRetornats;
    caminsRetornats.clear();
    (*this).getCamins(caminsRetornats);
    GrafSolucio g(caminsRetornats);

    //GrafSolucio g(*this);

    BallTree* ballTree = new BallTree;
    ballTree->construirArbre(g.getNodes());

    BallTree* arrelBallTree = ballTree->getArrel();

    Coordinate desdeCoord = desde->getCoord();
    Coordinate aCoord = a->getCoord();

    Coordinate desdeProperCoord = ballTree->nodeMesProper(desdeCoord, desdeProperCoord, arrelBallTree);
    Coordinate aProperCoord = ballTree->nodeMesProper(aCoord, aProperCoord, arrelBallTree);

    std::stack<Coordinate> cami;
    g.camiMesCurt(desdeProperCoord, aProperCoord, cami);

    std::vector<Coordinate> camiMesCurt;
    while (!cami.empty())
    {
        camiMesCurt.push_back(cami.top());
        cami.pop();
    }

    CamiSolucio* c = new CamiSolucio(camiMesCurt);
    return c;
}