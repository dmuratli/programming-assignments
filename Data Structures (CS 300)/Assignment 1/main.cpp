#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "strutils.h"

using namespace std;

struct city{ //Defines a city node
    string cityName;

    city *NW;
    city *NE;
    city *SW;
    city *SE;

    int x;
    int y;

    city(): cityName(""), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr), x(-1), y(-1){}
    city(string cname, int xcoord, int ycoord): NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr){
        cityName = cname;
        x = xcoord;
        y = ycoord;
    }
};

void insert(city &newCity, city *&root){ //Inserts a new node to the tree
    if (newCity.x < root->x){
        if (newCity.y < root->y){
            if (root->SW == nullptr){
                root->SW = &newCity;
            }else{
                insert(newCity, root->SW);
            }
        }else{
            if (root->NW == nullptr){
                root->NW = &newCity;
            }else{
                insert(newCity, root->NW);
            }
        }
    }else{
        if (newCity.y < root->y){
            if (root->SE == nullptr){
                root->SE = &newCity;
            }else{
                insert(newCity, root->SE);
            }
        }else{
            if (root->NE == nullptr){
                root->NE = &newCity;
            }else{
                insert(newCity, root->NE);
            }
        }
    }
}

void search(const int &xcoord, const int &ycoord, const int &radius, city *&root, vector<string> &inCircle, vector<string> &visited){ //Searches the quadtree for points in a circular region around the point of query
    int circleEqnP2 = radius*radius;
    if (root != nullptr){
        int circleEqnP1 = (root->x - xcoord)*(root->x - xcoord) + (root->y - ycoord)*(root->y - ycoord); 
        //Case numbering is based on a model I designed
        if (circleEqnP1 > circleEqnP2){
            visited.push_back(root->cityName);
            if ((root->x < (xcoord + radius) && root->x > (xcoord - radius)) && root->y >= (ycoord + radius)){ //Case 2: The point is to the [strictly] north of the circle.
                if (root->y == (ycoord + radius) && root->x > xcoord){ //Corner Case 9: The point is on the inner, upper right edge of the rectangle (top edge).
                    search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                    search(xcoord, ycoord, radius, root->NE, inCircle, visited);
                    search(xcoord, ycoord, radius, root->NW, inCircle, visited);
                }else if (root->y == (ycoord + radius) && root->x < xcoord){ //Corner Case 10: The point is on the inner, upper left edge of the rectangle (top edge).
                    search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                    search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                    search(xcoord, ycoord, radius, root->NE, inCircle, visited);
                }else{
                    search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                    search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                }
            }else if ((root->x < (xcoord + radius) && root->x > (xcoord - radius)) && root->y <= (ycoord - radius)){ //Case 3: The point is to the [strictly] south of the circle.
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }else if (root->x <= (xcoord - radius) && (root->y < (ycoord + radius) && root->y > (ycoord - radius))){ //Case 4: The point is to the [strictly] west of the circle.
                search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
            }else if (root->x >= (xcoord + radius) && (root->y < (ycoord + radius) && root->y > (ycoord - radius))){ //Case 5: The point is to the [strictly] east of the circle.
                if (root->x == (xcoord + radius) && root->y < ycoord){ //Corner Case 7: The point is at the inner, lower right edge of the rectangle (side edge).
                    search(xcoord, ycoord, radius, root->NE, inCircle, visited);
                    search(xcoord, ycoord, radius, root->NW, inCircle, visited);
                }else if (root->x == (xcoord + radius) && root->y > ycoord){ //Corner Case 8: The point is at the inner, upper right edge of the rectangle (side edge).
                    search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                    search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                    search(xcoord, ycoord, radius, root->NW, inCircle, visited);
                }else{
                    search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                    search(xcoord, ycoord, radius, root->NW, inCircle, visited);
                }
            }else if (root->x >= (xcoord + radius) && root->y > (ycoord + radius)){ //Case 6: The point is to the [strictly] northeast of the circle.
                if (root->x == (xcoord + radius)){ //Corner Case 19: The point is on the outer, upper right edge of the rectangle (side edge).
                    search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                    search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                }else{
                    search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                }
            }else if (root->x <= (xcoord - radius) && root->y > (ycoord + radius)){ //Case 7: The point is to the [strictly] northwest of the circle.
                search(xcoord, ycoord, radius, root->SE, inCircle, visited);
            }else if (root->x <= (xcoord - radius) && root->y < (ycoord - radius)){ //Case 8: The point is to the [strictly] southwest of the circle.
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
            }else if (root->x >= (xcoord + radius) && root->y < (ycoord - radius)){ //Case 9: The point is to the [strictly] southeast of the circle.
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }else if (root->x == (xcoord - radius) && root->y == (ycoord + radius)){ //Corner Case 1: The point is at the upper left corner of the rectangle.
                search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
            }else if (root->x == (xcoord + radius) && root->y == (ycoord + radius)){ //Corner Case 2: The point is at the upper right corner of the rectangle.
                search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }else if (root->x == (xcoord - radius) && root->y == (ycoord - radius)){ //Corner Case 3: The point is at the lower left corner of the rectangle.   
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
            }else if (root->x == (xcoord + radius) && root->y == (ycoord - radius)){ //Corner Case 4: The point is at the lower right corner of the rectangle.
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }else if (root->x < (xcoord - radius) && root->y == (ycoord + radius)){ //Corner Case 13: The point is on the outer, upper left edge of the rectangle (top edge).
                search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
            }else if (root->x < (xcoord - radius) && root->y == (ycoord - radius)){ //Corner Case 14: The point is on the outer, lower left edge of the rectangle (bottom edge).
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
            }else if (root->x == (xcoord + radius) && root->y < (ycoord - radius)){ //Corner Case 16: The point is on the outer, lower right edge of the rectangle (side edge).
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }else if (root->x > (xcoord + radius) && root->y == (ycoord - radius)){ //Corner Case 17: The point is on the outer, lower right edge of the rectangle (bottom edge).
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }else if (root->x > (xcoord + radius) && root->y == (ycoord + radius)){ //Corner Case 18: The point is on the outer, upper right edge of the rectangle (top edge).
                search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }else{
                search(xcoord, ycoord, radius, root->SE, inCircle, visited);
                search(xcoord, ycoord, radius, root->SW, inCircle, visited);
                search(xcoord, ycoord, radius, root->NE, inCircle, visited);
                search(xcoord, ycoord, radius, root->NW, inCircle, visited);
            }
        }else{ //Case 1: The point is within the circle.
            inCircle.push_back(root->cityName);
            visited.push_back(root->cityName);
            search(xcoord, ycoord, radius, root->SE, inCircle, visited);
            search(xcoord, ycoord, radius, root->SW, inCircle, visited);
            search(xcoord, ycoord, radius, root->NE, inCircle, visited);
            search(xcoord, ycoord, radius, root->NW, inCircle, visited);
        }
    }else{
        ;
    }
}

