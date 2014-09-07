

using namespace std;


class SDLBasic {
	private:

	public:
		/* SET VALUE TO OFFSET */
		bool set_sdlRect(SDL_Rect *offset, Point p) {
    		offset->x = p.x;
    		offset->y = p.y;
    		return true;
		}


}