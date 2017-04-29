
class Vec2{
public:
	float x = 0;
	float y = 0;

	Vec2(){
		x = 0;
		y = 0;
	}
	
	Vec2(int _x, int _y){
		x = float(_x);
		y = float(_y);
	}
	
	Vec2(float _x, float _y){
		x = _x;
		y = _y;
	}

	void randomize(float max_x, float max_y){
		x = rand()/float(RAND_MAX) * max_x;
		y = rand()/float(RAND_MAX) * max_y;
	}

	Vec2 operator*(float rhs){
		Vec2 ret;
		ret.x = x * rhs;
		ret.y = y * rhs;
		return ret;
	}
	
	Vec2 operator+(Vec2 rhs){
		Vec2 ret = *this;
		ret.x = ret.x + rhs.x;
		ret.y = ret.y + rhs.y;
		return ret;
	}

	Vec2 operator*(Vec2 rhs){
		Vec2 ret = *this;
		ret.x = ret.x * rhs.x;
		ret.y = ret.y * rhs.y;
		return ret;
	}
	
	Vec2 operator-(Vec2 rhs){
		Vec2 ret = *this;

		ret.x = ret.x - rhs.x;
		ret.y = ret.y - rhs.y;
		return ret;
	}
	
	void operator*=(float rhs){
		x *= rhs;
		y *= rhs;
	}

	void operator+=(Vec2 rhs){
		x += rhs.x;
		y += rhs.y;
	}

	void operator*=(Vec2 rhs){
		x *= rhs.x;
		y *= rhs.y;
	}

	void print(){
		std::cout << "x: " << x << " ";
		std::cout << "y: " << y;
		std::cout << std::endl;
	}

	void operator=(Vec2 rhs){
		x = rhs.x;
		y = rhs.y;
	}
	
};

Vec2 operator*(float lhs, Vec2 & rhs){
	Vec2 ret;
	ret.x = lhs * rhs.x;
	ret.y = lhs * rhs.y;
	return ret;
}

void Vec2_test_suite(){
	Vec2 my_vec;
	my_vec.x = 2;
	my_vec.y = 5;

	Vec2 my_vec2;
	my_vec2.x = 7;
	my_vec2.y = 4;

	
	my_vec += my_vec2 + my_vec;
	my_vec = my_vec - Vec2(1,1);

	assert(my_vec.x == 10);
	assert(my_vec.y == 13);

	my_vec = Vec2(1,2) * Vec2(3,4);
	assert(my_vec.x = 3);
	assert(my_vec.y = 8);

	my_vec = Vec2(2,3);
	my_vec *= Vec2(7,5);
	assert(my_vec.x = 14);
	assert(my_vec.y = 15);

	my_vec = Vec2(2,4) - Vec2(1,2);

	assert(my_vec.x = 1);	
	assert(my_vec.y = 2);
}
