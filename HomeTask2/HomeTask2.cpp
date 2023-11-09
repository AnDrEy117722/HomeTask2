#include <iostream>
#include <string>
#include "DoubleLinkedList.h"

using namespace std;

template <typename Type>
bool Comparator(Type a, Type b) {

    if (a >= b)
        return false;
    else
        return true;

}

class car {

    string Model;
    string year;
    int old;

public:
    int getOld() { return old; }
    string getModel() { return Model; }
    string getYear() { return year; }
    car(string model, string year, int old) : Model(model), year(year), old(old) {}
    car() : Model(""), year(""), old(0) {}
    bool operator > (const car& rhs) const {

        if (old > rhs.old)
            return true;
        else
            return false;

    }
    bool operator >= (const car& rhs) const {

        if (old >= rhs.old)
            return true;
        else
            return false;

    }
    bool operator < (const car& rhs) const {

        if (old < rhs.old)
            return true;
        else
            return false;

    }
    bool operator <= (const car& rhs) const {

        if (old <= rhs.old)
            return true;
        else
            return false;

    }
    bool operator == (const car& rhs) const {

        if (Model == rhs.Model && year == rhs.year && old == rhs.old)
            return true;
        else
            return false;

    }
    bool operator != (const car& rhs) const {

        if (Model != rhs.Model && year != rhs.year && old != rhs.old)
            return true;
        else
            return false;

    }

};
bool comparator_cars(car a, car b) {

    int year_a = stoi(a.getYear());
    int year_b = stoi(b.getYear());
    if (year_a >= year_b)
        return true;
    else
        return false;

}
ostream& operator << (ostream& stream, car& a)
{
    stream << "{Model: " << a.getModel() << " " << "year: " << a.getYear() << " " << "old: " << a.getOld() << "}" << endl;
    return stream;
}

int main()
{

    DoubleLinkedList<int> list;

    for (int i = 1; i <= 10; i++) {

        list.addFirst(i);

    }

    list.printList();

    list.addLast(11);
    list.printList();

    list.addInPosition(5, 6);
    list.printList();

    list.addAfterElement(3, 100);
    list.printList();

    list.remove(9);
    list.remove(1);
    list.printList();

    cout << endl;
    list.move(11, 10);
    list.printList();
    list.printListReverse();

    cout << endl;
    list.sort(Comparator);
    list.printList();
    list.printListReverse();

    DoubleLinkedList<car> list_car;

    car car1{"Mazda", "2015", 7};
    car car2{ "Toyota", "2003", 20 };
    car car3{ "Chevrolet", "2008", 15 };
    car car4{ "Jeep", "1993", 30 };
    car car5{ "Kia", "2003", 20 };

    list_car.addFirst(car1);
    list_car.addFirst(car2);
    list_car.addFirst(car3);
    list_car.addFirst(car4);
    list_car.addFirst(car5);

    list_car.printList();

    car car6{ "Honda", "2008", 15 };
    list_car.addLast(car6);
    list_car.printList();

    car car7{ "UAZ", "2010", 13 };
    list_car.addInPosition(car7, 3);
    list_car.printList();

    list_car.addAfterElement(car4, car2);
    list_car.printList();

    list_car.remove(car5);
    list_car.remove(car1);
    list_car.printList();

    cout << endl;
    list_car.move(car4, car3);
    list_car.printList();

    cout << endl;
    list_car.sort();
    list_car.printList();

    cout << endl;
    list_car.sort(comparator_cars);
    list_car.printList();
    //return 0;

}
