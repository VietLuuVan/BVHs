#include "BVHs.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


struct Triangle {
// Define a Triangle
    double x[3];
    double y[3];
    double z[3];

    Triangle(double xData[], double yData[], double zData[]) {
        // Constructor
        for (int i = 0; i < 3; i++) {
            x[i] = xData[i];
            y[i] = yData[i];
            z[i] = zData[i];
        }
    }

    double get_min(double (&data)[3]) {
        // Get minimum value of an array
        double min_value = data[0];
        for (auto i: data) {
            if (min_value >= i) {
                min_value = i;
            }
        }
        return min_value;
    }
    double get_max(double (&data)[3]) {
        // Get maximum value of an array
        double max_value = data[0];
        for (auto i: data) {
            if (max_value <= i) {
                max_value = i;
            }
        }
        return max_value;
    }

    double* get_centroid() {
        // Get the coordinates of the centroid of a rectangle.
        double x_min = get_min(x);
        double y_min = get_min(y);
        double z_min = get_min(z);
        double x_max = get_max(x);
        double y_max = get_max(y);
        double z_max = get_max(z);

        static double centroid[3] = {(double) (x_min+x_max)/2, (double) (y_min+y_max)/2,(double) (z_min+z_max)/2};
        return centroid;
    }
};

struct Box {
// Define the bouding volumn of a rectangle
    double v[8][3];
    double l[12][2];

    Box(double points[8][3], double lines[12][2]) {
    // Constructor
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                v[i][j] = points[i][j];
            }
        }
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 2; j++) {
                l[i][j] = lines[i][j];
            }
        }
    }
};

struct Node {
    // Define a Node
    public:
        vector<Triangle> tri_list;

        double get_x_min() {
        // Get minimum value on x coordinates of all rectangles stored at current node
            Triangle tri = tri_list[0];
            double min_x = tri.get_min(tri.x);
            int size = tri_list.size();
            double temp_min;
            for (int i = 1; i < size; i++) {
                tri = tri_list[i];
                temp_min = tri.get_min(tri.x);
                if (min_x >= temp_min) {
                    min_x = temp_min;
                }
            }
            return min_x;
        }

        double get_y_min() {
         // Get minimum value on y coordinates of all rectangles stored at current node
            Triangle tri = tri_list[0];
            double min_y = tri.get_min(tri.y);
            int size = tri_list.size();
            double temp_min;
            for (int i = 1; i < size; i++) {
                tri = tri_list[i];
                temp_min = tri.get_min(tri.y);
                if (min_y >= temp_min) {
                    min_y = temp_min;
                }
            }
            return min_y;
        }

        double get_z_min() {
         // Get minimum value on z coordinates of all rectangles stored at current node
            Triangle tri = tri_list[0];
            double min_z = tri.get_min(tri.z);
            int size = tri_list.size();
            double temp_min;
            for (int i = 1; i < size; i++) {
                tri = tri_list[i];
                temp_min = tri.get_min(tri.z);
                if (min_z >= temp_min) {
                    min_z = temp_min;
                }
            }
            return min_z;
        }

        double get_x_max() {
         // Get maximum value on x coordinates of all rectangles stored at current node
            Triangle tri = tri_list[0];
            double max_x = tri.get_max(tri.x);
            int size = tri_list.size();
            double temp_max;
            for (int i = 1; i < size; i++) {
                tri = tri_list[i];
                temp_max = tri.get_max(tri.x);
                if (max_x <= temp_max) {
                    max_x = temp_max;
                }
            }
            return max_x;
        }

        double get_y_max() {
         // Get maximum value on y coordinates of all rectangles stored at current node
            Triangle tri = tri_list[0];
            double max_y = tri.get_max(tri.y);
            int size = tri_list.size();
            double temp_max;
            for (int i = 1; i < size; i++) {
                tri = tri_list[i];
                temp_max = tri.get_max(tri.y);
                if (max_y <= temp_max) {
                    max_y = temp_max;
                }
            }
            return max_y;
        }

        double get_z_max() {
         // Get maximum value on z coordinates of all rectangles stored at current node
            Triangle tri = tri_list[0];
            double max_z = tri.get_max(tri.z);
            int size = tri_list.size();
            double temp_max;
            for (int i = 1; i < size; i++) {
                tri = tri_list[i];
                temp_max = tri.get_max(tri.z);
                if (max_z <= temp_max) {
                    max_z = temp_max;
                }
            }
            return max_z;
        }

