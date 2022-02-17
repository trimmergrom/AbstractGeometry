#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include<math.h>
#include <Windows.h>

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		/*console_red = 0x0C,
		console_green = 0x0A,
		console_blue = 0x09,
		console_yellow = 0x0E,*/
		console_red = 0xCC,
		console_green = 0xAA,
		console_blue = 0x99,
		console_yellow = 0xEE,
		console_default = 0x07,
	};

	class Shape
	{
	protected:
		Color color_pen;
		Color color_brush;
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;

	public:
		Color get_color_pen()const
		{
			return color_pen;
		}
		Color get_color_brush()const
		{
			return color_brush;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 1200)start_x = 1200;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 800)start_y = 800;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 25)line_width = 25;
			this->line_width = line_width;
		}

		Shape(unsigned int start_x, unsigned int start_y, unsigned int line_width,
			Color color_pen, Color color_brush)		
			:color_pen(color_pen), color_brush(color_brush)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		void info()const
		{
			std::cout << "Area of shape: " << get_area() << std::endl;
			std::cout << "Perimeter of shape: " << get_perimeter() << std::endl;
			draw();
		}
	};
	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 0)side = abs(side);
			this->side = side;
		}
		Square(double side, unsigned int start_x, unsigned int start_y,
			unsigned int line_width, Color color_pen)
			:Shape(start_x, start_y, line_width, color_pen, color_brush)
		{
			set_side(side);
		}
		~Square() {}
		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			/*char str[10]{};
			char command[20] = "color ";
			system(strcat(command, _itoa(get_color(), str, 10)));*/
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, get_color_pen());
			for (int i = 0; i < side; i++)
			{
				std::cout << "\t";
				for (int i = 0; i < side; i++)
				{
					std::cout << "* ";
				}
				std::cout << std::endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Side of square: " << side << std::endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_lehgth()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 10;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 10;
			this->length = length;
		}
		Rectangle(double width, double length, unsigned int start_x, unsigned int start_y,
			unsigned int line_width, Color color_pen, Color color_brush)
			:Shape(start_x, start_y, line_width, color_pen, color_brush)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return(width + length) * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			//HWND hwnd = GetDesktopWindow();
			//HWND hwnd = FindWindow(NULL, L"Calculator");
			//HWND hwnd = FindWindow(NULL, L"Inherintace - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			/*HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));*/
			HPEN hPen = CreatePen(PS_SOLID, line_width, color_pen);
			HBRUSH hBrush = CreateSolidBrush(color_brush);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + (int)width, start_y + (int)length);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			std::cout << "\n" << typeid(*this).name() << std::endl;
			std::cout << "Width of rectangle: " << width << std::endl;
			std::cout << "Length of rectangle: " << length << std::endl;
			Shape::info();
		}
	};

class Circle :public Shape
{
	double radius;
public:
	double get_radius()const
	{
		return this->radius;
	}
	void set_radius(double radius)
	{
		if (radius < 0 || radius >= 500)this->radius = 500;
		this->radius = radius;
	}
	double get_diameter()const
	{
		return radius * 2;
	}

	Circle(double radius, unsigned int start_x, unsigned int start_y, unsigned int line_width,
		Color color_pen, Color color_brush)
		:Shape(start_x, start_y, line_width, color_pen, color_brush)
	{
		set_radius(radius);
	}
	~Circle(){}
	double get_area()const
	{
		return M_PI * pow(radius, 2);
	}
	double get_perimeter()const
	{
		return 2 * M_PI * radius;
	}
	void draw()const
	{
		HWND hwnd = GetConsoleWindow();		
		HDC hdc = GetDC(hwnd);		
		HPEN hPen = CreatePen(PS_SOLID, line_width, color_pen);
		HBRUSH hBrush = CreateSolidBrush(color_brush);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);
	}
	void info()const
	{
		std::cout << "\n" << typeid(*this).name() << std::endl;
		std::cout << "Radius of circle: " << get_radius() << std::endl;
		std::cout << "Diameter of circle: " << get_diameter() << std::endl;
		Shape::info();
	}
};
class Polygons :public Shape
{
public:
	Polygons(unsigned int start_x, unsigned int start_y, unsigned int line_width,
		Color color_pen, Color color_brush)
		:Shape(start_x, start_y, line_width, color_pen, color_brush) {};
	~Polygons() {};
	virtual double get_higth()const = 0;
};
class EquilateralTriangle :public Polygons
{
	double side;
public:
	EquilateralTriangle(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width,
		Color color_pen, Color color_brush)
		:Polygons(start_x, start_y, line_width, color_pen, color_brush)
	{
		set_side(side);
	}
	~EquilateralTriangle(){}