void pretty_print(city *&root){ //Prints the quadtree
    if (root != nullptr){
        cout << root->cityName << endl; //For checks: cout << root->cityName << " " << root->x << " " << root->y << endl;
        pretty_print(root->SE);
        pretty_print(root->SW);
        pretty_print(root->NE);
        pretty_print(root->NW);
    }else{
        ;
    }
}

void quadtreeBuilder(const string &fileName, int &upperRightX, int &upperRightY, city *&root){ //Builds a quadtree based on the text file
    string a, b, c;
    ifstream cityFile(fileName.c_str());

    //First line
    cityFile >> a >> b;
    upperRightX = atoi(a);
    upperRightY = atoi(b);

    //Remaining lines
    while (cityFile >> a >> b >> c){
        if (root == nullptr){
            city *cityNode = new city(a, atoi(b), atoi(c));
            root = cityNode;
        }else{
            city *cityNode = new city(a, atoi(b), atoi(c));
            insert(*cityNode, root);
        }
    }
    cityFile.close();
}

void queryProcessor(const string &fileName, city *&root){ //Processes queries in the text file
    string a, b, c;
    ifstream queryFile(fileName.c_str());
    
    while (queryFile >> a >> b >> c){
        vector<string> citiesInCircle, visitedCities;
        search(atoi(a), atoi(b), atoi(c), root, citiesInCircle, visitedCities);

        //Prints the query results
        if (citiesInCircle.empty() == true){
            cout << "<None>" << endl;
        }else{
            for (int i = 0; i < citiesInCircle.size(); i++){
                string cname = citiesInCircle.at(i);
                
                if (i != citiesInCircle.size() - 1){
                    cout << cname << ", ";
                }else{
                    cout << cname << endl;
                }
            } 
        }

        //Prints the visited nodes
        for (int i = 0; i < visitedCities.size(); i++){
            string cname = visitedCities.at(i);

            if (i != visitedCities.size() - 1){
                cout << cname << ", ";
            }else{
                cout << cname << endl;
            }
        }
        
        cout << endl;
    }
    queryFile.close();
}

int main(){ //Executes the program as described in the guide PDF
    city *root = nullptr;
    int lowerLeftX = 0, lowerLeftY = 0;
    int upperRightX, upperRightY;

    quadtreeBuilder("cities.txt", upperRightX, upperRightY, root);

    pretty_print(root);
    cout << endl;
    
    queryProcessor("queries0.txt", root);

    return 0;
}