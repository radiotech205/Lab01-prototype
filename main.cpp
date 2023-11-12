/*Создать набор классов моделирующих графические элементы
на плоскости (Point, Line, Circle) и абстрактный класс
графических элементов (GraphObject). Реализовать прототипирование.*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class GraphObject;
vector<GraphObject*> graphObjectArr;

class Coords
{
public:
    int x, y;
};

class GraphObject
{
public:
    virtual GraphObject* Clone() = 0;
    virtual string ToString() = 0;
};

class Point : public GraphObject
{
protected:
    Coords coords;
public:
    Point(Coords& coords_) {this->coords = coords_;}
    Point* Clone() {return new Point(coords);}
    string ToString()
    {
        string str;
        str.append("Point (");
        str += to_string(this->coords.x);
        str +="; ";
        str += to_string(this->coords.y);
        str +=")\n";
        return str;
    }
};

class Line : public Point
{
protected:
    Coords coordsEnd;
public:
    Line(Coords& begin, Coords& end) : Point(begin), coordsEnd(end) {}
    Line* Clone() {return new Line(this->coords, this->coordsEnd);}
    string ToString()
    {
        string str;
        str.append("Line (");
        str += to_string(this->coords.x);
        str +="; ";
        str += to_string(this->coords.y);
        str +="), ";

        str.append("(");
        str += to_string(this->coordsEnd.x);
        str +="; ";
        str += to_string(this->coordsEnd.y);
        str +=")\n";
        return str;
    }
};

class Circle : public Point
{
protected:
    int radius;
public:
    Circle(Coords& center_, int radius_) : Point(center_), radius(radius_) {}
    Circle* Clone() {return new Circle(this->coords, this->radius);}
    string ToString()
    {
        string str;
        str.append("Circle (");
        str += to_string(this->coords.x);
        str +="; ";
        str += to_string(this->coords.y);
        str +="), radius =  ";
        str += to_string(this->radius);
        str +="\n";
        return str;
    }
};
/*Создать класс графической сцены (Scene), как множества
разнотипных графических объектов. Сделать сцену одиночкой.*/
class Singleton1
{
private:
    Singleton1(vector<GraphObject*> graphObject_) : graphObject(graphObject_)
    {cout << "Singleton1 created" << endl;}
    static Singleton1* singleton1;
    vector<GraphObject*> graphObject;
public:
    static Singleton1* GetInstance(vector<GraphObject*> graphObject_)
    {
        if(singleton1 == nullptr)
            singleton1 = new Singleton1(graphObject_);
        return singleton1;
    }
    vector<GraphObject*> GetData() {return graphObject;}
    void SetData(vector<GraphObject*> graphObject_) {this->graphObject = graphObject_;}
};
Singleton1* Singleton1::singleton1 = nullptr;
/*Обеспечить автоматическое добавление графических
объектов в сцену (через hook’и фабричных методов)*/
class Factory
{
public:
    virtual GraphObject* CreateObject(Coords& coords) = 0;
    void HookFunction(GraphObject* go) {graphObjectArr.push_back(go);}
};
class FactoryPoint : public Factory
{
public:
    GraphObject* CreateObject(Coords& coords)
    {
        GraphObject* go = new Point(coords);
        HookFunction(go);
        return go;
    }
};

class FactoryLine : public Factory
{
public:
    GraphObject* CreateObject(Coords& coords)
    {
        GraphObject* go = new Line(coords, coords);
        HookFunction(go);
        return go;
    }
};

class FactoryCircle : public Factory
{
public:
    GraphObject* CreateObject(Coords& coords)
    {
        GraphObject* go = new Circle(coords, 0);
        HookFunction(go);
        return go;
    }
};

/*Реализовать создание объектов через абстрактную фабрику.
Сделать отдельно фабрику для создания цветной и черно-
белой сцены*/
class PointColor : public GraphObject
{
protected:
    Coords coords;
    string color;
public:
    PointColor(Coords& coords_, string color_)
    {
        this->coords = coords_;
        this->color = color_;
    }
    PointColor* Clone() {return new PointColor(coords, color);}
    string ToString()
    {
        string str;
        str.append("Point (");
        str += to_string(this->coords.x);
        str +="; ";
        str += to_string(this->coords.y);
        str +=") ,color: ";

        str.append(color);
        str +="\n";
        return str;
    }
};

