#include "pch.h"
#include "BallTree.h"


double BallTree::distanciaMax(Coordinate& c1, Coordinate& cRes, const std::vector<Coordinate>& coordenades)
{
    double max = 0;
    for (auto coords : coordenades)
    {
        double distancia = Util::DistanciaHaversine(c1, coords);
        if (distancia > max)
        {
            max = distancia;
            cRes = coords;
        }
    }
    return max;
}
void BallTree::construirArbreRec(std::vector<Coordinate>& coordenades, BallTree* root)
{
    m_coordenades = coordenades;
    m_root = root;
    if (!coordenades.empty()) m_pivot = Util::calcularPuntCentral(coordenades);
    if (coordenades.size() > 1)
    {
        Coordinate cA;
        Coordinate cB;
        double DA = distanciaMax(m_pivot, cA, coordenades);
        double DB = distanciaMax(cA, cB, coordenades);
        m_radi = DA;

        std::vector<Coordinate> coordEsq, coordDre;
        for (auto c : coordenades)
        {
            double D1 = Util::DistanciaHaversine(cA, c);
            double D2 = Util::DistanciaHaversine(cB, c);
            if (D1 >= D2) coordDre.push_back(c);
            else coordEsq.push_back(c);
        }
        m_left = new BallTree;
        m_right = new BallTree;
        m_left->construirArbreRec(coordEsq, this);
        m_right->construirArbreRec(coordDre, this);
    }
}
void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
    // TODO: Utilitza aquest metode per construir el teu BallTree
    // TODO: amb les coordenades que se us passen per parametre
    std::vector<Coordinate> coord;
    for (const auto c : coordenades)
    {
        if (std::find(coord.begin(), coord.end(), c) == coord.end())
            coord.push_back(c);
    }
    construirArbreRec(coord, this);
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    if (m_left != nullptr)
        m_left->inOrdre(out);
    out.emplace_back(m_coordenades.begin(), m_coordenades.end());
    if (m_right != nullptr)
        m_right->inOrdre(out);
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    out.emplace_back(m_coordenades.begin(), m_coordenades.end());
    if (m_left != nullptr)
        m_left->preOrdre(out);
    if (m_right != nullptr)
        m_right->preOrdre(out);
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    if (m_left != nullptr)
        m_left->postOrdre(out);
    if (m_right != nullptr)
        m_right->postOrdre(out);

    out.emplace_back(m_coordenades.begin(), m_coordenades.end());
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {

    double D1 = Util::DistanciaHaversine(targetQuery, ball->m_pivot);
    double D2 = Util::DistanciaHaversine(Q, ball->m_pivot);

    if (D1 - ball->m_radi >= D2) {
        return Q;
    }

    if (!ball->m_coordenades.empty()) {
        for (const auto& coord : ball->m_coordenades) {
            double distancia = Util::DistanciaHaversine(targetQuery, coord);
            if (distancia < Util::DistanciaHaversine(targetQuery, Q)) {
                Q = coord;
            }
        }
    }

    if (ball->m_left != nullptr) {
        Q = nodeMesProper(targetQuery, Q, ball->m_left);
    }
    if (ball->m_right != nullptr) {
        Q = nodeMesProper(targetQuery, Q, ball->m_right);
    }

    return Q;
}