	void set_side(double side)
	{
		if (side < 20)side = 20;
		if (side > 500)side = 500;
		this->side = side;
	}
	double get_side()const
	{
		return side;
	}
	double get_higth()const
	{
		return side * cos(30 * M_PI / 180);
	}
	double get_area()const
	{
		return get_higth() * side / 4;
	}
	double get_perimeter()const
	{
		return side * 3;
	}
	void draw()const
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		HPEN hPen = CreatePen(PS_SOLID, line_width, color_pen);
		HBRUSH hBrush = CreateSolidBrush(color_brush);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT points[] =
		{
			{start_x, start_y + side},
			{start_x + side, start_y + side},
			{start_x + side / 2, start_y + side - get_higth()}
		};
		::Polygon(hdc, points, sizeof(points)/sizeof(POINT));

		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);
	}
	void info()const
	{
		std::cout << "\n" << typeid(*this).name() << std::endl;
		std::cout << "Length of side: " << get_side() << std::endl;
		std::cout << "Higth:\t" << get_higth() << std::endl;
		Shape::info();
	}
};
class IsoscalesTriangle :public Polygons
{
	double base;
	double base_angle;
public:
	IsoscalesTriangle(double base, double base_angle, unsigned int start_x, unsigned int start_y,
		unsigned int line_width, Color color_pen, Color color_brush)
		:Polygons(start_x, start_y, line_width, color_pen, color_brush)
	{
		set_base(base);
		set_base_angle(base_angle);
	}
	~IsoscalesTriangle(){}

	void set_base(double base)
	{
		if (base < 20)base = 20;
		if (base > 200)base = 200;
		this->base = base;
	}
	void set_base_angle(double base_angle)
	{
		/*if (base_angle < 10)base_angle = 10;
		if (base_angle > 89)base_angle = 89;*/
		this->base_angle = base_angle;
	}
	double get_side()const
	{
		return get_higth() * sin(base_angle * M_PI / 180) * 2 + base;
	}
	double get_base()const
	{
		return base;
	}
	double get_base_angle()const
	{
		return base_angle;
	}
	double get_higth()const
	{
		return base / 2 * tan(base_angle * M_PI / 180);
	}
	double get_area()const
	{
		return base / 2 * get_higth();
	}
	double get_perimeter()const
	{
		return get_side() * 2 + base;
	}
	void draw()const
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		HPEN hPen = CreatePen(PS_SOLID, line_width, color_pen);
		HBRUSH hBrush = CreateSolidBrush(color_brush);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT points[] =
		{
			{start_x, start_y + get_side()},
			{start_x + base, start_y + get_side()},
			{start_x + base / 2, start_y + get_side() - get_higth()}
		};
		::Polygon(hdc, points, sizeof(points) / sizeof(POINT));

		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);
	}
	void info()const
	{
		std::cout << "\n" << typeid(*this).name() << std::endl;
		std::cout << "Base of triangle: " << get_base() << std::endl;
		std::cout << "Side of triangle: " << get_side() << std::endl;
		std::cout << "Base_angle of triangle: " << base_angle << std::endl;
		std::cout << "Higth of triangle: " << get_higth() << std::endl;
		Shape::info();
	}
};

class Parallelogram:public Polygons
{
	double side_a;
	double side_b;
	double base_angle;
public:
	void set_side_a(double side_a)
	{
		if (side_a < 0)side_a = abs(side_a);
		if (side_a > 500)side_a = 500;
		this->side_a = side_a;
	}
	void set_side_b(double side_b)
	{
		if (side_b < 0)side_b = abs(side_b);
		if (side_b > 500)side_b = 500;
		this->side_b = side_b;
	}
	void set_base_angle(double base_angle)
	{
		//if (alfa > 90)alfa = 90;
		this->base_angle = base_angle;
	}
	Parallelogram(double side_a, double side_b, double base_angle, unsigned int start_x,
		unsigned int start_y, unsigned int line_width, Color color_pen, Color color_brush)
		:Polygons(start_x, start_y, line_width, color_pen, color_brush)
	{
		set_side_a(side_a);
		set_side_b(side_b);
		set_base_angle(base_angle);
	}
	~Parallelogram(){}

