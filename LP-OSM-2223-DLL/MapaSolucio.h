#pragma once
#include "MapaBase.h"
#include "BallTree.h"

class MapaSolucio : public MapaBase
{
public:
    MapaSolucio() {}
    void getPdis(std::vector<PuntDeInteresBase*>& pdis) override;
    void getCamins(std::vector<CamiBase*>& caminsRetornats) override;
    void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;
    CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) override;
    ~MapaSolucio();
private:
    bool esPuntInteres( XmlElement& x) const;
    bool esRestaurant( XmlElement& x) const;
    bool esBotiga( XmlElement& x) const;
    bool esCami(XmlElement& x) const;
    void getAtributsRestaurant(std::string& cuisine, std::string& wheelchair, std::string& name, XmlElement& xElem);
    void getAtributsBotiga(std::string& shop, std::string& openH, std::string& wheelchair, std::string& name, XmlElement& xElem);
    void getAtributName(std::string& name, XmlElement& xElem);
    std::string getId(const XmlElement& x) const;
    std::string getLat(const XmlElement& x)const;
    std::string getLon(const XmlElement& x) const;
    std::vector<PuntDeInteresBase*> m_puntsDeInteres;
    std::vector<CamiBase*> m_camins;
};
