class GridSaver{
public:
	void save_image(
		cell cells[GRID_W][GRID_H],
		Vec2 particles[PARTICLES_NUM],
		std::string filename) {
		int w = GRID_W;
		int h = GRID_H;
		
		rgb8_image_t img(w, h);
		
		rgb8_image_t::view_t v = view(img);
		
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				//cell * cell = &cells[i][j];
				//Vec2 * cu = &cell->u;
				
				//v(i,j) = rgb8_pixel_t(cu->x * 255 + 128, cu->y * 255 + 128, 0);
				v(i,j) = rgb8_pixel_t(0, 0, 0);
			}
		}

		for(int i = 0; i < PARTICLES_NUM; i++){
			int posi = particles[i].x;
			int posj = particles[i].y;
			
			if(posi < 0 || posi > w || posj < 0 || posj > h){
				continue;
			}
			
			v(posi, posj) = rgb8_pixel_t(255, 255, 255);
		}
		
		png_write_view(filename, const_view(img));
	}
};
