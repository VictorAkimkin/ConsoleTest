#pragma once
class Proper {
    int field;
    int mass[2][2];
public:
    void set_field(int val) {
        field = val;
    }
    int get_field() {
        return field;
    }
    void set_mass(int row, int col, int val) {
        mass[row][col] = val;
    }
    int get_mass(int row, int col) {
        return mass[row][col];
    }
    __declspec (property (get = get_field, put = set_field)) int field_property;
    __declspec (property (get = get_mass, put = set_mass)) int mass_property[][];
};