        double get_x_length() {
        // Get length on x coordinates of all rectangles stored at current node
            return get_x_max() - get_x_min();
        }
        double get_y_length() {
            return get_y_max() - get_y_min();
        }
        double get_z_length() {
            return get_z_max() - get_z_min();
        }

        Box get_box() {
        // Get the bounding box of all rectangles stored at current node
            double x_min = get_x_min();
            double y_min = get_y_min();
            double z_min = get_z_min();
            double x_max = get_x_max();
            double y_max = get_y_max();
            double z_max = get_z_max();

            static double points[8][3] = {
            {x_min,y_min,z_min},
            {x_min,y_max,z_min},
            {x_max,y_min,z_min},
            {x_max,y_max,z_min},
            {x_min,y_min,z_max},
            {x_min,y_max,z_max},
            {x_max,y_min,z_max},
            {x_max,y_max,z_max}
            };
            static double lines[12][2] = {
            {0,1},
            {0,2},
            {2,3},
            {1,3},
            {0,4},
            {1,5},
            {2,6},
            {3,7},
            {4,5},
            {4,6},
            {6,7},
            {5,7}
            };

            Box box(points, lines);
            return box;
        }
};

bool compare_x(Triangle t1, Triangle t2) {
// A method to compare 2 triangle by their x coordinate.
    double* t1_centroid = t1.get_centroid();
    double* t2_centroid = t2.get_centroid();
    return (t1_centroid[0] < t2_centroid[0]);
}
bool compare_y(Triangle t1, Triangle t2) {
// A method to compare 2 triangle by their y coordinate.
    double* t1_centroid = t1.get_centroid();
    double* t2_centroid = t2.get_centroid();
    return (t1_centroid[1] < t2_centroid[1]);
}
bool compare_z(Triangle t1, Triangle t2) {
// A method to compare 2 triangle by their z coordinate.
    double* t1_centroid = t1.get_centroid();
    double* t2_centroid = t2.get_centroid();
    return (t1_centroid[2] < t2_centroid[2]);
}

Node* construct_bvhs(vector<Triangle> rec) {
// A method to construct BVHs tree on a Node, which is the root of current tree.
    int n = rec.size();
    int size = ceil(log2(n));
    n = (int) pow(2,size+1)-1;
    static Node arr[10000000];
    Node root;
    root.tri_list = rec;
    double x_length = root.get_x_length();
    double y_length = root.get_y_length();
    double z_length = root.get_z_length();
    if (x_length >= y_length && x_length >= z_length) {
        sort(root.tri_list.begin(), root.tri_list.end(),compare_x);
    } else if (y_length >= x_length && y_length >= z_length) {
       sort(root.tri_list.begin(), root.tri_list.end(),compare_y);
    } else {
        sort(root.tri_list.begin(), root.tri_list.end(),compare_z);
    }
    arr[1] = root;
    for (int i = 2; i < n+1; i++) {
        if (arr[i/2].tri_list.size() == 1) {
            vector<Triangle> tri;
            Node temp;
            temp.tri_list = tri;
            arr[i] = temp;
            continue;
        }
        int med = arr[i/2].tri_list.size()/2;
        if (i%2==0) {
            vector<Triangle> temp_left;
            for (int j = 0; j < med; j++) {
                temp_left.push_back(arr[i/2].tri_list[j]);
            }
            Node left;
            left.tri_list = temp_left;
            double x_length = left.get_x_length();
            double y_length = left.get_y_length();
            double z_length = left.get_z_length();
            if (x_length >= y_length && x_length >= z_length) {
                sort(left.tri_list.begin(), left.tri_list.end(),compare_x);
            } else if (y_length >= x_length && y_length >= z_length) {
               sort(left.tri_list.begin(), left.tri_list.end(),compare_y);
            } else {
                sort(left.tri_list.begin(), left.tri_list.end(),compare_z);
            }
            arr[i] = left;
        } else {
            vector<Triangle> temp_right;
            for (int j = med; j < (int) arr[i/2].tri_list.size(); j++) {
                temp_right.push_back(arr[i/2].tri_list[j]);
            }
            Node right;
            right.tri_list = temp_right;
            double x_length = right.get_x_length();
            double y_length = right.get_y_length();
            double z_length = right.get_z_length();
            if (x_length >= y_length && x_length >= z_length) {
                sort(right.tri_list.begin(), right.tri_list.end(),compare_x);
            } else if (y_length >= x_length && y_length >= z_length) {
               sort(right.tri_list.begin(), right.tri_list.end(),compare_y);
            } else {
                sort(right.tri_list.begin(), right.tri_list.end(),compare_z);
            }
            arr[i] = right;
        }
    }
    return arr;
}

