//
// Created by Muaz Moin on 15/03/2024.
//

#include "Triangles.h"
#include "Face.h"

// een hoop vlakken en punten die we meekrijgen
std::pair<std::vector<Face>, std::vector<Vector3D>>
Triangles::split_Faces(const std::vector<Face> &faces, const std::vector<Vector3D> &points, const int &splitAmount) { //dit lijntje is gegenereerd door chatgpt, omdat ik telkens iets fout deed bij het schrijven van de code.


    // 2 neieuwe lege vectoren om punten en vlakken in op te slaan.
    std::vector<Face> split_Faces = faces;
    std::vector<Vector3D> split_Points = points;

    //splitAmount is het aantal keer dat we de driehoek willen splitsen
    for (int i = 0; i < splitAmount; ++i) {

        std::vector<Face> FaceNew;

        for (int j = 0; j < split_Faces.size(); ++j) {
            Face face = split_Faces[j];


            //oorspronkelijke punten van driehoek
            Vector3D A = split_Points[face.point_indexes[0]];
            Vector3D B = split_Points[face.point_indexes[1]];
            Vector3D C = split_Points[face.point_indexes[2]];

            // nieuwe punten die zijn bijgekomen en deze zijn telkens middelpunten van de zijden van de oorspronkelijke driehoek.
            Vector3D D = Vector3D::point((A.x + B.x) / 2,
                                         (A.y + B.y) / 2,
                                         (A.z + B.z) / 2);
            Vector3D E = Vector3D::point((A.x + C.x) / 2,
                                         (A.y + C.y) / 2,
                                         (A.z + C.z) / 2);
            Vector3D F = Vector3D::point((B.x + C.x) / 2,
                                         (B.y + C.y) / 2,
                                         (B.z + C.z) / 2);



            //Er worden 3 nieuwe punten toegevoegd aan vector. Dus drie nieuwe punten en hieruit volgt sat de totale lengte nu 6 is.
            split_Points.push_back(D);
            split_Points.push_back(E);
            split_Points.push_back(F);

            //Indexen van de punten worden opgeslagen in variabelen
            int IndexA = face.point_indexes[0]; //eerste punt van oorspronkelijke driehoek
            int IndexB = face.point_indexes[1]; //tweede punt van oorspronkelijke driehoek
            int IndexC = face.point_indexes[2]; //derde punt van oorspronkelijke driehoek

            //vector betaat nu uit 6 puten.
            int IndexD = split_Points.size() -
                         3; //Index van D. Totale lengte van de vector is 6, maar d wordt als eerste toegevoegd en heeft dus index 3
            int IndexE = split_Points.size() -
                         2; //Index van E. Totale lengte van de vector is 6, maar e wordt als tweede toegevoegd en heeft dus index 4
            int IndexF = split_Points.size() -
                         1; //Index van F. Totale lengte van de vector is 6, maar f wordt als derde toegevoegd en heeft dus index 5


            //Nieuwe vlakken worden toegevoegd aan de vector
            FaceNew.push_back(Face({IndexA, IndexD, IndexE}));
            FaceNew.push_back(Face({IndexB, IndexF, IndexD}));
            FaceNew.push_back(Face({IndexC, IndexE, IndexF}));
        }
        split_Faces = FaceNew;

    }


    return {split_Faces, split_Points};
}

void Triangles::triangulateFigures(Figures3d &figures) {
    std::cout << "De functie triangulateFigures begint." << std::endl;

    for (auto &figure : figures) {
        std::cout << "Nieuwe figuur." << std::endl;

        std::vector<Face> newFaces;
        for (auto &face : figure.faces) {
            if (face.point_indexes.size() <= 3) {
                newFaces.push_back(face);
                continue;
            }
            for (int i = 1; i < static_cast<int>(face.point_indexes.size()) - 1; ++i) {
                newFaces.push_back(Face({face.point_indexes[0], face.point_indexes[i], face.point_indexes[i + 1]}));
            }
        }
        figure.faces = newFaces;
    }

    std::cout << "De functie triangulateFigures eindigt." << std::endl;
    std::cout.flush();
}



