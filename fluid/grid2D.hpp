
class grid2D{
public:
	int w = GRID_W;
	int h = GRID_H;
	cell cells[GRID_W][GRID_H];

	void iterate(){
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				
			}
		}
	}

	void save_image(std::string filename){
		rgb8_image_t img(w, h);
		rgb8_pixel_t red(255, 0, 0);
		
		fill_pixels(view(img), red);
		
		rgb8_image_t::view_t v = view(img);

		for(int i = 5; i < w; i++){
			for(int j = 1; j < h; j++){
				cell * cell = &cells[i][j];
				vec2 * cu = &cell->u;
				
				v(i,j) = rgb8_pixel_t(cu->x, cu->y, 0);
			}
		}

		png_write_view(filename, const_view(img));
	}
};