void create_obj_file(Node* arr, int n) {
// A method to create obj file by writing all vertices and lines of each bounding box.
    ofstream MyFile("result.text");
    for (int i = 1; i < n+1; i++) {
        if (arr[i].tri_list.size() == 0) {
            continue;
        }
        Box box = arr[i].get_box();
        for (int j = 0; j < 8; j++) {
                MyFile << "v ";
                for (int k = 0; k < 3; k++) {
                    MyFile << std::to_string(box.v[j][k])+" ";
                }
                MyFile << "\n";
        }
    }
    for (int i = 1; i < n+1; i++) {
        if (arr[i].tri_list.size() == 0) {
            continue;
        }
        Box box = arr[i].get_box();
        for (int j = 0; j < 12; j++) {
            MyFile << "l ";
            for (int k = 0; k < 2; k++) {
                 MyFile << std::to_string((int) box.l[j][k]+i*8+1)+" ";
            }
            MyFile << "\n";
        }

    }
    MyFile.close();
}

vector<vector<string>> get_vertices() {
// A method to get all vertices of the object.
    ifstream MyReadFile("c:\\Users\\VTO\\Downloads\\Human11.txt");
    string myText;
    vector<vector<string>> ver;
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
      // Output the text from the file
      if (myText.substr(0,2).compare("v ") != 0) {
        continue;
      }
      vector<string> v;
      istringstream ss(myText.substr(2,myText.size() - 2));

        string word;
        while (ss >> word) {
            // print the read word
            v.push_back(word);
        }
        ver.push_back(v);
    }
    MyReadFile.close();
    return ver;
}
vector<Triangle> get_triangle() {
// A method to get all rectangles from their vertices and the faces of a object.
    vector<Triangle> tri_list;
    ifstream MyReadFile("c:\\Users\\VTO\\Downloads\\Human11.txt");
    vector<vector<string>> ver;
    string myText;
    while (getline (MyReadFile, myText)) {
      if (myText.substr(0,2).compare("f ") != 0) {
        continue;
      }
      vector<string> v;
      istringstream ss(myText.substr(2,myText.size() - 2));
        string word;
        while (ss >> word) {
            for (int s = 0; s <(int) word.size(); s++) {
                if (word[s]==('/')) {
                    v.push_back(word.substr(0,s));
                    break;
                }
            }
        }
        ver.push_back(v);
    }
    MyReadFile.close();
    vector<vector<string>> vertices = get_vertices();
    for (int i = 0; i <(int) ver.size(); i++) {
        double x[3] = {stod(vertices[stoi(ver[i][0])-1][0]),
                        stod(vertices[stoi(ver[i][1])-1][0]),
                        stod(vertices[stoi(ver[i][2])-1][0])};

        double y[3] = {stod(vertices[stoi(ver[i][0])-1][1]),
                        stod(vertices[stoi(ver[i][1])-1][1]),
                        stod(vertices[stoi(ver[i][2])-1][1])};

        double z[3] = {stod(vertices[stoi(ver[i][0])-1][2]),
                        stod(vertices[stoi(ver[i][1])-1][2]),
                        stod(vertices[stoi(ver[i][2])-1][2])};
        Triangle tri(x,y,z);
        tri_list.push_back(tri);
    }
    return tri_list;
}
int main() {
    vector<Triangle> tri_list = get_triangle();
    //cout << "test " << test << '\n';
    //cout << "test.left " <<  test->left->tri_list.size() << '\n';
    //root.travel_tree(&root);
    Node* ptr;
    ptr = construct_bvhs(tri_list);
    int n = tri_list.size();
    int size = ceil(log2(n));
    n = (int) pow(2,size+1)-1;
    create_obj_file(ptr, n);
}