class LineColor : public Point
{
protected:
    Coords coordsEnd;
    string color;
public:
    LineColor(Coords& begin, Coords& end, string color_)
        : Point(begin), coordsEnd(end), color(color_){}
    LineColor* Clone() {return new LineColor(this->coords, this->coordsEnd, this->color);}
    string ToString()
    {
        string str;
        str.append("Line (");
        str += to_string(this->coords.x);
        str +="; ";
        str += to_string(this->coords.y);
        str +="), ";

        str.append("(");
        str += to_string(this->coordsEnd.x);
        str +="; ";
        str += to_string(this->coordsEnd.y);
        str +="), color: ";

        str.append(color);
        str +="\n";
        return str;
    }
};

class CircleColor : public Point
{
protected:
    int radius;
    string color;
public:
    CircleColor(Coords& center_, int radius_, string color_)
        : Point(center_), radius(radius_), color(color_) {}
    CircleColor* Clone() {return new CircleColor(this->coords, this->radius, this->color);}
    string ToString()
    {
        string str;
        str.append("Circle (");
        str += to_string(this->coords.x);
        str +="; ";
        str += to_string(this->coords.y);
        str +="), radius =  ";
        str += to_string(this->radius);
        str +=", color: ";

        str.append(color);
        str +="\n";
        return str;
    }
};
class AbstractFactory
{
public:
    virtual Point* CreatePoint(Coords& coords_) = 0;
    virtual Line* CreateLine(Coords& begin, Coords& end) = 0;
    virtual Circle* CreateCircle(Coords& center_, int radius_) = 0;

    virtual PointColor* CreatePointColor(Coords& coords_, string color_) = 0;
    virtual LineColor* CreateLineColor(Coords& begin, Coords& end, string color_) = 0;
    virtual CircleColor* CreateCircleColor(Coords& center_, int radius_, string color_) = 0;
};

class AbstractFactoryGrey : public AbstractFactory
{
    Point* CreatePoint(Coords& coords_)
    {
        return new Point(coords_);
    }
    Line* CreateLine(Coords& begin, Coords& end)
    {
        return new Line(begin, end);
    }
    Circle* CreateCircle(Coords& center_, int radius_)
    {
        return new Circle(center_, radius_);
    }
    PointColor* CreatePointColor(Coords& coords_, string color_) {return nullptr;}
    LineColor* CreateLineColor(Coords& begin, Coords& end, string color_) {return nullptr;}
    CircleColor* CreateCircleColor(Coords& center_, int radius_, string color_) {return nullptr;}
};

class AbstractFactoryColor : public AbstractFactory
{
    Point* CreatePoint(Coords& coords_) {return nullptr;}
    Line* CreateLine(Coords& begin, Coords& end) {return nullptr;}
    Circle* CreateCircle(Coords& center_, int radius_) {return nullptr;}

    PointColor* CreatePointColor(Coords& coords_, string color_)
    {
        return new PointColor(coords_, color_);
    }
    LineColor* CreateLineColor(Coords& begin, Coords& end, string color_)
    {
        return new LineColor(begin, end, color_);
    }
    CircleColor* CreateCircleColor(Coords& center_, int radius_, string color_)
    {
        return new CircleColor(center_, radius_, color_);
    }
};
/*Сделать два Строителя сцены – одни для реального
построения тестовой сцены из нескольких объектов, другой
для расчета занимаемой ими памяти.*/
class Builder
{
public:
    virtual void Crean() = 0;
    virtual void PlacePoint(Coords& coords_) = 0;
    virtual void PlaceLine(Coords& begin, Coords& end) = 0;
    virtual void PlaceCircle(Coords& center, int radius) = 0;
};

class SceneBuilder : public Builder
{
private:
    vector<GraphObject*> scene;
public:
    void Crean() {scene.clear();}
    void PlacePoint(Coords& coords_)
    {
        Point* p = new Point(coords_);
        scene.push_back(p);
    }
    void PlaceLine(Coords& begin, Coords& end)
    {
        Line* l = new Line(begin, end);
        scene.push_back(l);
    }
    void PlaceCircle(Coords& center, int radius)
    {
        Circle* c = new Circle(center, radius);
        scene.push_back(c);
    }

    vector<GraphObject*> Rendering() {return scene;}
};

class MemoryBuilder : public Builder
{
private:
    int size;
public:
    void Crean() {size = 0;}
    void PlacePoint(Coords& coords_){size += sizeof(Point);}
    void PlaceLine(Coords& begin, Coords& end){size += sizeof(Line);}
    void PlaceCircle(Coords& center, int radius){size += sizeof(Circle);}
    int Total() {return size;}
};

