#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/extension/io/png_dynamic_io.hpp>

using namespace boost::gil;

#define GRID_W 100
#define GRID_H 100
#define PARTICLES_NUM 2000

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
	
	void swirl(float xx, float yy, float direction){
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				float x = (float(i) - float(GRID_H) / 2.0) / float(w);
				float y = (float(j) - float(GRID_W) / 2.0) / float(h);

				float dfac = distance(Vec2(x,y), Vec2(xx,yy));
				dfac = pow(1 - dfac, 2.0);
				
				x -= xx;
				y -= yy;
				
				cells[i][j].u.x += -y * direction * dfac;
				cells[i][j].u.y += x * direction * dfac;
			}
		}
	}
	
	void init(){
		swirl(0, 0.2, 0.8);
		swirl(0, -0.2, -0.8);

		for(int i = 0; i < PARTICLES_NUM; i++){
			particles[i].randomize(w, h);
		}
	}
	
	inline void iterate(){
		for(int i = 1; i < w - 1; i++){
			for(int j = 1; j < h - 1; j++){
				computenu(i,j);
			}
		}
		for(int i = 1; i < w - 1; i++){
			for(int j = 1; j < h - 1; j++){
				computennu(i,j);
			}
		}

		float border_damp = 0.9;
		
		// Copy border conditions to border cells
		for(int i = 0; i < w; i++){
			cells[i][0].nu = cells[i][1].nu * border_damp;
			cells[i][w-1].nu = cells[i][w-2].nu * border_damp;
			cells[i][0].nnu = cells[i][1].nnu * border_damp;
			cells[i][w-1].nnu = cells[i][w-2].nnu * border_damp;
		}

		// Copy border conditions to border cells
		for(int j = 0; j < h; j++){
			cells[0][j].nu = cells[1][j].nu * border_damp;
			cells[h-1][j].nu = cells[h-2][j].nu * border_damp;
			cells[0][j].nnu = cells[1][j].nnu * border_damp;
			cells[h-1][j].nnu = cells[h-2][j].nnu * border_damp;
		}
		
		for(int i = 1; i < w - 1; i++){
			for(int j = 1; j < h - 1; j++){
				computefluid(i,j);
			}
		}
	}
	
	/**
	   Find nabla(u)
	 */
	inline void computenu(int i, int j){
		cell * cur = &cells[i][j];
		cell * top = top_cell(i,j);
		cell * left = left_cell(i,j);
		cell * right = right_cell(i,j);
		cell * bottom = bottom_cell(i,j);
		
		// Find nabla(u)
		float dx = (right->u - left->u).x;
		float dy = (top->u - bottom->u).y;
		cur->nu.x = dx;
		cur->nu.y = dy;
		
		if(dx != 0 || dy != 0){
			//std::cout << top->u.y << " " << bottom->u.y << std::endl;
			//std::cout << dx * 100000 << " " << dy * 100000 << std::endl;
		}
	}
	
	/**
	   Find nabla(nabla(u))
	 */
	inline void computennu(int i, int j){
		cell * cur = &cells[i][j];
		cell * top = top_cell(i,j);
		cell * left = left_cell(i,j);
		cell * right = right_cell(i,j);
		cell * bottom = bottom_cell(i,j);
		
		float dx = (right->nu - left->nu).x;
		float dy = (top->nu - bottom->nu).y;
		cur->nnu.x = dx;
		cur->nnu.y = dy;
	}
	
	inline void computefluid(int i, int j){
		cell * cur = &cells[i][j];
		cell * top = top_cell(i,j);
		cell * left = left_cell(i,j);
		cell * right = right_cell(i,j);
		cell * bottom = bottom_cell(i,j);
		
		float v = 0.4;
		
		Vec2 du = v * cur->nnu - cur->u * cur->nu;
		du *= 0.002;
		
		cur->u += du;
	}
	
	inline int pacman_clamp(int number, int max){
		int ret = number;
		
		if(ret < 0){
			ret += max;
		} else if (ret >= max) {
			ret -= max;
		}
		
		ret = ret % max;
		
		return ret;
	}

	float pacman_clamp_float(float num, float max){
		float ret = num;
		
		while(ret < 0 || ret > max){
			if(ret < 0){
				ret += max;
			} else if (ret >= max) {
				ret -= max;
			}
		}
		
		return ret;
	}
	
	inline void computeParticles(){
		for(int i = 0; i < PARTICLES_NUM; i++){
			particles[i].x = pacman_clamp_float(particles[i].x, w);
			particles[i].y = pacman_clamp_float(particles[i].y, h);

			int posi = particles[i].x;
			int posj = particles[i].y;
			
			particles[i].x += cells[posi][posj].u.x;
			particles[i].y += cells[posi][posj].u.y;
		}
	}
	
	inline cell * top_cell(int i, int j){
		i--;
		return &cells[i][j];
	}

	inline cell * bottom_cell(int i, int j){
		i++;
		return &cells[i][j];
	}

	inline cell * right_cell(int i, int j){
		j++;
		return &cells[i][j];
	}

	inline cell * left_cell(int i, int j){
		j--;
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
	
	int frames = 2000;
	int subframes = 50;
	
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

		int percent = i/float(frames) * 100;
		
		std::cout << "done: " << i << "/" << frames << " ("<< percent << "%)\r";
		std::cout.flush();
		grid.save_image(filename);
	}
	
	return 0;
}
