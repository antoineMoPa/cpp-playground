#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/extension/io/png_dynamic_io.hpp>

using namespace boost::gil;

#define GRID_W 400
#define GRID_H 400
#define PARTICLES_NUM 1000

#include <iostream>
#include <iomanip>

#include "Vec2.hpp"

class cell{
public:
	Vec2 u;			// u (field)
	Vec2 nu;		// nabla of u
	Vec2 nnu;		// nabla of nabla of u
};

#include "GridSaver.hpp"

class Grid2D{
public:
	int w = GRID_W;
	int h = GRID_H;
	cell cells[GRID_W][GRID_H];

	Vec2 particles[PARTICLES_NUM];
	
	void init(){
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				float x = (float(i) - float(GRID_H) / 2.0) / float(w);
				float y = (float(j) - float(GRID_W) / 2.0) / float(h);
				
				cells[i][j].u.x = -y;
				cells[i][j].u.y = x;

				if(y < 0.1 && y > -0.1){
					cells[i][j].u.x += 0.1;
				}
			}
		}

		for(int i = 0; i < PARTICLES_NUM; i++){
			particles[i].randomize(w, h);
		}
	}
	
	void iterate(){
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				computenu(i,j);
			}
		}
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				computennu(i,j);
			}
		}
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				computefluid(i,j);
			}
		}
	}

	/**
	   Find nabla(u)
	 */
	void computenu(int i, int j){
		cell * cur = &cells[i][j];
		cell * top = top_cell(i,j);
		cell * left = left_cell(i,j);
		cell * right = right_cell(i,j);
		cell * bottom = bottom_cell(i,j);
		
		// Find nabla(u)
		float dx = -(right->u.x - left->u.x);
		float dy = top->u.y - bottom->u.y;
		cur->nu.x = dx;
		cur->nu.y = dy;
		
		//std::cout << top->u.y << " " << bottom->u.y << std::endl;
		//std::cout << dx * 100000 << " " << dy * 100000 << std::endl;
	}
	
	/**
	   Find nabla(nabla(u))
	 */
	void computennu(int i, int j){
		cell * cur = &cells[i][j];
		cell * top = top_cell(i,j);
		cell * left = left_cell(i,j);
		cell * right = right_cell(i,j);
		cell * bottom = bottom_cell(i,j);
		
		float dx = -(right->nu.x - left->nu.x);
		float dy = top->nu.y - bottom->nu.y;
		cur->nnu.x = dx;
		cur->nnu.y = dy;
	}
	
	void computefluid(int i, int j){
		cell * cur = &cells[i][j];
		cell * top = top_cell(i,j);
		cell * left = left_cell(i,j);
		cell * right = right_cell(i,j);
		cell * bottom = bottom_cell(i,j);
		
		float v = 10.0;
		
		Vec2 du = v * cur->nnu - cur->u * cur->nu;
        du *= 0.002;
		
		cur->u += du;
	}

	void computeParticles(){
		for(int i = 0; i < PARTICLES_NUM; i++){
			int posi = particles[i].x;
			int posj = particles[i].y;
			
			if(posi < 0 || posi > w || posj < 0 || posj > h){
				particles[i].randomize(w, h);
				posi = particles[i].x;
				posj = particles[i].y;
			}
			
			particles[i].x += cells[posi][posj].u.x;
			particles[i].y += cells[posi][posj].u.y;
		}
	}

	int pacman_clamp(int number, int max){
		int ret = number;
		
		if(ret < 0){
			ret += max;
		} else if (ret > max){
			ret -= max;
		}
		
		ret = ret % max;
		
		return ret;
	}
	
	cell * top_cell(int i, int j){
		j--;
		j = pacman_clamp(j, h);
		return &cells[i][j];
	}

	cell * bottom_cell(int i, int j){
		j++;
		j = pacman_clamp(j, h);
		return &cells[i][j];
	}

	cell * right_cell(int i, int j){
		i++;
		i = pacman_clamp(i,w);
		return &cells[i][j];
	}

	cell * left_cell(int i, int j){
		i--;
		i = pacman_clamp(i,w);
		return &cells[i][j];
	}
	
	void save_image(std::string filename){
		GridSaver gs;
		gs.save_image(cells, particles, filename);
	}
};

int main(int argc, char ** argv){
	Grid2D grid;

	Vec2_test_suite();
	
	int frames = 100;
	int subframes = 20;
	
	grid.init();

	std::cout << "---------------------------------------\n";
	
	for(int i = 0; i < frames; i++){
		for(int j = 0; j < subframes; j++){
			grid.iterate();
		}

		grid.computeParticles();
		
		std::ostringstream stringStream;
		stringStream << std::setfill('0') << std::setw(5) << i << ".png";
		std::string filename = stringStream.str();
		
		std::cout << "done: " << i << "/" << frames << '\r';
		std::cout.flush();
		grid.save_image(filename);
	}
	
	return 0;
}