class Director
{
private:
    Builder* builder;
public:
    Director(Builder* b) : builder(b) {}
    void Make(int count, Coords& begin, Coords& end, int radius)
    {
        builder->Crean();
        for(int i = 0; i < count; i++)
        {
            builder->PlacePoint(begin);
            builder->PlaceLine(begin, end);
            builder->PlaceCircle(begin, radius);
        }
    }

};
/****************************************/
int main()
{
    Coords coords11 = {.x = 1, .y = 1};
    Coords coords22 = {.x = 2, .y = 2};

    Point* pointDonor = new Point(coords11);
    Point* pointClone = pointDonor->Clone();

    cout << pointDonor->ToString();
    cout << pointClone->ToString();

    Line* lineDonor = new Line(coords11, coords22);
    Line* lineClone = lineDonor->Clone();

    cout << lineDonor->ToString();
    cout << lineClone->ToString();

    Circle* circleDonor = new Circle(coords11, 1);
    Circle* circleClone = circleDonor->Clone();

    cout << circleDonor->ToString();
    cout << circleClone->ToString();
    cout << "/**************************************/" << endl;
    /**************************************/
    vector<GraphObject*> graphObject;
    graphObject.push_back(pointClone);
    graphObject.push_back(lineClone);
    graphObject.push_back(circleClone);

    vector<GraphObject*> graphObjectRev;
    graphObjectRev.push_back(circleClone);
    graphObjectRev.push_back(lineClone);
    graphObjectRev.push_back(pointClone);

    Singleton1* singleton1 = Singleton1::GetInstance(graphObject);
    cout << singleton1 << endl;
    Singleton1* singleton1Clone = Singleton1::GetInstance(graphObjectRev);
    cout << singleton1Clone << endl;

    singleton1Clone->SetData(graphObject);
    vector<GraphObject*> graphObjectTemp = singleton1Clone->GetData();
    for(uint i = 0; i < graphObjectTemp.size(); i++)
        cout << graphObjectTemp.at(i)->ToString();
    cout << singleton1Clone << endl;
    cout << "/**************************************/" << endl;
    /**************************************/
    FactoryPoint* factoryPoint = new FactoryPoint();
    GraphObject* goPoint = factoryPoint->CreateObject(coords11);

    FactoryLine* factoryLine = new FactoryLine();
    GraphObject* goLine = factoryLine->CreateObject(coords11);

    FactoryCircle* factoryCircle = new FactoryCircle();
    GraphObject* goCircle = factoryCircle->CreateObject(coords11);

    for(GraphObject* go : graphObjectArr)
        cout << go->ToString();
    cout << "/**************************************/" << endl;
    /**************************************/
    AbstractFactory* abstractFactoryGrey = new AbstractFactoryGrey();
    Point* point = abstractFactoryGrey->CreatePoint(coords11);
    cout << point->ToString();

    Line* line = abstractFactoryGrey->CreateLine(coords11, coords22);
    cout << line->ToString();

    Circle* circle = abstractFactoryGrey->CreateCircle(coords11, 10);
    cout << circle->ToString();

    AbstractFactory* abstractFactoryColor = new AbstractFactoryColor();
    PointColor* pointColor = abstractFactoryColor->CreatePointColor(coords11, "RED");
    cout << pointColor->ToString();

    LineColor* lineColor = abstractFactoryColor->CreateLineColor(coords11, coords22, "BLUE");
    cout << lineColor->ToString();

    CircleColor* circleColor = abstractFactoryColor->CreateCircleColor(coords11, 11, "GREEN");
    cout << circleColor->ToString();
    cout << "/**************************************/" << endl;
    /*****************************/
    SceneBuilder* sceneBuilder = new SceneBuilder();
    MemoryBuilder* memoryBuilder = new MemoryBuilder();

    Director* sceneDirector = new Director(sceneBuilder);
    Director* memoryDirector = new Director(memoryBuilder);

    int count = 10;
    sceneDirector->Make(count, coords11, coords22, 1);
    memoryDirector->Make(count, coords11, coords22, 1);

    vector<GraphObject*> sceneResult = sceneBuilder->Rendering();
    int sizeResult = memoryBuilder->Total();

    for(GraphObject* go : sceneResult)
        cout << go->ToString();

    cout << "sizeResult = " << sizeResult << endl;

    cout << "Hello World!" << endl;
    return 0;
}