	double get_side_a()const
	{
		return side_a;
	}
	double get_side_b()const
	{
		return side_b;
	}
	double get_alfa()const
	{
		return base_angle;
	}
	double get_area()const
	{
		return side_a*side_b * sin(base_angle * M_PI / 180);
	}
	double get_perimeter()const
	{
		return (side_a + side_b) * 2;
	}
	double get_higth()const
	{
		return side_b * sin(base_angle * M_PI / 180);
	}
	double get_delta()const
	{
		return side_b * cos(base_angle * M_PI / 180);
	}
	void draw()const
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		HPEN hPen = CreatePen(PS_SOLID, line_width, color_pen);
		HBRUSH hBrush = CreateSolidBrush(color_brush);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT points[] =
		{
			{start_x, start_y + side_b},
			{start_x + side_a, start_y + side_b},
			{start_x + side_a + get_delta(), start_y + side_b - get_higth()},
			{start_x + get_delta(), start_y + side_b - get_higth()}
		};
		::Polygon(hdc, points, sizeof(points) / sizeof(POINT));

		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);
	}void info()const
	{
		std::cout << "\n" << typeid(*this).name() << std::endl;
		std::cout << "Side_A of prallelogram: " << side_a << std::endl;
		std::cout << "Side_B of prallelogram: " << side_b << std::endl;
		std::cout << "Base_angle of prallelogram: " << base_angle << std::endl;
		std::cout << "Higth of prallelogram: " << get_higth() << std::endl;
		Shape::info();
	}
};
class Trapezoid :public Polygons
{
	double base;
	double higth;
	double base_angle;
public:
	void set_base(double base)
	{
		this->base = base;
	}
	void set_higth(double higth)
	{
		this->higth = higth;
	}
	void set_base_angle(double base_angle)
	{
		this->base_angle = base_angle;
	}
	Trapezoid(double base, double higth, double base_angle, unsigned int start_x,
		unsigned int start_y, unsigned int line_width, Color color_pen, Color color_brush)
		:Polygons(start_x, start_y, line_width, color_pen, color_brush)
	{
		set_base(base);
		set_higth(higth);
		set_base_angle(base_angle);
	}
	~Trapezoid(){}
	double get_higth()const
	{
		return higth;
	}
	double get_side()const
	{
		return higth / sin(base_angle * M_PI / 180);
	}
	double get_delta()const
	{
		return get_side() * cos(base_angle * M_PI / 180);
	}
	double get_top()const
	{
		return base - 2 * get_delta();
	}
	double get_area()const
	{
		return pow(get_top(), 2) + get_delta() * higth;
	}
	double get_perimeter()const
	{
		return base + get_top() + 2 * get_side();
	}
	void draw()const
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		HPEN hPen = CreatePen(PS_SOLID, line_width, color_pen);
		HBRUSH hBrush = CreateSolidBrush(color_brush);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		POINT points[] =
		{
			{start_x, start_y + get_side()},
			{start_x + base, start_y + get_side()},
			{start_x + base - get_delta(), start_y + get_side() - higth},
			{start_x + base - get_delta() - get_top(), start_y + get_side() - higth}
		};
		::Polygon(hdc, points, sizeof(points) / sizeof(POINT));

		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);
	}
	void info()const
	{
		std::cout << "\n" << typeid(*this).name() << std::endl;
		std::cout << "Base of trapezoid: " << base << std::endl;
		std::cout << "Higth of trapezoid: " << higth << std::endl;
		std::cout << "Base_angle of trapezoid: " << base_angle << std::endl;
		std::cout << "Side of trapezoid: " << get_side() << std::endl;
		std::cout << "Top of trapezoid: " << get_top() << std::endl;
		std::cout << "Area of trapezoid: " << get_area() << std::endl;
		std::cout << "Perimeter of trapezoid: " << get_perimeter() << std::endl;
		Shape::info();
	}	
};
}

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD console_rect{ 120, 32 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &console_rect);

	Geometry::Square square(5, 150, 100, 3,  Geometry::Color::console_red);
	square.info();
	Geometry::Rectangle rect(150, 100, 400, 150, 3, Geometry::Color::yellow, Geometry::Color::blue);
	rect.info();
	Geometry::Circle circle(100, 650, 200, 3, Geometry::Color::blue, Geometry::Color::green);
	circle.info();
	Geometry::EquilateralTriangle eqt(150, 1200, 500, 5, Geometry::Color::red, Geometry::Color::green);
	eqt.info();
	Geometry::IsoscalesTriangle isct (150, 70, 950, 10, 5, Geometry::Color::blue, Geometry::Color::red);
	isct.info();
	Geometry::Parallelogram prlgm(130, 130, 110, 450, 500, 5, Geometry::Color::yellow, Geometry::Color::red);
	prlgm.info();
	Geometry::Trapezoid trpzd(150, 60, 60, 700, 600, 3, Geometry::Color::blue, Geometry::Color::yellow);
	trpzd.info();
}
